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

// STL headers
#include <string>

namespace base {
namespace api {

    /// @brief Default behaviour is compiler-specific, and not ideal.
    template <typename T>
    std::string
    name_from_type() {
        return typeid(T).name();
    }

    /// @brief Manually override for unsigned short ints.
    template<>
    std::string
    name_from_type< unsigned short >() {
        return "unsigned short int";
    }

    /// @brief Manually override for unsigned ints.
    template<>
    std::string
    name_from_type< unsigned int >() {
        return "unsigned int";
    }

    /// @brief Manually override for unsigned long ints.
    template<>
    std::string
    name_from_type< unsigned long >() {
        return "unsigned long int";
    }

    /// @brief Manually override for signed short ints.
    template<>
    std::string
    name_from_type< signed short >() {
        return "signed short int";
    }

    /// @brief Manually override for signed ints.
    template<>
    std::string
    name_from_type< signed int >() {
        return "signed int";
    }

    /// @brief Manually override for signed long ints.
    template<>
    std::string
    name_from_type< signed long >() {
        return "signed long int";
    }

    /// @brief Manually override for floats.
    template<>
    std::string
    name_from_type< float >() {
        return "float";
    }

    /// @brief Manually override for doubles.
    template<>
    std::string
    name_from_type< double >() {
        return "double";
    }

    /// @brief Manually override for strings.
    template<>
    std::string
    name_from_type< std::string >() {
        return "std::string";
    }

} // namespace api
} // namespace base

#endif //Masala_src_base_api_names_from_types_tmpl_hh