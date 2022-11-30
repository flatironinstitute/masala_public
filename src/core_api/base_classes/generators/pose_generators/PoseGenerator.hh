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

/// @file src/core_api/base_classes/generators/pose_generators/PoseGenerator.hh
/// @brief Header for a pure virtual base class for PoseGenerators.
/// @details PoseGenerators generate poses based on some input or some set of
/// user-supplied parameters.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_generators_pose_generators_PoseGenerator_hh
#define Masala_src_core_api_base_classes_generators_pose_generators_PoseGenerator_hh

// Parent class:
#include <core_api/base_classes/generators/Generator.hh>

// Forward declarations:
#include <core_api/base_classes/generators/pose_generators/PoseGenerator.fwd.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace generators {
namespace pose_generators {

/// @brief A pure virtual base class for PoseGenerators.
/// @details PoseGenerators generate poses based on some input or some set of
/// user-supplied parameters.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class PoseGenerator : public core_api::base_classes::generators::Generator {

public:

	/// @brief Default constructor.
	PoseGenerator() = default;

	/// @brief Copy constructor.
	PoseGenerator( PoseGenerator const & ) = default;

	/// @brief Destructor.
	~PoseGenerator() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


}; // class PoseGenerator

} // namespace pose_generators
} // namespace generators
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_generators_pose_generators_PoseGenerator_hh