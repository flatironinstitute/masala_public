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

/// @file src/base/managers/engine/engine_request/MasalaEngineKeywordCriterion.hh
/// @brief Headers for a class for imposing the condition that a particular engine have (or not have) a particular keyword.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_engine_request_MasalaEngineKeywordCriterion_hh
#define Masala_src_base_managers_engine_engine_request_MasalaEngineKeywordCriterion_hh

// Forward declarations:
#include <base/managers/engine/engine_request/MasalaEngineKeywordCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/engine_request/MasalaEngineRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

enum class MasalaEngineKeywordCompatibilityCriterionMode {
    INVALID_MODE = 0, // Keep first
    MUST_HAVE_AT_LEAST_ONE_KEYWORD = 1, // Keep second
    MUST_HAVE_ALL_KEYWORDS,
    MUST_NOT_HAVE_ANY_KEYWORD, // Keep second-to-last
    N_MODES = MUST_NOT_HAVE_ANY_KEYWORD // Keep last
};

/// @brief A class for imposing the condition that a particular engine have (or not have) a particular keyword.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineKeywordCriterion : public masala::base::managers::engine::engine_request::MasalaEngineRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaEngineKeywordCriterion() = default;

    /// @brief Copy constructor.
    MasalaEngineKeywordCriterion( MasalaEngineKeywordCriterion const & ) = default;

    // Destructor.
    ~MasalaEngineKeywordCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaEngineKeywordCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::engine_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaEngineKeywordCriterion".
    static std::string class_name_static();

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::engine_request".
    static std::string class_namespace_static();

    /// @brief Determine whether a particular engine is compatible with this criterion.
    /// @returns True if it is compatible, false otherwise.
    bool
    engine_is_compatible_with_criterion(
        masala::base::managers::engine::MasalaEngineCreator const & creator
    ) const override;

    /// @brief Are we enforcing that the engine have at least one keyword, have all keywords, or have no keywords?
    void set_criterion_mode( MasalaEngineKeywordCompatibilityCriterionMode const mode );

    /// @brief Set the keywords that we are matching.
    /// @details Overwrites any previously-set keywords.
    void set_keywords(
        std::vector< std::string > const & keywords
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Return true if an engine has a keyword, false otherwise.
    /// @param keyword The keyword to consider.
    /// @param creator The creator for the engine that we are considering.
    static
    bool
    has_keyword(
        std::string const & keyword,
        masala::base::managers::engine::MasalaEngineCreator const & creator
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief The keywords that we are matching.
    std::vector< std::string > keywords_;

    /// @brief How are we treating the various keywords?
    MasalaEngineKeywordCompatibilityCriterionMode mode_ = MasalaEngineKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD;

};

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_engine_request_MasalaEngineKeywordCriterion_hh