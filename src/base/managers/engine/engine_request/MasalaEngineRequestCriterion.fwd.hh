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

/// @file src/base/managers/engine/engine_request/MasalaEngineRequestCriterion.fwd.hh
/// @brief A pure virtual base class for criteria for Masala engine requests.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_engine_request_MasalaEngineRequestCriterion_fwd_hh
#define Masala_src_base_managers_engine_engine_request_MasalaEngineRequestCriterion_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

    class MasalaEngineRequestCriterion;

    using MasalaEngineRequestCriterionSP = MASALA_SHARED_POINTER< MasalaEngineRequestCriterion >;
    using MasalaEngineRequestCriterionCSP = MASALA_SHARED_POINTER< MasalaEngineRequestCriterion const >;
    using MasalaEngineRequestCriterionWP = MASALA_WEAK_POINTER< MasalaEngineRequestCriterion >;
    using MasalaEngineRequestCriterionCWP = MASALA_WEAK_POINTER< MasalaEngineRequestCriterion const >;


} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_engine_request_MasalaEngineRequestCriterion_fwd_hh