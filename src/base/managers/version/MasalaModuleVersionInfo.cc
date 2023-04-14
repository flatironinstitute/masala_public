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
#include <base/managers/version/MasalaModuleVersionRequirement.hh>

namespace masala {
namespace base {
namespace managers {
namespace version {


/// @brief Initialization constructor.
MasalaModuleVersionInfo::MasalaModuleVersionInfo(
    std::string const & library_name,
    std::pair< masala::base::Size, masala::base::Size > const & version
) :
    masala::base::MasalaObject(),
    library_name_( library_name ),
    major_version_( version.first ),
    minor_version_( version.second )
{
    CHECK_OR_THROW(
        !library_name_.empty(),
        class_namespace_static() + "::" + class_name_static(),
        "MasalaModuleVersionInfo",
        "The library name cannot be empty!"
    );
}

/// @brief Every class can name itself.  This is the static version.
/// @returns "MasalaModuleVersionInfo".
/*static*/
std::string
MasalaModuleVersionInfo::class_name_static() {
    return "MasalaModuleVersionInfo";
}

/// @brief Every class can provide its own namespace.  This is the static version.
/// @returns "masala::base::managers::version".
/*static*/
std::string
MasalaModuleVersionInfo::class_namespace_static() {
    return "masala::base::managers::version";
}

/// @brief Every class can name itself.
/// @returns "MasalaModuleVersionInfo".  Calls class_name_static().
std::string
MasalaModuleVersionInfo::class_name() const {
	return class_name_static();
}

/// @brief Every class can provide its own namespace.
/// @returns "masala::base::managers::version".  Calls class_namespace_static().
std::string
MasalaModuleVersionInfo::class_namespace() const {
	return class_namespace_static();
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

/// @brief Get a string of "<major version>.<minor version>".
/// @note Somewhat expensive.  Generated for each call.
std::string
MasalaModuleVersionInfo::version_string() const {
    return std::to_string( major_version_ ) + "." + std::to_string(minor_version_); 
}

/// @brief Indicate that another module is required, with no minimum or maximum version
/// for that other module.  Not really recommended.
/// @param[in] other_module_name The name of the required library.
/// @param[in] other_module_not_loaded_message An optional message to display if the required
/// library is not loaded.
void
MasalaModuleVersionInfo::add_requirement(
    std::string const & other_module_name,
    std::string const & other_module_not_loaded_message /*=""*/
) {
    CHECK_OR_THROW_FOR_CLASS( !other_module_name.empty(), "add_requirement",
        "The other module name cannot be empty!"
    );
    version_requirements_.insert(
        std::make_shared< MasalaModuleVersionRequirement >( other_module_name, other_module_not_loaded_message )
    );
}

/// @brief Indicate that another module may be required, with a minimum version
/// for that other module if it is present.
void
MasalaModuleVersionInfo::add_requirement_with_minimum_version(
    std::string const & other_module_name,
    bool const other_module_is_required,
    std::pair< masala::base::Size, masala::base::Size > const & other_module_min_version,
    std::string const & other_module_not_loaded_message /*=""*/,
    std::string const & other_module_below_min_version_message /*=""*/
) {
    CHECK_OR_THROW_FOR_CLASS( !other_module_name.empty(), "add_requirement_with_minimum_version",
        "The other module name cannot be empty!"
    );
    version_requirements_.insert(
        std::make_shared< MasalaModuleVersionRequirement >(
            other_module_name,
            other_module_is_required,
            other_module_min_version,
            true,
            other_module_not_loaded_message,
            other_module_below_min_version_message
        )
    );
}

/// @brief Indicate that another module may be required, with a maximum version
/// for that other module if it is present.
/// @param[in] other_module_name The name of the library that may or may not be required.
/// @param[in] other_module_is_required True if we throw an error if this library is not loaded, and
/// false if we're only checking the version if it happens to be loaded.
/// @param[in] other_module_max_version The maximum version required for the other library, as a pair
/// of <major version, minor version>.
/// @param[in] other_module_not_loaded_message An optional message to display if the required
/// library is not loaded.  Only used if other_module_is_required is true.
/// @param[in] other_module_above_max_version_message An optional message to display if the other
/// library is above the maximum version.
void
MasalaModuleVersionInfo::add_requirement_with_maximum_version(
    std::string const & other_module_name,
    bool const other_module_is_required,
    std::pair< masala::base::Size, masala::base::Size > const & other_module_max_version,
    std::string const & other_module_not_loaded_message /*=""*/,
    std::string const & other_module_above_max_version_message /*=""*/
) {
    CHECK_OR_THROW_FOR_CLASS( !other_module_name.empty(), "add_requirement_with_maximum_version",
        "The other module name cannot be empty!"
    );
    version_requirements_.insert(
        std::make_shared< MasalaModuleVersionRequirement >(
            other_module_name,
            other_module_is_required,
            other_module_max_version,
            false,
            other_module_not_loaded_message,
            other_module_above_max_version_message
        )
    );
}

/// @brief Indicate that another module may be required, with a minimum and maximum version
/// for that other module if it is present.
/// @param[in] other_module_name The name of the library that may or may not be required.
/// @param[in] other_module_is_required True if we throw an error if this library is not loaded, and
/// false if we're only checking the version if it happens to be loaded.
/// @param[in] other_module_min_version The minimum version required for the other library, as a pair
/// of <major version, minor version>.
/// @param[in] other_module_max_version The maximum version required for the other library, as a pair
/// of <major version, minor version>.
/// @param[in] other_module_not_loaded_message An optional message to display if the required
/// library is not loaded.  Only used if other_module_is_required is true.
/// @param[in] other_module_below_min_version_message An optional message to display if the other
/// library is below the minimum version.
/// @param[in] other_module_above_max_version_message An optional message to display if the other
/// library is above the maximum version.
void
MasalaModuleVersionInfo::add_requirement_with_minimum_and_maximum_version(
    std::string const & other_module_name,
    bool const other_module_is_required,
    std::pair< masala::base::Size, masala::base::Size > const & other_module_min_version,
    std::pair< masala::base::Size, masala::base::Size > const & other_module_max_version,
    std::string const & other_module_not_loaded_message /*=""*/,
    std::string const & other_module_below_min_version_message /*=""*/,
    std::string const & other_module_above_max_version_message /*=""*/
) {
    CHECK_OR_THROW_FOR_CLASS( !other_module_name.empty(), "add_requirement_with_minimum_and_maximum_version",
        "The other module name cannot be empty!"
    );
    version_requirements_.insert(
        std::make_shared< MasalaModuleVersionRequirement >(
            other_module_name,
            other_module_is_required,
            other_module_min_version,
            other_module_max_version,
            other_module_not_loaded_message,
            other_module_below_min_version_message,
            other_module_above_max_version_message
        )
    );
}

/// @brief Given a set of MasalaModuleVersionInfo objects, check that all of the requirements
/// stored in this object are satisfied.
/// @param version_info_map A map containing a bunch of other MasalaModuleVersionInfo objects.  This
/// object may be included, in which case it is skipped.
/// @param messages If the requirements are NOT satisfied, this string will have messages appended to it.
/// @returns True if requirements are satisfied, false otherwise.
bool
MasalaModuleVersionInfo::check_version_requirements_satisfied(
    std::unordered_map< std::string, MasalaModuleVersionInfoCSP > const & version_info_map,
    std::string & messages
) const {
    std::string new_messages;
    bool satisfied(true);
    // Loop through all requirements:
    for( auto const & requirement : version_requirements_ ) {
        satisfied &= requirement->check_version_requirements_satisfied( version_info_map, new_messages );
    }
    if( !satisfied ) {
        messages += "\n" + new_messages;
    }
    return satisfied;
}

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala
