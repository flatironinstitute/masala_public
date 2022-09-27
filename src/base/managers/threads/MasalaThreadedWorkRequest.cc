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

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
