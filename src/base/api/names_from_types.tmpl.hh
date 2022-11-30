/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
#include <memory>
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
            std::shared_ptr<T> tempobj(
                std::make_shared<T>()
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
    name_from_type(type<std::shared_ptr<T>>) {
        return "std::shared_ptr< " + name_from_type(type<T>()) + " >";
    }

    /// @brief Manually override for const shared pointers.
    template<class T>
    std::string
    name_from_type(type<std::shared_ptr<T const>>) {
        return "std::shared_ptr< " + name_from_type(type<T>()) + " const >";
    }

    /// @brief Manually override for weak pointers.
    template<class T>
    std::string
    name_from_type(type<std::weak_ptr<T>>) {
        return "std::weak_ptr< " + name_from_type(type<T>()) + " >";
    }

    /// @brief Manually override for const weak pointers.
    template<class T>
    std::string
    name_from_type(type<std::weak_ptr<T const>>) {
        return "std::weak_ptr< " + name_from_type(type<T>()) + " const >";
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