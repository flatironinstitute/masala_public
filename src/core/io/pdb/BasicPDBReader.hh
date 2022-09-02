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

/// @file src/core/chemistry/BasicPDBReader.hh
/// @brief A class for reading the basic information from a PDB file quickly, and
/// setting up a minimal pose.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_io_pdb_BasicPDBReader_hh
#define Masala_src_core_io_pdb_BasicPDBReader_hh

// Forward declarations:
#include <core/io/pdb/BasicPDBReader.fwd.hh>

// Core headers:

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

namespace core {
namespace io {
namespace pdb {

/// @brief A class for reading the basic information from a PDB file quickly, and
/// setting up a minimal pose.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class BasicPDBReader : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    BasicPDBReader() = default;

    /// @brief Copy constructor.
    BasicPDBReader( BasicPDBReader const & src ) = default;

    /// @brief Default destructor.
    ~BasicPDBReader() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    BasicPDBReaderSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    /// @details Threadsafe.  Be sure to update this function whenever a private member is added!
    virtual
    BasicPDBReaderSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "BasicPDBReader".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "core::io::pdb".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////


};

} // namespace pdb
} // namespace io
} // namespace core

#endif // Masala_src_core_io_pdb_BasicPDBReader_hh