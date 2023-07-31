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

/// @file src/base/managers/engine/data_representation_request/MasalaDataRepresentationCategoryCriterion.hh
/// @brief A class for imposing the condition that a particular data representation be in (or not in) a particular category.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationCategoryCriterion_hh
#define Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationCategoryCriterion_hh

// Forward declarations:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationCategoryCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

enum class MasalaDataRepresentationCategoryCompatibilityCriterionMode {
    INVALID_MODE = 0, // Keep first
    MUST_BE_IN_AT_LEAST_ONE_CATEGORY = 1, // Keep second
    MUST_NOT_BE_IN_ANY_CATEGORIES, // Keep second-to-last
    N_MODES = MUST_NOT_BE_IN_ANY_CATEGORIES // Keep last
};

/// @brief A class for imposing the condition that a particular data representation be in (or not in) a particular category.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationCategoryCriterion : public masala::base::managers::engine::data_representation_request::MasalaDataRepresentationRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationCategoryCriterion() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationCategoryCriterion( MasalaDataRepresentationCategoryCriterion const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationCategoryCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationCategoryCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationCategoryCriterion".
    static std::string class_name_static();

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    static std::string class_namespace_static();

    /// @brief Determine whether a particular data representation is compatible with this criterion.
    /// @returns True if it is compatible, false otherwise.
    bool
    data_representation_is_compatible_with_criterion(
        masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
    ) const;

    /// @brief Are we enforcing that the data representation be in categories or not in categories?
    void set_criterion_mode( MasalaDataRepresentationCategoryCompatibilityCriterionMode const mode );

    /// @brief Set whether we are matching subcategories.
    bool set_allow_subcategories( bool const setting );

    /// @brief Set the categories that we are matching.
    /// @details Overwrites any previously-set categories.
    void set_categories(
        std::vector< std::vector< std::string > > const & categories
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Return true if a data representation is in a category, false otherwise.
    /// @param category The category to consider.
    /// @param creator The creator for the data representation that we are considering.
    /// @param allow_subcategories If true, we return true if the data representation is in
    /// any subcategory of the category that we are considering.
    static
    bool
    is_in_category(
        std::vector< std::string > const & category,
        masala::base::managers::engine::MasalaDataRepresentationCreator const & creator,
        bool const allow_subcategories
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief The categories that we are matching.
    std::vector< std::vector< std::string > > categories_;

    /// @brief Are we matching subcategories?
    bool allow_subcategories_ = true;

    /// @brief Are we enforcing that the data representation be in categories or not in categories?
    MasalaDataRepresentationCategoryCompatibilityCriterionMode mode_ = MasalaDataRepresentationCategoryCompatibilityCriterionMode::MUST_BE_IN_AT_LEAST_ONE_CATEGORY;

};

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationCategoryCriterion_hh