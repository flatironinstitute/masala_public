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

/// @file src/core/chemistry/Molecules.hh
/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_Molecules_hh
#define Masala_src_core_chemistry_Molecules_hh

// Forward declarations:
#include <core/chemistry/Molecules.fwd.hh>

// Core headers:
#include <core/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.fwd.hh>
#include <core/chemistry/bonds/ChemicalBondInstance.fwd.hh>
#include <core/chemistry/MoleculesConfiguration.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/configuration/ConfigurationBase.fwd.hh>

// STL headers:
#include <array>
#include <set>
#include <vector>
#include <map>
#include <mutex>

namespace masala {
namespace core {
namespace chemistry {

/// @brief A class contiaining a collection of atoms and chemical bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Molecules : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    /// @details Gets configuration from configuration manager, which may trigger load from disk.
    Molecules();

    /// @brief Copy constructor.
    /// @details Must be explicitly declared due to mutex.
    Molecules( Molecules const & src );

    /// @brief Default destructor.
    ~Molecules() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    MoleculesSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    /// @details Threadsafe.  Be sure to update this function whenever a private member is added!
    virtual
    MoleculesSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "Molecules".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "core::chemistry".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Add an atom to this molecule.
    void
    add_atom(
        masala::core::chemistry::atoms::AtomInstanceSP const & atom_in,
        std::array< masala::core::Real, 3 > const & coords
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the master coordinate representation.
    /// @details Creates the representation from options if necessary.
    /// @note For nonconst access. Use with care!  Avoid:
    /// - Holding on to this owning pointer past a single manipulation or set of manipulations.
    /// - Calling this from multiple threads.  This function does not lock the object mutex!  It should
    /// only be called from locked contexts!
    masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP
    master_atom_coordinate_representation_mutex_locked();

	/// @brief Create a configuration object for this object.
	/// @details Can trigger read from disk.  Private since it intended to be called only the first time
	/// that configuration settings are requested, by the MasalaConfigurationManager.  The base class
	/// implementation throws.  Must be implemented by derived classes that have configurations.
	/// @note Receives an instance of a MasalaConfigurationManagerAuthorization object.  Since this has a
	/// private constructor, it can only be instantiated by the MasalaConfigurationManager, its only friend
	/// class.  This version creates a MoleculesConfiguration object.
	base::managers::configuration::ConfigurationBaseCSP
	load_configuration(
		base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey
	) const override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex for locking a whole molecules object.
    mutable std::mutex whole_object_mutex_;

    /// @brief Configuration for this object.
    MoleculesConfigurationCSP configuration_;

    /// @brief The representation of the atom coordinates.
    /// @details Different calculators might need atoms represented in different ways, internally (e.g.
    /// matrices of coordinates, etc.)  Different subclasses of the AtomCoordinateRepresentation class
    /// store the data differently, but all offer iterators to access atom coordinates.
    /// @note This is the MASTER representation.  All other representations either update this
    /// representation, or are updated by this representation.  Be sure to use master_atom_coordinate_representation()
    /// internally, since this does a check for whether it's necessary to create the master representation.
    masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP master_atom_coordinate_representation_;

    /// @brief Have the master coordinates changed?
    bool master_coordinates_have_changed_ = false;

    /// @brief Additional representations of atom coordinates.
    std::vector< masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP > additional_atom_coordinate_representations_;

    /// @brief The atoms themselves and their properties.
    /// @details The Molecules container is responsible for keeping these linked to the
    /// AtomCoordinateRepresentation.
    /// @note This is deliberately a set and not a vector to prevent an arbitrary index
    /// from being handed out or used for atoms.  Iterators are properly used to iterate
    /// over all atoms, and pointers to access a particular atom.  This also allows more
    /// efficient insertions and deletions of atoms.  AtomCoordinateRepresentations are
    /// responsible for keeping track of coordinates given atom smart pointers.
    std::set< masala::core::chemistry::atoms::AtomInstanceSP > atoms_;

    /// @brief The bonds between atoms.
    /// @note This is deliberately a set and not a vector to prevent an arbitrary index
    /// from being handed out or used for bonds.  Iterators are properly used to iterate
    /// over all bonds, and pointers to access a particular bonds.  This also allows more
    /// efficient insertions and deletions of bonds.
    std::set< masala::core::chemistry::bonds::ChemicalBondInstanceSP > bonds_;

};

} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_Molecules_hh