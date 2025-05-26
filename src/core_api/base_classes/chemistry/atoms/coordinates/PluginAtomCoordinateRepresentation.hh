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

/// @file src/core/chemistry/atoms/coordinates/PluginAtomCoordinateRepresentation.hh
/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient,
/// to be implemented in plugin libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_chemistry_atoms_coordinates_PluginAtomCoordinateRepresentation_hh
#define Masala_src_core_api_base_classes_chemistry_atoms_coordinates_PluginAtomCoordinateRepresentation_hh

// Forward declarations:
#include <core_api/base_classes/chemistry/atoms/coordinates/PluginAtomCoordinateRepresentation.fwd.hh>

// Parent headers:
#include <core/chemistry/atoms/coordinates/AtomCoordinateRepresentation.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace chemistry {
namespace atoms {
namespace coordinates {


/// @brief A pure virtual base class class for the container of a collection of atom
/// coordinates, represented in a manner that can make manipulations very efficient,
/// to be implemented in plugin libraries.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginAtomCoordinateRepresentation : public masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentation {

	typedef masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentation Parent;
	typedef masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP ParentSP;
	typedef masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	PluginAtomCoordinateRepresentation() = default;

	/// @brief Copy constructor.
	PluginAtomCoordinateRepresentation( PluginAtomCoordinateRepresentation const & ) = default;

	// Destructor.
	~PluginAtomCoordinateRepresentation() override = default;

	/// @brief Clone operation: make a copy of this object and return a shared pointer
	/// to the copy.  Must be implemented by derived classes.
	masala::core::chemistry::atoms::coordinates::AtomCoordinateRepresentationSP
	clone() const override = 0;

	/// @brief Get the class name.  Must be implemented by derived classes.
	std::string class_name() const override = 0;

	/// @brief Get the class namespace.  Must be implemented by derived classes.
	std::string class_namespace() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PLUGIN CLASS FUNCTIONS -- MUST BE IMPLEMENTED BY DERIVED CLASSES.
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the categories for this plugin.
	/// @returns {{ "AtomCoordinateRepresentation" }}
	std::vector< std::vector< std::string > >
	get_categories() const override = 0;

	/// @brief Get the keywords for this plugin.
	/// @returns { "atom_coordinate_representation" }
	std::vector< std::string >
	get_keywords() const override = 0;

	/// @brief Get the categories for this DataRepresentation.
	/// @returns {{ "AtomCoordinateRepresentation" }}
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override = 0;

	/// @brief Get the keywords that this data representation plugin has.
	/// @details Categories are hierarchical, with the hierarchy represented as a vector of
	/// strings.  One data representation category can be classified into multiple categories.
	/// @returns { "atom_coordinate_representation" }
	std::vector< std::string >
	get_data_representation_keywords() const override = 0;

	/// @brief Get the compatible engines for this data representation.
	/// @returns Currently an empty list.  This may change in the future.
	std::vector< std::string >
	get_compatible_masala_engines() const override = 0;

	/// @brief Get the properties of this data representation.
	/// @returns { "atom_coordinate_representation" }
	std::vector< std::string >
	get_present_data_representation_properties() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS -- MUST BE IMPLEMENTED BY DERIVED CLASSES
////////////////////////////////////////////////////////////////////////////////


	/// @brief Replace an atom instance with a new one.
	/// @details Used for deep cloning, since the PluginAtomCoordinateRepresentation does not itself
	/// implement a deep_clone() function.
	/// @note Must be implemented by derived classes.
	void
	replace_atom_instance(
		masala::core::chemistry::atoms::AtomInstanceCSP const & old_instance,
		masala::core::chemistry::atoms::AtomInstanceCSP const & new_instance
	) override = 0;

	/// @brief Add an atom.
	/// @note Must be implemented by derived classes.
	void
	add_atom_instance(
		masala::core::chemistry::atoms::AtomInstanceCSP const & new_atom,
		std::array< masala::base::Real, 3 > const & new_atom_coordinates
	) override = 0;

	/// @brief Get the coordinates of an atom.
	/// @note Must be implemented by derived classes.
	virtual
	std::array< masala::base::Real, 3 >
	get_atom_coordinates(
		masala::core::chemistry::atoms::AtomInstanceCSP const & atom
	) const override = 0;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API DEFINITION GETTER -- MUST BE IMPLEMENTED BY DERIVED CLASSES
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get an object describing the API for this object.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override = 0;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is this data representation empty?
	/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
	/// @returns True if no data have been loaded into this data representation, false otherwise.
	/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
	bool
	protected_empty() const override = 0;

	/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
	/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
	void
	protected_clear() override = 0;

	/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
	/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
	void
	protected_reset() override = 0;

	/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
	/// by derived classses.  Performs no mutex-locking.
	void
	protected_make_independent() override = 0;

	/// @brief Assign src to this.  Performs no mutex-locking.
	void
	protected_assign(
		masala::base::managers::engine::MasalaDataRepresentation const & src
	) override = 0;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

};

} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_chemistry_atoms_coordinates_PluginAtomCoordinateRepresentation_hh