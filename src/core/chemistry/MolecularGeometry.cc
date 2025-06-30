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

/// @file src/core/chemistry/MolecularGeometry.cc
/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/MolecularGeometry.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/chemistry/atoms/AtomInstanceConstIterator.hh>
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.hh>
#include <core/chemistry/MolecularGeometryConfiguration.hh>

// Base headers:
#include <base/enums/ChemicalBondTypeEnum.hh>
#include <base/managers/configuration/MasalaConfigurationManager.hh>
#include <base/managers/engine/MasalaDataRepresentationManager.hh>
#include <base/managers/engine/MasalaDataRepresentationAPI.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_OneInput.tmpl.hh>
#include <base/api/setter/MasalaObjectAPISetterDefinition_ThreeInput.tmpl.hh>

// STL headers:
#include <string>
//#include <iostream> // COMMENT ME OUT -- FOR DEBUGGING ONLY.

namespace masala {
namespace core {
namespace chemistry {

/// @brief Default constructor.
/// @details Gets configuration from configuration manager, which may trigger load from disk.
MolecularGeometry::MolecularGeometry() :
    masala::base::MasalaObject(),
    configuration_(
        OBTAIN_CONFIGURATION_FROM_CONFIGURATION_MANAGER( MolecularGeometry, MolecularGeometryConfiguration )
    )
{
	// std::cout << "**CONSTRUCTING MOLECULAR GEOMETRY**" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
}

/// @brief Copy constructor.
/// @details Must be explicitly declared due to mutex.
MolecularGeometry::MolecularGeometry(
    MolecularGeometry const & src
) :
    masala::base::MasalaObject(src)
{
    // std::cout << "***COPY CONSTRUCTOR LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    std::lock_guard< std::mutex > mutexlock( src.whole_object_mutex_ );
    configuration_ = src.configuration_;
    master_atom_coordinate_representation_ = src.master_atom_coordinate_representation_;
    additional_atom_coordinate_representations_ = src.additional_atom_coordinate_representations_;
    atoms_ = src.atoms_;
    atoms_const_ = src.atoms_const_;
    bonds_ = src.bonds_;
    // Deliberately do not copy api_definition_.
}

/// @brief Assignment operator.
/// @details Be sure to update this as data are added.
MolecularGeometry &
MolecularGeometry::operator=(
    MolecularGeometry const & src
) {
    { //Scope for lock guards:
        // std::cout << "***ASSIGNMENT OPERATOR LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
        std::lock( whole_object_mutex_, src.whole_object_mutex_ );
        std::lock_guard< std::mutex > lock1( whole_object_mutex_, std::adopt_lock );
        std::lock_guard< std::mutex > lock2( src.whole_object_mutex_, std::adopt_lock );
        // mutex deliberately not copied.
        configuration_ = src.configuration_;
        master_atom_coordinate_representation_ = src.master_atom_coordinate_representation_;
        master_coordinates_have_changed_ = src.master_coordinates_have_changed_;
        additional_atom_coordinate_representations_ = src.additional_atom_coordinate_representations_;
        atoms_ = src.atoms_;
        atoms_const_ = src.atoms_const_;
        bonds_ = src.bonds_;
        // api_definition deliberately not copied.
    }

    make_independent();

    return *this;
}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
MolecularGeometrySP
MolecularGeometry::clone() const {
    // std::cout << "***CLONE LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    return masala::make_shared< MolecularGeometry >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
MolecularGeometrySP
MolecularGeometry::deep_clone() const {
    MolecularGeometrySP molecular_geometry_copy;
    {   // Scope for lock guard.
        // std::cout << "***DEEP CLONE LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
        std::lock_guard< std::mutex > whole_object_lock( whole_object_mutex_ );
        molecular_geometry_copy = masala::make_shared< MolecularGeometry >( *this );
    }
    molecular_geometry_copy->make_independent();
    return molecular_geometry_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void
MolecularGeometry::make_independent() {
    // std::cout << "***MAKE INDEPENDENT LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    std::lock_guard< std::mutex > whole_object_lock( whole_object_mutex_ );

    configuration_ = configuration_->deep_clone();

    masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationCSP old_coordinates( master_atom_coordinate_representation_mutex_locked() );
    master_atom_coordinate_representation_ = old_coordinates->clone();
    std::set< masala::core::chemistry::atoms::AtomInstanceSP > const old_atom_instances( atoms_ );
    atoms_.clear();
    atoms_const_.clear();
    for(
        std::set< masala::core::chemistry::atoms::AtomInstanceSP >::const_iterator it( old_atom_instances.begin() );
        it != old_atom_instances.end();
        ++it
    ) {
        masala::core::chemistry::atoms::AtomInstanceSP new_atom( (*it)->deep_clone() );
        atoms_.insert( new_atom );
        atoms_const_.insert( new_atom );
        master_atom_coordinate_representation_mutex_locked()->replace_atom_instance( *it, new_atom );
    }

    std::set< masala::core::chemistry::bonds::ChemicalBondInstanceSP > const old_bonds( bonds_ );
    bonds_.clear();
    for(
        std::set< masala::core::chemistry::bonds::ChemicalBondInstanceSP >::const_iterator it( old_bonds.begin() );
        it != old_bonds.end();
        ++it
    ) {
        bonds_.insert( (*it)->deep_clone() );
    }

    //TODO TODO TODO -- deep-clone additional atom coordinate representations.

    //TODO TODO TODO -- need maps of atoms to bonds and bonds to atoms.
    //Need to clone these appropriately.
}

/// @brief Returns "MolecularGeometry".
std::string
MolecularGeometry::class_name() const {
    return "MolecularGeometry";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry".
std::string
MolecularGeometry::class_namespace() const {
    return "masala::core::chemistry";
}

/// @brief Get the API definition for this object.
base::api::MasalaObjectAPIDefinitionCWP
MolecularGeometry::get_api_definition() {
    using namespace base::api;
    using namespace base::api::constructor;
    using namespace base::api::getter;
    using namespace base::api::setter;

    // std::cout << "***API DEFINITION LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "A container for atoms and chemical bonds, and for data representations "
                "that allow efficient geometric manipulations.",
                false, false
            )
        );

        ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( MolecularGeometry, api_def );

		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_ThreeInput<
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
						void(MolecularGeometry::*)(
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							std::string const &
						)
					> (&MolecularGeometry::add_bond),
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3
				)
			)
		);
		api_def->add_setter(
			masala::make_shared< MasalaObjectAPISetterDefinition_ThreeInput<
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
						void(MolecularGeometry::*)(
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							masala::core::chemistry::atoms::AtomInstanceCSP const &,
							masala::core::chemistry::bonds::ChemicalBondType const
						)
					> (&MolecularGeometry::add_bond),
					this,
					std::placeholders::_1,
					std::placeholders::_2,
					std::placeholders::_3
				)
			)
		);

        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < base::Size > >(
                "total_atoms", "Gets the total number of atoms in this MolecularGeometry object.",
                "total_atoms", "The number of atoms in the MolecularGeometry object.",
                false, false,
                std::bind( &MolecularGeometry::total_atoms, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < atoms::AtomInstanceConstIterator > >(
                "atoms_begin", "Get a const iterator over atoms, initialized to first atom.",
                "atoms_begin", "Iterator pointing to the first atom in the set stored in the MolecularGeometry object.",
                false, false,
                std::bind( &MolecularGeometry::atoms_begin, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < atoms::AtomInstanceConstIterator > >(
                "atoms_end", "Get a const iterator over atoms, initialized to one past the last atom.",
                "atoms_end", "Iterator pointing one past the last atom in the set stored in the MolecularGeometry object.",
                false, false,
                std::bind( &MolecularGeometry::atoms_end, this )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_OneInput < std::array< masala::base::Real, 3 >, atoms::AtomInstanceConstIterator const > >(
                "get_atom_coordinates", "Get the coordinates of a particular atom in a molecular geometry object.",
                "atom_iterator", "An AtomInstanceConstIterator pointing to the atom whose coordinates we wish to obtain.",
                "coordinates", "A 3-vector containing the x, y, and z coordinates of the atom.",
                false, false,
                std::bind( &MolecularGeometry::get_atom_coordinates, this, std::placeholders::_1 )
            )
        );
        api_def->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_OneInput< bool, masala::core::chemistry::atoms::AtomInstanceCSP const & > >(
                "has_atom", "Check whether an atom exists in this object.  Returns true if it does, false otherwise.",
                "atom", "The atom which may or may not be in this object.",
                "present", "True if atom is present in the object; false otherwise.",
                false, false, std::bind( &MolecularGeometry::has_atom, this, std::placeholders::_1 )
            )
        );

        api_definition_ = api_def; // Nonconst to const.
    }
    return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add an atom to this molecule.
void
MolecularGeometry::add_atom(
    masala::core::chemistry::atoms::AtomInstanceSP const & atom_in,
    std::array< masala::base::Real, 3 > const & coords
) {
    // std::cout << "***ADD ATOM LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );

    // Add the atom:
    atoms_.insert(atom_in);
    atoms_const_.insert(atom_in);
    master_atom_coordinate_representation_mutex_locked()->add_atom_instance( atom_in, coords );

    //TODO update anything that needs to be updated (observers, etc.) when an atom is added.
    //update_additional_representations_from_master();
}

/// @brief Get the number of atoms in this molecule.
base::Size
MolecularGeometry::total_atoms() const {
    return atoms_.size();
}

/// @brief Begin const iterator for accessing atoms.
atoms::AtomInstanceConstIterator
MolecularGeometry::atoms_begin() const {
    return atoms::AtomInstanceConstIterator( atoms_const_.cbegin() );
}

/// @brief End const iterator for accessing atoms.
atoms::AtomInstanceConstIterator
MolecularGeometry::atoms_end() const {
    return atoms::AtomInstanceConstIterator( atoms_const_.cend() );
}

/// @brief Access the coordinates for an atom.
std::array< masala::base::Real, 3 >
MolecularGeometry::get_atom_coordinates(
    atoms::AtomInstanceConstIterator const atom_iterator
) const {
    // std::cout << "**GET ATOM COORDINATE LOCK*** this=" << this << " master_atom_coordinate_representation_.get()=" << master_atom_coordinate_representation_.get() << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );
    return master_atom_coordinate_representation_->get_atom_coordinates( atom_iterator.ptr() );
}

/// @brief Add a bond to this molecule, with the bond type specified by string.
void
MolecularGeometry::add_bond(
	masala::core::chemistry::atoms::AtomInstanceCSP const & first_atom,
	masala::core::chemistry::atoms::AtomInstanceCSP const & second_atom,
	std::string const & bond_type_string
) {
	using namespace core::chemistry::bonds;
	ChemicalBondType const bond_type( masala::base::enums::bond_type_from_string( bond_type_string ) );
	CHECK_OR_THROW_FOR_CLASS( bond_type != ChemicalBondType::INVALID_CHEMICAL_BOND_TYPE, "add_bond",
		"The string \"" + bond_type_string + "\" could not be parsed as a valid bond type."
	);
	add_bond( first_atom, second_atom, bond_type );
}

/// @brief Add a bond to this molecule.
void
MolecularGeometry::add_bond(
    masala::core::chemistry::atoms::AtomInstanceCSP const & first_atom,
    masala::core::chemistry::atoms::AtomInstanceCSP const & second_atom,
    masala::core::chemistry::bonds::ChemicalBondType const bond_type
) {
    // std::cout << "***ADD BOND LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );
    CHECK_OR_THROW_FOR_CLASS(
        atoms_const_.count( first_atom ) != 0, "add_bond",
        "The first atom for this chemical bond was not found in the molecular geometry object."
    );
    CHECK_OR_THROW_FOR_CLASS(
        atoms_const_.count( second_atom ) != 0, "add_bond",
        "The second atom for this chemical bond was not found in the molecular geometry object."
    );
    CHECK_OR_THROW_FOR_CLASS(
        !has_bond_mutex_locked( first_atom, second_atom ), "add_bond",
        "The molecular geometry object already has a bond between the specified atoms."
    )
    bonds_.insert(
        masala::make_shared< masala::core::chemistry::bonds::ChemicalBondInstance >(
			first_atom, second_atom, bond_type
        )
    );
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the master coordinate representation.
/// @details Creates the representation from options if necessary.
/// @note For nonconst access. Use with care!  Avoid:
/// - Holding on to this owning pointer past a single manipulation or set of manipulations.
/// - Calling this from multiple threads.  This function does not lock the object mutex!  It should
/// only be called from locked contexts!
core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP
MolecularGeometry::master_atom_coordinate_representation_mutex_locked() {
    if( master_atom_coordinate_representation_ == nullptr ) {
        master_atom_coordinate_representation_ = std::dynamic_pointer_cast< masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentation >(
            masala::base::managers::engine::MasalaDataRepresentationManager::get_instance()->create_data_representation(
                configuration_->default_atom_coordinate_representation()
            )->get_inner_data_representation_object()
        );
        CHECK_OR_THROW_FOR_CLASS( master_atom_coordinate_representation_ != nullptr, "master_atom_coordinate_representation", configuration_->default_atom_coordinate_representation() + " was not an AtomCoordinateRepresentation!" );
    }
    return master_atom_coordinate_representation_;
}

/// @brief Create a configuration object for this object.
/// @details Can trigger read from disk.  Private since it intended to be called only the first time
/// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
/// implementation throws.  Must be implemented by derived classes that have configurations.
/// @note Receives an instance of a MasalaConfigurationManagerAuthorization object.  Since this has a
/// private constructor, it can only be instantiated by the MasalaConfigurationManager, its only friend
/// class.  This version creates a MolecularGeometryConfiguration object.
base::managers::configuration::ConfigurationBaseCSP
MolecularGeometry::load_configuration(
    masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
) const {

    write_to_tracer( "Loading default MolecularGeometry configuration." );

    return masala::make_shared< MolecularGeometryConfiguration >( passkey );
}

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Check whether an atom exists in this object.
/// @returns True if the atom exists, false otherwise.
bool
MolecularGeometry::has_atom(
    masala::core::chemistry::atoms::AtomInstanceCSP const & atom
) const {
    // std::cout << "***HAS ATOM LOCK***" << std::endl; // COMMENT ME OUT -- FOR DEBUGGING ONLY.
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );
    return (atoms_const_.count( atom ) != 0);
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Does a bond exist between two atoms?
/// @details Intended to be called from a mutex-locked context.
bool
MolecularGeometry::has_bond_mutex_locked(
	masala::core::chemistry::atoms::AtomInstanceCSP const & atom1,
	masala::core::chemistry::atoms::AtomInstanceCSP const & atom2
) const {
	for( auto const & bond : bonds_ ) {
		if( (*bond) == std::make_pair( atom1, atom2 ) ) { return true; }
	}
	return false;
}

} // namespace chemistry
} // namespace core
} // namespace masala