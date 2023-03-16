/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/// @file src/core/chemistry/MolecularGeometryConfiguration.cc
/// @brief A container of configuration settings for a MolecularGeometry object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <core/chemistry/MolecularGeometryConfiguration.hh>

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
MolecularGeometryConfiguration::MolecularGeometryConfiguration(
    masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
) :
    masala::base::managers::configuration::ConfigurationBase( passkey )
{
    write_to_tracer( "Loading MolecularGeometry class configuration from configuration settings on disk." );
    //TODO load configuration from disk here.
}

/// @brief Clone operation: make a copy of this object and return a shared_ptr to the copy.
MolecularGeometryConfigurationSP
MolecularGeometryConfiguration::clone() const {
    return masala::make_shared< MolecularGeometryConfiguration >(*this);
}

/// @brief Deep clone operation: make an independent copy of this object and return a shared_ptr to the copy.
MolecularGeometryConfigurationSP
MolecularGeometryConfiguration::deep_clone() const {
    return masala::make_shared< MolecularGeometryConfiguration >(*this);
}

/// @brief Returns "MolecularGeometryConfiguration".
std::string
MolecularGeometryConfiguration::class_name() const {
    return "MolecularGeometryConfiguration";
}

/// @brief Returns "masala::core::chemistry".
std::string
MolecularGeometryConfiguration::class_namespace() const {
    return "masala::core::chemistry";
}

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the default kinematic representation.
std::string const &
MolecularGeometryConfiguration::default_atom_coordinate_representation() const {
    return default_atom_coordinate_representation_;
}

} // namespace chemistry
} // namespace core
} // namespace masala
