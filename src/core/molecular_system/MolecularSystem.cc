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

/// @file src/core/molecular_system/MolecularSystem.cc
/// @brief A class representing a molecular structure.
/// @details MolecularSystems store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @note A MolecularSystem is equivalent to what is called a "Pose" in other molecular modelling
/// packages, such as Rosetta.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core/molecular_system/MolecularSystem.hh>

// Core headers:
#include <core/chemistry/MolecularGeometry.hh>
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_TwoInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_TwoInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_TwoInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>
#include <base/api/setter/setter_annotation/DeprecatedSetterAnnotation.hh>
#include <base/api/getter/getter_annotation/DeprecatedGetterAnnotation.hh>
#include <base/api/work_function/work_function_annotation/DeprecatedWorkFunctionAnnotation.hh>
#include <base/api/constructor/constructor_annotation/DeprecatedConstructorAnnotation.hh>
#include <base/enums/ChemicalBondTypeEnum.hh>

namespace masala {
namespace core {
namespace molecular_system {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor, making an empty MolecularSystem.
/// @details Ensures that the molecular_geometry_ object always exists.
MolecularSystem::MolecularSystem() :
    masala::base::MasalaObject(),
    molecular_geometry_( masala::make_shared< masala::core::chemistry::MolecularGeometry >() )
{}

/// @brief Copy constructor (explicit due to mutex).
/// @details Doesn't make this independent.  Use deep_clone() or make_independent() for that.
MolecularSystem::MolecularSystem(
    MolecularSystem const & src
) :
    masala::base::MasalaObject(src)
{
    (*this) = src;
}

/// @brief An example of a deprecated constructor.  Does nothing.
MolecularSystem::MolecularSystem(
	std::string const & ,//dummy_setting_in,
	masala::base::Size const //another_setting
) :
	masala::base::MasalaObject()
{
	// GNDN
}

/// @brief Assignment operator (explicit due to mutex).
MolecularSystem &
MolecularSystem::operator=(
    MolecularSystem const & src
) {
    std::lock( mutex_, src.mutex_ );
    std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
    std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
    molecular_geometry_ = src.molecular_geometry_;
    // Deliberately do not copy api definition.
    return *this;
}


/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
MolecularSystemSP
MolecularSystem::clone() const {
    return masala::make_shared< MolecularSystem >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
MolecularSystemSP
MolecularSystem::deep_clone() const {
    MolecularSystemSP new_molecular_system( masala::make_shared< MolecularSystem >( *this ) );
    new_molecular_system->make_independent();
    return new_molecular_system;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Be sure to update this function whenever a private member is added!
void
MolecularSystem::make_independent() {
    std::lock_guard< std::mutex > lock( mutex_ );
    molecular_geometry_ = molecular_geometry_->deep_clone();
}

/// @brief Returns "MolecularSystem".
std::string
MolecularSystem::class_name() const {
    return class_name_static();
}

/// @brief Returns "MolecularSystem".
/// @details Called by non-static version.
std::string
MolecularSystem::class_name_static() {
    return "MolecularSystem";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::molecular_system".
std::string
MolecularSystem::class_namespace() const {
    return class_namespace_static();
}

/// @brief Returns "masala::core::molecular_system".
/// @details Called by non-static version.
std::string
MolecularSystem::class_namespace_static() {
    return "masala::core::molecular_system";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the MolecularGeometry object in this molecular system, by shared pointer.
/// @details The MolecularGeometry object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A MolecularGeometry object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MolecularGeometryCSP
MolecularSystem::molecular_geometry_shared_ptr() const {
    std::lock_guard< std::mutex > lock( mutex_ );
    return molecular_geometry_;
}

/// @brief Access the MolecularGeometry object in this molecular system, by weak pointer.
/// @details The MolecularGeometry object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A MolecularGeometry object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MolecularGeometryCWP
MolecularSystem::molecular_geometry_weak_ptr() const {
    std::lock_guard< std::mutex > lock( mutex_ );
    return molecular_geometry_;
}

/// @brief Access the MolecularGeometry object in this molecular system, by const reference.
/// @details The MolecularGeometry object contains the coordinates and properties of atoms
/// and chemical bonds.
/// @note A MolecularGeometry object may contain more than one molecule (i.e. its atoms may
/// not all form one contiguously-bonded set).
core::chemistry::MolecularGeometry const &
MolecularSystem::molecular_geometry() const {
    std::lock_guard< std::mutex > lock( mutex_ );
    return *molecular_geometry_;
}

/// @brief An example of a deprecated API getter.
bool
MolecularSystem::deprecated_api_getter(
	masala::base::Size const //input1
) {
	// GNDN
	return false;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add an atom to this molecular system.
void
MolecularSystem::add_atom(
    masala::core::chemistry::atoms::AtomInstanceSP const & new_atom,
    std::array< masala::base::Real, 3 > const & coords
) {
    std::lock_guard< std::mutex > lock( mutex_ );
    CHECK_OR_THROW_FOR_CLASS( !molecular_geometry_->has_atom( new_atom ), "add_atom",
        "The molecular system already contains the atom!"
    );
    molecular_geometry_->add_atom( new_atom, coords );
}

/// @brief Add a bond to this molecule, with the bond type specified by string.
void
MolecularSystem::add_bond(
    masala::core::chemistry::atoms::AtomInstanceCSP const & first_atom,
    masala::core::chemistry::atoms::AtomInstanceCSP const & second_atom,
    std::string const & bond_type_string
) {
    std::lock_guard< std::mutex > lock( mutex_ );
    molecular_geometry_->add_bond( first_atom, second_atom, bond_type_string );
}

/// @brief Add a bond to this molecule.
void
MolecularSystem::add_bond(
    masala::core::chemistry::atoms::AtomInstanceCSP const & first_atom,
    masala::core::chemistry::atoms::AtomInstanceCSP const & second_atom,
    masala::core::chemistry::bonds::ChemicalBondType const bond_type
) {
    std::lock_guard< std::mutex > lock( mutex_ );
    molecular_geometry_->add_bond( first_atom, second_atom, bond_type );
}


/// @brief An example of a deprecated API setter.
void
MolecularSystem::deprecated_api_setter(
    masala::base::Size const //input1
) {
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief An example of a deprecated API work function.
masala::base::Size
MolecularSystem::deprecated_api_work_function(
    masala::base::Real const input1,
    bool const input2
) {
    //GNDN
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the MolecularSystem class.
base::api::MasalaObjectAPIDefinitionCWP
MolecularSystem::get_api_definition() {
    using namespace masala::base::api;
    using masala::base::Size;
    using masala::base::Real;

    std::lock_guard< std::mutex > lock( mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The MolecularSystem class stores information about the geometry, chemical properties, annotations, "
                "and energies of a molecule or group of molecules, as well as any cached data for that "
                "molecule or group of molecules.  It is roughly equivalent to the Pose class in other molecular "
                "modelling programs, such as Rosetta.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < MolecularSystem > > (
                class_name_static(),
                "Creates an empty MolecularSystem, initializing it only with an empty MolecularGeometry object."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < MolecularSystem, MolecularSystem const & > > (
                class_name_static(),
                "Copy constructor: copies an input MolecularSystem.  Note that this does not make a unique MolecularSystem unless "
                "make_independent() is subsequently called.",
                "src", "The input MolecularSystem to copy.  Unaltered by this operation."
            )
        );
		{
			constructor::MasalaObjectAPIConstructorDefinition_TwoInputSP< MolecularSystem, std::string const &, masala::base::Size const > deprecated_constructor(
				masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_TwoInput< MolecularSystem, std::string const &, masala::base::Size const > >(
					class_name_static(),
					"Example of a deprecated constructor.",
					"dummy_parameter", "A dummy input parameter.",
					"dummy_parameter_2", "Another dummy input parameter"
				)
			);
			deprecated_constructor->add_constructor_annotation(
				masala::make_shared< constructor::constructor_annotation::DeprecatedConstructorAnnotation >(
					"Masala", std::pair< Size, Size >(0, 9), std::pair< Size, Size >(0, 10)
				)
			);
			api_def->add_constructor( deprecated_constructor );
		}

        // Getters:
        api_def->add_getter(
            masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::MolecularGeometryCSP > >(
                "molecular_geometry_shared_ptr",
                "Access the MolecularGeometry object within the MolecularSystem, by shared pointer.",
                "molecular_geometry", "A const shared pointer to the MolecularGeometry object, which stores atoms, atomic geometry, "
                "and chemical connectivity.", false, false,
                std::bind( &MolecularSystem::molecular_geometry_shared_ptr, this )
            )
        );
		{
			getter::MasalaObjectAPIGetterDefinition_OneInputSP< bool, Size > deprecated_fxn(
				masala::make_shared< getter::MasalaObjectAPIGetterDefinition_OneInput< bool, Size > >(
					"deprecated_api_getter", "An example of a deprecated API getter, annotated as such.  Does nothing.",
					"input1", "An input for this function.",
					"output1", "An output parameter for this function.",
					false, false,
					std::bind( &MolecularSystem::deprecated_api_getter, this, std::placeholders::_1 )
				)
			);
			deprecated_fxn->add_getter_annotation(
				masala::make_shared< getter::getter_annotation::DeprecatedGetterAnnotation >(
					"Masala", std::pair< Size, Size >(0, 9), std::pair< Size, Size >(0, 10)
				)
			);
			api_def->add_getter( deprecated_fxn );
		}
        // api_def->add_getter(
        //     masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::MolecularGeometryCWP > >(
        //         "molecular_geometry_weak_ptr",
        //         "Access the MolecularGeometry object within the MolecularSystem, by weak pointer.",
        //         "molecular_geometry", "A const weak pointer to the MolecularGeometry object, which stores atoms, atomic geometry, "
        //         "and chemical connectivity.  Must be converted to a shared pointer before use.", false, false,
        //         std::bind( &MolecularSystem::molecular_geometry_weak_ptr, this )
        //     )
        // );
        // api_def->add_getter(
        //     masala::make_shared< getter::MasalaObjectAPIGetterDefinition_ZeroInput< masala::core::chemistry::MolecularGeometry const & > >(
        //         "molecular_geometry",
        //         "Access the MolecularGeometry object within the MolecularSystem.",
        //         "molecular_geometry", "A const reference to the MolecularGeometry object, which stores atoms, atomic geometry, "
        //         "and chemical connectivity.", false, false,
        //         std::bind( &MolecularSystem::molecular_geometry, this )
        //     )
        // );

        // Setters:
        api_def->add_setter(
            masala::make_shared<
                setter::MasalaObjectAPISetterDefinition_TwoInput<
                    masala::core::chemistry::atoms::AtomInstanceSP const &,
                    std::array< masala::base::Real, 3 > const &
                > 
            > (
                    "add_atom", "Add an atom to this molecular system.",
                    "atom_in", "The atom object to add.  Used directly; not cloned.",
                    "coords", "The atomic coordinates of this atom.",
                    false, false,
                    std::bind( &MolecularSystem::add_atom, this, std::placeholders::_1, std::placeholders::_2 )
            )
        );
		api_def->add_setter(
			masala::make_shared<
				setter::MasalaObjectAPISetterDefinition_ThreeInput<
					masala::core::chemistry::atoms::AtomInstanceCSP const &,
					masala::core::chemistry::atoms::AtomInstanceCSP const &,
					std::string const &
				>
			>(
                "add_bond", "Add a bond to this molecule between two atoms already present in the molecule.",
				"atom1", "The first atom in this molecule that will be connected by the bond.",
				"atom2", "The second atom in this molecule that will be connected by the bond.",
				"bond_type", "The type of chemical bond.  Allowed types are: "
				+ masala::base::enums::list_bond_types( ", ", true ),
				false, false,
				std::bind(
					static_cast<
						void(MolecularSystem::*)(
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							std::string const &
						)
					> (&MolecularSystem::add_bond),
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3
				)
			)
		);
		api_def->add_setter(
			masala::make_shared<
                setter::MasalaObjectAPISetterDefinition_ThreeInput<
					masala::core::chemistry::atoms::AtomInstanceCSP const &,
					masala::core::chemistry::atoms::AtomInstanceCSP const &,
					masala::core::chemistry::bonds::ChemicalBondType const
				>
			>(
				"add_bond", "Add a bond to this molecule between two atoms already present in the molecule.",
				"atom1", "The first atom in this molecule that will be connected by the bond.",
				"atom2", "The second atom in this molecule that will be connected by the bond.",
				"bond_type", "The type of chemical bond, specified by enum.",
				false, false,
				std::bind(
					static_cast<
						void(MolecularSystem::*)(
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							masala::core::chemistry::bonds::ChemicalBondType const
						)
					> (&MolecularSystem::add_bond),
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3
				)
			)
		);
		{
			setter::MasalaObjectAPISetterDefinition_OneInputSP< Size > deprecated_fxn(
				masala::make_shared< setter::MasalaObjectAPISetterDefinition_OneInput< Size > >(
					"deprecated_api_setter", "An example of a deprecated API setter, annotated as such.  Does nothing.",
					"input1", "An input for this function.",
					false, false,
					std::bind( &MolecularSystem::deprecated_api_setter, this, std::placeholders::_1 )
				)
			);
			deprecated_fxn->add_setter_annotation(
				masala::make_shared< setter::setter_annotation::DeprecatedSetterAnnotation >(
					"Masala", std::pair< Size, Size >(0, 9), std::pair< Size, Size >(0, 10)
				)
			);
			api_def->add_setter( deprecated_fxn );
		}

        // Work functions:
        {
			work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInputSP< Size, Real const, bool const > deprecated_fxn(
				masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_TwoInput< Size, Real const, bool const > >(
					"deprecated_api_work_function", "An example of a deprecated API work function, annotated as such.  Does nothing.",
                    false, false, false, false,
					"input1", "A real-valued input for this function.",
					"input2", "A boolean-valued input for this function.",
					"output_val", "An integer-valued output.",
					std::bind( &MolecularSystem::deprecated_api_work_function, this, std::placeholders::_1, std::placeholders::_2 )
				)
			);
			deprecated_fxn->add_work_function_annotation(
				masala::make_shared< work_function::work_function_annotation::DeprecatedWorkFunctionAnnotation >(
					"Masala", std::pair< Size, Size >(0, 9), std::pair< Size, Size >(0, 10)
				)
			);
			api_def->add_work_function( deprecated_fxn );
		}

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
}

} // namespace molecular_system
} // namespace core
} // namespace masala
