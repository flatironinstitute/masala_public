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

/// @file src/base/managers/database/elements/MasalaElementDatabase.hh
/// @brief Headers for a class stored within the MasalaDatabaseManager, which
/// manages element data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_database_elements_MasalaElementDatabase_hh
#define Masala_src_base_managers_database_elements_MasalaElementDatabase_hh

// Forward declarations:
#include <base/managers/database/elements/MasalaElementDatabase.fwd.hh>

// Parent headers:
#include <base/MasalaObject.hh>

// Base headers:
#include <base/managers/database/MasalaDatabaseManagerCreationKey.fwd.hh>
#include <base/managers/database/elements/ElementType.fwd.hh>

// STL headers:
#include <vector>
#include <string>
#include <map>

namespace masala {
namespace base {
namespace managers {
namespace database {
namespace elements {

/// @brief Headers for a class stored within the MasalaDatabaseManager, which
/// manages element data.
/// @note Can only be created by the MasalaDatabaseManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaElementDatabase : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor, explicitly deleted.
	MasalaElementDatabase() = delete;

	/// @brief Public constructor.
	/// @details Requires authorization key; can only be constructed by the MasalaDatabaseManager.
	MasalaElementDatabase( base::managers::database::MasalaDatabaseManagerCreationKey const & key );

	/// @brief Copy constructor.
	MasalaElementDatabase( MasalaElementDatabase const & ) = delete;

	/// @brief Destructor.
	~MasalaElementDatabase() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Every class can name itself.  Returns "MasalaElementDatabase".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.  Returns
	/// "masala::base::managers::database::elements"
	std::string class_namespace() const override;

	/// @brief Given the abbreviation of an element (e.g. "Ca" for calcium), get its full data.
	/// @param[in] abbreviation The short name for an element, with standard capitalization
	/// (e.g. "Ca", "Au", "C", "Zn").
	/// @returns A const shared pointer to the ElementType object for that element.
	ElementTypeCSP element_type_from_abbreviation( std::string const & abbreviation ) const;

	/// @brief Given the abbreviation of an element in upper case (e.g. "CA" for calcium), get
	/// its full data.
	/// @param[in] abbreviation The short name for an element, in uppercase (e.g. "CA", "AU",
	/// "C", "ZN").
	/// @returns A const shared pointer to the ElementType object for that element.
	ElementTypeCSP element_type_from_ucase_abbreviation( std::string const & abbreviation ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Initialize this object from the Masala database.
	/// @details Triggers read from disk!
	void initialize();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The standard elements, indexed by atomic number.
	/// @note Vectors are indexed from zero, but elements start at atomic number 1 (hydrogen).
	/// For this reason, entry zero in this vector is a special, "unknown" element.
	std::vector< ElementTypeCSP > canonical_elements_;

	/// @brief A map of standard element abbreviations (e.g. "Ca", "Au", "C", "Zn") to ElementType
	/// objects storing information about those elements.
	/// @details Includes "Unk" for unknown.
	std::map< std::string, ElementTypeCSP > canonical_elements_by_abbreviation_;

	/// @brief A map of uppercase element abbreviations (e.g. "CA", "AU", "C", "ZN") to ElementType
	/// objects storing information about those elements.
	/// @details Includes "UNK" for unknown.
	std::map< std::string, ElementTypeCSP > canonical_elements_by_ucase_abbreviation_;

}; // class MasalaElementDatabase

} // namespace elements
} // namespace database
} // namespace managers
} // namespace base
} // namesapce masala

#endif //Masala_src_base_managers_database_elements_MasalaElementDatabase_hh