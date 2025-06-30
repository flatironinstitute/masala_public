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

/// @file src/base/managers/version/version_requirement/MasalaModuleVersionRequirement.hh
/// @brief Headers for a class storing a requirement, specified by one Masala module, for
/// the version of another Masala module.
/// @note This class offers no thread-safety.  It should only be instantiated by a MasalaModuleVersionInfo object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_version_version_requirement_MasalaModuleVersionRequirement_hh
#define Masala_src_base_managers_version_version_requirement_MasalaModuleVersionRequirement_hh

// Forward declarations:
#include <base/managers/version/version_requirement/MasalaModuleVersionRequirement.fwd.hh>

// Base headers:
#include <base/managers/version/MasalaModuleVersionInfo.fwd.hh>
#include <base/MasalaObject.hh>
#include <base/types.hh>

// STL headers:
#include <string>
#include <utility>
#include <unordered_map>
#include <vector>

namespace masala {
namespace base {
namespace managers {
namespace version {
namespace version_requirement {

/// @brief Headers for a class storing a requirement, specified by one Masala module, for
/// the version of another Masala module.
/// @note This class offers no thread-safety.  It should only be instantiated by a MasalaModuleVersionInfo object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaModuleVersionRequirement : masala::base::MasalaObject {

public:

	/// @brief Default constructor, deleted.
	MasalaModuleVersionRequirement() = delete;

	/// @brief Constructor to specify another module as required WITHOUT specifying any
	/// minimum or maximum version requirement for that module.  Not really recommended.
	/// @details Sets other_module_must_be_loaded_ to true.
	MasalaModuleVersionRequirement(
		std::string const & other_module_name,
		std::string const & other_module_not_loaded_message = ""
	);

	/// @brief Constructor with minimum OR maximum version (but not both).
	/// @details If set_minimum_version is true, we set the minimum version; otherwise we set the maximum.
	MasalaModuleVersionRequirement(
		std::string const & other_module_name,
		bool const other_module_must_be_loaded,
		std::pair< masala::base::Size, masala::base::Size > const & min_or_max_version,
		bool const set_minimum_version = true,
		std::string const & other_module_not_loaded_message = "",
		std::string const & message_for_below_min_or_above_max_version = ""
	);

	/// @brief Constructor with minimum AND maximum version.
	MasalaModuleVersionRequirement(
		std::string const & other_module_name,
		bool const other_module_must_be_loaded,
		std::pair< masala::base::Size, masala::base::Size > const & min_version,
		std::pair< masala::base::Size, masala::base::Size > const & max_version,
		std::string const & other_module_not_loaded_message = "",
		std::string const & below_min_version_message = "",
		std::string const & above_max_version_message = ""
	);

	/// @brief Copy constructor, defaulted.
	MasalaModuleVersionRequirement( MasalaModuleVersionRequirement const & ) = default;
	
	/// @brief Assignment operator, defaulted.
	MasalaModuleVersionRequirement &
	operator=(
		MasalaModuleVersionRequirement const &
	) = default;

	/// @brief Virtual destructor.
	~MasalaModuleVersionRequirement() override = default;

	/// @brief Every class can name itself.  This is the static version.
	/// @returns "MasalaModuleVersionRequirement".
	static std::string class_name_static();

	/// @brief Every class can provide its own namespace.  This is the static version.
	/// @returns "masala::base::managers::version::version_requirement".
	static std::string class_namespace_static();

	/// @brief Every class can name itself.
	/// @returns "MasalaModuleVersionRequirement".  Calls class_name_static().
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
	/// @returns "masala::base::managers::version::version_requirement".  Calls class_namespace_static().
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given a set of MasalaModuleVersionInfo objects, check that this requirement is satisfied.
	/// @param version_info_map A map containing a bunch of other MasalaModuleVersionInfo objects.
	/// @param this_version_info Address of MasalaModuleVersionInfo object to skip.
	/// @param messages If the requirements are NOT satisfied, this string will have messages appended to it.
	/// @returns True if requirements are satisfied, false otherwise.
	bool
	check_version_requirements_satisfied(
		std::unordered_map< std::string, MasalaModuleVersionInfoCSP > const & version_info_map,
		MasalaModuleVersionInfo const * this_version_info,
		std::string & messages
	) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns true if ver1 is less than ver2, false otherwise.
	static
	bool
	version_lt(
		std::pair< masala::base::Size, masala::base::Size > ver1,
		std::pair< masala::base::Size, masala::base::Size > ver2
	);

	/// @brief Returns true if ver1 is greater than ver2, false otherwise.
	static
	bool
	version_gt(
		std::pair< masala::base::Size, masala::base::Size > ver1,
		std::pair< masala::base::Size, masala::base::Size > ver2
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief The module for which we're imposing a version requirement.
	std::string other_module_name_;

	/// @brief Must the other module exist / be loaded?
	bool other_module_must_be_loaded_ = false;

	/// @brief Are we requiring that the version be greater than or equal to some cutoff?
	bool min_version_specified_ = false;

	/// @brief Are we requiring that the version be less than or equal to some cutoff?
	bool max_version_specified_ = false;

	/// @brief The minimum version, as a pair of <major, minor>.
	std::pair< masala::base::Size, masala::base::Size > min_version_ = std::make_pair( 0, 0 );

	/// @brief The maximum version, as a pair of <major, minor>.
	std::pair< masala::base::Size, masala::base::Size > max_version_ = std::make_pair( 0, 0 );

	/// @brief An optional message to be displayed if a requred module is not loaded.
	std::string required_module_not_loaded_message_;

	/// @brief An optional message to be displayed if a module has less than the specified minimum version.
	std::string below_min_version_message_;

	/// @brief An optional message to be displayed if a module has more than the specified maximum verson.
	std::string above_max_version_message_;

}; // class MasalaModuleVersionRequirement

} // namespace version_requirement
} // namespace version
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_version_version_requirement_MasalaModuleVersionRequirement_hh