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

/// @file src/base/managers/threads/thread_pool/MasalaThread.cc
/// @brief A container for a threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/threads/thread_pool/MasalaThread.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

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
    thread_index_(thread_index),
    forced_idle_(false),
    forced_termination_(false)
{
    contained_thread_ = std::thread( &MasalaThread::wrapper_function_executed_in_thread, this ); //Launch a thread.
    system_thread_id_ = contained_thread_.get_id();
    base::managers::tracer::MasalaTracerManager::get_instance()->register_thread_id( system_thread_id_, thread_index );
}

/// @brief Destructor.
/// @details Calls terminate_thread().
MasalaThread::~MasalaThread() {
    terminate_thread();
}

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

/// @brief Get the thread ID used by the system for the contained thread.
std::thread::id
MasalaThread::system_thread_id() const {
    return system_thread_id_;
} // MasalaThread::system_thread_id()

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
    forced_idle_.store( setting );
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
    std::condition_variable & job_completion_cond_var,
    std::atomic_ulong & num_jobs_completed,
    std::mutex & job_completion_mutex
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( forced_idle_.load(), "set_function", "Program error: must be in the forced-idle state to set the thread function." );
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( function_ == nullptr, "set_function", "Program error: expected function_ to be nullptr." );
    function_ = &function;
    job_completion_cond_var_ = &job_completion_cond_var;
    num_jobs_completed_ = &num_jobs_completed;
    job_completion_mutex_ = &job_completion_mutex;
} // MasalaThread::set_function()

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

/// @brief The function that the thread actually executes, which wraps
/// whatever function is passed in.
void
MasalaThread::wrapper_function_executed_in_thread() {
    std::unique_lock< std::mutex > unique_lock( thread_mutex_ ); //Locked
    write_to_tracer( "Launching thread " + std::to_string(thread_index_) + "." );
    //base::managers::random::RandomNumberManager::get_instance()->initialize_thread( thread_index_ );

    do {
        if( !(
                forced_termination_ ||
                (!(forced_idle_.load()) && function_ != nullptr)
            )
        ) {
            cv_for_wakeup_.wait( unique_lock, [this]{ return( forced_termination_ || (!(forced_idle_.load()) && function_ != nullptr ) ); } );
        } // Wait for either the terminations signal, or for the function to be non-null (and the state to be non-idle).  When this is the case, the mutex will be locked.

        if( forced_termination_.load() ) {
            // We are spinning down.
            break;
        }

        if( !(forced_idle_.load()) && function_ != nullptr ) {
            unique_lock.unlock();
            // We have work to do!
            (*function_)(); // Do the work.

            unique_lock.lock();
            DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
                job_completion_mutex_ != nullptr && job_completion_cond_var_ != nullptr && num_jobs_completed_ != nullptr,
                "wrapper_function_executed_in_thread", "Program error: one or more control variable pointers were null."
            );

            std::condition_variable * temp_cond_variable_ptr = job_completion_cond_var_;

            {
                std::unique_lock< std::mutex > unique_lock2( *job_completion_mutex_);
                ++(*num_jobs_completed_);
                function_ = nullptr;
                job_completion_cond_var_ = nullptr;
                num_jobs_completed_ = nullptr;
            } // Scope for lock guard 2.
            unique_lock.unlock();
            temp_cond_variable_ptr->notify_one(); // Signal that this thread is now free.
            unique_lock.lock();
        }
    } while(true); //Loop until we break.

    write_to_tracer( "Terminating thread " + std::to_string( thread_index_ ) + "." );

} // MasalaThread::wrapper_function_executed_in_thread()

/// @brief Spins down the std::thread object contained (i.e. prevents it from
/// accepting new work).
/// @details Should only be called by this object's destructor.
void
MasalaThread::terminate_thread() {
    CHECK_OR_THROW_FOR_CLASS( forced_idle_, "terminate_thread", "Program error: expected thread to be in the forced idle state!" );
    forced_termination_.store(true);
    cv_for_wakeup_.notify_one();
    contained_thread_.join();
    base::managers::tracer::MasalaTracerManager::get_instance()->unregister_thread_id( system_thread_id_ );
} // MasalaThread::terminate_thread()

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
