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
    base::managers::database::MasalaDatabaseManagerCreationKey const & /*key*/
) :
    base::MasalaObject()
{}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Every class can name itself.  Returns "MasalaElementDatabase".
	std::string MasalaElementDatabase::class_name() const { return "MasalaElementDatabase"; }

	/// @brief Every class can provide its own namespace.  Returns
	/// "masala::base::managers::database::elements"
	std::string MasalaElementDatabase::class_namespace() const { return "masala::base::managers::database::elements"; }

} // namespace elements
} // namespace database
} // namespace managers
} // namespace base
} // namesapce masala
