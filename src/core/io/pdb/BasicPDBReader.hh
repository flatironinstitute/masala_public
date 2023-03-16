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

/// @file src/core/chemistry/BasicPDBReader.hh
/// @brief A class for reading the basic information from a PDB file quickly, and
/// setting up a minimal molecular system.
/// @note This is intended for testing only.  The proper PDB reader will be in the
/// standard Masala plugins library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_io_pdb_BasicPDBReader_hh
#define Masala_src_core_io_pdb_BasicPDBReader_hh

// Forward declarations:
#include <core/io/pdb/BasicPDBReader.fwd.hh>

// Core headers:
#include <core/molecular_system/MolecularSystem.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <string>
#include <vector>

namespace masala {
namespace core {
namespace io {
namespace pdb {

/// @brief A class for reading the basic information from a PDB file quickly, and
/// setting up a minimal molecular system.
/// @note This is intended for testing only.  The proper PDB reader will be in the
/// standard Masala plugins library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class BasicPDBReader : public masala::base::MasalaObject {

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

    /// @brief Every class can provide its own namespace.  This returns "masala::core::io::pdb".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Given the contents of a PDB file, generate a MolecularSystem.
    masala::core::molecular_system::MolecularSystemSP
    molecular_system_from_pdb_file_contents(
        std::vector< std::string > const & file_lines
    ) const;

    /// @brief Given a PDB file name, read the PDB file and generate a MolecularSystem.
    /// @note Warning!  This triggers a read from disk!  This is threadsafe and
    /// properly managed through the disk manager.
    masala::core::molecular_system::MolecularSystemSP
    molecular_system_from_pdb_file_on_disk(
        std::string const & filename
    ) const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a description of the API for the BasicPDBReader class.
    masala::base::api::MasalaObjectAPIDefinitionCWP
    get_api_definition() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Read the ATOM and HETATM lines in a PDB file, and add atoms to a MolecularSystem.
    /// @details This modifies molecular_system, as well as atom_lines_read, marking off which lines
    /// in the file are ATOM or HETATM lines to avoid re-parsing these lines later.
    /// @note In its current form, this does NOT set up residue information.  It only assigns
    /// atom coordinates and identities.
    void
    add_atoms_from_file_lines(
        masala::core::molecular_system::MolecularSystem & molecular_system,
        std::vector< std::string > const & file_lines,
        std::vector< bool > & atom_lines_read
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief A description of this object's interface.
    /// @details Generated on first request.  Persists only as long as this instance
    /// persists.  Weak pointers are handed out.
    masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

};

} // namespace pdb
} // namespace io
} // namespace core
} // namespace masala

#endif // Masala_src_core_io_pdb_BasicPDBReader_hh