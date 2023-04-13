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

/// @file src/base/managers/version/MasalaModuleVersionRequirement.hh
/// @brief Headers for a class storing a requirement, specified by one Masala module, for
/// the version of another Masala module.
/// @note This class offers no thread-safety.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_version_MasalaModuleVersionRequirement_hh
#define Masala_src_base_managers_version_MasalaModuleVersionRequirement_hh

// Forward declarations:
#include <base/managers/version/MasalaModuleVersionRequirement.fwd.hh>

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

/// @brief Headers for a class storing a requirement, specified by one Masala module, for
/// the version of another Masala module.
/// @note This class offers no thread-safety.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaModuleVersionRequirement : masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaModuleVersionRequirement() = default;

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
	/// @returns "masala::base::managers::version".
	static std::string class_namespace_static();

	/// @brief Every class can name itself.
	/// @returns "MasalaModuleVersionRequirement".  Calls class_name_static().
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
	/// @returns "masala::base::managers::version".  Calls class_namespace_static().
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////


}; // class MasalaModuleVersionRequirement

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_version_MasalaModuleVersionRequirement_tmpl_hh