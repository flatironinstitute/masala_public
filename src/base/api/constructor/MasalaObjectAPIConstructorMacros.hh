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

/// @file src/base/api/constructor/MasalaObjectAPIConstructorMacros.hh
/// @brief Macros to conveniently add constructor definitions.
/// @details Every API class needs to have definitions for the default and copy constructors
/// added to its API.  These macros make this easy.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_constructor_MasalaObjectAPIConstructorMacros_hh
#define Masala_src_base_api_constructor_MasalaObjectAPIConstructorMacros_hh

// Constructor headers.
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>

namespace masala {
namespace base {
namespace api {
namespace constructor {

#define ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( CLASS_NAME, API_DEFINITION ) \
        API_DEFINITION->add_constructor( \
            masala::make_shared< masala::base::api::constructor::MasalaObjectAPIConstructorDefinition_ZeroInput< CLASS_NAME > > ( \
                #CLASS_NAME , "Construct an instance of the " #CLASS_NAME " class.  Protected, to prevent instantiation of " \
                "this base class -- i.e. can only be called from derived constructors." \
            ) \
        ); \
        API_DEFINITION->add_constructor( \
            masala::make_shared< masala::base::api::constructor::MasalaObjectAPIConstructorDefinition_OneInput< CLASS_NAME, CLASS_NAME const & > > ( \
                #CLASS_NAME, "Copy-construct the " #CLASS_NAME " class.  Protected, to prevent instantiation of " \
                "this base class -- i.e. can only be called from derived constructors.", \
                "src", "The " #CLASS_NAME " instance to copy.  Unaltered by this operation." \
            ) \
        );

#define ADD_PUBLIC_CONSTRUCTOR_DEFINITIONS( CLASS_NAME, API_DEFINITION ) \
        API_DEFINITION->add_constructor( \
            masala::make_shared< masala::base::api::constructor::MasalaObjectAPIConstructorDefinition_ZeroInput< CLASS_NAME > > ( \
                #CLASS_NAME , "Construct an instance of the " #CLASS_NAME " class." \
            ) \
        ); \
        API_DEFINITION->add_constructor( \
            masala::make_shared< masala::base::api::constructor::MasalaObjectAPIConstructorDefinition_OneInput< CLASS_NAME, CLASS_NAME const & > > ( \
                #CLASS_NAME, "Copy-construct the " #CLASS_NAME " class.", \
                "src", "The " #CLASS_NAME " instance to copy.  Unaltered by this operation." \
            ) \
        );

} // namespace constructor
} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_constructor_MasalaObjectAPIConstructorMacros_hh