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

// STL headers:
#include <string>

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
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
/// @details Creates the thread pool object, but that does not launch threads until
/// work is first assigned to threads (lazy thread launching).
MasalaThreadManager::MasalaThreadManager() :
    base::MasalaObject(),
    thread_pool_( std::make_shared< base::managers::threads::thread_pool::MasalaThreadPool >() )
{}


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
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

/// @brief Do a vector of work in threads, without a reservation.
/// @param[in] request An object describing the work to be done and the
/// number of requested threads in which to do it.
/// @returns A summary of what work was done, the number of threads
/// in which it was actually executed, and how long it took.
MasalaThreadedWorkExecutionSummary
MasalaThreadManager::do_work_in_threads(
    MasalaThreadedWorkRequest const & request
) {
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
    TODO TODO TODO

    //return MasalaThreadedWorkExecutionSummary( MasalaThreadedWorkStatus::WORK_SUCCESSFUL, 0, 0.0 );
}

/// @brief Get the total number of threads that the thread pool is set
/// to run.  (May not have been launched yet.)
base::Size
MasalaThreadManager::total_threads() const {
    std::lock_guard< std::mutex > lock( thread_manager_mutex_ );
    return total_threads_;
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
