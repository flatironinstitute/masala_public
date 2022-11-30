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

/// @file src/core_api/base_classes/generators/Gelector.hh
/// @brief Header for a pure virtual base class for Generators.
/// @details Generators create an instance of something (e.g. a Pose from a data
/// source or from some input paramaters).
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_generators_Generator_hh
#define Masala_src_core_api_base_classes_generators_Generator_hh

// Forward declarations:
#include <core_api/base_classes/generators/Generator.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Core API headers:
#include <core_api/auto_generated_api/pose/Pose_API.fwd.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace generators {

/// @brief Header for a pure virtual base class for Generators.
/// @details Generators create an instance of something (e.g. a Pose from a data
/// source or from some input paramaters).
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Generator : public base::managers::plugin_module::MasalaPlugin {

public:

	/// @brief Default constructor.
	Generator() = default;

	/// @brief Copy constructor.
	Generator( Generator const & ) = default;

	/// @brief Destructor.
	~Generator() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

}; // class Generator

} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namesapce masala

#endif // Masala_src_core_api_base_classes_selectors_Generator_hh