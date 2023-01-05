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

	/// @brief Every class can name itself.  Returns "MasalaElementDatabase".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.  Returns
	/// "masala::base::managers::database::elements"
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


}; // class MasalaElementDatabase

} // namespace elements
} // namespace database
} // namespace managers
} // namespace base
} // namesapce masala

#endif //Masala_src_base_managers_database_elements_MasalaElementDatabase_hh