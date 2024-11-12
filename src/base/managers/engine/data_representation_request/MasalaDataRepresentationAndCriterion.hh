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

/// @file src/base/managers/engine/data_representation_request/MasalaDataRepresentationAndCriterion.hh
/// @brief Headers for a class for requiring that two or more criteria all be true.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationAndCriterion_hh
#define Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationAndCriterion_hh

// Forward declarations:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationAndCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

/// @brief A class for requiring that two or more criteria all be true.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationAndCriterion : public masala::base::managers::engine::data_representation_request::MasalaDataRepresentationRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationAndCriterion() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationAndCriterion( MasalaDataRepresentationAndCriterion const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationAndCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationAndCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationAndCriterion".
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

	/// @brief Add a criterion to the list of criteria that must be satisfied in order for
	/// this criterion to return true.
	/// @param criterion_in A const shared pointer to the criterion to be added.  Used directly; not cloned.
	/// @note This appends to the existing list.
	void
	add_criterion(
		MasalaDataRepresentationAndCriterionCSP const & criterion_in
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The criteria that must all be true in order for this criterion to pass.
	std::vector< MasalaDataRepresentationAndCriterionCSP > and_criteria_;

};

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationAndCriterion_hh