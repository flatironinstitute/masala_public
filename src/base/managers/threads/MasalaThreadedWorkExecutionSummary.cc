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
/// @brief A base class for all Masala objects.
/// @details Masala objects all define certain functions, such as write_to_tracer(),
/// class_name(), and class_namespace().
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

// STL headers
#include <string>

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
    nthreads_actual_(nthreads_actual),
    execution_time_microseconds_(execution_time_microseconds)
{}


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThreadedWorkExecutionSummary".
std::string
MasalaThreadedWorkExecutionSummary::class_name() const {
    return "MasalaThreadedWorkExecutionSummary";
}

/// @brief Returns "masala::base::managers::threads".
std::string
MasalaThreadedWorkExecutionSummary::class_namespace() const {
    return "masala::base::managers::threads";
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
