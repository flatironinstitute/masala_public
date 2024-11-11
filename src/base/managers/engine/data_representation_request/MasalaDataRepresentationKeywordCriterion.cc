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

/// @file src/base/managers/engine/data_representation_request/MasalaDataRepresentationKeywordCriterion.cc
/// @brief Implementations for a class for imposing the condition that a particular data representation
/// have (or not have) a particular keyword.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationKeywordCriterion.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.hh>
// #include <base/managers/tracer/MasalaTracerManager.hh> // DELETE ME

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this class.
/// @returns "MasalaDataRepresentationKeywordCriterion".
std::string
MasalaDataRepresentationKeywordCriterion::class_name() const {
    return class_name_static();
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::data_representation_request".
std::string
MasalaDataRepresentationKeywordCriterion::class_namespace() const {
    return class_namespace_static();
}

/// @brief Get the name of this class.
/// @returns "MasalaDataRepresentationKeywordCriterion".
/*static*/
std::string
MasalaDataRepresentationKeywordCriterion::class_name_static() {
    return "MasalaDataRepresentationKeywordCriterion";
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::data_representation_request".
/*static*/
std::string
MasalaDataRepresentationKeywordCriterion::class_namespace_static() {
    return "masala::base::managers::engine::data_representation_request";
}

/// @brief Determine whether a particular data representation is compatible with this criterion.
/// @returns True if it is compatible, false otherwise.
bool
MasalaDataRepresentationKeywordCriterion::data_representation_is_compatible_with_criterion(
    masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
) const {
    CHECK_OR_THROW_FOR_CLASS( mode_ != MasalaDataRepresentationKeywordCompatibilityCriterionMode::INVALID_MODE,
        "data_representation_is_compatible_with_criterion",
        "An invalid mode was set for this class!"
    );
    if( keywords_.empty() ) {
        if( mode_ == MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD ||
			mode_ == MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_ALL_KEYWORDS
		) {
            return false;
        }
        return true;
    }

    for( auto const & keyword : keywords_ ) {
        if( has_keyword( keyword, creator ) ) {
            if( mode_ == MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD ) {
                return true;
            } else if( mode_ == MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_NO_KEYWORDS ) {
                return false;
            }
        } else {
			if( mode_ == MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_ALL_KEYWORDS ) {
				return false;
			}
		}
    }

    if( mode_ == MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD ) {
        return false;
    }
    return true;
}

/// @brief Are we enforcing that the data representation be in categories or not in categories?
void
MasalaDataRepresentationKeywordCriterion::set_criterion_mode(
    MasalaDataRepresentationKeywordCompatibilityCriterionMode const mode
) {
    mode_ = mode;
}

/// @brief Set the categories that we are matching.
/// @details Overwrites any previously-set categories.
void
MasalaDataRepresentationKeywordCriterion::set_keywords(
    std::vector< std::string > const & keywords
) {
    keywords_ = keywords;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Return true if a data representation has a keyword, false otherwise.
/// @param keyword The keyword to consider.
/// @param creator The creator for the data representation that we are considering.
/*static*/
bool
MasalaDataRepresentationKeywordCriterion::has_keyword(
	std::string const & keyword,
	masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
) {
    using namespace masala::base::utility::container;

    CHECK_OR_THROW( !keyword.empty(), class_namespace_static() + "::" + class_name_static(), "has_keyword",
        "Got an empty keyword!  This is a program error.  Consult a developer."
    );
    std::vector< std::string > const dr_keywords( creator.get_data_representation_keywords() );
    for( auto const & dr_keyword : dr_keywords ) {
        CHECK_OR_THROW( !dr_keyword.empty(), class_namespace_static() + "::" + class_name_static(), "has_keyword",
            creator.get_plugin_object_name() + " lists itself as having an empty keyword!  This is a program error.  Consult a developer."
        );
		
		if( keyword == dr_keyword ) {
			return true;
		}
    }
    return false;
}

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
