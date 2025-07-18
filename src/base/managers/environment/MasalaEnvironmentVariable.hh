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

/// @file src/base/managers/environment/MasalaEnvironmentVariable.hh
/// @brief Headers for a class storing one environment variable.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_environment_MasalaEnvironmentVariable_hh
#define Masala_src_base_managers_environment_MasalaEnvironmentVariable_hh

// Forward declarations:
#include <base/managers/environment/MasalaEnvironmentVariable.fwd.hh>

// Base headers:
#include <base/managers/environment/MasalaEnvironmentManager.fwd.hh>
#include <base/MasalaObject.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace environment {

/// @brief A class storing one environment variable.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEnvironmentVariable : masala::base::MasalaObject {

	friend class masala::base::managers::environment::MasalaEnvironmentManager;

private:

	/// @brief Default constructor, deleted.
	MasalaEnvironmentVariable() = delete;

	/// @brief Options constructor.
	/// @details Private, to allow creation only by the environment manager.
	MasalaEnvironmentVariable(
		bool const env_var_is_set,
		std::string const & env_var_value
	);

public:

	/// @brief Copy constructor, deleted.
	MasalaEnvironmentVariable( MasalaEnvironmentVariable const & ) = delete;
	
	/// @brief Assignment operator, deleted.
	void operator=( MasalaEnvironmentVariable const & ) = delete;

	/// @brief Virtual destructor.
	~MasalaEnvironmentVariable() override = default;

	/// @brief Every class can name itself.
	/// @returns "MasalaEnvironmentVariable".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
	/// @returns "masala::base::managers::environment".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get whether the environment variable was set.
	bool
	env_var_was_set() const;

	/// @brief Get the value of the environment variable.
	std::string const &
	env_var_value() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief Has the environment variable been set?
	bool const env_var_is_set_ = false;

	/// @brief The value of the environment variable.
	std::string const env_var_value_;

}; // class MasalaEnvironmentVariable

} // namespace environment
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_environment_MasalaEnvironmentVariable_tmpl_hh