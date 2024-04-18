/*
    Masala
    Copyright (C) 2024 Vikram K. Mulligan

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

/// @file src/core/scoring/ScoringTermAdditionalInput.hh
/// @brief Headers for a base class a container for additional
/// input into a scoring term.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_scoring_ScoringTermAdditionalInput_hh
#define Masala_src_core_scoring_ScoringTermAdditionalInput_hh

// Forward declarations:
#include <core/scoring/ScoringTermAdditionalInput.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace core {
namespace scoring {

/// @brief A base class a container for additional input into a scoring term.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ScoringTermAdditionalInput : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	ScoringTermAdditionalInput() = default;

	/// @brief Copy constructor.
	/// @details Explicit copy constructor needed due to mutex.
	ScoringTermAdditionalInput( ScoringTermAdditionalInput const & src );

	/// @brief Virtual destructor.
	virtual ~ScoringTermAdditionalInput() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Needed for API definition.
	std::string
	class_name() const override;

	/// @brief Needed for API definition.
	std::string
	class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the ScoringTermAdditionalInput class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Allow derived classes to access the mutex for this object.
	/// @note The mutex is mutable, and can be locked from a const function.
	std::mutex & mutex() const;

	/// @brief Allow derived classes to access the API definition.
	/// @note Could be nullptr.
	masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for accessing this class.
	mutable std::mutex mutex_;

	/// @brief The API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

}; // class ScoringTermAdditionalInput

} // namespace scoring
} // namespace core
} // namespace masala

#endif //Masala_src_core_scoring_ScoringTermAdditionalInput_hh