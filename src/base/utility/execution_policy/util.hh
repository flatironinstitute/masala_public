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

/// @file src/base/utility/execution_policy/util.hh
/// @brief Utility functions for dealing with execution policies in C++17 and C++20.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_utility_execution_policy_util_hh
#define Masala_src_base_utility_execution_policy_util_hh

// STL headers
#ifdef MASALA_USE_STL_PARALLEL
#include <execution>

#define MASALA_SEQ_EXECUTION_POLICY std::execution::seq,
#define MASALA_PAR_EXECUTION_POLICY std::execution::par,
#define MASALA_PAR_UNSEQ_EXECUTION_POLICY std::execution::par_unseq,

#if defined __cplusplus && __cplusplus >= 202002L
#define MASALA_UNSEQ_EXECUTION_POLICY std::execution::unseq,
#else
#define MASALA_UNSEQ_EXECUTION_POLICY std::execution::seq,
#endif

#else

#define MASALA_SEQ_EXECUTION_POLICY
#define MASALA_PAR_EXECUTION_POLICY
#define MASALA_PAR_UNSEQ_EXECUTION_POLICY
#define MASALA_UNSEQ_EXECUTION_POLICY

#endif

namespace masala {
namespace base {
namespace utility {
namespace execution_policy {


} // namespace execution_policy
} // namespace utility
} // namsespace base
} // namespace masala

#endif //Masala_src_base_utility_execution_policy_util_hh