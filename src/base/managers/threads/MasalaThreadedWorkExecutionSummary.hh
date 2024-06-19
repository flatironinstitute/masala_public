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

/// @file src/base/managers/threads/MasalaThreadedWorkExecutionSummary.hh
/// @brief A class that will store a summary of what work was done in threads,
/// how long it took, and how many threads were actually assigned to the work.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadedWorkExecutionSummary_hh
#define Masala_src_base_managers_threads_MasalaThreadedWorkExecutionSummary_hh

// Forward declarations:
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/threads/thread_pool/MasalaThread.fwd.hh>
#include <base/types.hh>

// STL headers:
#include <vector>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief An enum for the exit status following a threaded work request.
enum class MasalaThreadedWorkStatus {
	INVALID_STATUS = 0, // Keep first
	WORK_IN_PROGRESS,
	NO_WORK_DONE,
	WORK_THREW_EXCEPTION,
	WORK_SUCCESSFUL, // Keep second-to-last
	NUM_STATUS_TYPES = WORK_SUCCESSFUL // Keep last
}; // enum class MasalaThreadedWorkStatus

/// @brief A class that will store a summary of what work was done in threads,
/// how long it took, and how many threads were actually assigned to the work.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadedWorkExecutionSummary : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Constructor that initializes nthreads_actual_ and
	/// execution_time_microseconds_ to zero.  These must be set later.
	/// @details Initializes status to WORK_IN_PROGRESS.  The idea is that
	/// this will be updated when execution finishes.
	MasalaThreadedWorkExecutionSummary() = default;

	/// @brief Options constructor.
	/// @param[in] status The status for the work done.
	/// @param[in] nthreads_requested The number of threads that were
	/// requested.
	/// @param[in] nthreads_actual The number of threads that were
	/// actually used for carrying out the work.
	/// @param[in] njobs The number of jobs carried out.
 	/// @param[in] execution_time The time, in microseconds, that
	/// execution took.
	MasalaThreadedWorkExecutionSummary(
		MasalaThreadedWorkStatus const status,
		base::Size const nthreads_requested,
		base::Size const nthreads_actual,
		base::Size const njobs,
		base::Real const execution_time_microseconds
	);

	/// @brief Copy constructor.
	MasalaThreadedWorkExecutionSummary( MasalaThreadedWorkExecutionSummary const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaThreadedWorkExecutionSummary() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadedWorkExecutionSummary".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads".
	std::string class_namespace() const override;

	/// @brief Indicate that all threads were requested.  (Sets ntherads_requested_ to 0.)
	void set_all_threads_requested();

	/// @brief Set the number of threads requested.
	void set_nthreads_requested( base::Size const nthreads_requested );

	/// @brief Set the number of jobs.
	void set_njobs( base::Size const njobs );

	/// @brief Allow the MasalaThreadPool to record which threads have been assigned to this
	/// job.  We will store:
	/// - Indices of the threads, based on the thread pool's numbering.
	/// - Indices of the threads, based on internal numbering.  (For instance, if we got threads
	/// 0, 5, 6, and 7, internally we would refer to these as threads 0, 1, 2, and 3).
	/// @note It is assumed that the thread which calls this function is the parent thread that
	/// has been assigned to the job.  It is set as thread zero, and the rest of the threads are
	/// given positive internal indices.
	void
	set_assigned_threads(
		masala::base::Size const current_thread,
		std::vector< thread_pool::MasalaThreadSP > const & other_threads
	);

	/// @brief Given the index of a thread manager thread, get the index in the set of threads
	/// assigned to this task.
	/// @details For instance, if thread manager threads 0, 5, 6, and 7 are assigned to this task,
	/// their indices in the set assigned are 0, 1, 2, and 3, respectively.  If I give this function
	/// thread 6, it should return 2.
	base::Size get_thread_index_in_assigned_thread_set( base::Size const thread_manager_thread_id ) const;

	/// @brief Given a thread index in the assigned thread set, get the thread index used by the
	/// thread manager.
	/// @details For instance, if thread manager threads 0, 5, 6, and 7 are assigned to this task,
	/// their indices in the set assigned are 0, 1, 2, and 3, respectively.  If I give this function
	/// thread 2, it should return 6.
	base::Size get_thread_manager_thread_index( base::Size const index_in_assigned_thread_set ) const;

	/// @brief Get the status of the work.
	inline MasalaThreadedWorkStatus work_status() const { return work_status_; }

	/// @brief Were all threads requested?
	inline bool all_threads_requested() const { return all_threads_requested_; }

	/// @brief Get the number of threads that were requested.
	/// @details Will be zero if all threads were requested.
	inline base::Size nthreads_requested() const { return nthreads_requested_; }

	/// @brief Get the number of threads that were actually used for the work (which can
	/// be less than the number requested).
	inline base::Size nthreads_actual() const { return nthreads_actual_; }

	/// @brief Get the number of jobs that were carried out.
	inline base::Size njobs() const { return njobs_; }

	/// @brief Set the execution time in microseconds.
	void set_execution_time_microseconds( base::Real const execution_time_microseconds );

	/// @brief Get the wall-time, in microseconds, that the work took.
	inline
	base::Real
	execution_time_microseconds() const {
		return execution_time_microseconds_;
	}

	/// @brief Set the execution time in microseconds of an assigned thread.
	/// @param[in] thread_index_in_assigned_set The index of the thread for which we're setting
	/// execution time in the set of threads assigned to this block of work.
	/// @param[in] execution_time_microseconds The execution time, in microseconds, for the work
	/// done in this thread.  Adds to current value
	void
	increment_execution_time_microseconds_individual_thread(
		base::Size const thread_index_in_assigned_set,
		base::Real const execution_time_microseconds
	);

	/// @brief Get the time, in microseconds, that each assigned thread spent on the work.
	/// @details The vector is indexed by thread index.  Use get_thread_manager_thread_index()
	/// to convert indices in the assigned thread set into global indices.
	/// @note This is the time that each thread was actually doing work, omitting any time spent
	/// looking for work to do.
	inline
	std::vector< base::Real > const &
	execution_time_microseconds_individual_threads() const {
		return execution_time_microseconds_individual_threads_;
	}

	/// @brief Inicate that an exception was thrown during execution of the work.
	/// @param err The exception that was thrown.  Copied and stored.
	void set_work_exception( std::exception const & err );

	/// @brief Retrieve the exception thrown during the work.
    /// @returns A const shared pointer to the error, or nullptr if no error.
	/// @note You can try casting this to a MasalaException to see if there's an error message.
	MASALA_SHARED_POINTER< std::exception const > get_work_exception() const;

	/// @brief Indicate that the work was done successfully.
	void set_work_successful();

	/// @brief Write a summary of the work done to the tracer.
	void write_summary_to_tracer() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief The status of the work.
	MasalaThreadedWorkStatus work_status_ = MasalaThreadedWorkStatus::WORK_IN_PROGRESS;

	/// @brief The wall-time, in microseconds that the work took.
	base::Real execution_time_microseconds_ = 0.0;

	/// @brief The total time spent on the task by each assigned thread, in microseconds.
	std::vector< base::Real > execution_time_microseconds_individual_threads_;

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA that are set by the set_assigned_child_threads function:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Were all threads requested?
	bool all_threads_requested_ = false;

	/// @brief The number of threads that were requested.
	base::Size nthreads_requested_ = 0;

	/// @brief The number of threads that were actually used for the work (which can
	/// be less than the number requested).
	base::Size nthreads_actual_ = 0;

	/// @brief The number of jobs that were carried out.
	base::Size njobs_ = 0;

	/// @brief The indices of the threads assigned.  The parent thread is the 0th entry.
	std::vector< base::Size > assigned_thread_indices_;

	/// @brief A possible error returned by a thread.  Null if no error.
	MASALA_SHARED_POINTER< std::exception const > err_ptr_ = nullptr;

}; // class MasalaThreadedWorkExecutionSummary

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadedWorkExecutionSummary_hh