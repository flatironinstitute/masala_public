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

/// @file src/base/managers/engine/data_representation_request/MasalaEngineCompatibilityCriterion.hh
/// @brief A class for imposing the condition that a particular data representation be compatible with (or
/// be incompatible with) a particular Masala engine.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_data_representation_request_MasalaEngineCompatibilityCriterion_hh
#define Masala_src_base_managers_engine_data_representation_request_MasalaEngineCompatibilityCriterion_hh

// Forward declarations:
#include <base/managers/engine/data_representation_request/MasalaEngineCompatibilityCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

enum class MasalaEngineCompatibilityCriterionMode {
    INVALID_MODE = 0, // Keep first
    MUST_BE_EXPLICITLY_COMPATIBLE = 1, // Keep second
    MUST_BE_EXPLICITLY_INCOMPATIBLE, // Keep second-to-last
    N_MODES = MUST_BE_EXPLICITLY_INCOMPATIBLE // Keep last
};

/// @brief A class for imposing the condition that a particular data representation be compatible with (or
/// be incompatible with) a particular Masala engine.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineCompatibilityCriterion : public masala::base::managers::engine::data_representation_request::MasalaDataRepresentationRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaEngineCompatibilityCriterion() = default;

    /// @brief Copy constructor.
    MasalaEngineCompatibilityCriterion( MasalaEngineCompatibilityCriterion const & ) = default;

    // Destructor.
    ~MasalaEngineCompatibilityCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaEngineCompatibilityCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    std::string class_namespace() const override;

    /// @brief Determine whether a particular data representation is compatible with this criterion.
    /// @returns True if it is compatible, false otherwise.
    bool
    data_representation_is_compatible_with_criterion(
        masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
    ) const;

    /// @brief Set the Masala engine with which the data representation must be compatible/incompatible.
    /// @details Adds to list if other have been set.
    void set_engine_namespace_and_name( std::string const & engine_namespace_and_name );

    /// @brief Set Masala engines with which the data representation must be compatible.
    /// @details If match_any is true (the default), then the Masala data representation must be compatible/incompatible
    /// with at least one engine from the list.  Otherwise, it must be compatible/incompatible with all of them.
    /// @note Overwrites any existing engine namespaces or names.
    void
    set_engines_namespace_and_name(
        std::vector< std::string > const & engine_namespaces_and_names,
        bool const match_any = true
    );

    /// @brief Set whether this criterion requres compatibility or incompatibility with (a) Masala engine(s).
    void set_criterion_mode( MasalaEngineCompatibilityCriterionMode const mode );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief The engines that we are matching.
    std::vector< std::string > engine_namespaces_and_names_;

    /// @brief Are we matching any of the engines listed (true) or all (false)?
    bool match_any_ = true;

    /// @brief Are we enforcing compatibility or incompatibility?
    MasalaEngineCompatibilityCriterionMode mode_ = MasalaEngineCompatibilityCriterionMode::MUST_BE_EXPLICITLY_COMPATIBLE;

};

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_data_representation_request_MasalaEngineCompatibilityCriterion_hh