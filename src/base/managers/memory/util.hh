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

/// @file src/base/managers/memory/util.hh
/// @brief Utility functions and definitions for allocating memory.
/// @details Defines Masala shared and weak pointers (currently as MASALA_SHARED_POINTER
/// and MASALA_WEAK_POINTER).  Also defines MASALA_MAKE_SHARED macro (which currently
/// just invokes masala::make_shared).
/// @note By defining these in one place, it is easy at a later time to
/// switch Masala to use a different memory allocation system, should a
/// better one come along.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_memory_util_hh
#define Masala_src_base_managers_memory_util_hh

// STL headers
#include <memory>

namespace masala { 
namespace base { 
namespace managers { 
namespace memory {

    using std::shared_ptr;
    using std::weak_ptr;

    using std::make_shared;

} // namespace memory
} // namespace managers
} // namespace base

    // Allows use of masala::make_shared as a shorthand for base::managers::memory::make_shared:
    using base::managers::memory::make_shared;

} // namespace masala

template < typename T >
using MASALA_SHARED_POINTER = masala::base::managers::memory::shared_ptr<T>;

template< typename T >
using MASALA_WEAK_POINTER = masala::base::managers::memory::weak_ptr<T>;

#endif // Masala_src_base_managers_memory_util_hh
