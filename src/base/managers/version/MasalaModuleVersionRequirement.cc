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

/// @brief Constructor to specify another module as required WITHOUT specifying any
/// minimum or maximum version requirement for that module.  Not really recommended.
/// @details Sets other_module_must_be_loaded_ to true.
MasalaModuleVersionRequirement::MasalaModuleVersionRequirement(
    std::string const & other_module_name
) :
    masala::base::MasalaObject(),
    other_module_name_( other_module_name ),
    other_module_must_be_loaded_( true ),
    min_version_specified_( false ),
    max_version_specified_( false ),
    min_version_( std::make_pair( 0, 0 ) ),
    max_version_( std::make_pair( 0, 0 ) )
{
    CHECK_OR_THROW(
        !other_module_name_.empty(),
        class_namespace_static() + "::" + class_name_static(),
        "MasalaModuleVersionRequirement",
        "The other module name cannot be empty!"
    );
}

/// @brief Constructor with minimum OR maximum version (but not both).
/// @details If set_minimum_version is true, we set the minimum version; otherwise we set the maximum.
MasalaModuleVersionRequirement::MasalaModuleVersionRequirement(
    std::string const & other_module_name,
    bool const other_module_must_be_loaded,
    std::pair< masala::base::Size, masala::base::Size > const & min_or_max_version,
    bool const set_minimum_version = true
) :
    masala::base::MasalaObject(),
    other_module_name_( other_module_name ),
    other_module_must_be_loaded_( other_module_must_be_loaded ),
    min_version_specified_( set_minimum_version ),
    max_version_specified_( !set_minimum_version ),
    min_version_( set_minimum_version ? min_or_max_version : std::make_pair( 0, 0 ) ),
    max_version_( set_minimum_version ? std::make_pair( 0, 0 ) : min_or_max_version )
{
    CHECK_OR_THROW(
        !other_module_name_.empty(),
        class_namespace_static() + "::" + class_name_static(),
        "MasalaModuleVersionRequirement",
        "The other module name cannot be empty!"
    );
}

/// @brief Constructor with minimum AND maximum version.
MasalaModuleVersionRequirement::MasalaModuleVersionRequirement(
    std::string const & other_module_name,
    bool const other_module_must_be_loaded,
    std::pair< masala::base::Size, masala::base::Size > const & min_version,
    std::pair< masala::base::Size, masala::base::Size > const & max_version
) :
    masala::base::MasalaObject(),
    other_module_name_( other_module_name ),
    other_module_must_be_loaded_( other_module_must_be_loaded ),
    min_version_specified_( true ),
    max_version_specified_( true ),
    min_version_( min_version ),
    max_version_( max_version )
{
    CHECK_OR_THROW(
        !other_module_name_.empty(),
        class_namespace_static() + "::" + class_name_static(),
        "MasalaModuleVersionRequirement",
        "The other module name cannot be empty!"
    );
}

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
