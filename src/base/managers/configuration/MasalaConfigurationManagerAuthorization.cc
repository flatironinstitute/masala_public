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

/// @file src/base/managers/configuration/MasalaConfigurationManagerAuthorization.cc
/// @brief A "key" class with a private constructor, which can only be instantiated by
/// the MasalaConfigurationManager, used to ensure that only the configuration manager
/// can instantiate configuration objects.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Base headers
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.hh>

// STL headers
#include <string>

namespace masala {
namespace base{
namespace managers{
namespace configuration{


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the class name ("MasalaConfigurationManagerAuthorization").
std::string
MasalaConfigurationManagerAuthorization::class_name() const {
    return "MasalaConfigurationManagerAuthorization";
}

/// @brief Get the class namespace ("masala::base::managers::configuration").
std::string
MasalaConfigurationManagerAuthorization::class_namespace() const {
    return "bas::managers::configuration";
}

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala
