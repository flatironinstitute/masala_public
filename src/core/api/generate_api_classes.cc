/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/core/api/generate_api_classes.cc
/// @brief Utility functions to generate all of the classes in core that define
/// an API.  Used for auto-generating the core api.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header
#include <core/api/generate_api_classes.hh>

// Core headers
#include <core/molecular_system/MolecularSystem.hh>
#include <core/chemistry/MolecularGeometry.hh>
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/chemistry/atoms/AtomInstanceConstIterator.hh>
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.hh>
#include <core/chemistry/atoms/data/AtomData.hh>
#include <core/chemistry/atoms/data/PDBAtomData.hh>
#include <core/molecular_system/kinematics/KinematicDataRepresentationBase.hh>
#include <core/selection/atom_selection/AtomSelection.hh>
#include <core/io/pdb/BasicPDBReader.hh>
#include <core/scoring/ScoringTerm.hh>
#include <core/scoring/ScoringTermAdditionalInput.hh>
#include <core/scoring/ScoringTermAdditionalOutput.hh>
#include <core/scoring/ScoringTermCache.hh>

namespace masala {
namespace core {
namespace api {

    /// @brief Generate an instance of each of the classes in core that have a defined API, and
    /// return a vector of owning pointers to these instances.
    /// @details Used for auto-generating the core API description (as a JSON file).
    std::vector< masala::base::MasalaObjectSP >
    generate_api_classes() {
        std::vector< masala::base::MasalaObjectSP > outvec;

        // Add to this vector whenever a class is added with a defined API:
        outvec.emplace_back( masala::make_shared< masala::core::molecular_system::MolecularSystem >() );
        outvec.emplace_back( masala::make_shared< masala::core::chemistry::MolecularGeometry >() );
        outvec.emplace_back( masala::make_shared< masala::core::chemistry::atoms::AtomInstance >() );
        outvec.emplace_back( masala::make_shared< masala::core::chemistry::atoms::AtomInstanceConstIterator >() );
        outvec.emplace_back( masala::make_shared< masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentation >() );
        outvec.emplace_back( masala::make_shared< masala::core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentation >() );
        outvec.emplace_back( masala::make_shared< masala::core::chemistry::atoms::data::AtomData >() );
        outvec.emplace_back( masala::make_shared< masala::core::chemistry::atoms::data::PDBAtomData >() );
        outvec.emplace_back( masala::make_shared< masala::core::selection::atom_selection::AtomSelection >() );
        outvec.emplace_back( masala::make_shared< masala::core::molecular_system::kinematics::KinematicDataRepresentationBase >() );
        outvec.emplace_back( masala::make_shared< masala::core::io::pdb::BasicPDBReader >() );
        outvec.emplace_back( masala::make_shared< masala::core::scoring::ScoringTerm >() );
        outvec.emplace_back( masala::make_shared< masala::core::scoring::ScoringTermAdditionalInput >() );
        outvec.emplace_back( masala::make_shared< masala::core::scoring::ScoringTermAdditionalOutput >() );
        outvec.emplace_back( masala::make_shared< masala::core::scoring::ScoringTermCache >() );
        // ADD MORE ENTRIES HERE

        return outvec;
    }

} // namespace api
} // namespace core
} // namespace masala
