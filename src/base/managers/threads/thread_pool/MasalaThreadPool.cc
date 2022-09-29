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

/// @file src/base/managers/threads/thread_pool/MasalaThreadPool.cc
/// @brief A container for a set of threads.  Controls launching, destroying,
/// or renumbering threads in a threadsafe way.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/threads/thread_pool/MasalaThreadPool.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/threads/thread_pool/MasalaThread.hh>

// STL headers
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace threads {
namespace thread_pool {

////////////////////////////////////////////////////////////////////////////////
// MasalaThreadPoolCreationKey PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThreadPoolCreationKey".
std::string
MasalaThreadPoolCreationKey::class_name() const {
    return "MasalaThreadPoolCreationKey";
}

/// @brief Returns "masala::base::managers::threads::thread_pool".
std::string
MasalaThreadPoolCreationKey::class_namespace() const {
    return "masala::base::managers::threads::thread_pool";
}

////////////////////////////////////////////////////////////////////////////////
// MasalaThreadPool CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Keyed constructor.
/// @details The MasalaThreadPoolCreationKey class has a private constructor,
/// and has the MasalaThreadManager as its only friend.  This ensures that only
/// the thread manager can create thread pools (or can control what other classes
/// can create thread pools).
MasalaThreadPool::MasalaThreadPool(
    MasalaThreadPoolCreationKey const & 
) :
    base::MasalaObject()
{}

////////////////////////////////////////////////////////////////////////////////
// MasalaThreadPool PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThreadPool".
std::string
MasalaThreadPool::class_name() const {
    return "MasalaThreadPool";
}

/// @brief Returns "masala::base::managers::threads::thread_pool".
std::string
MasalaThreadPool::class_namespace() const {
    return "masala::base::managers::threads::thread_pool";
}

/// @brief Check whether threads need to be launched, and launch
/// them if necessary.
/// @details Obtains a lock of the thread pool mutex as needed.  If desired
/// thread count is greater than number launched, we launch more.  If it is
/// less than number launched, we annotate threads for pruning and prune them
/// when they become idle.
void
MasalaThreadPool::launch_threads_if_needed(
    base::Size const desired_thread_count
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( desired_thread_count > 0, "launch_threads_if_needed", "Desired thread count must be positive." );
    {
        std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
        switch( thread_pool_state_ ) {
            case MasalaThreadPoolState::THREADS_NOT_LAUNCHED :
            {
                DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( threads_.empty(), "launch_threads_if_needed", "Program error: threads have been launched, but thread pool status indicates that they have not." );
                launch_threads_mutexlocked( desired_thread_count );
                thread_pool_state_ = MasalaThreadPoolState::THREADS_READY;
            }
            case MasalaThreadPoolState::THREADS_READY :
            {
                if( desired_thread_count > num_active_threads_ ) {
                    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( num_inactive_threads_ == 0, "launch_threads_if_needed", "Program error: in mode THREADS_READY, yet inactive threads were found!" );
                    launch_threads_mutexlocked( desired_thread_count - num_active_threads_ );
                } else if( desired_thread_count < num_active_threads_ ) {
                    increment_inactive_threads_mutexlocked( num_active_threads_ - desired_thread_count ); // Alters num_active_threads_ and num_inactive_threads_.
                    thread_pool_state_ = MasalaThreadPoolState::SOME_THREADS_SPINNING_DOWN;
                }
            }
            case MasalaThreadPoolState::SOME_THREADS_SPINNING_DOWN :
            {
                if( desired_thread_count > num_active_threads_ ) {
                    decrement_inactive_threads_mutexlocked( desired_thread_count - num_active_threads_ ); // Alters num_active_threads_ and num_inactive_threads_.
                    // We may still need to launch more.
                    if( desired_thread_count > num_active_threads_ ) {
                        launch_threads_mutexlocked( desired_thread_count - num_active_threads_ );
                        thread_pool_state_ = MasalaThreadPoolState::THREADS_READY;
                    }
                } else if( desired_thread_count < num_active_threads_ ) {
                    increment_inactive_threads_mutexlocked( num_active_threads_ - desired_thread_count ); // Alters num_active_threads_ and num_inactive_threads_.
                }
            }
            case MasalaThreadPoolState::ALL_THREADS_SPINNING_DOWN :
            {
                MASALA_THROW( class_namespace_and_name(), "launch_threads_if_needed", "Received request for threads after spin-down signal." );
            }
        }
    }
} // MasalaThreadPool::launch_threads_if_needed()

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

/// @brief Increase the number of threads in the threadpool by N.
/// @details The thread_pool_mutex_ must be locked before calling this function!
void
MasalaThreadPool::launch_threads_mutexlocked(
    base::Size const n_threads_to_launch
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( n_threads_to_launch > 0, "launch_threads_mutexlocked", "The number of threads to launch must be greater than zero." );
    base::Size const startindex( threads_.size() ), endindex( threads_.size() + n_threads_to_launch );
    threads_.reserve( endindex );
    for( base::Size i(startindex); i<endindex; ++i ) {
        threads_[i] = std::make_shared< MasalaThread >( next_thread_index_, MasalaThreadCreationKey() );
        ++next_thread_index_;
    }
    write_to_tracer( "Launched " + std::to_string( n_threads_to_launch ) + " new threads." );
} // MasalaThreadPool::launch_threads_mutexlocked()

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
