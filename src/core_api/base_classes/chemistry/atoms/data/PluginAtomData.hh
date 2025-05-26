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

/// @file src/core_api/base_classes/chemistry/atoms/data/PluginAtomData.hh
/// @brief Headers for a container for additional optional data that might be
/// attached to an atom.
/// @details Note that this is a pure virtual base class for plugin
/// atom data containers.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_chemistry_atoms_data_PluginAtomData_hh
#define Masala_src_core_api_base_classes_chemistry_atoms_data_PluginAtomData_hh

// Forward declarations:
#include <core_api/base_classes/chemistry/atoms/data/PluginAtomData.fwd.hh>

// Core headers:
#include <core/chemistry/atoms/data/AtomData.hh>

// Base headers:

// STL headers:

namespace masala {
namespace core_api {
namespace base_classes {
namespace chemistry {
namespace atoms {
namespace data {


/// @brief A container for additional optional data that might be
/// attached to an atom.
/// @details Note that this is a pure virtual base class for plugin
/// atom data containers.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PluginAtomData : public masala::core::chemistry::atoms::data::AtomData {

    typedef masala::core::chemistry::atoms::data::AtomData Parent;
    typedef masala::core::chemistry::atoms::data::AtomDataSP ParentSP;
    typedef masala::core::chemistry::atoms::data::AtomDataCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    PluginAtomData() = default;

    /// @brief Copy constructor.
    PluginAtomData( PluginAtomData const & src ) = default;

    /// @brief Default destructor.
    ~PluginAtomData() override = default;

	/// @brief Get the class name.  Must be implemented by derived classes.
	std::string class_name() const override = 0;

	/// @brief Get the class namespace.  Must be implemented by derived classes.
	std::string class_namespace() const override = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.
	/// @details Must be implemented by derived classes.  Derived classes should ensure that
    /// this appends to the AtomData::get_categories() output (which returns {{"AtomData"}}.
	std::vector< std::vector< std::string > >
	get_categories() const override = 0;

	/// @brief Get the keywords for this plugin class.
	/// @details Must be implemented by derived classes.  Derived classes should ensure that
    /// this appends to the AtomData::get_keywords() output (which returns {"atom_data"});
	std::vector< std::string >
	get_keywords() const override = 0;

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Make this object independent by making a deep copy of all of its private members.
	/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
	void
	protected_make_independent() override;

	/// @brief Assign src to this.
	/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
	/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
	void
	protected_assign( masala::core::chemistry::atoms::data::AtomData const & src ) override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

};

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_chemistry_atoms_data_PluginAtomData_hh