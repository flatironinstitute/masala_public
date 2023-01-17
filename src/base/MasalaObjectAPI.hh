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

/// @file src/base/MasalaObjectAPI.hh
/// @brief A base class for all Masala derived API classes.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_MasalaObjectAPI_hh
#define Masala_src_base_MasalaObjectAPI_hh

// Forward declarations:
#include <base/MasalaObjectAPI.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace masala {
namespace base {

/// @brief A base class for Masala API derived classes.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPI : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaObjectAPI() = default;

	/// @brief Copy constructor.
	MasalaObjectAPI( MasalaObjectAPI const & ) = default;

	/// @brief Destructor.
	virtual ~MasalaObjectAPI() = default;

public:

	/// @brief Get the name of the class for which this class provides an API.
	/// @details Must be implemented by derived classes.
	virtual
    std::string
    inner_class_name() const = 0;

    /// @brief Get the namespace of the class for which this class provides an API.
	/// @details Must be implemented by derived classes.
	virtual
    std::string
    inner_class_namespace() const = 0;

    /// @brief Get the API definition for the contained class.
    /// @details Must be implemented by derived classes.
    virtual
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition_for_inner_class() = 0;

}; // class MasalaObjectAPI

} // namespace base
} // namespace masala

#endif //Masala_src_base_MasalaObjectAPI_hh