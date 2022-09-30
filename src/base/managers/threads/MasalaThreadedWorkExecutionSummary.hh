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
class MasalaThreadedWorkExecutionSummary : public base::MasalaObject {

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
	/// @param[in] nthreads_actual The number of threads that were
	/// actually used for carrying out the work.
	/// @param[in] execution_time The time, in microseconds, that
	/// execution took.
	MasalaThreadedWorkExecutionSummary(
		MasalaThreadedWorkStatus const status,
		base::Size const nthreads_actual,
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

	/// @brief Allow the MasalaThreadPool to record which threads have been assigned to this
	/// job.  We will store:
	/// - Indices of the threads, based on the thread pool's numbering.
	/// - Indices of the threads, based on internal numbering.  (For instance, if we got threads
	/// 0, 5, 6, and 7, internally we would refer to these as threads 0, 1, 2, and 3).
	/// @note It is assumed that the thread which calls this function is the parent thread that
	/// has been assigned to the job.
	void set_assigned_child_threads( std::vector< thread_pool::MasalaThreadSP > const & threads );

	/// @brief Given the index of a thread manager thread, get the index in the set of threads
	/// assigned to this task.
	/// @details For instance, if thread manager threads 0, 5, 6, and 7 are assigned to this task,
	/// their indices in the set assigned are 0, 1, 2, and 3, respectively.  If I give this function
	/// thread 6, it should return 2.
	base::Size get_thread_index_in_assigned_thread_set( base::Size const thread_manager_thread_id ) const;

	/// @brief Get the status of the work.
	inline MasalaThreadedWorkStatus work_status() const { return work_status_; }

	/// @brief Get the number of threads that were actually used for the work (which can
	/// be less than the number requested).
	inline base::Size nthreads_actual() const { return nthreads_actual_; }

	/// @brief Get the wall-time, in microseconds that the work took.
	inline base::Real execution_time_microseconds() const { return execution_time_microseconds_; }

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief The status of the work.
	MasalaThreadedWorkStatus work_status_ = MasalaThreadedWorkStatus::WORK_IN_PROGRESS;

	/// @brief The wall-time, in microseconds that the work took.
	base::Real execution_time_microseconds_ = 0.0;

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA that are set by the set_assigned_child_threads function:
////////////////////////////////////////////////////////////////////////////////

	/// @brief The number of threads that were actually used for the work (which can
	/// be less than the number requested).
	base::Size nthreads_actual_ = 0;

	/// @brief The indices of the child threads assigned.
	std::vector< base::Size > assigned_child_thread_indices_;

	/// @brief The index of the parent (calling) thread assigned.  This is 0 if it's
	/// the global master thread for the process, or higher if it's a thread pool thread.
	base::Size parent_thread_index_ = 0;

}; // class MasalaThreadedWorkExecutionSummary

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadedWorkExecutionSummary_hh