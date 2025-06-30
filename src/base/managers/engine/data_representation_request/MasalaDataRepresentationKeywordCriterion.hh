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

/// @file src/base/managers/engine/data_representation_request/MasalaDataRepresentationKeywordCriterion.hh
/// @brief Headers for a class for imposing the condition that a particular data representation
/// have (or not have) a particular keyword.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationKeywordCriterion_hh
#define Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationKeywordCriterion_hh

// Forward declarations:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationKeywordCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

enum class MasalaDataRepresentationKeywordCompatibilityCriterionMode {
    INVALID_MODE = 0, // Keep first
    MUST_HAVE_AT_LEAST_ONE_KEYWORD = 1, // Keep second
    MUST_HAVE_ALL_KEYWORDS,
    MUST_HAVE_NO_KEYWORDS, // Keep second-to-last
    N_MODES = MUST_HAVE_NO_KEYWORDS // Keep last
};

/// @brief A class for imposing the condition that a particular data representation
/// have (or not have) a particular keyword.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationKeywordCriterion : public masala::base::managers::engine::data_representation_request::MasalaDataRepresentationRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationKeywordCriterion() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationKeywordCriterion( MasalaDataRepresentationKeywordCriterion const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationKeywordCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationKeywordCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationKeywordCriterion".
    static std::string class_name_static();

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    static std::string class_namespace_static();

    /// @brief Determine whether a particular data representation is compatible with this criterion.
    /// @returns True if it is compatible, false otherwise.
    bool
    data_representation_is_compatible_with_criterion(
        masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
    ) const override;

    /// @brief Are we enforcing that the data representation have one of the specified keywords,
    /// have all of the specified keywords, or have none of the specified keywords?
    void set_criterion_mode( MasalaDataRepresentationKeywordCompatibilityCriterionMode const mode );

	/// @brief Set the keywords that we are matching.
	/// @details Overwrites any previously-set keywords.
	void set_keywords(
		std::vector< std::string > const & keywords
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Return true if a data representation has a keyword, false otherwise.
	/// @param keyword The keyword to consider.
	/// @param creator The creator for the data representation that we are considering.
    static
    bool
    has_keyword(
        std::string const & keyword,
        masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief The keywords that we are matching.
    std::vector< std::string > keywords_;

    /// @brief Are we enforcing that the data representation be in categories or not in categories?
    MasalaDataRepresentationKeywordCompatibilityCriterionMode mode_ = MasalaDataRepresentationKeywordCompatibilityCriterionMode::MUST_HAVE_AT_LEAST_ONE_KEYWORD;

};

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationKeywordCriterion_hh