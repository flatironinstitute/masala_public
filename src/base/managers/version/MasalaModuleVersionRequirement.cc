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
#include <base/managers/version/MasalaModuleVersionInfo.hh>
#include <base/error/ErrorHandling.hh>
#include <base/utility/container/container_util.tmpl.hh>

namespace masala {
namespace base {
namespace managers {
namespace version {

/// @brief Constructor to specify another module as required WITHOUT specifying any
/// minimum or maximum version requirement for that module.  Not really recommended.
/// @details Sets other_module_must_be_loaded_ to true.
MasalaModuleVersionRequirement::MasalaModuleVersionRequirement(
    std::string const & other_module_name,
    std::string const & other_module_not_loaded_message /*= ""*/
) :
    masala::base::MasalaObject(),
    other_module_name_( other_module_name ),
    other_module_must_be_loaded_( true ),
    min_version_specified_( false ),
    max_version_specified_( false ),
    min_version_( std::make_pair( 0, 0 ) ),
    max_version_( std::make_pair( 0, 0 ) ),
    required_module_not_loaded_message_( other_module_not_loaded_message ),
    below_min_version_message_(""),
    above_max_version_message_("")
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
    bool const set_minimum_version /*=true*/,
    std::string const & other_module_not_loaded_message /*=""*/,
    std::string const & message_for_below_min_or_above_max_version /*=""*/
) :
    masala::base::MasalaObject(),
    other_module_name_( other_module_name ),
    other_module_must_be_loaded_( other_module_must_be_loaded ),
    min_version_specified_( set_minimum_version ),
    max_version_specified_( !set_minimum_version ),
    min_version_( set_minimum_version ? min_or_max_version : std::pair< masala::base::Size, masala::base::Size >( 0, 0 ) ),
    max_version_( set_minimum_version ? std::pair< masala::base::Size, masala::base::Size >( 0, 0 ) : min_or_max_version ),
    required_module_not_loaded_message_( other_module_not_loaded_message ),
    below_min_version_message_( set_minimum_version ? message_for_below_min_or_above_max_version : "" ),
    above_max_version_message_( set_minimum_version ? "" : message_for_below_min_or_above_max_version )
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
    std::pair< masala::base::Size, masala::base::Size > const & max_version,
    std::string const & other_module_not_loaded_message /*=""*/,
    std::string const & below_min_version_message /*=""*/,
    std::string const & above_max_version_message /*=""*/
) :
    masala::base::MasalaObject(),
    other_module_name_( other_module_name ),
    other_module_must_be_loaded_( other_module_must_be_loaded ),
    min_version_specified_( true ),
    max_version_specified_( true ),
    min_version_( min_version ),
    max_version_( max_version ),
    required_module_not_loaded_message_( other_module_not_loaded_message ),
    below_min_version_message_( below_min_version_message ),
    above_max_version_message_( above_max_version_message )
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


/// @brief Given a set of MasalaModuleVersionInfo objects, check that this requirement is satisfied.
/// @param version_info_map A map containing a bunch of other MasalaModuleVersionInfo objects.
/// @param this_version_info Address of MasalaModuleVersionInfo object to skip.
/// @param messages If the requirements are NOT satisfied, this string will have messages appended to it.
/// @returns True if requirements are satisfied, false otherwise.
bool
MasalaModuleVersionRequirement::check_version_requirements_satisfied(
    std::unordered_map< std::string, MasalaModuleVersionInfoCSP > const & version_info_map,
    MasalaModuleVersionInfo const * this_version_info,
    std::string & messages
) const {
    bool satisfied( true );
    bool required_module_is_loaded( !other_module_must_be_loaded_ );
    bool module_has_greater_than_eq_min_version( !min_version_specified_ );
    bool module_has_less_than_eq_max_version( !max_version_specified_ );

    for(
        std::unordered_map< std::string, MasalaModuleVersionInfoCSP >::const_iterator it( version_info_map.begin() );
        it != version_info_map.end();
        ++it
    ) {
        MasalaModuleVersionInfo const & other_version_info( *(it->second) );
        if( this_version_info == &other_version_info ) {
            continue;
        }

        if( other_version_info.library_name() == other_module_name_ ) {
            // Check whether required modules are loaded.
            if( other_module_must_be_loaded_ ) {
                required_module_is_loaded = true;
            }
            
            // Check whether other module is less than min version.
            if( min_version_specified_ && version_lt( other_version_info.version(), min_version_ ) ) {
                module_has_greater_than_eq_min_version = false;
            }

            // Check whether other module is greater than max version.
            if( max_version_specified_ && version_gt( other_version_info.version(), max_version_ ) ) {
                module_has_less_than_eq_max_version = false;
            }
        }
    }

    if( other_module_must_be_loaded_ && !required_module_is_loaded ) {
        satisfied = false;
        if( !messages.empty() ) {
            messages += "\n";
        }
        messages += "\tLibrary \"" + other_module_name_ + "\" is required by library \""
            + this_version_info->library_name() + "\" version " + this_version_info->version_string()
            + ".";
        if( !required_module_not_loaded_message_.empty() ) {
            messages += "  " + required_module_not_loaded_message_;
        }
    }

    if( min_version_specified_ && !module_has_greater_than_eq_min_version ) {
        satisfied = false;
        if( !messages.empty() ) {
            messages += "\n";
        }
        messages += "\tLibrary \"" + other_module_name_ + "\" must have at least version "
            + std::to_string( min_version_.first ) + "." + std::to_string( min_version_.second )
            + ", as specified by library \""
            + this_version_info->library_name() + "\" version " + this_version_info->version_string()
            + ".";
        if( !below_min_version_message_.empty() ) {
            messages += "  " + below_min_version_message_;
        }
    }

    if( max_version_specified_ && !module_has_less_than_eq_max_version ) {
        satisfied = false;
        if( !messages.empty() ) {
            messages += "\n";
        }
        messages += "\tLibrary \"" + other_module_name_ + "\" must have at most version "
            + std::to_string( max_version_.first ) + "." + std::to_string( max_version_.second )
            + ", as specified by library \""
            + this_version_info->library_name() + "\" version " + this_version_info->version_string()
            + ".";
        if( !above_max_version_message_.empty() ) {
            messages += "  " + above_max_version_message_;
        }
    }

    return satisfied;
}

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala
