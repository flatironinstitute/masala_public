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

/// @file src/base/managers/engine/engine_request/MasalaEngineRequestCriterion.hh
/// @brief A pure virtual base class for criteria for Masala engine requests.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_engine_request_MasalaEngineRequestCriterion_hh
#define Masala_src_base_managers_engine_engine_request_MasalaEngineRequestCriterion_hh

// Forward declarations:
#include <base/managers/engine/engine_request/MasalaEngineRequestCriterion.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

/// @brief A pure virtual base class for criteria for Masala engine requests.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineRequestCriterion : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaEngineRequestCriterion() = default;

    /// @brief Copy constructor.
    MasalaEngineRequestCriterion( MasalaEngineRequestCriterion const & ) = default;

    // Destructor.
    ~MasalaEngineRequestCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS DEFINED BY ALL CRITERIA
////////////////////////////////////////////////////////////////////////////////

    /// @brief Determine whether a particular engine is compatible with this criterion.
    /// @returns True if it is compatible, false otherwise.
    /// @note Must be implemented by derived classes.
    virtual
    bool
    engine_is_compatible_with_criterion(
        masala::base::managers::engine::MasalaEngineCreator const & creator
    ) const = 0;

};

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_engine_request_MasalaEngineRequestCriterion_hh