/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
#include <sstream>
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
/// @param[in] nthreads_requested The number of threads that were
/// requested.
/// @param[in] nthreads_actual The number of threads that were
/// actually used for carrying out the work.
/// @param[in] njobs The number of jobs carried out.
/// @param[in] execution_time The time, in microseconds, that
/// execution took.
MasalaThreadedWorkExecutionSummary::MasalaThreadedWorkExecutionSummary(
    MasalaThreadedWorkStatus const status,
    base::Size const nthreads_requested,
    base::Size const nthreads_actual,
    base::Size const njobs,
    base::Real const execution_time_microseconds
) :
    base::MasalaObject(),
    work_status_(status),
    execution_time_microseconds_(execution_time_microseconds),
    nthreads_requested_(nthreads_requested),
    nthreads_actual_(nthreads_actual),
    njobs_(njobs)
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

/// @brief Set the number of threads requested.
void
MasalaThreadedWorkExecutionSummary::set_nthreads_requested(
    base::Size const nthreads_requested
) {
    nthreads_requested_ = nthreads_requested;
}

/// @brief Set the number of jobs.
void
MasalaThreadedWorkExecutionSummary::set_njobs(
    base::Size const njobs
) {
    njobs_ = njobs;
}

/// @brief Allow the MasalaThreadPool to record which threads have been assigned to this
/// job.  We will store:
/// - Indices of the threads, based on the thread pool's numbering.
/// - Indices of the threads, based on internal numbering.  (For instance, if we got threads
/// 0, 5, 6, and 7, internally we would refer to these as threads 0, 1, 2, and 3).
/// @note It is assumed that the thread which calls this function is the parent thread that
/// has been assigned to the job.  It is set as thread zero, and the rest of the threads are
/// given positive internal indices.
void
MasalaThreadedWorkExecutionSummary::set_assigned_threads(
    std::vector< thread_pool::MasalaThreadSP > const & threads
) {
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_assigned_threads", "Cannot alter work status after work has completed." );
    nthreads_actual_ = threads.size() + 1; // The parent thread is also an assigned thread.
    assigned_thread_indices_.resize( threads.size() + 1 );
    execution_time_microseconds_individual_threads_.clear();
    execution_time_microseconds_individual_threads_.resize( threads.size() + 1, 0.0 ); //Initialize times to zero.
    assigned_thread_indices_[0] = MasalaThreadManager::get_instance()->get_thread_manager_thread_id_from_system_thread_id( std::this_thread::get_id() );
    for( base::Size i(0), imax(threads.size()); i<imax; ++i ) {
        assigned_thread_indices_[i+1] = threads[i]->thread_index();
    }
} // MasalaThreadedWorkExecutionSummary::set_assigned_threads()

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
            assigned_thread_indices_.begin(),
            assigned_thread_indices_.end(),
            thread_manager_thread_id
        )
    );
    CHECK_OR_THROW_FOR_CLASS(
        it != assigned_thread_indices_.end(),
        "get_thread_index_in_assigned_thread_set",
        "Thread index " + std::to_string( thread_manager_thread_id ) + " is not "
        "among the threads assigned to this task!"
    );
    return static_cast< base::Size >( it - assigned_thread_indices_.begin() );
} //MasalaThreadedWorkExecutionSummary::get_thread_index_in_assigned_thread_set()

/// @brief Given a thread index in the assigned thread set, get the thread index used by the
/// thread manager.
/// @details For instance, if thread manager threads 0, 5, 6, and 7 are assigned to this task,
/// their indices in the set assigned are 0, 1, 2, and 3, respectively.  If I give this function
/// thread 2, it should return 6.
base::Size
MasalaThreadedWorkExecutionSummary::get_thread_manager_thread_index(
    base::Size const index_in_assigned_thread_set
) const {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        index_in_assigned_thread_set < assigned_thread_indices_.size(),
        "get_thread_manager_thread_index",
        "Thread " + std::to_string( index_in_assigned_thread_set ) + " in the assigned "
        "set was requested, but only " + std::to_string( assigned_thread_indices_.size() ) +
        " threads are in the assigned set."
    );
    return assigned_thread_indices_[index_in_assigned_thread_set];
}

/// @brief Set the execution time in microseconds.
void
MasalaThreadedWorkExecutionSummary::set_execution_time_microseconds(
    base::Real const execution_time_microseconds
) {
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_work_exception", "Cannot set execution time after work has completed." );
    CHECK_OR_THROW_FOR_CLASS( execution_time_microseconds_ >= 0.0, "set_execution_time_microseconds", "Cannot set a negative execution time." );
    execution_time_microseconds_ = execution_time_microseconds;
}

/// @brief Set the execution time in microseconds of an assigned thread.
/// @param[in] thread_index_in_assigned_set The index of the thread for which we're setting
/// execution time in the set of threads assigned to this block of work.
/// @param[in] execution_time_microseconds The execution time, in microseconds, for the work
/// done in this thread.  Adds to current value
void
MasalaThreadedWorkExecutionSummary::increment_execution_time_microseconds_individual_thread(
    base::Size const thread_index_in_assigned_set,
    base::Real const execution_time_microseconds
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( thread_index_in_assigned_set < assigned_thread_indices_.size(), "set_execution_time_microseconds_individual_thread", "Index " + std::to_string( thread_index_in_assigned_set ) + " is out of range: " + std::to_string( assigned_thread_indices_.size() ) + " threads are in the assigned set." );
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_execution_time_microseconds_individual_thread", "Cannot set execution times for individual threads after work has completed." );
    execution_time_microseconds_individual_threads_[thread_index_in_assigned_set] += execution_time_microseconds;
} // MasalaThreadedWorkExecutionSummary::set_execution_time_microseconds_individual_thread()


/// @brief Inicate that an exception was thrown during execution of the work.
/// @param err The exception that was thrown.  Copied and stored.
void
MasalaThreadedWorkExecutionSummary::set_work_exception(
    std::exception const & err
) {
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_work_exception", "Cannot alter work status after work has completed." );
    work_status_ = MasalaThreadedWorkStatus::WORK_THREW_EXCEPTION;
    err_ptr_ = masala::make_shared< std::exception const >( err );
} // MasalaThreadedWorkExecutionSummary::set_work_exception()

/// @brief Retrieve the exception thrown during the work.
/// @returns A const shared pointer to the error, or nullptr if no error.
/// @note You can try casting this to a MasalaException to see if there's an error message.
MASALA_SHARED_POINTER< std::exception const >
MasalaThreadedWorkExecutionSummary::get_work_exception() const {
    return err_ptr_;
} // MasalaThreadedWorkExecutionSummary::get_work_exception()

/// @brief Indicate that the work was done successfully.
void
MasalaThreadedWorkExecutionSummary::set_work_successful() {
    CHECK_OR_THROW_FOR_CLASS( work_status_ == MasalaThreadedWorkStatus::WORK_IN_PROGRESS, "set_work_successful", "Cannot alter work status after work has completed." );
    work_status_ = MasalaThreadedWorkStatus::WORK_SUCCESSFUL;
}

/// @brief Write a summary of the work done to the tracer.
void
MasalaThreadedWorkExecutionSummary::write_summary_to_tracer() const {
    std::ostringstream ss;

    ss << "Executed " << njobs_ << " in " << nthreads_actual_ << " threads (" << nthreads_requested_ << " were requested)." << std::endl;
    ss << "Total walltime:\t" << execution_time_microseconds_ << " microseconds." << std::endl;
    ss << "\tThreadID:\tTime(us):" << std::endl;
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        nthreads_actual_ == assigned_thread_indices_.size(), "write_summary_to_tracer", "Program error: "
        "mismatch between assigned thread count and length of thread index vector."
    );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        nthreads_actual_ == execution_time_microseconds_individual_threads_.size(), "write_summary_to_tracer", "Program error: "
        "mismatch between assigned thread count and length of thread execution time vector."
    );
    for( base::Size i(0); i<nthreads_actual_; ++i ) {
        ss << "\t" << assigned_thread_indices_[i] << "\t" << execution_time_microseconds_individual_threads_[i] << std::endl;
    }
    write_to_tracer( ss.str() );
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
