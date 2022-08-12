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

/// @file src/core/chemistry/AtomInstance.fwd.hh
/// @brief Forward declarations for a class contiaining a description of the properties of
/// a particular atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_AtomInstance_fwd_hh
#define Masala_src_core_chemistry_AtomInstance_fwd_hh

#include <memory>

namespace core {
namespace chemistry {

    class AtomInstance;

    using AtomInstanceSP = std::shared_ptr< AtomInstance >;
    using AtomInstanceCSP = std::shared_ptr< AtomInstance const >;
    using AtomInstanceWP = std::weak_ptr< AtomInstance >;
    using AtomInstanceCWP = std::weak_ptr< AtomInstance const >;

} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_AtomInstance_fwd_hh