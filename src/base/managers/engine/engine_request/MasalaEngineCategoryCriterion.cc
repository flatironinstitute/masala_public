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

/// @file src/base/managers/engine/engine_request/MasalaEngineCategoryCriterion.cc
/// @brief A class for imposing the condition that a particular engine be in (or not in) a particular category.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/engine_request/MasalaEngineCategoryCriterion.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>
#include <base/managers/engine/MasalaEngineCreator.hh>
// #include <base/managers/tracer/MasalaTracerManager.hh> // DELETE ME

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
/// @returns "MasalaEngineCategoryCriterion".
std::string
MasalaEngineCategoryCriterion::class_name() const {
    return class_name_static();
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
std::string
MasalaEngineCategoryCriterion::class_namespace() const {
    return class_namespace_static();
}

/// @brief Get the name of this class.
/// @returns "MasalaEngineCategoryCriterion".
/*static*/
std::string
MasalaEngineCategoryCriterion::class_name_static() {
    return "MasalaEngineCategoryCriterion";
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
/*static*/
std::string
MasalaEngineCategoryCriterion::class_namespace_static() {
    return "masala::base::managers::engine::engine_request";
}

/// @brief Determine whether a particular engine is compatible with this criterion.
/// @returns True if it is compatible, false otherwise.
bool
MasalaEngineCategoryCriterion::engine_is_compatible_with_criterion(
    masala::base::managers::engine::MasalaEngineCreator const & creator
) const {
    CHECK_OR_THROW_FOR_CLASS( mode_ != MasalaEngineCategoryCompatibilityCriterionMode::INVALID_MODE,
        "engine_is_compatible_with_criterion",
        "An invalid mode was set for this class!"
    );
    if( categories_.empty() ) {
        if( mode_ == MasalaEngineCategoryCompatibilityCriterionMode::MUST_BE_IN_AT_LEAST_ONE_CATEGORY ) {
            return false;
        }
        return true;
    }

    for( auto const & category : categories_ ) {
        if( is_in_category( category, creator, allow_subcategories_ ) ) {
            if( mode_ == MasalaEngineCategoryCompatibilityCriterionMode::MUST_BE_IN_AT_LEAST_ONE_CATEGORY ) {
                return true;
            } else if( mode_ == MasalaEngineCategoryCompatibilityCriterionMode::MUST_NOT_BE_IN_ANY_CATEGORIES ) {
                return false;
            }
        }
    }

    if( mode_ == MasalaEngineCategoryCompatibilityCriterionMode::MUST_BE_IN_AT_LEAST_ONE_CATEGORY ) {
        return false;
    }
    return true;
}

/// @brief Are we enforcing that the engine be in categories or not in categories?
void
MasalaEngineCategoryCriterion::set_criterion_mode(
    MasalaEngineCategoryCompatibilityCriterionMode const mode
) {
    mode_ = mode;
}

/// @brief Set whether we are matching subcategories.
void
MasalaEngineCategoryCriterion::set_allow_subcategories(
    bool const setting
) {
    allow_subcategories_ = setting;
}

/// @brief Set the categories that we are matching.
/// @details Overwrites any previously-set categories.
void
MasalaEngineCategoryCriterion::set_categories(
    std::vector< std::vector< std::string > > const & categories
) {
    categories_ = categories;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Return true if an engine is in a category, false otherwise.
/// @param category The category to consider.
/// @param creator The creator for the engine that we are considering.
/// @param allow_subcategories If true, we return true if the engine is in
/// any subcategory of the category that we are considering.
/*static*/
bool
MasalaEngineCategoryCriterion::is_in_category(
    std::vector< std::string > const & category,
    masala::base::managers::engine::MasalaEngineCreator const & creator,
    bool const allow_subcategories
) {
    using namespace masala::base::utility::container;

    CHECK_OR_THROW( !category.empty(), class_namespace_static() + "::" + class_name_static(), "is_in_category",
        "Got an empty category!  This is a program error.  Consult a developer."
    );
    std::vector< std::vector< std::string > > const dr_categories( creator.get_engine_categories() );
    for( auto const & dr_category : dr_categories ) {
        CHECK_OR_THROW( !dr_category.empty(), class_namespace_static() + "::" + class_name_static(), "is_in_category",
            creator.get_plugin_object_name() + " lists itself as belonging to an empty category!  This is a program error.  Consult a developer."
        );
        // base::managers::tracer::MasalaTracerManager::get_instance()->write_to_tracer( class_namespace_static() + "::" + class_name_static(), 
        //     "For " + creator.class_name() + ", checking whether " + container_to_string( dr_category, "::" ) + " matches " + container_to_string( category, "::" ) + "."
        // ); // DELETE ME
        if( !allow_subcategories ) {
            if( dr_category == category ) {
                return true;
            }
        } else {
            if( dr_category.size() < category.size() ) {
                continue;
            } else if( dr_category.size() == category.size() && dr_category == category ) {
                return true;
            } else { //dr_category.size() > category.size()
                std::vector< std::string > parent_category( category.size() );
                for( masala::base::Size i(0), imax(category.size()); i<imax; ++i ) {
                    parent_category[i] = dr_category[i];
                }
                // base::managers::tracer::MasalaTracerManager::get_instance()->write_to_tracer( class_namespace_static() + "::" + class_name_static(), 
                //     "\tComparing " + container_to_string( dr_category, "::" ) + " to " + container_to_string( parent_category, "::" ) + "."
                // ); // DELETE ME
                if( category == parent_category ) {
                    // base::managers::tracer::MasalaTracerManager::get_instance()->write_to_tracer( class_namespace_static() + "::" + class_name_static(), 
                    //     "\tMatch!"
                    // ); // DELETE ME
                    return true;
                }
            }
        }
    }
    return false;
}

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
