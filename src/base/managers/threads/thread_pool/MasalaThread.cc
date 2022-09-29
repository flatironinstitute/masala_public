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
/// @brief A container for a set of threads.  Controls launching, destroying,
/// or renumbering threads in a threadsafe way.
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
    MasalaThreadCreationKey const & 
) :
    base::MasalaObject()
{}

////////////////////////////////////////////////////////////////////////////////
// MasalaThread PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "MasalaThread".
std::string
MasalaThread::class_name() const {
    return "MasalaThread";
}

/// @brief Returns "masala::base::managers::threads::thread_pool".
std::string
MasalaThread::class_namespace() const {
    return "masala::base::managers::threads::thread_pool";
}

} // namespace thread_pool
} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
