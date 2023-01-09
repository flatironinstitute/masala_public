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

/// @file src/base/managers/environment/MasalaEnvironmentVariable.cc
/// @brief A class storing one environment variable.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <base/managers/environment/MasalaEnvironmentVariable.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace managers {
namespace environment {

/// @brief Options constructor.
/// @details Private, to allow creation only by the environment manager.
MasalaEnvironmentVariable::MasalaEnvironmentVariable(
	bool const env_var_is_set,
	std::string const & env_var_value
) :
	env_var_is_set_( env_var_is_set ),
	env_var_value_( env_var_is_set ? env_var_value : "" )
{}


/// @brief Every class can name itself.
/// @returns "MasalaEnvironmentVariable".
std::string
MasalaEnvironmentVariable::class_name() const {
	return "MasalaEnvironmentVariable";
}

/// @brief Every class can provide its own namespace.
/// @returns "masala::base::managers::environment".
std::string
MasalaEnvironmentVariable::class_namespace() const {
	return "masala::base::managers::environment";
}

/// @brief Get whether the environment variable was set.
bool
MasalaEnvironmentVariable::env_var_was_set() const {
	return env_var_is_set_;
}

/// @brief Get the value of the environment variable.
std::string const &
MasalaEnvironmentVariable::env_var_value() const {
	CHECK_OR_THROW_FOR_CLASS( env_var_is_set_, "env_var_value", "Attempted to access an environment variable's value that was not set!" );
	return env_var_value_;
}

} // namesapce environment
} // namesapce managers
} // namespace base
} // namesapce masala
