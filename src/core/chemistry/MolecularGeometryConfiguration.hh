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

/// @file src/core/chemistry/MolecularGeometryConfiguration.hh
/// @brief A container of configuration settings for a MolecularGeometry object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_MolecularGeometryConfiguration_hh
#define Masala_src_core_chemistry_MolecularGeometryConfiguration_hh

// Parent header
#include <base/managers/configuration/ConfigurationBase.hh>

// Project headers:
#include <core/chemistry/MolecularGeometryConfiguration.fwd.hh>

// Base headers
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.fwd.hh>

// STL headers
#include <string>

namespace masala {
namespace core {
namespace chemistry {

class MolecularGeometryConfiguration : public masala::base::managers::configuration::ConfigurationBase {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MolecularGeometryConfiguration() = delete;

    /// @brief MasalaConfigurationManager-authorized constructor.
    /// @details The MasalaConfigurationManagerAuthorization object is an object that only the
    /// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
    /// ConfigurationBase-derived object.
    MolecularGeometryConfiguration( masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey );

    /// @brief Copy constructor.
    MolecularGeometryConfiguration( MolecularGeometryConfiguration const & src ) = default;

    /// @brief Default destructor.
    ~MolecularGeometryConfiguration() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared_ptr to the copy.
    MolecularGeometryConfigurationSP clone() const;

    /// @brief Deep operation: make an independent copy of this object and return a shared_ptr to the copy.
    MolecularGeometryConfigurationSP deep_clone() const;

    /// @brief Returns "MolecularGeometryConfiguration".
    std::string class_name() const override;

    /// @brief Returns "masala::core::chemistry".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the default kinematic representation.
    std::string const &
    default_atom_coordinate_representation() const;

private:

////////////////////////////////////////////////////////////////////////////////
// Data
////////////////////////////////////////////////////////////////////////////////

    /// @brief The default atom coordinate representation.
    std::string const default_atom_coordinate_representation_ = "masala::core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentation";

};

} // namespace chemistry
} // namespace core
} // namespace masala

#endif //Masala_src_core_chemistry_MolecularGeometryConfiguration_hh
