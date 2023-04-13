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

/// @file src/base/managers/version/MasalaModuleVersionInfo.cc
/// @brief A class storing version information and requirements for one Masala module.
/// @note This class offers no thread-safety.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <base/managers/version/MasalaModuleVersionInfo.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace managers {
namespace version {


/// @brief Every class can name itself.
/// @returns "MasalaModuleVersionInfo".
std::string
MasalaModuleVersionInfo::class_name() const {
	return "MasalaModuleVersionInfo";
}

/// @brief Every class can provide its own namespace.
/// @returns "masala::base::managers::version".
std::string
MasalaModuleVersionInfo::class_namespace() const {
	return "masala::base::managers::version";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Set the library name.
void
MasalaModuleVersionInfo::set_library_name(
    std::string const & library_name
) {
    CHECK_OR_THROW_FOR_CLASS( !library_name.empty(), "set_library_name", "The library name cannot be empty." );
    library_name_ = library_name;
}

/// @brief Get the library name.
std::string const &
MasalaModuleVersionInfo::library_name() const {
    return library_name_;
}

/// @brief Set the major and minor version numbers, by a pair of <major, minor>.
void
MasalaModuleVersionInfo::set_major_and_minor_version(
    std::pair< masala::base::Size, masala::base::Size > const & version
) {
    major_version_ = version.first;
    minor_version_ = version.second;
}

/// @brief Set the major and minor version numbers.
void
MasalaModuleVersionInfo::set_major_and_minor_version(
    masala::base::Size const major_version,
    masala::base::Size const minor_version
) {
    major_version_ = major_version;
    minor_version_ = minor_version;
}

/// @brief Set the major verison.
void
MasalaModuleVersionInfo::set_major_version(
    masala::base::Size const major_version
) {
    major_version_= major_version;
}

/// @brief Set the minor verison.
void
MasalaModuleVersionInfo::set_minor_version(
    masala::base::Size const minor_version
) {
    minor_version_ = minor_version;
}

/// @brief Get the major version.
masala::base::Size
MasalaModuleVersionInfo::major_version() const {
    return major_version_;
}

/// @brief Get the minor version.
masala::base::Size
MasalaModuleVersionInfo::minor_version() const {
    return minor_version_;
}

/// @brief Get the major and minor version as a pair of <major, minor>.
std::pair< masala::base::Size, masala::base::Size >
MasalaModuleVersionInfo::version() const {
    return std::make_pair( major_version_, minor_version_ );
}

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala
