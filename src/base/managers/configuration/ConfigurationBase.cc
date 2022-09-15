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

/// @file src/base/managers/configuration/ConfigurationBase.cc
/// @brief Pure virtual base class for containers that store configuration
/// settings for modules.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <base/managers/configuration/ConfigurationBase.hh>

namespace masala {
namespace base {
namespace managers {
namespace configuration {

/// @brief MasalaConfigurationManager-authorized constructor.
/// @details The MasalaConfigurationManagerAuthorization object is an object that only the
/// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
/// ConfigurationBase-derived object.
ConfigurationBase::ConfigurationBase(
    MasalaConfigurationManagerAuthorization const &
) : 
    masala::base::MasalaObject()
{}

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala
