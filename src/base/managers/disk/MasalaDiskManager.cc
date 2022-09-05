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

/// @file src/base/managers/disk/MasalaDiskManager.cc
/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/disk/MasalaDiskManager.hh>

// STL headers:
#include <string>

namespace base {
namespace managers {
namespace disk {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaDiskManagerHandle
MasalaDiskManager::getInstance() {
    static const MasalaDiskManager disk_manager;
    return &disk_manager;
}

/// @brief Get the name of this object.
/// @details Returns "MasalaDiskManager".
std::string
MasalaDiskManager::class_name() const {
    return "MasalaDiskManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "base::managers::disk".
std::string
MasalaDiskManager::class_namespace() const {
    return "base::managers::disk";
}

} // namespace disk
} // namespace managers
} // namespace base
