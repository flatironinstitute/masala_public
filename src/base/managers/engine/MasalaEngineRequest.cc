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

/// @file src/base/managers/plugin_module/MasalaEngineRequest.cc
/// @brief A class used to request engines.
/// @details This class stores a list of criteria that an engine must satisfy.
/// @note This class is not threadsafe.  It is expected to be created, used, and destroyed
/// by a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Forward declarations:
#include <base/managers/engine/MasalaEngineRequest.hh>

// Base headers:
#include <base/managers/engine/engine_request/MasalaEngineNameRequirementCriterion.hh>
#include <base/managers/engine/engine_request/MasalaEngineCategoryCriterion.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Every class can name itself.
/// @returns "MasalaEngineRequest".
std::string
MasalaEngineRequest::class_name() const {
    return class_name_static();
}

/// @brief Every class can provide its own namespace.
/// @returns "masala::base::managers::engine".
std::string
MasalaEngineRequest::class_namespace() const {
    return class_namespace_static();
}

/// @brief Every class can name itself.  Static version.
/// @returns "MasalaEngineRequest".
/*static*/
std::string
MasalaEngineRequest::class_name_static() {
    return "MasalaEngineRequest";
}

/// @brief Every class can provide its own namespace.  Static version.
/// @returns "masala::base::managers::engine".
/*static*/
std::string
MasalaEngineRequest::class_namespace_static() {
    return "masala::base::managers::engine";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add a requirement that engines have a particular name.
/// @details The input name may or may not include namespace.  If it DOES, then the full
/// name must match.  If it does NOT, then the short name must match.
void
MasalaEngineRequest::add_engine_name_requirement(
	std::string const & name_in
) {
	using namespace engine_request;
    MasalaEngineNameRequirementCriterionSP criterion( masala::make_shared< MasalaEngineNameRequirementCriterion >( name_in ) );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that engines be in one of a set of
/// engine categories.
/// @details Categories are provided as a vector of vectors of strings.  For instance, if
/// we want to indicate that an engine may be in Fruits->Apples->MacIntoshApples
/// or in Vegetables->RootVegetables->Carrots, we provide {
///     { "Fruits", "Apples", "MacIntoshApples" },
///     { "Vegetables", "RootVegetables", "Carrots" }, 
/// }.
/// @note If allow_subcategories is true, then representations may be in subcategories
/// of these categories.  An engine matches if it is in ANY category listed.
void
MasalaEngineRequest::add_engine_category_requirement(
    std::vector< std::vector< std::string > > const & categories,
    bool const allow_subcategories
) {
    using namespace engine_request;
    MasalaEngineCategoryCriterionSP criterion( masala::make_shared< MasalaEngineCategoryCriterion >() );
    criterion->set_categories( categories );
    criterion->set_allow_subcategories( allow_subcategories );
    criterion->set_criterion_mode( MasalaEngineCategoryCompatibilityCriterionMode::MUST_BE_IN_AT_LEAST_ONE_CATEGORY );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that engines NOT be in ANY of a set of
/// engine categories.
/// @details Categories are provided as a vector of vectors of strings.  For instance, if
/// we want to indicate that an engine may not be in Fruits->Apples->MacIntoshApples
/// or in Vegetables->RootVegetables->Carrots, we provide {
///     { "Fruits", "Apples", "MacIntoshApples" },
///     { "Vegetables", "RootVegetables", "Carrots" }, 
/// }.
/// @note If allow_subcategories is true, then representations that are in subcategories
/// of these categories are also excluded.  An engine is excluded if it is in ANY
/// category listed.
void
MasalaEngineRequest::add_engine_category_exclusion(
    std::vector< std::vector< std::string > > const & categories,
    bool const allow_subcategories
) {
    using namespace engine_request;
    MasalaEngineCategoryCriterionSP criterion( masala::make_shared< MasalaEngineCategoryCriterion >() );
    criterion->set_categories( categories );
    criterion->set_allow_subcategories( allow_subcategories );
    criterion->set_criterion_mode( MasalaEngineCategoryCompatibilityCriterionMode::MUST_NOT_BE_IN_ANY_CATEGORIES );
    request_criteria_.push_back( criterion );
}

/// @brief Add an arbitrary engine criterion to the list of criteria that must be true.
/// @details Used directly; not cloned.
void
MasalaEngineRequest::add_engine_criterion(
	engine_request::MasalaEngineRequestCriterionCSP const & criterion_in
) {
	CHECK_OR_THROW_FOR_CLASS( criterion_in != nullptr, "add_engine_criterion", "A null pointer was passed to this function." );
	request_criteria_.push_back( criterion_in );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Check whether a particular creator is compatible with the criteria listed.
/// @returns True for compatibility, false for incompatibility.
bool
MasalaEngineRequest::engine_is_compatible_with_criteria(
    MasalaEngineCreator const & creator
) const {
    for( auto const & criterion : request_criteria_ ) {
        if( !criterion->engine_is_compatible_with_criterion( creator ) ) {
            return false;
        }
    }
    return true;
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
