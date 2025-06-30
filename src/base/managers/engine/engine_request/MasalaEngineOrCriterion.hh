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

/// @file src/base/managers/engine/engine_request/MasalaEngineOrCriterion.hh
/// @brief Headers for a class for imposing that at least one of two or more conditions be true when selecting engines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_engine_request_MasalaEngineOrCriterion_hh
#define Masala_src_base_managers_engine_engine_request_MasalaEngineOrCriterion_hh

// Forward declarations:
#include <base/managers/engine/engine_request/MasalaEngineOrCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/engine_request/MasalaEngineRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

/// @brief A class for imposing that at least one of two or more conditions be true when selecting engines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineOrCriterion : public masala::base::managers::engine::engine_request::MasalaEngineRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaEngineOrCriterion() = default;

    /// @brief Copy constructor.
    MasalaEngineOrCriterion( MasalaEngineOrCriterion const & ) = default;

    // Destructor.
    ~MasalaEngineOrCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaEngineOrCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::engine_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaEngineOrCriterion".
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

	/// @brief Add a MasalaEngineRequestCriterion to the set of criteria, at least one of which
    /// must be true for this criterion to pass.
	/// @details The input criterion is used directly, not cloned.
	void
	add_criterion(
		MasalaEngineRequestCriterionCSP const & criterion_in
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The criteria that we must match.
	std::vector< MasalaEngineRequestCriterionCSP > or_criteria_;

};

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_engine_request_MasalaEngineOrCriterion_hh