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

/// @file src/base/managers/database/elements/MasalaElementDatabase.cc
/// @brief A base class for all Masala objects.
/// @details Masala objects all define certain functions, such as write_to_tracer(),
/// class_name(), and class_namespace().
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <base/managers/database/elements/MasalaElementDatabase.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/utility/string/string_manipulation.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace database {
namespace elements {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Public constructor.
/// @details Requires authorization key; can only be constructed by the MasalaDatabaseManager.
MasalaElementDatabase::MasalaElementDatabase(
    base::managers::database::MasalaDatabaseManagerCreationKey const & /*key*/,
    std::string const & database_path
) :
    base::MasalaObject()
{
    initialize( database_path );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Every class can name itself.  Returns "MasalaElementDatabase".
	std::string MasalaElementDatabase::class_name() const { return "MasalaElementDatabase"; }

	/// @brief Every class can provide its own namespace.  Returns
	/// "masala::base::managers::database::elements"
	std::string MasalaElementDatabase::class_namespace() const { return "masala::base::managers::database::elements"; }

/// @brief Given the abbreviation of an element (e.g. "Ca" for calcium), get its full data.
/// @param[in] abbreviation The short name for an element, with standard capitalization
/// (e.g. "Ca", "Au", "C", "Zn").
/// @returns A const shared pointer to the ElementType object for that element.
ElementTypeCSP
MasalaElementDatabase::element_type_from_abbreviation(
    std::string const & abbreviation
) const {
    std::map< std::string, ElementTypeCSP >::const_iterator it( canonical_elements_by_abbreviation_.find( abbreviation ) );
    CHECK_OR_THROW_FOR_CLASS(
        it != canonical_elements_by_abbreviation_.end(),
        "element_type_from_abbreviation",
        "Could not find an element with abbreviation \"" + abbreviation + "\"."
    );
    return it->second;
}

/// @brief Given the abbreviation of an element in upper case (e.g. "CA" for calcium), get
/// its full data.
/// @param[in] abbreviation The short name for an element, in uppercase (e.g. "CA", "AU",
/// "C", "ZN").
/// @returns A const shared pointer to the ElementType object for that element.
ElementTypeCSP
MasalaElementDatabase::element_type_from_ucase_abbreviation(
    std::string const & abbreviation
) const {
    std::string const ucase_abbreviation( base::utility::string::to_uppercase(abbreviation) );
    std::map< std::string, ElementTypeCSP >::const_iterator it( canonical_elements_by_ucase_abbreviation_.find( ucase_abbreviation ) );
    CHECK_OR_THROW_FOR_CLASS(
        it != canonical_elements_by_ucase_abbreviation_.end(),
        "element_type_from_abbreviation",
        "Could not find an element with upper-case abbreviation \"" + ucase_abbreviation + "\"."
    );
    return it->second;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Initialize this object from the Masala database.
/// @details Triggers read from disk!
void
MasalaElementDatabase::initialize(
	std::string const & database_path
) {
    std::string const elements_path( database_path + "/chemistry/elements/elements.json" );
    write_to_tracer( "Initializing Masala element database from \"" + elements_path + "\"." );
    write_to_tracer( "Completed initialization of Masala element database." );
}

} // namespace elements
} // namespace database
} // namespace managers
} // namespace base
} // namesapce masala
