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

/// @file src/core/scoring/ScoringTermAdditionalInput.cc
/// @brief A base class a container for additional input into a scoring term.
/// @details Scoring terms may optionally accept additional inputs, beyond a
/// vector of structures.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core/scoring/ScoringTermAdditionalInput.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>

// STL headers:

namespace masala {
namespace core {
namespace scoring {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Copy constructor.
/// @details Explicit copy constructor needed due to mutex.
ScoringTermAdditionalInput::ScoringTermAdditionalInput(
	ScoringTermAdditionalInput const & src
) :
	masala::base::MasalaObject(src)
	// Deliberately do not copy mutex or API definition.
{}

/// @brief Assignment operator.
/// @details Explicit assignment operator needed due to mutex.
ScoringTermAdditionalInput &
ScoringTermAdditionalInput::operator=(
	ScoringTermAdditionalInput const & src
) {
	masala::base::MasalaObject::operator=(src);
	// {
	// 	std::lock( mutex_, src.mutex_ );
	// 	std::lock_guard< std::mutex > lock( mutex_, std::adopt_lock );
	// 	std::lock_guard< std::mutex > lock2( src.mutex_, std::adopt_lock );
	// }
	return *this;
}

/// @brief Make a fully independent copy of this object.
ScoringTermAdditionalInputSP
ScoringTermAdditionalInput::deep_clone() const {
    ScoringTermAdditionalInputSP new_object( masala::make_shared< ScoringTermAdditionalInput >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
ScoringTermAdditionalInput::make_independent() {
    std::lock_guard< std::mutex > lock( mutex_ );
    api_definition_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Needed for API definition.
std::string
ScoringTermAdditionalInput::class_name() const {
	return "ScoringTermAdditionalInput";
}

/// @brief Needed for API definition.
std::string
ScoringTermAdditionalInput::class_namespace() const {
	return "masala::core::scoring";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the ScoringTermAdditionalInput class.
masala::base::api::MasalaObjectAPIDefinitionCWP
ScoringTermAdditionalInput::get_api_definition() {
	using namespace masala::base::api;

	std::lock_guard< std::mutex > lock( mutex() );

	if( api_definition() == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"The ScoringTermAdditionalInput class defines a base class for a container "
                "for additional input to scoring terms.  This is not intended to be instantiated by "
                "protocols.",
				false, true
			)
		);

		// Constructors:
		ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( ScoringTermAdditionalInput, api_def );

		api_definition() = api_def; //Make const.
	}

	return api_definition();
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Allow derived classes to access the mutex for this object.
/// @note The mutex is mutable, and can be locked from a const function.
std::mutex &
ScoringTermAdditionalInput::mutex() const {
    return mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.
masala::base::api::MasalaObjectAPIDefinitionCSP &
ScoringTermAdditionalInput::api_definition() {
    return api_definition_;
}

} // namespace scoring
} // namespace core
} // namespace masala
