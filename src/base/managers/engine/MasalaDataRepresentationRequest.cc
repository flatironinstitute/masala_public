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

/// @file src/base/managers/plugin_module/MasalaDataRepresentationRequest.cc
/// @brief A class used to request data representations.
/// @details This class stores a list of criteria that a data representation must satisfy.
/// @note This class is not threadsafe.  It is expected to be created, used, and destroyed
/// by a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).


// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationRequest.hh>

// Base headers:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationNameRequirementCriterion.hh>
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationEngineCompatibilityCriterion.hh>
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationCategoryCriterion.hh>
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
/// @returns "MasalaDataRepresentationRequest".
std::string
MasalaDataRepresentationRequest::class_name() const {
    return class_name_static();
}

/// @brief Every class can provide its own namespace.
/// @returns "masala::base::managers::engine".
std::string
MasalaDataRepresentationRequest::class_namespace() const {
    return class_namespace_static();
}

/// @brief Every class can name itself.  Static version.
/// @returns "MasalaDataRepresentationRequest".
/*static*/
std::string
MasalaDataRepresentationRequest::class_name_static() {
    return "MasalaDataRepresentationRequest";
}

/// @brief Every class can provide its own namespace.  Static version.
/// @returns "masala::base::managers::engine".
/*static*/
std::string
MasalaDataRepresentationRequest::class_namespace_static() {
    return "masala::base::managers::engine";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

/// @brief Add a requirement that data representations have a particular name.
/// @details The input name may or may not include namespace.  If it DOES, then the full
/// name must match.  If it does NOT, then the short name must match.
void
MasalaDataRepresentationRequest::add_data_representation_name_requirement(
	std::string const & name_in
) {
	using namespace data_representation_request;
    MasalaDataRepresentationNameRequirementCriterionSP criterion( masala::make_shared< MasalaDataRepresentationNameRequirementCriterion >( name_in ) );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that data representations are explicitly marked as compatible
/// with a particular MasalaEngine.
/// @note The engine must be provided as a full name (namespace + name).
void
MasalaDataRepresentationRequest::add_engine_compatibility_requirement(
    std::string const & engine_namespace_and_name
) {
    using namespace data_representation_request;
    MasalaDataRepresentationEngineCompatibilityCriterionSP criterion( masala::make_shared< MasalaDataRepresentationEngineCompatibilityCriterion >() );
    criterion->set_engine_namespace_and_name( engine_namespace_and_name );
    criterion->set_criterion_mode( MasalaDataRepresentationEngineCompatibilityCriterionMode::MUST_BE_EXPLICITLY_COMPATIBLE );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that data representations are explicitly marked as compatible
/// with one of a set of MasalaEngines.
/// @details If match_any is true (the default), then the Masala data representation must be compatible
/// with at least one engine from the list.  Otherwise, it must be compatible with all of them.
/// @note The engines must be provided as a full name (namespace + name).
void
MasalaDataRepresentationRequest::add_engines_compatibility_requirement(
    std::vector< std::string > const & engine_namespaces_and_names,
    bool const match_any /*= true*/
) {
    using namespace data_representation_request;
    MasalaDataRepresentationEngineCompatibilityCriterionSP criterion( masala::make_shared< MasalaDataRepresentationEngineCompatibilityCriterion >() );
    criterion->set_engines_namespace_and_name( engine_namespaces_and_names, match_any );
    criterion->set_criterion_mode( MasalaDataRepresentationEngineCompatibilityCriterionMode::MUST_BE_EXPLICITLY_COMPATIBLE );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that data representations are explicitly marked as incompatible
/// with a particular MasalaEngine.
/// @note The engine must be provided as a full name (namespace + name).
void
MasalaDataRepresentationRequest::add_engine_incompatibility_requirement(
    std::string const & engine_namespace_and_name
) {
    using namespace data_representation_request;
    MasalaDataRepresentationEngineCompatibilityCriterionSP criterion( masala::make_shared< MasalaDataRepresentationEngineCompatibilityCriterion >() );
    criterion->set_engine_namespace_and_name( engine_namespace_and_name );
    criterion->set_criterion_mode( MasalaDataRepresentationEngineCompatibilityCriterionMode::MUST_BE_EXPLICITLY_INCOMPATIBLE );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that data representations are explicitly marked as incompatible
/// with one of a set of MasalaEngines.
/// @details If match_any is true (the default), then the Masala data representation must be incompatible
/// with at least one engine from the list.  Otherwise, it must be incompatible with all of them.
/// @note The engines must be provided as a full name (namespace + name).
void
MasalaDataRepresentationRequest::add_engines_incompatibility_requirement(
    std::vector< std::string > const & engine_namespaces_and_names,
    bool const match_any /*= true*/
) {
    using namespace data_representation_request;
    MasalaDataRepresentationEngineCompatibilityCriterionSP criterion( masala::make_shared< MasalaDataRepresentationEngineCompatibilityCriterion >() );
    criterion->set_engines_namespace_and_name( engine_namespaces_and_names, match_any );
    criterion->set_criterion_mode( MasalaDataRepresentationEngineCompatibilityCriterionMode::MUST_BE_EXPLICITLY_INCOMPATIBLE );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that data representations be in one of a set of
/// data representation categories.
/// @details Categories are provided as a vector of vectors of strings.  For instance, if
/// we want to indicate that a data representation may be in Fruits->Apples->MacIntoshApples
/// or in Vegetables->RootVegetables->Carrots, we provide {
///     { "Fruits", "Apples", "MacIntoshApples" },
///     { "Vegetables", "RootVegetables", "Carrots" }, 
/// }.
/// @note If allow_subcategories is true, then representations may be in subcategories
/// of these categories.  A data representation matches if it is in ANY category listed.
void
MasalaDataRepresentationRequest::add_data_representation_category_requirement(
    std::vector< std::vector< std::string > > const & categories,
    bool const allow_subcategories
) {
    using namespace data_representation_request;
    MasalaDataRepresentationCategoryCriterionSP criterion( masala::make_shared< MasalaDataRepresentationCategoryCriterion >() );
    criterion->set_categories( categories );
    criterion->set_allow_subcategories( allow_subcategories );
    criterion->set_criterion_mode( MasalaDataRepresentationCategoryCompatibilityCriterionMode::MUST_BE_IN_AT_LEAST_ONE_CATEGORY );
    request_criteria_.push_back( criterion );
}

/// @brief Add a requirement that data representations NOT be in ANY of a set of
/// data representation categories.
/// @details Categories are provided as a vector of vectors of strings.  For instance, if
/// we want to indicate that a data representation may not be in Fruits->Apples->MacIntoshApples
/// or in Vegetables->RootVegetables->Carrots, we provide {
///     { "Fruits", "Apples", "MacIntoshApples" },
///     { "Vegetables", "RootVegetables", "Carrots" }, 
/// }.
/// @note If allow_subcategories is true, then representations that are in subcategories
/// of these categories are also excluded.  A data representation is excluded if it is in ANY
/// category listed.
void
MasalaDataRepresentationRequest::add_data_representation_category_exclusion(
    std::vector< std::vector< std::string > > const & categories,
    bool const allow_subcategories
) {
    using namespace data_representation_request;
    MasalaDataRepresentationCategoryCriterionSP criterion( masala::make_shared< MasalaDataRepresentationCategoryCriterion >() );
    criterion->set_categories( categories );
    criterion->set_allow_subcategories( allow_subcategories );
    criterion->set_criterion_mode( MasalaDataRepresentationCategoryCompatibilityCriterionMode::MUST_NOT_BE_IN_ANY_CATEGORIES );
    request_criteria_.push_back( criterion );
}


/// @brief Add an arbitrary criterion to the list of criteria that must be true.
/// @note Input is used directly, not cloned.
void
MasalaDataRepresentationRequest::add_data_representation_criterion(
	data_representation_request::MasalaDataRepresentationRequestCriterionCSP const & criterion_in
) {
	CHECK_OR_THROW_FOR_CLASS( criterion_in != nullptr, "add_data_representation_criterion", "A null pointer was passed to this function." );
	request_criteria_.push_back( criterion_in );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Check whether a particular creator is compatible with the criteria listed.
/// @returns True for compatibility, false for incompatibility.
bool
MasalaDataRepresentationRequest::data_representation_is_compatible_with_criteria(
    MasalaDataRepresentationCreator const & creator
) const {
    for( auto const & criterion : request_criteria_ ) {
        if( !criterion->data_representation_is_compatible_with_criterion( creator ) ) {
            return false;
        }
    }
    return true;
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
