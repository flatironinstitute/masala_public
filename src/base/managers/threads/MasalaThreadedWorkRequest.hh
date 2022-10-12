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

/// @file src/base/managers/threads/MasalaThreadedWorkRequest.hh
/// @brief A class that stores a vector of work to do in threads plus configuration
/// options describing how the work is to be done.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadedWorkRequest_hh
#define Masala_src_base_managers_threads_MasalaThreadedWorkRequest_hh

// Forward declarations:
#include <base/managers/threads/MasalaThreadedWorkRequest.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/types.hh>

// STL headers
#include <functional>
#include <vector>
#include <atomic>
#include <mutex>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief An enum specifying how we'll request threads.
enum class MasalaThreadedWorkRequestMode {
	INVALID_REQUEST_MODE = 0, // Keep first
	REQUEST_ALL_THREADS,
	REQUEST_SPECIFIED_NUMBER_OF_THREADS, // Keep second-to-last
	NUM_REQUEST_MODES = REQUEST_SPECIFIED_NUMBER_OF_THREADS // Keep last
}; // enum class MasalaThreadedWorkRequestMode

/// @brief A struct for a job to be done as part of a vector of work.
/// @details Contains a function to execute, an atomic_bool indicating whether
/// the job has been done, and a mutex used for locking the atomic_bool.
struct MasalaThreadedJob {

public:

	/// @brief Default constructor, deleted.
	MasalaThreadedJob() = delete;

	/// @brief Initialization constructor.
	MasalaThreadedJob( std::function< void() > const & work_fxn_in_ );

	/// @brief Copy constructor.
	/// @details Must be explicitly defined due to mutex.
	MasalaThreadedJob( MasalaThreadedJob const & );

	/// @brief Assignment operator.
	/// @details Must be explicitly defined due to mutex.
	MasalaThreadedJob & operator=( MasalaThreadedJob const & );

public:

	/// @brief The function to do in threads.
	std::function< void() > work_function_;

	/// @brief An atomic bool indicating whether the work has been done.
	std::atomic_bool job_was_completed_;

	/// @brief A mutex for locking the atomic bool.
	mutable std::mutex job_mutex_;

}; // struct MasalaThreadedJob

/// @brief A class that stores a vector of work to do in threads plus configuration
/// options describing how the work is to be done.
class MasalaThreadedWorkRequest : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaThreadedWorkRequest() = default;

	/// @brief Constructor specifying number of threads to request.
	/// @details A value of 0 means request all.
	MasalaThreadedWorkRequest( base::Size const threads_to_request );

	/// @brief Copy constructor.
	MasalaThreadedWorkRequest( MasalaThreadedWorkRequest const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaThreadedWorkRequest() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadedWorkRequest".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads".
	std::string class_namespace() const override;

	/// @brief Is the vector of work to do empty?
	/// @returns True if there's no work in the work vector, false otherwise.
	bool empty() const;

	/// @brief Get the number of entries in the work vector.
	base::Size work_vector_size() const;

	/// @brief Are we requesting all threads?
	bool all_threads_requested() const;

	/// @brief How many threads have been requested?
	/// @details Throws unless mode is REQUEST_SPECIFIED_NUMBER_OF_THREADS.
	base::Size n_threads_requested() const;

	/// @brief Set the number of threads to request.
	/// @details A value of 0 means request all available.
	void set_n_threads_to_request( base::Size const threads_to_request );

	/// @brief Set the number of threads to request to ALL.
	void set_request_all_threads();

	/// @brief Ensure that the work vector is large enough for at least N jobs.
	void reserve( base::Size const jobs_to_reserve );

	/// @brief Add a job to the list of jobs to do.
	/// @details Inputs is a function bundled with its arguments.  Must be threadsafe.
	void add_job( std::function< void() > const & function_in );

	/// @brief Has a particular job completed?
    /// @details Does not lock the job mutex for the check.
    bool
    job_is_complete(
        base::Size const job_index
    ) const;

	/// @brief Indicate that a particular job is complete.
	/// @details Does not lock the job mutex when modifying
	/// the atomic_bool.  The proper workflow is to check the
	/// atomic bool, obtain a mutex lock (by calling job_mutex),
	/// check again, mark the job complete, release the mutex
	/// lock, and then run the job.
	void
	mark_job_complete(
		base::Size const job_index
	);

	/// @brief Access the mutex for a particular job.
	/// @details Used for obtaining a mutex lock.  Note that the mutex is
	/// intended for checking and flipping the status of the job completion
	/// atomic_bool, not for locking the job while work is being done.
	/// @note The mutex access is nonconst, despite this being a const function.
	/// The mutex is mutable to allow a lock to be obtained.
	std::mutex & job_mutex( base::Size const job_index ) const;

	/// @brief Execute the Nth work function.
	void run_job( base::Size const job_index ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief The vector of work to do in threads.
	/// @details This work might be done in any order.
	std::vector< MasalaThreadedJob > work_vector_;

	/// @brief The mode for requesting threads.
	MasalaThreadedWorkRequestMode request_mode_ = MasalaThreadedWorkRequestMode::REQUEST_ALL_THREADS;

	/// @brief The number of threads requested.
	base::Size n_threads_requested_ = 0;

}; // class MasalaThreadedWorkRequest

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadedWorkRequest_hh