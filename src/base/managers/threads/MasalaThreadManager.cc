/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/base/managers/threads/MasalaThreadManager.cc
/// @brief A static singleton for managing a thread pool, and execution of code
/// in parallel threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/threads/MasalaThreadManager.hh>

// Base headers:
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.hh>
#include <base/managers/threads/MasalaThreadedWorkRequest.hh>
#include <base/managers/threads/thread_pool/MasalaThreadPool.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>
#include <cmath>
#include <sstream>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaThreadManagerHandle
MasalaThreadManager::get_instance() {
    static MasalaThreadManager config_manager;
    return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// MasalaThreadManagerAccessKey PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThreadManagerAccessKey".
std::string
MasalaThreadManagerAccessKey::class_name() const {
    return "MasalaThreadPoolCreationKey";
}

/// @brief Returns "masala::base::managers::threads".
std::string
MasalaThreadManagerAccessKey::class_namespace() const {
    return "masala::base::managers::threads";
}


////////////////////////////////////////////////////////////////////////////////
// MasalaThreadManager PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
/// @details Creates the thread pool object, but that does not launch threads until
/// work is first assigned to threads (lazy thread launching).
MasalaThreadManager::MasalaThreadManager() :
    base::MasalaObject(),
    thread_pool_(
        std::make_shared< base::managers::threads::thread_pool::MasalaThreadPool >(
            base::managers::threads::thread_pool::MasalaThreadPoolCreationKey()
        )
    ),
    master_thread_id_( std::this_thread::get_id() )
{}


////////////////////////////////////////////////////////////////////////////////
// MasalaThreadManager PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaThreadManager".
std::string
MasalaThreadManager::class_name() const {
    return "MasalaThreadManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::thread".
std::string
MasalaThreadManager::class_namespace() const {
    return "masala::base::managers::threads";
}

/// @brief Given the system ID of a thread, return the whether this thread is
/// known to the thread manager.
bool
MasalaThreadManager::has_system_thread_id(
    std::thread::id const system_thread_id
) const {
    std::lock_guard< std::mutex > lock( thread_manager_mutex_ );

    if( system_thread_id == master_thread_id_ ) {
        return true;
    }
    if( thread_pool_ != nullptr ) {
        return thread_pool_->has_system_thread_id( system_thread_id );
    }
    return false;
} // MasalaThreadManager::has_system_thread_id()

/// @brief Given the system ID of a thread, return the index of the thread as
/// known to the thread manager.
/// @details Throws if the thread is not known to or managed by the thread
/// manager.  Use has_system_thread_id() to check whether a system thread
/// is known to or managed by the thread manager.
base::Size
MasalaThreadManager::get_thread_manager_thread_id_from_system_thread_id(
    std::thread::id const system_thread_id
) const {
    std::lock_guard< std::mutex > lock( thread_manager_mutex_ );

    if( system_thread_id == master_thread_id_ ) {
        return 0;
    }
    if( thread_pool_ != nullptr ) {
        return thread_pool_->get_thread_manager_thread_id_from_system_thread_id( system_thread_id );
    }
    // If we reach here, the thread is unknown.
    std::ostringstream ss;
    ss << system_thread_id;
    MASALA_THROW(
        class_namespace_and_name(), "get_thread_manager_thread_id_from_system_thread_id",
        "The system thread with ID " + ss.str() + " is not known to the Masala thread manager."
    );
    return 0; //Keep older compilers happy.
} // MasalaThreadManager::get_thread_manager_thread_id_from_system_thread_id()

/// @brief Do a vector of work in threads, without a reservation.
/// @param[in] request An object describing the work to be done and the
/// number of requested threads in which to do it.
/// @returns A summary of what work was done, the number of threads
/// in which it was actually executed, and how long it took.
MasalaThreadedWorkExecutionSummary
MasalaThreadManager::do_work_in_threads(
    MasalaThreadedWorkRequest & request,
    bool const throw_on_error /*= true*/
) const {
    if( request.empty() ) {
        write_to_tracer( "The MasalaThreadManager received an empty work vector.  Returning without doing anything." );
        return MasalaThreadedWorkExecutionSummary( MasalaThreadedWorkStatus::NO_WORK_DONE, 0, 0.0 );
    }

    // The number of threads to actually request should be:
    // - all threads if all_threads_requested() == true.
    // - n_threads_requested() otherwise.
    // - no more than the number of tasks to do.
    base::Size const n_threads_to_actually_request(
        std::min(
            request.all_threads_requested() ?
            total_threads_ :
            request.n_threads_requested(),
            request.work_vector_size()
        )
    );

    // The summary of how the threaded work was actually executed.  During
    // execution, this stores information about how many threads have actually
    // been assigned and which threads they are.
    MasalaThreadedWorkExecutionSummary summary;

    // Prepare a parallel function for doing a vector of work:
    std::function< void() > const inner_fxn(
        std::bind(
            &MasalaThreadManager::threaded_execution_function,
            this,
            std::ref( request ),
            std::cref( summary )
        )
    );

    try {
        // Run the function in threads:
        execute_function_in_threads(
            inner_fxn,
            n_threads_to_actually_request,
            MasalaThreadManagerAccessKey(),
            summary
        );
    } catch( base::error::MasalaException const & err ) {
        summary.set_work_exception(err);
        if( throw_on_error ) {
            MASALA_THROW( class_namespace_and_name(), "do_work_in_threads", "Threaded work threw exception:\n" + err.message() );
        }
        return summary;
    } catch( std::exception const & err ) {
        summary.set_work_exception( err );
        if( throw_on_error ) {
            MASALA_THROW( class_namespace_and_name(), "do_work_in_threads", "Threaded work threw a non-Masala exception." );
        }
        return summary;
    }

    summary.set_work_successful();
    return summary;
} // MasalaThreadManager::do_work_in_threads()

/// @brief Given a function, run it in a given number of threads.
/// @note Calling this function requires a MasalaThreadManagerAccessKey.
/// This is an (empty) class with a private constructor, and the
/// MasalaThreadManager is its only friend.  This is a means by which
/// access to this advanced API is restricted to avoid unsafe thread
/// practices.  For most purposes, you want to create a MasalaThreadedWorkRequest
/// containing a vector of work to do, and pass it to the do_work_in_threads()
/// function.
void
MasalaThreadManager::execute_function_in_threads(
    std::function< void() > const & fxn,
    base::Size const threads_to_request,
    MasalaThreadManagerAccessKey const & access_key,
    MasalaThreadedWorkExecutionSummary & summary
) const {
    thread_pool_->launch_threads_if_needed( total_threads_ );
    thread_pool_->execute_function_in_threads( fxn, threads_to_request, summary );
} // MasalaThreadManager::execute_function_in_threads()

/// @brief Get the total number of threads that the thread pool is set
/// to run.  (May not have been launched yet.)
base::Size
MasalaThreadManager::total_threads() const {
    std::lock_guard< std::mutex > lock( thread_manager_mutex_ );
    return total_threads_;
}

////////////////////////////////////////////////////////////////////////////////
// MasalaThreadManager PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given a request containing a vector of work, this function
/// can be executed in parallel in order to actually do the work.
void
MasalaThreadManager::threaded_execution_function(
    MasalaThreadedWorkRequest & request,
    MasalaThreadedWorkExecutionSummary const & summary
) const {
    // The number of threads actually assigned:
    base::Size const nthreads_assigned( summary.nthreads_actual() );

    // The zero-based index of this thread in the set of threads assigned:
    base::Size const thisthread_index(
        summary.get_thread_index_in_assigned_thread_set(
            get_thread_manager_thread_id_from_system_thread_id(
                std::this_thread::get_id()
            )
        )
    );

    // The number of jobs in the work vector:
    base::Size const njobs( request.work_vector_size() );

    // Where do we finish looking for work to do?  (We will start one job past this, and wrap around):
    base::Size const lastjob( std::round( thisthread_index * static_cast< float >( njobs ) / static_cast< float >( nthreads_assigned ) ) );

    // What's the current job that we're considering?
    base::Size curjob(lastjob);

    do {
        ++curjob;
        if( curjob >= njobs ) {
            curjob = 0;
        }

        // First, check whether a job is complete without locking the mutex:
        if( request.job_is_complete( curjob ) ) {
            continue;
        }

        // Next, get a mutex lock, and check again.
        {
            std::lock_guard< std::mutex > lock( request.job_mutex( curjob ) );
            if( request.job_is_complete( curjob ) ) {
                continue;
            } else {
                request.mark_job_complete( curjob );
            }
        } // Scope for mutex lock.

        // If we reach here, we want to actually execute the current job:
        request.run_job( curjob );

    } while( curjob != lastjob );
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
