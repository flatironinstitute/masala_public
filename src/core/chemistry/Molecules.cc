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
#include <core/chemistry/atoms/AtomInstanceConstIterator.hh>
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.hh>
#include <core/chemistry/MoleculesConfiguration.hh>
#include <core/initialization/registrators/CoreAtomCoordinateRepresentationRegistrator.hh>

// Base headers:
#include <base/managers/configuration/MasalaConfigurationManager.hh>
#include <base/managers/engine/MasalaDataRepresentationManager.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/error/ErrorHandling.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {

/// @brief Default constructor.
/// @details Gets configuration from configuration manager, which may trigger load from disk.
Molecules::Molecules() :
    masala::base::MasalaObject(),
    configuration_(
        OBTAIN_CONFIGURATION_FROM_CONFIGURATION_MANAGER( Molecules, MoleculesConfiguration )
    )
{}

/// @brief Copy constructor.
/// @details Must be explicitly declared due to mutex.
Molecules::Molecules(
    Molecules const & src
) :
    masala::base::MasalaObject(src)
{
    std::lock_guard< std::mutex > mutexlock( src.whole_object_mutex_ );
    configuration_ = src.configuration_;
    master_atom_coordinate_representation_ = src.master_atom_coordinate_representation_;
    additional_atom_coordinate_representations_ = src.additional_atom_coordinate_representations_;
    atoms_ = src.atoms_;
    bonds_ = src.bonds_;
    // Deliberately do not copy api_definition_.
}

/// @brief Assignment operator.
/// @details Be sure to update this as data are added.
Molecules &
Molecules::operator=(
    Molecules const & src
) {
    { //Scope for lock guard:
        std::lock_guard< std::mutex > lock( whole_object_mutex_ );
        // mutex deliberately not copied.
        configuration_ = src.configuration_;
        master_atom_coordinate_representation_ = src.master_atom_coordinate_representation_;
        master_coordinates_have_changed_ = src.master_coordinates_have_changed_;
        additional_atom_coordinate_representations_ = src.additional_atom_coordinate_representations_;
        atoms_ = src.atoms_;
        bonds_ = src.bonds_;
        // api_definition deliberately not copied.
    }

    make_independent();

    return *this;
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

    masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationCSP old_coordinates( master_atom_coordinate_representation_mutex_locked() );
    master_atom_coordinate_representation_ = old_coordinates->clone();
    std::set< masala::core::chemistry::atoms::AtomInstanceSP > const old_atom_instances( atoms_ );
    atoms_.clear();
    for(
        std::set< masala::core::chemistry::atoms::AtomInstanceSP >::const_iterator it( old_atom_instances.begin() );
        it != old_atom_instances.end();
        ++it
    ) {
        masala::core::chemistry::atoms::AtomInstanceSP new_atom( (*it)->deep_clone() );
        atoms_.insert( new_atom );
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

/// @brief Returns "Molecules".
std::string
Molecules::class_name() const {
    return "Molecules";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry".
std::string
Molecules::class_namespace() const {
    return "masala::core::chemistry";
}

/// @brief Get the API definition for this object.
base::api::MasalaObjectAPIDefinitionCWP
Molecules::get_api_definition() {
    using namespace base::api;
    using namespace base::api::constructor;
    using namespace base::api::getter;

    std::lock_guard< std::mutex > lock( whole_object_mutex_ );

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            std::make_shared< MasalaObjectAPIDefinition >(
                class_name(), class_namespace(),
                "A container for atoms and chemical bonds, and for data representations "
                "that allow efficient geometric manipulations."
            )
        );
        api_def->add_constructor(
            std::make_shared< MasalaObjectAPIConstructorDefinition_ZeroInput< Molecules > >(
                class_name(), "Construct an empty instance of a Molecules object, with no options."
            )
        );
        api_def->add_constructor(
            std::make_shared< MasalaObjectAPIConstructorDefinition_OneInput< Molecules, Molecules const & > >(
                class_name(), "Molecules object copy constructor.",
                "src", "The input Molecules object to copy."
            )
        );

        api_def->add_getter(
            std::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < core::Size > >(
                "total_atoms", "Gets the total number of atoms in this Molecules object.",
                "total_atoms", "The number of atoms in the Molecules object.",
                std::bind( &Molecules::total_atoms, this )
            )
        );
        api_def->add_getter(
            std::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < atoms::AtomInstanceConstIterator > >(
                "atoms_begin", "Get an iterator over atoms, initialized to first atom.",
                "atoms_begin", "Iterator pointing to the first atom in the set stored in the Molecules object.",
                std::bind( &Molecules::atoms_begin, this )
            )
        );
        api_def->add_getter(
            std::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput < atoms::AtomInstanceConstIterator > >(
                "atoms_end", "Get an iterator over atoms, initialized to one past the last atom.",
                "atoms_end", "Iterator pointing one past the last atom in the set stored in the Molecules object.",
                std::bind( &Molecules::atoms_end, this )
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
Molecules::add_atom(
    masala::core::chemistry::atoms::AtomInstanceSP const & atom_in,
    std::array< masala::core::Real, 3 > const & coords
) {
    std::lock_guard< std::mutex > lock( whole_object_mutex_ );

    // Add the atom:
    atoms_.insert(atom_in);
    master_atom_coordinate_representation_mutex_locked()->add_atom_instance( atom_in, coords );

    //TODO update anything that needs to be updated (observers, etc.) when an atom is added.
    //update_additional_representations_from_master();
}

/// @brief Get the number of atoms in this molecule.
core::Size
Molecules::total_atoms() const {
    return atoms_.size();
}

/// @brief Begin const iterator for accessing atoms.
atoms::AtomInstanceConstIterator
Molecules::atoms_begin() const {
    return atoms::AtomInstanceConstIterator( atoms_.cbegin() );
}

/// @brief End const iterator for accessing atoms.
atoms::AtomInstanceConstIterator
Molecules::atoms_end() const {
    return atoms::AtomInstanceConstIterator( atoms_.cend() );
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
Molecules::master_atom_coordinate_representation_mutex_locked() {
    if( master_atom_coordinate_representation_ == nullptr ) {
        masala::core::initialization::registrators::CoreAtomCoordinateRepresentationRegistrator::register_atom_coordinate_representations(); //Make sure that these are registered.
        master_atom_coordinate_representation_ = std::dynamic_pointer_cast< masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentation >(
            masala::base::managers::engine::MasalaDataRepresentationManager::get_instance()->create_data_representation(
                configuration_->default_atom_coordinate_representation()
            )
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
/// class.  This version creates a MoleculesConfiguration object.
base::managers::configuration::ConfigurationBaseCSP
Molecules::load_configuration(
    masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
) const {

    write_to_tracer( "Loading default Molecules configuration." );

    return std::make_shared< MoleculesConfiguration >( passkey );
}

} // namespace chemistry
} // namespace core
} // namespace masala