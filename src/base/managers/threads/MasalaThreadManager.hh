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

/// @file src/base/managers/threads/MasalaThreadManager.hh
/// @brief A static singleton for managing a thread pool, and execution of code
/// in parallel threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadManager_hh
#define Masala_src_base_managers_threads_MasalaThreadManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/threads/MasalaThreadManager.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.fwd.hh>
#include <base/managers/threads/MasalaThreadedWorkRequest.fwd.hh>
#include <base/managers/threads/thread_pool/MasalaThreadPool.fwd.hh>

// STL headers:
#include <mutex>
#include <atomic>

namespace masala {
namespace base {
namespace managers {
namespace threads {


/// @brief A static singleton for managing a thread pool, and execution of code
/// in parallel threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaThreadManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    /// @details Creates the thread pool object, but that does not launch threads until
    /// work is first assigned to threads (lazy thread launching).
    MasalaThreadManager();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaThreadManager( MasalaThreadManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaThreadManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaThreadManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaThreadManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::thread".
    std::string
    class_namespace() const override;

    /// @brief Do a vector of work in threads, without a reservation.
    /// @param[in] request An object describing the work to be done and the
    /// number of requested threads in which to do it.
    /// @returns A summary of what work was done, the number of threads
    /// in which it was actually executed, and how long it took.
    MasalaThreadedWorkExecutionSummary
    do_work_in_threads(
        MasalaThreadedWorkRequest const & request
    );

    /// @brief Get the total number of threads that the thread pool is set
    /// to run.  (May not have been launched yet.)
    base::Size
    total_threads() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Given a request containing a vector of work, this function
    /// can be executed in parallel in order to actually do the work.
    void
    threaded_execution_function(
        MasalaThreadedWorkRequest const & request,
        MasalaThreadedWorkExecutionSummary const & summary
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief Lock the thread manager (e.g. for resizing thread pools).
    mutable std::mutex thread_manager_mutex_;

    /// @brief The total number of threads to launch.
    base::Size total_threads_ = 1;

    /// @brief The thread pool.  These are created on instantiation of the thread
    /// manager.  Threads are launched internally on first request, and are kept
    /// idling until work is assigned.
    base::managers::threads::thread_pool::MasalaThreadPoolSP thread_pool_;

};

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_threads_MasalaThreadManager_hh