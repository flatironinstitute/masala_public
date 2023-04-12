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

// STL headers:

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

	/// @brief Copy constructor, defaulted.
	MasalaModuleVersionInfo( MasalaModuleVersionInfo const & ) = default;
	
	/// @brief Assignment operator, defaulted.
	void operator=( MasalaModuleVersionInfo const & ) = default;

	/// @brief Virtual destructor.
	~MasalaModuleVersionInfo() override = default;

	/// @brief Every class can name itself.
	/// @returns "MasalaModuleVersionInfo".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
	/// @returns "masala::base::managers::version".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////


}; // class MasalaModuleVersionInfo

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_version_MasalaModuleVersionInfo_tmpl_hh