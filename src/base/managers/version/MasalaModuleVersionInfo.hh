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

/// @file src/base/managers/version/MasalaModuleVersionInfo.hh
/// @brief Headers for a class storing version information and requirements for one Masala module.
/// @note This class offers no thread-safety.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_version_MasalaModuleVersionInfo_hh
#define Masala_src_base_managers_version_MasalaModuleVersionInfo_hh

// Forward declarations:
#include <base/managers/version/MasalaModuleVersionInfo.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/types.hh>
#include <base/managers/version/MasalaModuleVersionRequirement.fwd.hh>

// STL headers:
#include <string>
#include <utility>
#include <set>

namespace masala {
namespace base {
namespace managers {
namespace version {

/// @brief A class storing version information and requirements for one Masala module.
/// @note This class offers no thread-safety.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaModuleVersionInfo : masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaModuleVersionInfo() = default;

	/// @brief Initialization constructor.
	MasalaModuleVersionInfo(
		std::string const & library_name,
		std::pair< masala::base::Size, masala::base::Size > const & version
	);

	/// @brief Copy constructor, defaulted.
	MasalaModuleVersionInfo( MasalaModuleVersionInfo const & ) = default;
	
	/// @brief Assignment operator, defaulted.
	MasalaModuleVersionInfo &
	operator=(
		MasalaModuleVersionInfo const &
	) = default;

	/// @brief Virtual destructor.
	~MasalaModuleVersionInfo() override = default;

	/// @brief Every class can name itself.  This is the static version.
	/// @returns "MasalaModuleVersionInfo".
	static std::string class_name_static();

	/// @brief Every class can provide its own namespace.  This is the static version.
	/// @returns "masala::base::managers::version".
	static std::string class_namespace_static();

	/// @brief Every class can name itself.
	/// @returns "MasalaModuleVersionInfo".  Calls class_name_static().
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
	/// @returns "masala::base::managers::version".  Calls class_namespace_static().
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Set the library name.
	void
	set_library_name(
		std::string const & library_name
	);

	/// @brief Get the library name.
	std::string const &
	library_name() const;

	/// @brief Set the major and minor version numbers, by a pair of <major, minor>.
	void
	set_major_and_minor_version(
		std::pair< masala::base::Size, masala::base::Size > const & version
	);

	/// @brief Set the major and minor version numbers.
	void
	set_major_and_minor_version(
		masala::base::Size const major_version,
		masala::base::Size const minor_version
	);

	/// @brief Set the major verison.
	void
	set_major_version(
		masala::base::Size const major_version
	);

	/// @brief Set the minor verison.
	void
	set_minor_version(
		masala::base::Size const minor_version
	);

	/// @brief Get the major version.
	masala::base::Size
	major_version() const;

	/// @brief Get the minor version.
	masala::base::Size
	minor_version() const;

	/// @brief Get the major and minor version as a pair of <major, minor>.
	std::pair< masala::base::Size, masala::base::Size >
	version() const;

	/// @brief Get a string of "<major version>.<minor version>".
	/// @note Somewhat expensive.  Generated for each call.
	std::string
	version_string() const;

	/// @brief Indicate that another module is required, with no minimum or maximum version
	/// for that other module.  Not really recommended.
	/// @param[in] other_module_name The name of the required library.
	/// @param[in] other_module_not_loaded_message An optional message to display if the required
	/// library is not loaded.
	void
	add_requirement(
		std::string const & other_module_name,
		std::string const & other_module_not_loaded_message = ""
	);

	/// @brief Indicate that another module may be required, with a minimum version
	/// for that other module if it is present.
	/// @param[in] other_module_name The name of the library that may or may not be required.
	/// @param[in] other_module_is_required True if we throw an error if this library is not loaded, and
	/// false if we're only checking the version if it happens to be loaded.
	/// @param[in] other_module_min_version The minimum version required for the other library, as a pair
	/// of <major version, minor version>.
	/// @param[in] other_module_not_loaded_message An optional message to display if the required
	/// library is not loaded.  Only used if other_module_is_required is true.
	/// @param[in] other_module_below_min_version_message An optional message to display if the other
	/// library is below the minimum version.
	void
	add_requirement_with_minimum_version(
		std::string const & other_module_name,
		bool const other_module_is_required,
		std::pair< masala::base::Size, masala::base::Size > const & other_module_min_version,
		std::string const & other_module_not_loaded_message = "",
		std::string const & other_module_below_min_version_message = ""
	);

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
	add_requirement_with_maximum_version(
		std::string const & other_module_name,
		bool const other_module_is_required,
		std::pair< masala::base::Size, masala::base::Size > const & other_module_max_version,
		std::string const & other_module_not_loaded_message = "",
		std::string const & other_module_above_max_version_message = ""
	);

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
	add_requirement_with_minimum_and_maximum_version(
		std::string const & other_module_name,
		bool const other_module_is_required,
		std::pair< masala::base::Size, masala::base::Size > const & other_module_min_version,
		std::pair< masala::base::Size, masala::base::Size > const & other_module_max_version,
		std::string const & other_module_not_loaded_message = "",
		std::string const & other_module_below_min_version_message = "",
		std::string const & other_module_above_max_version_message = ""
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief Name of the library.
	std::string library_name_;

	/// @brief The major version number.
	masala::base::Size major_version_ = 1;

	/// @brief The minor version number.
	masala::base::Size minor_version_ = 0;

	/// @brief A bunch of optional version requirements.
	/// @details This allows one module to indicate that another module is required, and possibly has
	/// a minimum or maximum required version.
	std::set< MasalaModuleVersionRequirementCSP > version_requirements_;


}; // class MasalaModuleVersionInfo

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_version_MasalaModuleVersionInfo_tmpl_hh