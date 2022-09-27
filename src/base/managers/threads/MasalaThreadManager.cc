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

/// @file src/base/managers/threads/MasalaThreadManager.cc
/// @brief A static singleton for managing a thread pool, and execution of code
/// in parallel threads.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/threads/MasalaThreadManager.hh>

// Base headers:
#include <base/types.hh>
#include <base/utility/string/string_manipulation.hh>

// STL headers:
#include <string>
#include <iostream>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaThreadManagerHandle
MasalaThreadManager::get_instance() {
    static MasalaThreadManager config_manager;
    return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaThreadManager".
std::string
MasalaThreadManager::class_name() const {
    return "MasalaThreadManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::thread".
std::string
MasalaThreadManager::class_namespace() const {
    return "masala::base::managers::threads";
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala
