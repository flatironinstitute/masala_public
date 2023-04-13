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

// STL headers:
#include <string>
#include <utility>

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
	void operator=( MasalaModuleVersionInfo const & ) = default;

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


}; // class MasalaModuleVersionInfo

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_version_MasalaModuleVersionInfo_tmpl_hh