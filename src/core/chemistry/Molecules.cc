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

/// @file src/core/chemistry/Molecules.cc
/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/Molecules.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.hh>
#include <core/chemistry/MoleculesConfiguration.hh>

// Base headers:
#include <base/managers/configuration/MasalaConfigurationManager.hh>

// STL headers:
#include <string>

namespace core {
namespace chemistry {

/// @brief Default constructor.
/// @details Gets configuration from configuration manager, which may trigger load from disk.
Molecules::Molecules() :
    base::MasalaObject(),
    configuration_( std::dynamic_pointer_cast< MoleculesConfiguration const >( base::managers::configuration::MasalaConfigurationManager::get_instance()->get_configuration_settings(*this) ) )
{}

/// @brief Copy constructor.
/// @details Must be explicitly declared due to mutex.
Molecules::Molecules(
    Molecules const & src
) :
    base::MasalaObject(src)
{
    std::lock_guard< std::mutex > mutexlock( src.whole_object_mutex_ );
    configuration_ = src.configuration_;
    master_atom_coordinate_representation_ = src.master_atom_coordinate_representation_;
    additional_atom_coordinate_representations_ = src.additional_atom_coordinate_representations_;
    atoms_ = src.atoms_;
    bonds_ = src.bonds_;
}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
MoleculesSP
Molecules::clone() const {
    std::lock_guard< std::mutex > whole_object_lock( whole_object_mutex_ );
    return std::make_shared< Molecules >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
MoleculesSP
Molecules::deep_clone() const {
    MoleculesSP molecules_copy;
    {   // Scope for lock guard.
        std::lock_guard< std::mutex > whole_object_lock( whole_object_mutex_ );
        molecules_copy = std::make_shared< Molecules >( *this );
    }
    molecules_copy->make_independent();
    return molecules_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void
Molecules::make_independent() {
    std::lock_guard< std::mutex > whole_object_lock( whole_object_mutex_ );

    configuration_ = configuration_->deep_clone();

    core::chemistry::atoms::coordinates::AtomCoordinateRepresentationCSP old_coordinates( master_atom_coordinate_representation_ );
    master_atom_coordinate_representation_ = old_coordinates->clone();
    std::set< core::chemistry::atoms::AtomInstanceSP > const old_atom_instances( atoms_ );
    atoms_.clear();
    for(
        std::set< core::chemistry::atoms::AtomInstanceSP >::const_iterator it( old_atom_instances.begin() );
        it != old_atom_instances.end();
        ++it
    ) {
        core::chemistry::atoms::AtomInstanceSP new_atom( (*it)->deep_clone() );
        atoms_.insert( new_atom );
        master_atom_coordinate_representation_->replace_atom_instance( *it, new_atom );
    }

    std::set< core::chemistry::bonds::ChemicalBondInstanceSP > const old_bonds( bonds_ );
    bonds_.clear();
    for(
        std::set< core::chemistry::bonds::ChemicalBondInstanceSP >::const_iterator it( old_bonds.begin() );
        it != old_bonds.end();
        ++it
    ) {
        bonds_.insert( (*it)->deep_clone() );
    }

    //TODO TODO TODO -- deep-clone additional atom coordinate representations.

    //TODO TODO TODO -- need maps of atoms to bonds and bonds to atoms.
    //Need to clone these appropriately.
}

/// @brief Returns "Molecules".
std::string
Molecules::class_name() const {
    return "Molecules";
}

/// @brief Every class can provide its own namespace.  This returns "core::chemistry".
std::string
Molecules::class_namespace() const {
    return "core::chemistry";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add an atom to this molecule.
void
Molecules::add_atom(
    core::chemistry::atoms::AtomInstanceSP const & atom_in,
    std::array< core::Real, 3 > const & coords
) {
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );
    //TODO: Ensure up-to-date.
    // if( master_atom_coordinate_representation_ == nullptr ) {
    //     create_master_atom_coordinate_representation();
    // }

    // Add the atom:
    atoms_.insert(atom_in);
    master_atom_coordinate_representation_->add_atom_instance( atom_in, coords );

    //TODO update anything that needs to be updated (observers, etc.) when an atom is added.
    //update_additional_representations_from_master();
}

} // namespace chemistry
} // namespace core