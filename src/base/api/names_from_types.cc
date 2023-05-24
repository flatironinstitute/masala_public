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

/// @file src/base/api/names_from_types.cc
/// @brief Given typenames, get human-readable strings.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers
#include <base/api/names_from_types.tmpl.hh>

// STL headers

namespace masala {
namespace base {
namespace api {

    /// @brief Manually override for void.
    template<>
    std::string
    name_from_type< void >(type<void>) {
        return "void";
    }

    /// @brief Manually override for booleans.
    template<>
    std::string
    name_from_type< bool >(type<bool>) {
        return "bool";
    }

    /// @brief Manually override for unsigned short ints.
    template<>
    std::string
    name_from_type< unsigned short >(type<unsigned short>) {
        return "unsigned short int";
    }

    /// @brief Manually override for unsigned ints.
    template<>
    std::string
    name_from_type< unsigned int >(type<unsigned int>) {
        return "unsigned int";
    }

    /// @brief Manually override for unsigned long ints.
    template<>
    std::string
    name_from_type< unsigned long >(type<unsigned long>) {
        return "unsigned long int";
    }

    /// @brief Manually override for signed short ints.
    template<>
    std::string
    name_from_type< signed short >(type<signed short>) {
        return "signed short int";
    }

    /// @brief Manually override for signed ints.
    template<>
    std::string
    name_from_type< signed int >(type<signed int>) {
        return "signed int";
    }

    /// @brief Manually override for signed long ints.
    template<>
    std::string
    name_from_type< signed long >(type<signed long>) {
        return "signed long int";
    }

    /// @brief Manually override for floats.
    template<>
    std::string
    name_from_type< float >(type<float>) {
        return "float";
    }

    /// @brief Manually override for float instances.
    template<>
    std::string
    name_from_type< float & >(type<float&>) {
        return "float &";
    }

    /// @brief Manually override for float const instances.
    template<>
    std::string
    name_from_type< float const & >(type<float const &>) {
        return "float const &";
    }

    /// @brief Manually override for doubles.
    template<>
    std::string
    name_from_type< double >(type<double>) {
        return "double";
    }

    /// @brief Manually override for double instances.
    template<>
    std::string
    name_from_type< double & >(type<double &>) {
        return "double &";
    }

    /// @brief Manually override for double const instances.
    template<>
    std::string
    name_from_type< double const & >(type<double const&>) {
        return "double const &";
    }

    /// @brief Manually override for strings.
    template<>
    std::string
    name_from_type< std::string >(type<std::string>) {
        return "std::string";
    }

    /// @brief Manually override for string instances.
    template<>
    std::string
    name_from_type< std::string & >(type<std::string &>) {
        return "std::string const &";
    }

    /// @brief Manually override for const instance strings.
    template<>
    std::string
    name_from_type< std::string const & >(type<std::string const&>) {
        return "std::string const &";
    }

    /// @brief Manually override for size pair hashes.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash >( type< masala::base::size_pair_hash > ) {
        return "masala::base::size_pair_hash";
    }

    /// @brief Manually override for const size pair hashes.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash const >( type< masala::base::size_pair_hash const > ) {
        return "masala::base::size_pair_hash const";
    }

    /// @brief Manually override for size pair hash instances.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash & >( type< masala::base::size_pair_hash & > ) {
        return "masala::base::size_pair_hash &";
    }

    /// @brief Manually override for const size pair hash const instances.
    template<>
    std::string
    name_from_type< masala::base::size_pair_hash const & >( type< masala::base::size_pair_hash const & > ) {
        return "masala::base::size_pair_hash const &";
    }

} // namespace api
} // namespace base
} // namespace masala
