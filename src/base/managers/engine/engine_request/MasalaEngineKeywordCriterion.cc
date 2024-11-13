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

/// @file src/base/managers/engine/engine_request/MasalaEngineKeywordCriterion.cc
/// @brief Implementations for a class for imposing the condition that a particular engine have (or not have) a particular keyword.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/engine_request/MasalaEngineKeywordCriterion.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>
#include <base/managers/engine/MasalaEngineCreator.hh>
// #include <base/managers/tracer/MasalaTracerManager.hh> // COMMENT ME OUT -- FOR DEBUGGING ONLY

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this class.
/// @returns "MasalaEngineKeywordCriterion".
std::string
MasalaEngineKeywordCriterion::class_name() const {
    return class_name_static();
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
std::string
MasalaEngineKeywordCriterion::class_namespace() const {
    return class_namespace_static();
}

/// @brief Get the name of this class.
/// @returns "MasalaEngineKeywordCriterion".
/*static*/
std::string
MasalaEngineKeywordCriterion::class_name_static() {
    return "MasalaEngineKeywordCriterion";
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
/*static*/
std::string
MasalaEngineKeywordCriterion::class_namespace_static() {
    return "masala::base::managers::engine::engine_request";
}

/// @brief Determine whether a particular engine is compatible with this criterion.
/// @returns True if it is compatible, false otherwise.
bool
MasalaEngineKeywordCriterion::engine_is_compatible_with_criterion(
    masala::base::managers::engine::MasalaEngineCreator const & creator
) const {
    CHECK_OR_THROW_FOR_CLASS( mode_ != MasalaEngineKeywordCompatibilityCriterionMode::INVALID_MODE,
        "engine_is_compatible_with_criterion",
        "An invalid mode was set for this class!"
    );
    if( keywords_.empty() ) {
        if( mode_ == MasalaEngineKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD || mode_ == MasalaEngineKeywordCompatibilityCriterionMode::MUST_HAVE_ALL_KEYWORDS ) {
            return false;
        }
        return true;
    }

    for( auto const & keyword : keywords_ ) {
        if( has_keyword( keyword, creator ) ) {
            if( mode_ == MasalaEngineKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD ) {
                return true;
            } else if( mode_ == MasalaEngineKeywordCompatibilityCriterionMode::MUST_NOT_HAVE_ANY_KEYWORD ) {
                return false;
            }
        } else {
			if( mode_ == MasalaEngineKeywordCompatibilityCriterionMode::MUST_HAVE_ALL_KEYWORDS ) {
				return false;
			}
		}
    }

    if( mode_ == MasalaEngineKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD ) {
        return false;
    }
    return true;
}

/// @brief Are we enforcing that the engine have at least one keyword, have all keywords, or have no keywords?
void
MasalaEngineKeywordCriterion::set_criterion_mode(
    MasalaEngineKeywordCompatibilityCriterionMode const mode
) {
    mode_ = mode;
}

/// @brief Set the keywords that we are matching.
/// @details Overwrites any previously-set keywords.
void
MasalaEngineKeywordCriterion::set_keywords(
    std::vector< std::string > const & keywords
) {
    for( auto const & keyword : keywords ) {
        CHECK_OR_THROW_FOR_CLASS( !keyword.empty(), "set_keywords", "A keyword cannot be an empty string!" );
    }
    keywords_ = keywords;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Return true if an engine has a keyword, false otherwise.
/// @param keyword The keyword to consider.
/// @param creator The creator for the engine that we are considering.
/*static*/
bool
MasalaEngineKeywordCriterion::has_keyword(
    std::string const & keyword,
    masala::base::managers::engine::MasalaEngineCreator const & creator
) {
    using namespace masala::base::utility::container;

    CHECK_OR_THROW( !keyword.empty(), class_namespace_static() + "::" + class_name_static(), "has_keyword",
        "Got an empty keyword!  This is a program error.  Please consult a developer."
    );
    std::vector< std::string > const engine_keywords( creator.get_engine_keywords() );
    for( auto const & engine_keyword : engine_keywords ) {
        CHECK_OR_THROW( !engine_keyword.empty(), class_namespace_static() + "::" + class_name_static(), "has_keyword",
            creator.get_plugin_object_name() + " lists itself as having an empty keyword!  This is a program error.  Please consult a developer."
        );
        // base::managers::tracer::MasalaTracerManager::get_instance()->write_to_tracer( class_namespace_static() + "::" + class_name_static(), 
        //     "For " + creator.class_name() + ", checking whether " + container_to_string( dr_category, "::" ) + " matches " + container_to_string( category, "::" ) + "."
        // ); // DELETE ME
        if( keyword == engine_keyword ) { return true; }
    }
    return false;
}

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
