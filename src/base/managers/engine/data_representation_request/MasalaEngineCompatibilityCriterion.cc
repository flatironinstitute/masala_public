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

/// @file src/base/managers/engine/data_representation_request/MasalaEngineCompatibilityCriterion.cc
/// @brief A class for imposing the condition that a particular data representation be compatible with (or
/// be incompatible with) a particular Masala engine.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/data_representation_request/MasalaEngineCompatibilityCriterion.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/error/ErrorHandling.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.hh>

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
/// @returns "MasalaEngineCompatibilityCriterion".
std::string
MasalaEngineCompatibilityCriterion::class_name() const {
    return "MasalaEngineCompatibilityCriterion";
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::data_representation_request".
std::string
MasalaEngineCompatibilityCriterion::class_namespace() const {
    return "masala::base::managers::engine::data_representation_request";
}

/// @brief Determine whether a particular data representation is compatible with this criterion.
/// @returns True if it is compatible, false otherwise.
bool
MasalaEngineCompatibilityCriterion::data_representation_is_compatible_with_criterion(
    masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
) const {
    CHECK_OR_THROW_FOR_CLASS( mode_ != MasalaEngineCompatibilityCriterionMode::INVALID_MODE,
        "data_representation_is_compatible_with_criterion",
        "An invalid mode was set for this class!"
    );
    if( engine_namespaces_and_names_.empty() ) {
        return false;
    }

    for( auto const & engine : engine_namespaces_and_names_ ) {
        if( mode_ == MasalaEngineCompatibilityCriterionMode::MUST_BE_EXPLICITLY_COMPATIBLE ) {
            if( match_any_ ) {
                if( masala::base::utility::container::has_value( creator.get_compatible_masala_engines(), engine ) ) {
                    return true;
                }
            } else {
                if( !masala::base::utility::container::has_value( creator.get_compatible_masala_engines(), engine ) ) {
                    return false;
                }
            }
        } else if( mode_ == MasalaEngineCompatibilityCriterionMode::MUST_BE_EXPLICITLY_INCOMPATIBLE ) {
            if( match_any_ ) {
                if( masala::base::utility::container::has_value( creator.get_incompatible_masala_engines(), engine ) ) {
                    return true;
                }
            } else {
                if( !masala::base::utility::container::has_value( creator.get_incompatible_masala_engines(), engine ) ) {
                    return false;
                }
            }
        }
    }

    if( match_any_ ) {
        return false;
    }
    return true;
}

/// @brief Set the Masala engine with which the data representation must be compatible/incompatible.
/// @details Adds to list if other have been set.
void
MasalaEngineCompatibilityCriterion::set_engine_namespace_and_name(
    std::string const & engine_namespace_and_name
) {
    if( !masala::base::utility::container::has_value( engine_namespaces_and_names_, engine_namespace_and_name ) ) {
        engine_namespaces_and_names_.push_back( engine_namespace_and_name );
    }
}

/// @brief Set Masala engines with which the data representation must be compatible.
/// @details If match_any is true (the default), then the Masala data representation must be compatible/incompatible
/// with at least one engine from the list.  Otherwise, it must be compatible/incompatible with all of them.
/// @note Overwrites any existing engine namespaces or names.
void
MasalaEngineCompatibilityCriterion::set_engines_namespace_and_name(
    std::vector< std::string > const & engine_namespaces_and_names,
    bool const match_any /*= true*/
) {
    engine_namespaces_and_names_ = engine_namespaces_and_names;
    match_any_ = match_any;
}

/// @brief Set whether this criterion requres compatibility or incompatibility with (a) Masala engine(s).
void
MasalaEngineCompatibilityCriterion::set_criterion_mode(
    MasalaEngineCompatibilityCriterionMode const mode
) {
    mode_ = mode;
}

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
