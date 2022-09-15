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

/// @file src/core/chemistry/BasicPDBReader.fwd.hh
/// @brief Forward declarations for a class for reading the basic information
/// from a PDB file quickly, and setting up a minimal pose.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_io_pdb_BasicPDBReader_fwd_hh
#define Masala_src_core_io_pdb_BasicPDBReader_fwd_hh

#include <memory>

namespace masala {
namespace core {
namespace io {
namespace pdb {

    class BasicPDBReader;

    using BasicPDBReaderSP = std::shared_ptr< BasicPDBReader >;
    using BasicPDBReaderCSP = std::shared_ptr< BasicPDBReader const >;
    using BasicPDBReaderWP = std::weak_ptr< BasicPDBReader >;
    using BasicPDBReaderCWP = std::weak_ptr< BasicPDBReader const >;

} // namespace pdb
} // namespace io
} // namespace core
} // namespace masala

#endif // Masala_src_core_io_pdb_BasicPDBReader_fwd_hh