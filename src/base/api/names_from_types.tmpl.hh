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

/// @file src/base/api/names_from_types.tmpl.hh
/// @brief Given typenames, get human-readable strings.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_names_from_types_tmpl_hh
#define Masala_src_base_api_names_from_types_tmpl_hh

// Base headers
#include <base/MasalaObject.hh>
#include <base/error/ErrorHandling.hh>

// STL headers
#include <string>
#include <base/managers/memory/util.hh>
#include <set>

namespace masala {
namespace base {
namespace api {

    template< typename T >
    struct type {

        /// @brief  Comparison operator.
        /// @return True if T is the same type as Tprime; false otherwise.
        template < typename Tprime >
        bool
        operator==( type<Tprime> const & other ) {
            return std::is_same<T, Tprime>::value;
        }

    };

    /// @brief Default behaviour is compiler-specific, and not ideal.
    template <class T>
    std::string
    name_from_type(type<T>) {
        CHECK_OR_THROW(
            !std::is_enum<T>::value, "base::api", "name_from_type",
            "Error in use of name_from_type() function: this function cannot be used for enums!  "
            "For enums as output from getters, use the MasalaObjectAPIGetterDefinition::set_custom_output_type_name() "
            "and MasalaObjectAPIGetterDefinition::set_custom_output_type_namespace() functions."
        );

        if constexpr( std::is_class<T>::value ) {
            MASALA_SHARED_POINTER<T> tempobj(
                masala::make_shared<T>()
            );

            masala::base::MasalaObjectSP tempptr(
                std::dynamic_pointer_cast< masala::base::MasalaObject >(tempobj)
            );
            if( tempptr != nullptr ) {
                return tempptr->class_namespace() + "::" + tempptr->class_name();
            }
        }
        return typeid(T).name();
    }

    /// @brief Manually override for references.
    template< class T >
    std::string
    name_from_type(type<T&>) {
        return name_from_type(type<T>()) + " &";
    }

    /// @brief Manually override for const references.
    template< class T >
    std::string
    name_from_type(type<T const &>) {
        return name_from_type(type<T>()) + " const &";
    }

    /// @brief Manually override for shared pointers.
    template<class T>
    std::string
    name_from_type(type<MASALA_SHARED_POINTER<T>>) {
        return "MASALA_SHARED_POINTER< " + name_from_type(type<T>()) + " >";
    }

    /// @brief Manually override for const shared pointers.
    template<class T>
    std::string
    name_from_type(type<MASALA_SHARED_POINTER<T const>>) {
        return "MASALA_SHARED_POINTER< " + name_from_type(type<T>()) + " const >";
    }

    /// @brief Manually override for weak pointers.
    template<class T>
    std::string
    name_from_type(type<MASALA_WEAK_POINTER<T>>) {
        return "MASALA_WEAK_POINTER< " + name_from_type(type<T>()) + " >";
    }

    /// @brief Manually override for const weak pointers.
    template<class T>
    std::string
    name_from_type(type<MASALA_WEAK_POINTER<T const>>) {
        return "MASALA_WEAK_POINTER< " + name_from_type(type<T>()) + " const >";
    }

    /// @brief Manually override for sets.
    template<class T>
    std::string
    name_from_type( type<std::set< T >> ) {
        return "std::set< " + name_from_type( type<T>() ) + " >";
    }

    /// @brief Manually override for const sets.
    template<class T>
    std::string
    name_from_type( type<std::set< T > const> ) {
        return "std::set< " + name_from_type( type<T>() ) + " > const";
    }

    /// @brief Manually override for sets of const elements.
    template<class T>
    std::string
    name_from_type( type<std::set< T const >> ) {
        return "std::set< " + name_from_type( type<T>() ) + " const >";
    }

    /// @brief Manually override for const sets of const elements.
    template<class T>
    std::string
    name_from_type( type<std::set< T const > const> ) {
        return "std::set< " + name_from_type( type<T>() ) + " const > const";
    }

    /// @brief Manually override for vectors.
    template<class T>
    std::string
    name_from_type( type<std::vector< T >> ) {
        return "std::vector< " + name_from_type( type<T>() ) + " >";
    }

    /// @brief Manually override for const vectors.
    template<class T>
    std::string
    name_from_type( type<std::vector< T > const> ) {
        return "std::vector< " + name_from_type( type<T>() ) + " > const";
    }

    /// @brief Manually override for vectors of const elements.
    template<class T>
    std::string
    name_from_type( type<std::vector< T const >> ) {
        return "std::vector< " + name_from_type( type<T>() ) + " const >";
    }

    /// @brief Manually override for const vectors of const elements.
    template<class T>
    std::string
    name_from_type( type<std::vector< T const > const> ) {
        return "std::vector< " + name_from_type( type<T>() ) + " const > const";
    }

    /// @brief Manually override for arrays.
    template<class T, std::size_t P >
    std::string
    name_from_type( type<std::array< T, P > > ) {
        return "std::array< " + name_from_type( type<T>() ) + ", " + std::to_string(P) + " >";
    }

    /// @brief Manually override for const arrays.
    template<class T, std::size_t P>
    std::string
    name_from_type( type<std::array< T, P > const > ) {
        return "std::array< " + name_from_type( type<T>() ) + ", " + std::to_string(P) + " > const";
    }

    /// @brief Manually override for arrays of const elements.
    template<class T, std::size_t P>
    std::string
    name_from_type( type<std::array< T const, P > > ) {
        return "std::array< " + name_from_type( type<T>() ) + " const, " + std::to_string(P) + " >";
    }

    /// @brief Manually override for const arrays of const elements.
    template<class T, std::size_t P>
    std::string
    name_from_type( type<std::array< T const, P > const > ) {
        return "std::array< " + name_from_type( type<T>() ) + " const, " + std::to_string(P) + " > const";
    }

    /// @brief Manually override for set const iterators.
    // template<class T>
    // std::string
    // name_from_type( type< typename std::set< T >::const_iterator > ) {
    //     return "std::set< " + name_from_type( type<T>() ) + " >::const_iterator";
    // }

    /// @brief Manually override for void.
    template<>
    std::string
    name_from_type< void >(type<void>);

    /// @brief Manually override for booleans.
    template<>
    std::string
    name_from_type< bool >(type<bool>);

    /// @brief Manually override for unsigned short ints.
    template<>
    std::string
    name_from_type< unsigned short >(type<unsigned short>);

    /// @brief Manually override for unsigned ints.
    template<>
    std::string
    name_from_type< unsigned int >(type<unsigned int>);

    /// @brief Manually override for unsigned long ints.
    template<>
    std::string
    name_from_type< unsigned long >(type<unsigned long>);

    /// @brief Manually override for signed short ints.
    template<>
    std::string
    name_from_type< signed short >(type<signed short>);

    /// @brief Manually override for signed ints.
    template<>
    std::string
    name_from_type< signed int >(type<signed int>);

    /// @brief Manually override for signed long ints.
    template<>
    std::string
    name_from_type< signed long >(type<signed long>);

    /// @brief Manually override for floats.
    template<>
    std::string
    name_from_type< float >(type<float>);

    /// @brief Manually override for float instances.
    template<>
    std::string
    name_from_type< float & >(type<float&>);

    /// @brief Manually override for float const instances.
    template<>
    std::string
    name_from_type< float const & >(type<float const &>);

    /// @brief Manually override for doubles.
    template<>
    std::string
    name_from_type< double >(type<double>);

    /// @brief Manually override for double instances.
    template<>
    std::string
    name_from_type< double & >(type<double &>);

    /// @brief Manually override for double const instances.
    template<>
    std::string
    name_from_type< double const & >(type<double const&>);

    /// @brief Manually override for strings.
    template<>
    std::string
    name_from_type< std::string >(type<std::string>);

    /// @brief Manually override for string instances.
    template<>
    std::string
    name_from_type< std::string & >(type<std::string &>);

    /// @brief Manually override for const instance strings.
    template<>
    std::string
    name_from_type< std::string const & >(type<std::string const&>);

} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_names_from_types_tmpl_hh