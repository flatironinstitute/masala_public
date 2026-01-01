/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/base/managers/threads/thread_pool/MasalaThreadPool.cc
/// @brief A container for a set of threads.  Controls launching, destroying,
/// or renumbering threads in a threadsafe way.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/threads/thread_pool/MasalaThreadPool.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.hh>
#include <base/managers/threads/MasalaThreadManager.hh>
#include <base/managers/threads/thread_pool/MasalaThread.hh>

// STL headers
#include <string>
#include <sstream>
#include <condition_variable>

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
{} // MasalaThreadPool::MasalaThreadPool()

/// @brief Destructor.
/// @details Safely terminates each thread.
MasalaThreadPool::~MasalaThreadPool() {
    std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
    thread_pool_state_ = MasalaThreadPoolState::ALL_THREADS_SPINNING_DOWN;
    for( std::vector< MasalaThreadSP >::iterator it( threads_.begin() ); it != threads_.end(); ) {
        write_to_tracer_with_spindown_check( "Terminating thread " + std::to_string( (*it)->thread_index() ) + "." );
        {
            std::unique_lock< std::mutex > lock2( (*it)->thread_mutex() );
            (*it)->set_forced_idle(true);
        }
        it = threads_.erase( it );
    }
} //MasalaThreadPool::MasalaThreadPool()

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
    {
        std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
        switch( thread_pool_state_ ) {
            case MasalaThreadPoolState::INVALID_STATE :
            {
                MASALA_THROW( class_namespace_and_name(), "launch_threads_if_needed", "Program error: thread pool is in an invalid state!" );
                break;
            }
            case MasalaThreadPoolState::THREADS_NOT_LAUNCHED :
            {
                DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( threads_.empty(), "launch_threads_if_needed", "Program error: threads have been launched, but thread pool status indicates that they have not." );
                if( desired_thread_count > num_active_threads_ ) {
                    launch_threads_mutexlocked( desired_thread_count );
                    num_active_threads_ = desired_thread_count;
                }
                num_inactive_threads_ = 0;
                thread_pool_state_ = MasalaThreadPoolState::THREADS_READY;
                break;
            }
            case MasalaThreadPoolState::THREADS_READY :
            {
                if( desired_thread_count > num_active_threads_ ) {
                    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( num_inactive_threads_ == 0, "launch_threads_if_needed", "Program error: in mode THREADS_READY, yet inactive threads were found!" );
                    base::Size const n_to_launch( desired_thread_count - num_active_threads_ );
                    launch_threads_mutexlocked( n_to_launch );
                    num_active_threads_ += n_to_launch;
                } else if( desired_thread_count < num_active_threads_ ) {
                    increment_inactive_threads_mutexlocked( num_active_threads_ - desired_thread_count ); // Alters num_active_threads_ and num_inactive_threads_.
                    thread_pool_state_ = MasalaThreadPoolState::SOME_THREADS_SPINNING_DOWN;
                }
                break;
            }
            case MasalaThreadPoolState::SOME_THREADS_SPINNING_DOWN :
            {
                if( desired_thread_count > num_active_threads_ ) {
                    decrement_inactive_threads_mutexlocked( desired_thread_count - num_active_threads_ ); // Alters num_active_threads_ and num_inactive_threads_.
                    // We may still need to launch more.
                    if( desired_thread_count > num_active_threads_ ) {
                        base::Size const n_to_launch( desired_thread_count - num_active_threads_ );
                        launch_threads_mutexlocked( n_to_launch );
                        num_active_threads_ += n_to_launch;
                    }
                    if( num_inactive_threads_ == 0 ) {
                        thread_pool_state_ = MasalaThreadPoolState::THREADS_READY;
                    }
                } else if( desired_thread_count < num_active_threads_ ) {
                    increment_inactive_threads_mutexlocked( num_active_threads_ - desired_thread_count ); // Alters num_active_threads_ and num_inactive_threads_.
                }
                break;
            }
            case MasalaThreadPoolState::ALL_THREADS_SPINNING_DOWN :
            {
                MASALA_THROW( class_namespace_and_name(), "launch_threads_if_needed", "Received request for threads after spin-down signal." );
                break;
            }
        }
    }
} // MasalaThreadPool::launch_threads_if_needed()

/// @brief Get the number of threads actually running.
/// @details Includes any threads that have received spindown signals but
/// which have not yet spun down.
base::Size
MasalaThreadPool::actual_threads_running() const {
    std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
    return threads_.size();
} // MasalaThreadPool::actual_threads_running()

/// @brief Given a function, run it in up to the requested number of threads.
/// @note The actual number of threads in which it runs might be less than
/// the requested number.
void
MasalaThreadPool::execute_function_in_threads(
    std::function< void() > const & fxn,
    base::Size const threads_to_request,
    masala::base::managers::threads::MasalaThreadedWorkExecutionSummary & summary
) {
    CHECK_OR_THROW_FOR_CLASS( threads_to_request > 0, "execute_function_in_threads", "The number of threads requested must be greater than zero." );

    std::vector< MasalaThreadSP > assigned_threads;
    assigned_threads.reserve( threads_.size() );
    std::mutex job_completion_mutex;
    std::condition_variable job_completion_condition_var;
    std::atomic_ulong num_jobs_completed(0);

    std::vector< MasalaThreadSP > threads_to_delete;
    threads_to_delete.reserve( threads_.size() );

    // Assign work to other threads (under mutex lock):
    {
        std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
        if( threads_to_request > 1 ) {
            base::Size assigned_thread_count(0);
            for( std::vector< MasalaThreadSP >::iterator it( threads_.begin() ); it!=threads_.end(); ) {
                MasalaThread & curthread( **it );
                std::unique_lock< std::mutex > thread_lock( curthread.thread_mutex() );
                if( curthread.is_idle() && !curthread.forced_idle() ) {

                    if(
                        thread_pool_state_ == MasalaThreadPoolState::SOME_THREADS_SPINNING_DOWN &&
                        num_inactive_threads_ > 0
                    ) {
                        // Purge threads that are spinning down and which aren't working:
                        write_to_tracer( "Marking thread " + std::to_string(curthread.thread_index()) + " for termination." );
                        curthread.set_forced_idle(true);
                        threads_to_delete.push_back(*it); // Ensures that these threads are taken out of the thread list, but persist until they can be safely deleted when the mutex lock is not held.
                        it = threads_.erase(it);
                        --num_inactive_threads_;
                        if( num_inactive_threads_ == 0 ) {
                            thread_pool_state_ = MasalaThreadPoolState::THREADS_READY;
                        }
                    } else {
                        // Assign work to remaining threads:
                        if( assigned_thread_count + 1 < threads_to_request ) { // +1 because this thread will also be assigned.
                            curthread.set_forced_idle( true );
                            curthread.set_function( fxn, job_completion_condition_var, num_jobs_completed, job_completion_mutex );
                            assigned_threads.push_back( *it );
                            ++assigned_thread_count;
                        }
                        ++it;
                    }
                } else {
                    ++it;
                }
            }
        }

        if( !threads_to_delete.empty() ) {
            threads_to_delete.clear(); // Since these are the only owning pointers for these MasalaThread objects, this triggers their destruction.  Their destructors call the thread termination code.
            write_to_tracer( "Terminated threads marked for termination.  A total of " +
                std::to_string(threads_.size()) + " child thread" + ( threads_.size() == 1 ? " remains" : "s remain" ) +
                " in the thread pool (not counting the parent thread)."
            );
        }

		Size const current_thread( get_thread_manager_thread_id_from_system_thread_id_mutexlocked( std::this_thread::get_id() ) );
		summary.set_assigned_threads( current_thread, assigned_threads ); // Needed even if assigned threads is empty, since information about this thread is stored.

        // At this point, it is safe to begin exection of the work in threads.
        if( !assigned_threads.empty() ) {
            for( auto & thread : assigned_threads ) {
                std::unique_lock< std::mutex > thread_lock( thread->thread_mutex() );
                thread->set_forced_idle( false );
            }
        }
    } // Mutex lock scope.

    // Also execute the function in this thread.
    fxn();

    if( assigned_threads.size() > 0 ) {
        // If other threads are working, wait for them.
        base::Size const nthread( assigned_threads.size() );
		std::unique_lock< std::mutex > job_completion_condition_lock( job_completion_mutex );
		if( num_jobs_completed.load() < nthread ) {
        	job_completion_condition_var.wait( job_completion_condition_lock, [&num_jobs_completed, nthread]{ return num_jobs_completed.load() == nthread; } );
		}
    }

    // Clean up threads (i.e. terminate) that have spindown signals (under lock guard):
    clean_up_threads_spinning_down();

} // MasalaThreadPool::execute_function_in_threads()

/// @brief Clean up threads (i.e. terminate) marked for deletion.
void
MasalaThreadPool::clean_up_threads_spinning_down() {
    std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
    if(
        thread_pool_state_ == MasalaThreadPoolState::SOME_THREADS_SPINNING_DOWN &&
        num_inactive_threads_ > 0
    ) {
        std::vector< MasalaThreadSP > threads_to_delete;
        threads_to_delete.reserve( threads_.size() );

        // Make a list of threads to delete:
        for( std::vector< MasalaThreadSP >::iterator it( threads_.begin() ); it!=threads_.end(); ) {
            MasalaThread & curthread( **it );
            std::unique_lock< std::mutex > thread_lock( curthread.thread_mutex() );
            if( (!curthread.is_idle()) || curthread.forced_idle() ) continue; // Don't spin down threads that are working or are being manipulated.
            write_to_tracer( "Marking thread " + std::to_string(curthread.thread_index()) + " for termination." );
            curthread.set_forced_idle(true);
            threads_to_delete.push_back(*it); // Ensures that these threads are taken out of the thread list, but persist until they can be safely deleted when the mutex lock is not held.
            it = threads_.erase(it);
            --num_inactive_threads_;
            if( num_inactive_threads_ == 0 ) {
                thread_pool_state_ = MasalaThreadPoolState::THREADS_READY;
                break;
            }
        }

        // Actually delete threads.  (Note that MasalaThread destructor triggers thread joining).
        if( !threads_to_delete.empty() ) {
            threads_to_delete.clear(); // Since these are the only owning pointers for these MasalaThread objects, this triggers their destruction.  Their destructors call the thread termination code.
            write_to_tracer( "Threads spinning down marked for termination.  A total of " + std::to_string(threads_.size()) +
                " child thread" + ( threads_.size() == 1 ? " remains" : "s remain" ) + " in the thread "
                "pool (not counting the parent thread)."
            );
        }
    }

} //MasalaThreadPool::clean_up_threads_spinning_down()

/// @brief Given a system thread ID, return whether a thread with that
/// system ID exists in the thread pool.
bool
MasalaThreadPool::has_system_thread_id(
    std::thread::id const system_thread_id
) const {
    std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
    for( auto const & thread : threads_ ) {
        if( thread->system_thread_id() == system_thread_id ) {
            return true;
        }
    }
    return false;
} // MasalaThreadPool::has_system_thread_id()

/// @brief Given a system thread ID, return the index of the stored thread with that
/// system ID.  Throws if no such thread exists in the thread pool.
base::Size
MasalaThreadPool::get_thread_manager_thread_id_from_system_thread_id(
    std::thread::id const system_thread_id
) const {
    std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
    return get_thread_manager_thread_id_from_system_thread_id_mutexlocked( system_thread_id );
} // MasalaThreadPool::get_thread_manager_thread_id_from_system_thread_id()

/// @brief Get the IDs of all threads currently running.
std::vector< masala::base::Size >
MasalaThreadPool::get_thread_manager_thread_ids() const {
    std::lock_guard< std::mutex > lock( thread_pool_mutex_ );
	std::vector< masala::base::Size > thread_ids( threads_.size() + 1 );
	thread_ids[0] = 0;
    for( masala::base::Size i(0), imax(threads_.size()); i<imax; ++i ) {
        thread_ids[i+1] = threads_[i]->thread_index();
    }
	thread_ids.shrink_to_fit();
	return thread_ids;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

/// @brief Given a system thread ID, return the index of the stored thread with that
/// system ID.  Throws if no such thread exists in the thread pool.
/// @details This version performs no mutex locking.
base::Size
MasalaThreadPool::get_thread_manager_thread_id_from_system_thread_id_mutexlocked(
    std::thread::id const system_thread_id
) const {
	if( system_thread_id == masala::base::managers::threads::MasalaThreadManager::get_instance()->get_system_thread_id_of_master_thread() ) {
		return 0;
	}

    for( auto const & thread : threads_ ) {
        if( thread->system_thread_id() == system_thread_id ) {
            return thread->thread_index();
        }
    }
    // If we reach here, we need to throw, since the thread doesn't exist in the pool.
    std::ostringstream ss;
    ss << system_thread_id;
    MASALA_THROW(
        class_namespace_and_name(), "get_thread_manager_thread_id_from_system_thread_id_mutexlocked",
        "The system thread with ID " + ss.str() + " is not contained in the thread pool."
    );
    return 0; // Keep older compilers happy.
} // MasalaThreadPool::get_thread_manager_thread_id_from_system_thread_id_mutexlocked()

/// @brief Increase the number of threads in the threadpool by N.
/// @details The thread_pool_mutex_ must be locked before calling this function!
void
MasalaThreadPool::launch_threads_mutexlocked(
    base::Size const n_threads_to_launch
) {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        n_threads_to_launch > 0, "launch_threads_mutexlocked", "The number of threads to "
        "launch must be greater than zero."
    );
    base::Size const startindex( threads_.size() ), endindex( threads_.size() + n_threads_to_launch );
    threads_.reserve( endindex );
    for( base::Size i(startindex); i<endindex; ++i ) {
        threads_.push_back( masala::make_shared< MasalaThread >( next_thread_index_, MasalaThreadCreationKey() ) );
        ++next_thread_index_;
    }
    write_to_tracer( "Launched " + std::to_string( n_threads_to_launch ) + " new threads.  "
        "A total of " + std::to_string(threads_.size()) + " child thread"
        + ( threads_.size() == 1 ? " is " : "s are " ) +
        "now running in the thread pool (not counting the parent thread)."
    );
} // MasalaThreadPool::launch_threads_mutexlocked()

/// @brief Mark additional threads as inactive.
/// @details The thread_pool_mutex_ must be locked before calling this function!
void
MasalaThreadPool::increment_inactive_threads_mutexlocked(
    base::Size n_new_inactive_threads
) {
    base::Size const actual_n_new_inactive_threads( std::min( num_active_threads_, n_new_inactive_threads ) );
    num_active_threads_ -= actual_n_new_inactive_threads;
    num_inactive_threads_ += actual_n_new_inactive_threads;
    write_to_tracer( "Spinning down " + std::to_string(actual_n_new_inactive_threads) + " threads." );
} // MasalaThreadPool::increment_inactive_threads_mutexlocked

/// @brief Unmark some threads as inactive.
/// @details The thread_pool_mutex_ must be locked before calling this function!
void
MasalaThreadPool::decrement_inactive_threads_mutexlocked(
    base::Size n_threads_to_reactivate
) {
    base::Size const actual_n_threads_to_reactivate( std::min( num_inactive_threads_, n_threads_to_reactivate ) );
    num_inactive_threads_ -= actual_n_threads_to_reactivate;
    num_active_threads_ += actual_n_threads_to_reactivate;
    write_to_tracer( "Spinning " + std::to_string( actual_n_threads_to_reactivate ) + " threads that had received spin-down signals back up." );
}

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
