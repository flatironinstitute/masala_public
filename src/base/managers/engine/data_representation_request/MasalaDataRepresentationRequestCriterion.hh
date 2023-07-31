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

/// @file src/base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.hh
/// @brief A pure virtual base class for criteria for Masala data representation requests.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationRequestCriterion_hh
#define Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationRequestCriterion_hh

// Forward declarations:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

/// @brief A pure virtual base class class for particular representations
/// of data that can be requested by engines for efficient manipulation of
/// those data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationRequestCriterion : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationRequestCriterion() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationRequestCriterion( MasalaDataRepresentationRequestCriterion const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationRequestCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS DEFINED BY ALL CRITERIA
////////////////////////////////////////////////////////////////////////////////

    /// @brief Determine whether a particular data representation is compatible with this criterion.
    /// @returns True if it is compatible, false otherwise.
    /// @note Must be implemented by derived classes.
    bool
    data_representation_is_compatible_with_criterion(
        masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
    ) const = 0;

};

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationRequestCriterion_hh