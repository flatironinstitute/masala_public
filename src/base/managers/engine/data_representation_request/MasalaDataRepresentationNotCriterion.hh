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

/// @file src/base/managers/engine/data_representation_request/MasalaDataRepresentationNotCriterion.hh
/// @brief Headers for a class for requiring that at a criterion be false.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationNotCriterion_hh
#define Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationNotCriterion_hh

// Forward declarations:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationNotCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

/// @brief A class for requiring that at a criterion be false.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationNotCriterion : public masala::base::managers::engine::data_representation_request::MasalaDataRepresentationRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationNotCriterion() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationNotCriterion( MasalaDataRepresentationNotCriterion const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationNotCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationNotCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationNotCriterion".
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

	/// @brief Set the criterion that must be false.
	/// @param criterion_in A const shared pointer to the criterion to be set.  Used directly; not cloned.
	/// @note This replaces anything already set.
	void
	set_criterion(
		MasalaDataRepresentationRequestCriterionCSP const & criterion_in
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The criterion that must be false.
	MasalaDataRepresentationRequestCriterionCSP not_criterion_;

};

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationNotCriterion_hh