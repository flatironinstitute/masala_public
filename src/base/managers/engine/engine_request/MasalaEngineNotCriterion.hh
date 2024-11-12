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

/// @file src/base/managers/engine/engine_request/MasalaEngineNotCriterion.hh
/// @brief Headers for a class for imposing a condition be false when selecting engines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_engine_request_MasalaEngineNotCriterion_hh
#define Masala_src_base_managers_engine_engine_request_MasalaEngineNotCriterion_hh

// Forward declarations:
#include <base/managers/engine/engine_request/MasalaEngineNotCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/engine_request/MasalaEngineRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

/// @brief A class for imposing a condition be false when selecting engines.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineNotCriterion : public masala::base::managers::engine::engine_request::MasalaEngineRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaEngineNotCriterion() = default;

    /// @brief Copy constructor.
    MasalaEngineNotCriterion( MasalaEngineNotCriterion const & ) = default;

    // Destructor.
    ~MasalaEngineNotCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaEngineNotCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::engine_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaEngineNotCriterion".
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

	/// @brief Set a MasalaEngineRequestCriterion that must be false in order for this criterion
	/// to evaluate to true.
	/// @details The input criterion is used directly, not cloned.  Overwrites anything previously set.
	void
	set_criterion(
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

	/// @brief The criterion that must be false.
	MasalaEngineRequestCriterionCSP not_criterion_;

};

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_engine_request_MasalaEngineNotCriterion_hh