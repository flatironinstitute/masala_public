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

/// @file src/core/scoring/ScoringTermCache.cc
/// @brief A base class a container anything that a scoring term may need to cache
/// to facilitate repeated similar calculations.
/// @details Scoring terms may optionally read from AND write to this, during scoring.
/// @note Since this class does not implement class_name() or class_namespace(),
/// it remains pure virtual. 
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class headers:
#include <core/scoring/ScoringTermCache.hh>

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
ScoringTermCache::ScoringTermCache(
	ScoringTermCache const & src
) :
	masala::base::managers::plugin_module::MasalaPlugin(src)
	// Deliberately do not copy mutex or API definition.
{}

/// @brief Assignment operator.
/// @details Explicit assignment operator needed due to mutex.
ScoringTermCache &
ScoringTermCache::operator=(
	ScoringTermCache const & src
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
ScoringTermCacheSP
ScoringTermCache::deep_clone() const {
    ScoringTermCacheSP new_object( masala::make_shared< ScoringTermCache >( *this ) );
    new_object->make_independent();
    return new_object;
}

/// @brief Ensure that all data are unique and not shared (i.e. everytihng is deep-cloned.)
void
ScoringTermCache::make_independent() {
    std::lock_guard< std::mutex > lock( mutex_ );
    api_definition_ = nullptr;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Needed for API definition.
std::string
ScoringTermCache::class_name() const {
	return "ScoringTermCache";
}

/// @brief Needed for API definition.
std::string
ScoringTermCache::class_namespace() const {
	return "masala::core::scoring";
}

/// @brief Get a list of categories that this object could be sorted into.
/// @returns { { "ScoringTermCache" } }
std::vector< std::vector< std::string > >
ScoringTermCache::get_categories() const {
	return { { "ScoringTermCache" } };
}

/// @brief Get a list of keywords associated with this object.
/// @returns { "scoring_term_cache" }
std::vector< std::string >
ScoringTermCache::get_keywords() const {
	return { "scoring_term_cache" };
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the ScoringTermCache class.
masala::base::api::MasalaObjectAPIDefinitionCWP
ScoringTermCache::get_api_definition() {
	using namespace masala::base::api;

	std::lock_guard< std::mutex > lock( mutex() );

	if( api_definition() == nullptr ) {

		MasalaObjectAPIDefinitionSP api_def(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this,
				"The ScoringTermCache class defines a base class for a container for caching data that should persist from scoring attempt to scoring attempt.  This is not intended to be instantiated by protocols.",
				false, true
			)
		);

		// Constructors:
		ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( ScoringTermCache, api_def );

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
ScoringTermCache::mutex() const {
    return mutex_;
}

/// @brief Allow derived classes to access the API definition.
/// @note Could be nullptr.
masala::base::api::MasalaObjectAPIDefinitionCSP &
ScoringTermCache::api_definition() {
    return api_definition_;
}

} // namespace scoring
} // namespace core
} // namespace masala
