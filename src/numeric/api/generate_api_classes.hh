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

/// @file src/numeric/api/generate_api_classes.hh
/// @brief Utility functions to generate all of the classes in numeric that define
/// an API.  Used for auto-generating the numeric api.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_api_generate_api_classes_hh
#define Masala_src_numeric_api_generate_api_classes_hh

// Base headers
#include <base/MasalaObject.fwd.hh>

// STL headers
#include <vector>

namespace masala {
namespace numeric {
namespace api {

    /// @brief Generate an instance of each of the classes in numeric that have a defined API, and
    /// return a vector of owning pointers to these instances.
    /// @details Used for auto-generating the numeric API description (as a JSON file).
    std::vector< masala::base::MasalaObjectSP > generate_api_classes();

} // namespace api
} // namespace numeric
} // namespace masala

#endif //Masala_src_numeric_api_generate_api_classes_hh