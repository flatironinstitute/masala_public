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
#include <base/hash_types.hh>

// Known base enums
#include <base/managers/database/elements/ElementType.fwd.hh> // ElementTypeEnum
#include <base/enums/ChemicalBondTypeEnum.fwd.hh> // ChemicalBondType

// Eigen headers
#include <external/eigen/Eigen/Dense>

// STL headers
#include <string>
#include <base/managers/memory/util.hh>
#include <set>
#include <tuple>
#include <map>
#include <unordered_map>

namespace masala {
namespace base {
namespace api {

    template< typename T >
    struct type {

        /// @brief  Comparison operator.
        /// @return True if T is the same type as Tprime; false otherwise.
        template < typename Tprime >
        bool
        operator==( type<Tprime> const & ) {
            return std::is_same<T, Tprime>::value;
        }

    };

////////////////////////////////////////////////////////////////////////////////
// KNOWN ENUM TYPES
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is a particular enum type a known type defined in masala::base?
	/// @details Returns false by default.
	template< class T >
	bool
	is_known_base_enum_type(
		type<T>,
		std::string & enum_name
	) {
		enum_name.clear();
		return false;
	}

	/// @brief Is a particular enum type a known type defined in masala::base?
	/// @details Override for masala::base::managers::database::elements::ElementTypeEnum
	template<>
	bool
	is_known_base_enum_type<masala::base::managers::database::elements::ElementTypeEnum>(
		type<masala::base::managers::database::elements::ElementTypeEnum>,
		std::string & enum_name
	);

	/// @brief Is a particular enum type a known type defined in masala::base?
	/// @details Override for masala::base::enums::ChemicalBondType
	template<>
	bool
	is_known_base_enum_type<masala::base::enums::ChemicalBondType>(
		type<masala::base::enums::ChemicalBondType>,
		std::string & enum_name
	);

////////////////////////////////////////////////////////////////////////////////
// NAMES FROM TYPES
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default behaviour is compiler-specific, and not ideal.
    template <class T>
    std::string
    name_from_type(type<T> t) {

        {
            std::string enum_name;

            CHECK_OR_THROW(
                (!std::is_enum<T>::value) || is_known_base_enum_type(t, enum_name ), "base::api", "name_from_type",
                "Error in use of name_from_type() function: this function cannot be used for enums other than those defined in masala::base!"
            );

            if( std::is_enum<T>::value ) {
                return enum_name;
            }
        }

        if constexpr( std::is_class<T>::value ) {
            if constexpr( std::is_abstract<T>::value ) {
                // If this is an abstract base class, try and see whether it has a class_namespace_and_name_static() function.
                return T::class_namespace_and_name_static();
            } else {

                MASALA_SHARED_POINTER<T> tempobj(
                    masala::make_shared<T>()
                );

                if constexpr( std::is_const<T>::value ) {
                    masala::base::MasalaObjectCSP tempptr(
                        std::dynamic_pointer_cast< masala::base::MasalaObject const >(tempobj)
                    );
                    if( tempptr != nullptr ) {
                        return tempptr->class_namespace() + "::" + tempptr->class_name();
                    }
                } else {
                    masala::base::MasalaObjectSP tempptr(
                        std::dynamic_pointer_cast< masala::base::MasalaObject >(tempobj)
                    );
                    if( tempptr != nullptr ) {
                        return tempptr->class_namespace() + "::" + tempptr->class_name();
                    }
                }
                
            }
        }
        return typeid(T).name();
    }

    /// @brief Manually override for pointers.
    template< class T >
    std::string
    name_from_type(type<T*>) {
        return name_from_type(type<T>()) + " *";
    }

    /// @brief Manually override for const pointers.
    template< class T >
    std::string
    name_from_type(type<T* const>) {
        return name_from_type(type<T>()) + " * const";
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

    /// @brief Manually override for pairs.
    template<class T1, class T2>
    std::string
    name_from_type( type<std::pair< T1, T2 >> ) {
        return "std::pair< " + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + " >";
    }

    /// @brief Manually override for const pairs.
    template<class T1, class T2>
    std::string
    name_from_type( type<std::pair< T1, T2 > const> ) {
        return "std::pair< " + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + " > const";
    }

    /// @brief Manually override for pairs of const elements.
    template<class T1, class T2>
    std::string
    name_from_type( type<std::pair< T1 const, T2 const >> ) {
        return "std::pair< " + name_from_type( type<T1>() ) + " const, "
            + name_from_type( type<T2>() ) + " const >";
    }

    /// @brief Manually override for pairs pairs of const elements.
    template<class T1, class T2>
    std::string
    name_from_type( type<std::pair< T1 const, T2 const > const> ) {
        return "std::pair< " + name_from_type( type<T1>() ) + " const, "
            + name_from_type( type<T2>() ) + " const > const";
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

    /// @brief Manually override for 3-tuples.
    template<class T1, class T2, class T3>
    std::string
    name_from_type( type<std::tuple< T1, T2, T3 >> ) {
        return "std::tuple< "
            + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + ", "
            + name_from_type( type<T3>() ) + " >";
    }

    /// @brief Manually override for const 3-tuples.
    template<class T1, class T2, class T3>
    std::string
    name_from_type( type<std::tuple< T1, T2, T3 > const> ) {
        return "std::tuple< "
            + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + ", "
            + name_from_type( type<T3>() ) + " > const";
    }

    /// @brief Manually override for 4-tuples.
    template<class T1, class T2, class T3, class T4>
    std::string
    name_from_type( type<std::tuple< T1, T2, T3, T4 >> ) {
        return "std::tuple< "
            + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + ", "
            + name_from_type( type<T3>() ) + ", "
            + name_from_type( type<T4>() ) + " >";
    }

    /// @brief Manually override for const 4-tuples.
    template<class T1, class T2, class T3, class T4>
    std::string
    name_from_type( type<std::tuple< T1, T2, T3, T4 > const> ) {
        return "std::tuple< "
            + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + ", "
            + name_from_type( type<T3>() ) + ", "
            + name_from_type( type<T4>() ) + " > const";
    }

    /// @brief Manually override for 5-tuples.
    template<class T1, class T2, class T3, class T4, class T5>
    std::string
    name_from_type( type<std::tuple< T1, T2, T3, T4, T5 >> ) {
        return "std::tuple< "
            + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + ", "
            + name_from_type( type<T3>() ) + ", "
            + name_from_type( type<T4>() ) + ", "
            + name_from_type( type<T5>() ) + " >";
    }

    /// @brief Manually override for const 5-tuples.
    template<class T1, class T2, class T3, class T4, class T5>
    std::string
    name_from_type( type<std::tuple< T1, T2, T3, T4, T5 > const> ) {
        return "std::tuple< "
            + name_from_type( type<T1>() ) + ", "
            + name_from_type( type<T2>() ) + ", "
            + name_from_type( type<T3>() ) + ", "
            + name_from_type( type<T4>() ) + ", "
            + name_from_type( type<T5>() ) + " > const";
    }

    /// @brief Manually override for maps.
    template< class T1, class T2 >
    std::string
    name_from_type( type< std::map< T1, T2 > > ) {
        return "std::map< " + name_from_type( type<T1>() ) + ", " + name_from_type( type<T2>() ) + ">";
    }

    /// @brief Manually override for const maps.
    template< class T1, class T2 >
    std::string
    name_from_type( type< std::map< T1, T2 > const > ) {
        return "std::map< " + name_from_type( type<T1>() ) + ", " + name_from_type( type<T2>() ) + "> const";
    }

    /// @brief Manually override for unordered maps.
    template< class T1, class T2 >
    std::string
    name_from_type( type< std::unordered_map< T1, T2 > > ) {
        return "std::unordered_map< " + name_from_type( type<T1>() ) + ", " + name_from_type( type<T2>() ) + ">";
    }

    /// @brief Manually override for const unordered maps.
    template< class T1, class T2 >
    std::string
    name_from_type( type< std::unordered_map< T1, T2 > const > ) {
        return "std::unordered_map< " + name_from_type( type<T1>() ) + ", " + name_from_type( type<T2>() ) + "> const";
    }

    /// @brief Manually override for unordered maps with custom hashes.
    template< class T1, class T2, class T3 >
    std::string
    name_from_type( type< std::unordered_map< T1, T2, T3 > > ) {
        return "std::unordered_map< " + name_from_type( type<T1>() ) + ", " + name_from_type( type<T2>() ) + ", " + name_from_type( type<T3>() ) + " >";
    }

    /// @brief Manually override for const unordered maps with custom hashes.
    template< class T1, class T2, class T3 >
    std::string
    name_from_type( type< std::unordered_map< T1, T2, T3 > const > ) {
        return "std::unordered_map< " + name_from_type( type<T1>() ) + ", " + name_from_type( type<T2>() ) + ", " + name_from_type( type<T3>() ) + " > const";
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

    /// @brief Manually override for const booleans.
    template<>
    std::string
    name_from_type< bool const >(type<bool const>);

    /// @brief Manually override for unsigned short ints.
    template<>
    std::string
    name_from_type< unsigned short >(type<unsigned short>);

    /// @brief Manually override for const unsigned short ints.
    template<>
    std::string
    name_from_type< unsigned short const >(type<unsigned short const>);

    /// @brief Manually override for unsigned ints.
    template<>
    std::string
    name_from_type< unsigned int >(type<unsigned int>);

    /// @brief Manually override for const unsigned ints.
    template<>
    std::string
    name_from_type< unsigned int const >(type<unsigned int const>);

    /// @brief Manually override for unsigned long ints.
    template<>
    std::string
    name_from_type< unsigned long >(type<unsigned long>);

    /// @brief Manually override for const unsigned long ints.
    template<>
    std::string
    name_from_type< unsigned long const >(type<unsigned long const>);

    /// @brief Manually override for signed short ints.
    template<>
    std::string
    name_from_type< signed short >(type<signed short>);

    /// @brief Manually override for const signed short ints.
    template<>
    std::string
    name_from_type< signed short const >(type<signed short const>);

    /// @brief Manually override for signed ints.
    template<>
    std::string
    name_from_type< signed int >(type<signed int>);

    /// @brief Manually override for const signed ints.
    template<>
    std::string
    name_from_type< signed int const >(type<signed int const>);

    /// @brief Manually override for signed long ints.
    template<>
    std::string
    name_from_type< signed long >(type<signed long>);

    /// @brief Manually override for const signed long ints.
    template<>
    std::string
    name_from_type< signed long const >(type<signed long const>);

    /// @brief Manually override for floats.
    template<>
    std::string
    name_from_type< float >(type<float>);

    /// @brief Manually override for const floats.
    template<>
    std::string
    name_from_type< float const >(type<float const>);

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

    /// @brief Manually override for const doubles.
    template<>
    std::string
    name_from_type< double const >(type<double const>);

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

    /// @brief Manually override for size pair hashes.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash >( type< masala::base::size_pair_hash > );

    /// @brief Manually override for const size pair hashes.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash const >( type< masala::base::size_pair_hash const > );

    /// @brief Manually override for size pair hash instances.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash & >( type< masala::base::size_pair_hash & > );

    /// @brief Manually override for const size pair hash const instances.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash const & >( type< masala::base::size_pair_hash const & > );

    /// @brief Manually override for Eigen matrices.
    template<class T>
    std::string
    name_from_type(type<Eigen::Matrix<T, Eigen::Dynamic, Eigen::Dynamic>>) {
        return "Eigen::Matrix< " + name_from_type(type<T>()) + ", Eigen::Dynamic, Eigen::Dynamic >";
    }

} // namespace api
} // namespace base
} // namespace masala

#endif //Masala_src_base_api_names_from_types_tmpl_hh