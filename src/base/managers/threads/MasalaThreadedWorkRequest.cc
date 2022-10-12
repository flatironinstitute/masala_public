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

/// @file src/base/managers/threads/MasalaThreadedWorkRequest.cc
/// @brief A class that stores a vector of work to do in threads plus configuration
/// options describing how the work is to be done.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/threads/MasalaThreadedWorkRequest.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace threads {

////////////////////////////////////////////////////////////////////////////////
// STRUCT MasalaThreadedJob:
////////////////////////////////////////////////////////////////////////////////

/// @brief Initialization constructor.
MasalaThreadedJob::MasalaThreadedJob(
    std::function< void() > const & work_fxn_in_
) :
    work_function_( work_fxn_in_ ),
    job_was_completed_(false)
{}

/// @brief Copy constructor.
/// @details Must be explicitly defined due to mutex.
MasalaThreadedJob::MasalaThreadedJob(
    MasalaThreadedJob const & src
) {
    (*this) = src;
}

/// @brief Assignment operator.
/// @details Must be explicitly defined due to mutex.
MasalaThreadedJob &
MasalaThreadedJob::operator=(
    MasalaThreadedJob const & src
) {
    std::lock_guard< std::mutex >( src.job_mutex_ );
    work_function_ = src.work_function_;
    job_was_completed_.store( src.job_was_completed_.load() );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

/// @brief Constructor specifying number of threads to request.
/// @details A value of 0 means request all.
MasalaThreadedWorkRequest::MasalaThreadedWorkRequest(
    base::Size const threads_to_request
) :
    base::MasalaObject()
{
    set_n_threads_to_request( threads_to_request );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThreadedWorkRequest".
std::string
MasalaThreadedWorkRequest::class_name() const {
    return "MasalaThreadedWorkRequest";
}

/// @brief Returns "masala::base::managers::threads".
std::string
MasalaThreadedWorkRequest::class_namespace() const {
    return "masala::base::managers::threads";
}

/// @brief Is the vector of work to do empty?
/// @returns True if there's no work in the work vector, false otherwise.
bool
MasalaThreadedWorkRequest::empty() const {
    return work_vector_.empty();
}

/// @brief Get the number of entries in the work vector.
base::Size
MasalaThreadedWorkRequest::work_vector_size() const {
    return work_vector_.size();
}

/// @brief Are we requesting all threads?
bool
MasalaThreadedWorkRequest::all_threads_requested() const {
    return request_mode_ == MasalaThreadedWorkRequestMode::REQUEST_ALL_THREADS;
}

/// @brief How many threads have been requested?
/// @details Throws unless mode is REQUEST_SPECIFIED_NUMBER_OF_THREADS.
base::Size
MasalaThreadedWorkRequest::n_threads_requested() const {
    CHECK_OR_THROW_FOR_CLASS(
        request_mode_ == MasalaThreadedWorkRequestMode::REQUEST_SPECIFIED_NUMBER_OF_THREADS,
        "n_threads_requested",
        "The request mode is not set to REQUEST_SPECIFIED_NUMBER_OF_THREADS, yet the number "
        "of threads was requested!"
    );
    return n_threads_requested_;
}

/// @brief Set the number of threads to request.
/// @details A value of 0 means request all available.
void
MasalaThreadedWorkRequest::set_n_threads_to_request(
    base::Size const threads_to_request
) {
    if( threads_to_request == 0 ) {
        request_mode_ = MasalaThreadedWorkRequestMode::REQUEST_ALL_THREADS;
        n_threads_requested_ = 0;
    } else {
        request_mode_ = MasalaThreadedWorkRequestMode::REQUEST_SPECIFIED_NUMBER_OF_THREADS;
        n_threads_requested_ = threads_to_request;
    }
}

/// @brief Set the number of threads to request to ALL.
void
MasalaThreadedWorkRequest::set_request_all_threads() {
    request_mode_ = MasalaThreadedWorkRequestMode::REQUEST_ALL_THREADS;
    n_threads_requested_ = 0;
}

/// @brief Ensure that the work vector is large enough for at least N jobs.
void
MasalaThreadedWorkRequest::reserve(
    base::Size const jobs_to_reserve
) {
    work_vector_.reserve(jobs_to_reserve);
}

/// @brief Add a job to the list of jobs to do.
/// @details Inputs is a function bundled with its arguments.  Must be threadsafe.
void
MasalaThreadedWorkRequest::add_job(
    std::function< void() > const & function_in
) {
    work_vector_.push_back( MasalaThreadedJob( function_in ) );
}

/// @brief Has a particular job completed?
/// @details Does not lock the job mutex for the check.
bool
MasalaThreadedWorkRequest::job_is_complete(
    base::Size const job_index
) const {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        job_index < work_vector_.size(), "job_is_complete",
        "The requested job index (" + std::to_string(job_index) + ") is not within the "
        "work vector (size " + std::to_string( work_vector_.size() ) + ")."
    );

    return work_vector_[job_index].job_was_completed_.load(); //Atomic operation.
}

/// @brief Indicate that a particular job is complete.
/// @details Does not lock the job mutex when modifying
/// the atomic_bool.  The proper workflow is to check the
/// atomic bool, obtain a mutex lock (by calling job_mutex),
/// check again, mark the job complete, release the mutex
/// lock, and then run the job.
void
MasalaThreadedWorkRequest::mark_job_complete(
    base::Size const job_index
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        job_index < work_vector_.size(), "mark_job_complete",
        "The requested job index (" + std::to_string(job_index) + ") is not within the "
        "work vector (size " + std::to_string( work_vector_.size() ) + ")."
    );

    work_vector_[job_index].job_was_completed_.store(true); //Atomic operation.
}

/// @brief Access the mutex for a particular job.
/// @details Used for obtaining a mutex lock.  Note that the mutex is
/// intended for checking and flipping the status of the job completion
/// atomic_bool, not for locking the job while work is being done.
/// @note The mutex access is nonconst, despite this being a const function.
/// The mutex is mutable to allow a lock to be obtained.
std::mutex &
MasalaThreadedWorkRequest::job_mutex(
    base::Size const job_index
) const {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        job_index < work_vector_.size(), "job_mutex",
        "The requested job index (" + std::to_string(job_index) + ") is not within the "
        "work vector (size " + std::to_string( work_vector_.size() ) + ")."
    );
    return work_vector_[job_index].job_mutex_;
}

/// @brief Execute the Nth work function.
void
MasalaThreadedWorkRequest::run_job(
    base::Size const job_index
) const {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        job_index < work_vector_.size(), "run_job",
        "The requested job index (" + std::to_string(job_index) + ") is not within the "
        "work vector (size " + std::to_string( work_vector_.size() ) + ")."
    );
    work_vector_[job_index].work_function_();
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
