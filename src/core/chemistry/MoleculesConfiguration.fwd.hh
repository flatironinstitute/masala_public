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

/// @file src/core/chemistry/MoleculesConfiguration.fwd.hh
/// @brief Forward declarations for a container of configuration settings for a
/// Molecules object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_MoleculesConfiguration_fwd_hh
#define Masala_src_core_chemistry_MoleculesConfiguration_fwd_hh

// STL headers
#include <memory>

namespace masala {
namespace core {
namespace chemistry {

    class MoleculesConfiguration;

    using MoleculesConfigurationSP = std::shared_ptr< MoleculesConfiguration >;
    using MoleculesConfigurationCSP = std::shared_ptr< MoleculesConfiguration const >;
    using MoleculesConfigurationWP = std::weak_ptr< MoleculesConfiguration >;
    using MoleculesConfigurationCWP = std::weak_ptr< MoleculesConfiguration const>;

} // namespace chemistry
} // namespace core
} // namespace masala

#endif //Masala_src_core_chemistry_MoleculesConfiguration_fwd_hh
