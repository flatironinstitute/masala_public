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

/// @file src/base/managers/plugin_module/MasalaDataRepresentationRequest.hh
/// @brief A class used to request data representations.
/// @details This class stores a list of criteria that a data representation must satisfy.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationRequest_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationRequest_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationRequest.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A class used to request data representations.
/// @details This class stores a list of criteria that a data representation must satisfy.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationRequest : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaDataRepresentationRequest() = default;

	/// @brief Copy constructor.
	MasalaDataRepresentationRequest( MasalaDataRepresentationRequest const & ) = default;

	/// @brief Destructor.
	virtual ~MasalaDataRepresentationRequest() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Every class can name itself.
    /// @returns "MasalaDataRepresentationRequest".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
    /// @returns "masala::base::managers::engine".
	std::string class_namespace() const override;

    /// @brief Every class can name itself.  Static version.
    /// @returns "MasalaDataRepresentationRequest".
	static std::string class_name_static();

	/// @brief Every class can provide its own namespace.  Static version.
    /// @returns "masala::base::managers::engine".
	static std::string class_namespace_static();

}; // class MasalaDataRepresentationRequest

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaDataRepresentationRequest_hh