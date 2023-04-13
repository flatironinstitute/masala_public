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

/// @file src/base/managers/version/MasalaModuleVersionRequirement.cc
/// @brief A class storing a requirement, specified by one Masala module, for
/// the version of another Masala module.
/// @note This class offers no thread-safety.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <base/managers/version/MasalaModuleVersionRequirement.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace managers {
namespace version {


/// @brief Every class can name itself.  This is the static version.
/// @returns "MasalaModuleVersionRequirement".
/*static*/
std::string
MasalaModuleVersionRequirement::class_name_static() {
    return "MasalaModuleVersionRequirement";
}

/// @brief Every class can provide its own namespace.  This is the static version.
/// @returns "masala::base::managers::version".
/*static*/
std::string
MasalaModuleVersionRequirement::class_namespace_static() {
    return "masala::base::managers::version";
}

/// @brief Every class can name itself.
/// @returns "MasalaModuleVersionRequirement".  Calls class_name_static().
std::string
MasalaModuleVersionRequirement::class_name() const {
	return class_name_static();
}

/// @brief Every class can provide its own namespace.
/// @returns "masala::base::managers::version".  Calls class_namespace_static().
std::string
MasalaModuleVersionRequirement::class_namespace() const {
	return class_namespace_static();
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala
