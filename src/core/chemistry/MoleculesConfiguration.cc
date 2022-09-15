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

/// @file src/core/chemistry/MoleculesConfiguration.cc
/// @brief A container of configuration settings for a Molecules object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <core/chemistry/MoleculesConfiguration.hh>

namespace masala {
namespace core {
namespace chemistry {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////


/// @brief MasalaConfigurationManager-authorized constructor.
/// @details The MasalaConfigurationManagerAuthorization object is an object that only the
/// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
/// ConfigurationBase-derived object.
MoleculesConfiguration::MoleculesConfiguration(
    masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
) :
    masala::base::managers::configuration::ConfigurationBase( passkey )
{
    write_to_tracer( "Loading Molecules class configuration from configuration settings on disk." );
    //TODO load configuration from disk here.
}

/// @brief Clone operation: make a copy of this object and return a shared_ptr to the copy.
MoleculesConfigurationSP
MoleculesConfiguration::clone() const {
    return std::make_shared< MoleculesConfiguration >(*this);
}

/// @brief Deep clone operation: make an independent copy of this object and return a shared_ptr to the copy.
MoleculesConfigurationSP
MoleculesConfiguration::deep_clone() const {
    return std::make_shared< MoleculesConfiguration >(*this);
}

/// @brief Returns "MoleculesConfiguration".
std::string
MoleculesConfiguration::class_name() const {
    return "MoleculesConfiguration";
}

/// @brief Returns "core::chemistry".
std::string
MoleculesConfiguration::class_namespace() const {
    return "core::chemistry";
}

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the default kinematic representation.
std::string const &
MoleculesConfiguration::default_atom_coordinate_representation() const {
    return default_atom_coordinate_representation_;
}

} // namespace chemistry
} // namespace core
} // namespace masala
