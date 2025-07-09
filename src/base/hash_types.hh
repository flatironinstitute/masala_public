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

/// @file src/base/hash_types.hh
/// @brief A utility file containing some typedefs for hashing basal types.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_hash_types_hh
#define Masala_src_base_hash_types_hh

// Masala base headers:
#include <base/types.hh>

// STL headers:
#include <functional>

namespace masala {
namespace base {

	/// @brief Used for std::unordered_map with std::pair< Size, Size > as the key.
	struct size_pair_hash {
		std::size_t
		operator () ( std::pair< Size, Size > const & key ) const {
			auto const h1 = std::hash< Size >{}( key.first );
			auto const h2 = std::hash< Size >{}( key.second );

			return (h1 << 32) | h2; // Will create some collisions for very large numbers.  
		}
	};

} // namespace base
} // namespace masala

#endif // Masala_src_base_hash_types_hh