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

/// @file src/base/managers/threads/thread_pool/MasalaThread.cc
/// @brief A container for a threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/threads/thread_pool/MasalaThread.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace threads {
namespace thread_pool {

////////////////////////////////////////////////////////////////////////////////
// MasalaThreadCreationKey PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThreadCreationKey".
std::string
MasalaThreadCreationKey::class_name() const {
    return "MasalaThreadCreationKey";
}

/// @brief Returns "masala::base::managers::threads::thread_pool".
std::string
MasalaThreadCreationKey::class_namespace() const {
    return "masala::base::managers::threads::thread_pool";
}

////////////////////////////////////////////////////////////////////////////////
// MasalaThread CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Keyed constructor.
/// @details The MasalaThreadCreationKey class has a private constructor,
/// and has the MasalaThreadPool as its only friend.  This ensures that only
/// the thread pool can launch threads.
MasalaThread::MasalaThread(
    base::Size const thread_index,
    MasalaThreadCreationKey const & 
) :
    base::MasalaObject(),
    thread_index_(thread_index)
{}

////////////////////////////////////////////////////////////////////////////////
// MasalaThread PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThread".
std::string
MasalaThread::class_name() const {
    return "MasalaThread";
} // MasalaThread::class_name()

/// @brief Returns "masala::base::managers::threads::thread_pool".
std::string
MasalaThread::class_namespace() const {
    return "masala::base::managers::threads::thread_pool";
} // MasalaThread::class_namespace()

/// @brief Get the index of this thread.
base::Size
MasalaThread::thread_index() const {
    return thread_index_;
} // MasalaThread::thread_index()

/// @brief Access the mutex for this thread.
std::mutex &
MasalaThread::thread_mutex() const {
    return thread_mutex_;
} // MasalaThread::thread_mutex()

/// @brief Set whether this thread is forced to idle.
/// @note Be sure to lock the thread mutex before calling this function!
void
MasalaThread::set_forced_idle(
    bool const setting
) {
    forced_idle_ = setting;
    if( setting == false ) {
        cv_for_wakeup_.notify_one();
    }
} // MasalaThread::set_forced_idle()

/// @brief Set the function that this thread will execute.
/// @details Must be in the forced idle state to set this.
/// @note Be sure to lock the thread mutex before calling this function!
void
MasalaThread::set_function(
    std::function< void() > const & function,
    std::mutex & job_completion_mutex,
    std::condition_variable & job_completion_cond_var,
    base::Size & num_jobs_completed
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( forced_idle_, "set_function", "Program error: must be in the forced-idle state to set the thread function." );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( function_ == nullptr, "set_function", "Program error: expected function_ to be nullptr." );
    function_ = &function;
    job_completion_mutex_ = &job_completion_mutex;
    job_completion_cond_var_ = &job_completion_cond_var;
    num_jobs_completed_ = &num_jobs_completed;
} // MasalaThread::set_function()

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
