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

/// @file src/base/managers/engine/EigenLinalgCartesianAtomCoordinateRepresentationCreator.hh
/// @brief A creator for Eigen linear algebra Cartesian atom coordinate data representations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentationCreator_hh
#define Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentationCreator_hh

// Parent declarations:
#include <base/managers/engine/MasalaDataRepresentationCreatorBase.hh>

// Forward declarations:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentationCreator.fwd.hh>
#include <core/initialization/registrators/CoreAtomCoordinateRepresentationRegistrator.fwd.hh>

// Base headers:

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {

/// @brief A creator for Eigen linear algebra Cartesian atom coordinate data representations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class EigenLinalgCartesianAtomCoordinateRepresentationCreator : public masala::base::managers::engine::MasalaDataRepresentationCreatorBase {

    friend class masala::core::initialization::registrators::CoreAtomCoordinateRepresentationRegistrator;

protected:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR -- PROTECTED TO ALLOW CoreAtomCoordinateRepresentationRegistrator
// ONLY TO CREATE CREATORS.
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    EigenLinalgCartesianAtomCoordinateRepresentationCreator() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Copy constructor.
    EigenLinalgCartesianAtomCoordinateRepresentationCreator( EigenLinalgCartesianAtomCoordinateRepresentationCreator const & ) = delete;

    // Destructor.
    ~EigenLinalgCartesianAtomCoordinateRepresentationCreator() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the class name.
    /// @returns "EigenLinalgCartesianAtomCoordinateRepresentationCreator".
    std::string class_name() const override;

    /// @brief Get the class namespace.
    /// @returns "masala::core::chemistry::atoms::coordinates"
    std::string class_namespace() const override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Creators must implement a create_data_representation() function.
    /// @details Protected so that this can only be called by the MasalaDataRepresentationManager,
    /// for which this is a friend class.
    masala::base::managers::engine::MasalaDataRepresentationBaseSP
    create_data_representation() const override;

};

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_coordinates_EigenLinalgCartesianAtomCoordinateRepresentationCreator_hh