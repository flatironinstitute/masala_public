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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreterAPI.fwd.hh
/// @brief Headers for a base class for all Masala file interpreter APIs.
/// @details Derived file interpreter subclasses have API classes derived from this.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_file_interpreter_MasalaFileInterpreterAPI_hh
#define Masala_src_base_managers_file_interpreter_MasalaFileInterpreterAPI_hh

// Forward declarations:
#include <base/managers/file_interpreter/MasalaFileInterpreterAPI.fwd.hh>

// Base headers:
#include <base/managers/file_interpreter/MasalaFileInterpreter.fwd.hh>
#include <base/managers/plugin_module/MasalaPluginAPI.hh>

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

/// @brief A base class for all Masala file interpreter APIs.
/// @details Derived file interpreter subclasses have API classes derived from this.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaFileInterpreterAPI : public masala::base::managers::plugin_module::MasalaPluginAPI {

public:

	/// @brief Default constructor.
	MasalaFileInterpreterAPI() = default;

	/// @brief Copy constructor.
	MasalaFileInterpreterAPI( MasalaFileInterpreterAPI const & ) = default;

	/// @brief Destructor.
	virtual ~MasalaFileInterpreterAPI() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Access the inner file interpreter object.
    /// @details Implemented by derived classes.
    /// @note Use this function with care!  Holding a shared pointer to the inner
    /// object can nullify the thread safety that the API object provides.
    virtual
    MasalaFileInterpreterSP
    get_inner_file_interpreter_object() = 0;

    /// @brief Access the inner file interpreter object (const access).
    /// @details Implemented by derived classes.
    /// @note Use this function with care!  Holding a const shared pointer to the inner
    /// object can nullify the thread safety that the API object provides.
    virtual
    MasalaFileInterpreterCSP
    get_inner_file_interpreter_object_const() const = 0;

}; // class MasalaFileInterpreterAPI

} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_file_interpreter_MasalaFileInterpreterAPI_hh