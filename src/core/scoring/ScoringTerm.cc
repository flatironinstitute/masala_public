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

/// @file src/core/scoring/ScoringTerm.cc
/// @brief A base class for all Masala scoring terms.
/// @details Masala scoring terms are components of Masala scoring functions.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core/scoring/ScoringTerm.hh>

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
ScoringTerm::ScoringTerm(
	ScoringTerm const & src
) :
	masala::base::managers::plugin_module::MasalaPlugin(src)
	// Deliberately do not copy mutex or API definition.
{}

/// @brief Assignment operator.
/// @details Explicit assignment operator needed due to mutex.
ScoringTerm &
ScoringTerm::operator=(
	ScoringTerm const & src
) {
	masala::base::managers::plugin_module::MasalaPlugin::operator=(src);
	// {
	// 	std::lock( mutex_, src.mutex_ );
	// 	std::lock_guard< std::mutex > lock( mutex_, std::adopt_lock );
	// 	std::lock_guard< std::mutex > lock2( src.mutex_, std::adopt_lock );
	// }
	return *this;
}

/// @brief Make a fully independent copy of this object.
ScoringTermSP
ScoringTerm::deep_clone() const {
    ScoringTermSP new_object( masala::make_shared< ScoringTerm >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
ScoringTerm::make_independent() {
    std::lock_guard< std::mutex > lock( mutex_ );
    api_definition_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Needed for API definition.
std::string
ScoringTerm::class_name() const {
	return "ScoringTerm";
}

/// @brief Needed for API definition.
std::string
ScoringTerm::class_namespace() const {
	return "masala::core::scoring";
}

/// @brief Get a list of categories that this object could be sorted into.
/// @returns { { "ScoringTerm" } }
std::vector< std::vector< std::string > >
ScoringTerm::get_categories() const {
	return { { "ScoringTerm" } };
}

/// @brief Get a list of keywords associated with this object.
/// @returns { "scoring_term" }
std::vector< std::string >
ScoringTerm::get_keywords() const {
	return { "scoring_term" };
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the ScoringTerm class.
masala::base::api::MasalaObjectAPIDefinitionCWP
ScoringTerm::get_api_definition() {
	using namespace masala::base::api;

	std::lock_guard< std::mutex > lock( mutex() );

	if( api_definition() == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"The ScoringTerm class defines a base class for scoring terms.  This is not intended to be instantiated by protocols.",
				false, true
			)
		);

		// Constructors:
		ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( ScoringTerm, api_def );

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
ScoringTerm::mutex() const {
    return mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.
masala::base::api::MasalaObjectAPIDefinitionCSP &
ScoringTerm::api_definition() {
    return api_definition_;
}

} // namespace scoring
} // namespace core
} // namespace masala
