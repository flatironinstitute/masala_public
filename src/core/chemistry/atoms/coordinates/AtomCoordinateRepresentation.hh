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

/// @file src/core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh
/// @brief A base class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @note This class is not intended to be instantiated outside of the API definition system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh
#define Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh

// Forward declarations:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.fwd.hh>

// Core headers:
#include <base/types.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentation.hh>

// STL headers:
#include <set>
#include <array>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {


/// @brief A base class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient.
/// @note This class is not intended to be instantiated outside of the API definition system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomCoordinateRepresentation : public masala::base::managers::engine::MasalaDataRepresentation {

	typedef masala::base::managers::engine::MasalaDataRepresentation Parent;
	typedef masala::base::managers::engine::MasalaDataRepresentationSP ParentSP;
	typedef masala::base::managers::engine::MasalaDataRepresentationCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    AtomCoordinateRepresentation() = default;

    /// @brief Copy constructor.  Explicit due to mutex.
    AtomCoordinateRepresentation( AtomCoordinateRepresentation const & src );

    // Destructor.
    ~AtomCoordinateRepresentation() override = default;

	/// @brief Clone operation: make a copy of this object and return a shared pointer
	/// to the copy.
	virtual
	AtomCoordinateRepresentationSP
	clone() const;

	/// @brief Deep clone operation: make a deep copy of this object and return a shared
	/// pointer to the deep copy.
	AtomCoordinateRepresentationSP
	deep_clone() const;

	/// @brief Returns "AtomCoordinateRepresentation".
	std::string
	class_name() const override;

	/// @brief Returns "masala::core::chemistry::atoms::coordinates".
	std::string
	class_namespace() const override;

	/// @brief Make this object instance fully independent.
	void
	make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PLUGIN CLASS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the categories for this plugin.
	/// @returns {{ "AtomCoordinateRepresentation" }}
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin.
	/// @returns { "atom_coordinate_representation" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief Get the categories for this DataRepresentation.
	/// @returns {{ "AtomCoordinateRepresentation" }}
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the keywords that this data representation plugin has.
	/// @details Categories are hierarchical, with the hierarchy represented as a vector of
	/// strings.  One data representation category can be classified into multiple categories.
	/// @returns { "atom_coordinate_representation" }
	std::vector< std::string >
	get_data_representation_keywords() const override;

	/// @brief Get the compatible engines for this data representation.
	/// @returns Currently an empty list.  This may change in the future.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the properties of this data representation.
	/// @returns { "atom_coordinate_representation" }
	std::vector< std::string >
	get_present_data_representation_properties() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


    /// @brief Replace an atom instance with a new one.
    /// @details Used for deep cloning, since the AtomCoordinateRepresentation does not itself
    /// implement a deep_clone() function.
    /// @note Must be implemented by derived classes.
    virtual
    void
    replace_atom_instance(
        AtomInstanceCSP const & old_instance,
        AtomInstanceCSP const & new_instance
    );

    /// @brief Add an atom.
    /// @note Must be implemented by derived classes.
    virtual
    void
    add_atom_instance(
        AtomInstanceCSP const & new_atom,
        std::array< masala::base::Real, 3 > const & new_atom_coordinates
    );

    /// @brief Get the coordinates of an atom.
    /// @note Must be implemented by derived classes.
    virtual
    std::array< masala::base::Real, 3 >
    get_atom_coordinates(
        AtomInstanceCSP const & atom
    ) const;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API DEFINITION GETTER
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get an object describing the API for this object.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is this data representation empty?
	/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
	/// @returns True if no data have been loaded into this data representation, false otherwise.
	/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
	bool
	protected_empty() const override;

	/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
	/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
	void
	protected_clear() override;

	/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
	/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
	void
	protected_reset() override;

	/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
	/// by derived classses.  Performs no mutex-locking.
	void
	protected_make_independent() override;

	/// @brief Assign src to this.  Performs no mutex-locking.
	void
	protected_assign(
		masala::base::managers::engine::MasalaDataRepresentation const & src
	) override;

	/// @brief Let derived classes access the API definition.  Could be nullptr.
	inline masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition() { return api_definition_; }

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

};

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_coordinates_AtomCoordinateRepresentation_hh