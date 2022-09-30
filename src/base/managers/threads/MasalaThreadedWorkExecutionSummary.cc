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

/// @file src/base/managers/threads/MasalaThreadedWorkExecutionSummary.cc
/// @brief A class that will store a summary of what work was done in threads,
/// how long it took, and how many threads were actually assigned to the work.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/threads/thread_pool/MasalaThread.hh>
#include <base/managers/threads/MasalaThreadManager.hh>

// STL headers
#include <algorithm>
#include <string>
#include <thread>

namespace masala {
namespace base {
namespace managers {
namespace threads {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor.
/// @param[in] status The status for the work done.
/// @param[in] nthreads_actual The number of threads that were
/// actually used for carrying out the work.
/// @param[in] execution_time The time, in microseconds, that
/// execution took.
MasalaThreadedWorkExecutionSummary::MasalaThreadedWorkExecutionSummary(
    MasalaThreadedWorkStatus const status,
    base::Size const nthreads_actual,
    base::Real const execution_time_microseconds
) :
    base::MasalaObject(),
    work_status_(status),
    execution_time_microseconds_(execution_time_microseconds),
    nthreads_actual_(nthreads_actual)
{}


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThreadedWorkExecutionSummary".
std::string
MasalaThreadedWorkExecutionSummary::class_name() const {
    return "MasalaThreadedWorkExecutionSummary";
} // MasalaThreadedWorkExecutionSummary::class_name()

/// @brief Returns "masala::base::managers::threads".
std::string
MasalaThreadedWorkExecutionSummary::class_namespace() const {
    return "masala::base::managers::threads";
} // MasalaThreadedWorkExecutionSummary::class_namespace()

/// @brief Allow the MasalaThreadPool to record which threads have been assigned to this
/// job.  We will store:
/// - Indices of the threads, based on the thread pool's numbering.
/// - Indices of the threads, based on internal numbering.  (For instance, if we got threads
/// 0, 5, 6, and 7, internally we would refer to these as threads 0, 1, 2, and 3).
void
MasalaThreadedWorkExecutionSummary::set_assigned_child_threads(
    std::vector< thread_pool::MasalaThreadSP > const & threads
) {
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_assigned_child_threads", "Cannot alter work status after work has completed." );
    nthreads_actual_ = threads.size() + 1; // The parent thread is also an assigned thread.
    assigned_child_thread_indices_.resize( threads.size() );
    for( base::Size i(1), imax(threads.size()); i<=imax; ++i ) {
        assigned_child_thread_indices_[i] = threads[i]->thread_index();
    }
    parent_thread_index_ = MasalaThreadManager::get_instance()->get_thread_manager_thread_id_from_system_thread_id( std::this_thread::get_id() );
} // MasalaThreadedWorkExecutionSummary::set_assigned_child_threads()

/// @brief Given the index of a thread manager thread, get the index in the set of threads
/// assigned to this task.
/// @details For instance, if thread manager threads 0, 5, 6, and 7 are assigned to this task,
/// their indices in the set assigned are 0, 1, 2, and 3, respectively.  If I give this function
/// thread 6, it should return 2.
base::Size
MasalaThreadedWorkExecutionSummary::get_thread_index_in_assigned_thread_set(
    base::Size const thread_manager_thread_id
) const {
    std::vector< base::Size >::const_iterator const it(
        std::find(
            assigned_child_thread_indices_.begin(),
            assigned_child_thread_indices_.end(),
            thread_manager_thread_id
        )
    );
    CHECK_OR_THROW_FOR_CLASS(
        it != assigned_child_thread_indices_.end(),
        "get_thread_index_in_assigned_thread_set",
        "Thread index " + std::to_string( thread_manager_thread_id ) + " is not "
        "among the threads assigned to this task!"
    );
    return (*it);
} //MasalaThreadedWorkExecutionSummary::get_thread_index_in_assigned_thread_set()

/// @brief Inicate that an exception was thrown during execution of the work.
/// @param err The exception that was thrown.  Copied and stored.
void
MasalaThreadedWorkExecutionSummary::set_work_exception(
    std::exception const & err
) {
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_work_exception", "Cannot alter work status after work has completed." );
    work_status_ = MasalaThreadedWorkStatus::WORK_THREW_EXCEPTION;
    err_ptr_ = std::make_shared< std::exception const >( err );
} // MasalaThreadedWorkExecutionSummary::set_work_exception()

/// @brief Retrieve the exception thrown during the work.
/// @returns A const shared pointer to the error, or nullptr if no error.
/// @note You can try casting this to a MasalaException to see if there's an error message.
std::shared_ptr< std::exception const >
MasalaThreadedWorkExecutionSummary::get_work_exception() const {
    return err_ptr_;
} // MasalaThreadedWorkExecutionSummary::get_work_exception()

/// @brief Indicate that the work was done successfully.
void
MasalaThreadedWorkExecutionSummary::set_work_successful() {
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_work_successful", "Cannot alter work status after work has completed." );
    work_status_ = MasalaThreadedWorkStatus::WORK_SUCCESSFUL;
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
