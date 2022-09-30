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
#include <string>
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
/// @param[in] nthreads_actual The number of threads that were
/// actually used for carrying out the work.
/// @param[in] execution_time The time, in microseconds, that
/// execution took.
MasalaThreadedWorkExecutionSummary::MasalaThreadedWorkExecutionSummary(
    MasalaThreadedWorkStatus const status,
    base::Size const nthreads_actual,
    base::Real const execution_time_microseconds
) :
    base::MasalaObject(),
    work_status_(status),
    execution_time_microseconds_(execution_time_microseconds),
    nthreads_actual_(nthreads_actual)
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

/// @brief Allow the MasalaThreadPool to record which threads have been assigned to this
/// job.  We will store:
/// - Indices of the threads, based on the thread pool's numbering.
/// - Indices of the threads, based on internal numbering.  (For instance, if we got threads
/// 0, 5, 6, and 7, internally we would refer to these as threads 0, 1, 2, and 3).
void
MasalaThreadedWorkExecutionSummary::set_assigned_child_threads(
    std::vector< thread_pool::MasalaThreadSP > const & threads
) {
    nthreads_actual_ = threads.size() + 1; // The parent thread is also an assigned thread.
    assigned_child_thread_indices_.resize( threads.size() );
    for( base::Size i(1), imax(threads.size()); i<=imax; ++i ) {
        assigned_child_thread_indices_[i] = threads[i]->thread_index();
    }
    parent_thread_index_ = MasalaThreadManager::get_instance()->get_thread_manager_thread_id_from_system_thread_id( std::this_thread::get_id() );
} // MasalaThreadedWorkExecutionSummary::set_assigned_child_threads()

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
