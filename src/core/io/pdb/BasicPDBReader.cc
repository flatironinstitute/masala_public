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

/// @file src/core/chemistry/BasicPDBReader.cc
/// @brief A class for reading the basic information from a PDB file quickly, and
/// setting up a minimal pose.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/io/pdb/BasicPDBReader.hh>

// Core headers:
#include <core/pose/Pose.hh>
#include <core/chemistry/Molecules.hh>
#include <core/chemistry/atoms/AtomInstance.hh>
#include <core/types.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/utility/string/string_parsing.tmpl.hh>

// STL headers:
#include <sstream>
#include <array>


namespace core {
namespace io {
namespace pdb {


/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
BasicPDBReaderSP
BasicPDBReader::clone() const {
    return std::make_shared< BasicPDBReader >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
BasicPDBReaderSP
BasicPDBReader::deep_clone() const {
    BasicPDBReaderSP reader_copy( std::make_shared< BasicPDBReader >( *this ) );
    reader_copy->make_independent();
    return reader_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void
BasicPDBReader::make_independent() {
    
}

/// @brief Returns "BasicPDBReader".
std::string
BasicPDBReader::class_name() const {
    return "BasicPDBReader";
}

/// @brief Every class can provide its own namespace.  This returns "core::io::pdb".
std::string
BasicPDBReader::class_namespace() const {
    return "core::io::pdb";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given the contents of a PDB file, generate a Pose.
core::pose::PoseSP
BasicPDBReader::pose_from_pdb_file_contents(
    std::vector< std::string > const & file_lines
) const {
    core::pose::PoseSP pose( std::make_shared< core::pose::Pose >() );

    std::vector< bool > atom_lines_read( file_lines.size(), false ); // Allows us to skip re-parsing the same lines.

    add_atoms_from_file_lines( *pose, file_lines, atom_lines_read );
    // add_bonds_from_conect_and_link_records( *pose, file_lines );
    // infer_bonds( *pose );

    return pose;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Read the ATOM and HETATM lines in a PDB file, and add atoms to a Pose.
/// @details This modifies pose, as well as atom_lines_read, marking off which lines
/// in the file are ATOM or HETATM lines to avoid re-parsing these lines later.
/// @note In its current form, this does NOT set up residue information.  It only assigns
/// atom coordinates and identities.
void
BasicPDBReader::add_atoms_from_file_lines(
    core::pose::Pose & pose,
    std::vector< std::string > const & file_lines,
    std::vector< bool > & atom_lines_read
) const {
    for( core::Size i(0), imax(file_lines.size()); i<=imax; ++i ) {
        if( atom_lines_read[i] ) continue;
        std::string const & curline( file_lines[i] );
        if( curline.size() < 6 ) continue; //Skip short lines.
        std::string const curline_record( curline.substr(0, 6) );
        if( curline_record != "ATOM  " && curline_record != "HETATM" ) continue;

        CHECK_OR_THROW_FOR_CLASS( curline.size() >= 80, "add_atoms_from_file_lines", "Expected 80-character ATOM or HETATM record.  Instead got:\n" + curline + "\n" );

        // Mark this as an ATOM or HETATOM line:
        atom_lines_read[i] = true;

        // Just parsing out some of the salient information -- not the residue annotations at this time.
        std::string const curline_atomno( curline.substr(6, 5) );
        std::string const curline_atomname( curline.substr(12, 4) );
        std::string const curline_xcoord( curline.substr(30, 8) );
        std::string const curline_ycoord( curline.substr(38, 8) );
        std::string const curline_zcoord( curline.substr(46, 8) );
        std::string const curline_element( curline.substr(76, 2) );

        // Containers:
        signed long const atomno( base::utility::string::parse_string< signed long >( curline_atomno, true ) );
        std::array< core::Real, 3 > coords{
            base::utility::string::parse_string< core::Real >( curline_xcoord, true ),
            base::utility::string::parse_string< core::Real >( curline_ycoord, true ),
            base::utility::string::parse_string< core::Real >( curline_zcoord, true )
        };

        // The new atom.
        core::chemistry::atoms::AtomInstanceSP newatom( std::make_shared< core::chemistry::atoms::AtomInstance >( curline_atomname, atomno, curline_element ) );
        pose.molecules_nonconst().add_atom( newatom, coords );
    }
}


} // namespace pdb
} // namespace io
} // namespace core
