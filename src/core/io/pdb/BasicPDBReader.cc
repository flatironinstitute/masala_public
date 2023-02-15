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

/// @file src/core/chemistry/BasicPDBReader.cc
/// @brief A class for reading the basic information from a PDB file quickly, and
/// setting up a minimal pose.
/// @note This is intended for testing only.  The proper PDB reader will be in the
/// standard Masala plugins library.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/io/pdb/BasicPDBReader.hh>

// Core headers:
#include <core/pose/Pose.hh>
#include <core/chemistry/Molecules.hh>
#include <core/chemistry/atoms/AtomInstance.hh>
#include <base/types.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/utility/string/string_parsing.tmpl.hh>
#include <base/utility/string/string_manipulation.hh>
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/managers/disk/MasalaDiskManager.hh>

// STL headers:
#include <sstream>
#include <array>

namespace masala {
namespace core {
namespace io {
namespace pdb {


/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
BasicPDBReaderSP
BasicPDBReader::clone() const {
    return masala::make_shared< BasicPDBReader >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
BasicPDBReaderSP
BasicPDBReader::deep_clone() const {
    BasicPDBReaderSP reader_copy( masala::make_shared< BasicPDBReader >( *this ) );
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

/// @brief Every class can provide its own namespace.  This returns "masala::core::io::pdb".
std::string
BasicPDBReader::class_namespace() const {
    return "masala::core::io::pdb";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given the contents of a PDB file, generate a Pose.
core::pose::PoseSP
BasicPDBReader::pose_from_pdb_file_contents(
    std::vector< std::string > const & file_lines
) const {
    masala::core::pose::PoseSP pose( masala::make_shared< masala::core::pose::Pose >() );

    std::vector< bool > atom_lines_read( file_lines.size(), false ); // Allows us to skip re-parsing the same lines.

    add_atoms_from_file_lines( *pose, file_lines, atom_lines_read );
    // add_bonds_from_conect_and_link_records( *pose, file_lines );
    // infer_bonds( *pose );

    return pose;
}

/// @brief Given a PDB file name, read the PDB file and generate a Pose.
/// @note Warning!  This triggers a read from disk!  This is threadsafe and
/// properly managed through the disk manager.
masala::core::pose::PoseSP
BasicPDBReader::pose_from_pdb_file_on_disk(
    std::string const & filename
) const {
    return pose_from_pdb_file_contents(
        base::managers::disk::MasalaDiskManager::get_instance()->read_ascii_file_to_string_vector( filename )
    );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a description of the API for the Pose class.
base::api::MasalaObjectAPIDefinitionCWP
BasicPDBReader::get_api_definition() {
    using namespace masala::base::api;

    if( api_definition_ == nullptr ) {

        MasalaObjectAPIDefinitionSP api_def(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "The BasicPDBReader is intended as a bare-bones means of generating a Pose.  It is "
                "intended ONLY for testing other classes' functionality.  A full PDB reader will be "
                "available in the standard_masala_plugins library.",
                false, false
            )
        );

        // Constructors:
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_ZeroInput < BasicPDBReader > > (
                "BasicPDBReader",
                "Creates a BasicPDBReader."
            )
        );
        api_def->add_constructor(
            masala::make_shared< constructor::MasalaObjectAPIConstructorDefinition_OneInput < BasicPDBReader, BasicPDBReader const & > > (
                "BasicPDBReader",
                "Copy constructor: copies an input BasicPDBReader.",
                "src", "The input BasicPDBReader to copy.  Unaltered by this operation."
            )
        );

        // Work functions:
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput < core::pose::PoseSP, std::vector< std::string > const & > >(
                "pose_from_pdb_file_contents",
                "Given the contents of a PDB file as a vector of strings, generate a Pose and return a "
                "shared pointer to the pose.",
                true, false, false, false,
                "file_lines", "The lines of a PDB file, as a vector of strings (one string per line).",
                "pose", "A shared pointer to the pose generated from the PDb file contents.",
                std::bind( &BasicPDBReader::pose_from_pdb_file_contents, this, std::placeholders::_1 )
            )
        );
        api_def->add_work_function(
            masala::make_shared< work_function::MasalaObjectAPIWorkFunctionDefinition_OneInput< core::pose::PoseSP, std::string const & > >(
                "pose_from_pdb_file_on_disk",
                "Read a PDB file from disk, and return a pose.  Note that invoking this function triggers a read from "
                "disk!  However, this function does use the Masala disk manager to ensure that disk reads are "
                "managed and threadsafe.",
                true, false, false, false,
                "file_name", "The input PDB file.  This file will be read from disk.",
                "pose", "A shared pointer to the pose generated from the PDb file contents.",
                std::bind( &BasicPDBReader::pose_from_pdb_file_on_disk, this, std::placeholders::_1 )
            )
        );

        api_definition_ = api_def; //Make const.
    }

    return api_definition_;
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
    masala::core::pose::Pose & pose,
    std::vector< std::string > const & file_lines,
    std::vector< bool > & atom_lines_read
) const {
    for( masala::base::Size i(0), imax(file_lines.size()); i<imax; ++i ) {
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
        std::string const curline_atomname( base::utility::string::trim( curline.substr(12, 4) ) );
        std::string const curline_xcoord( curline.substr(30, 8) );
        std::string const curline_ycoord( curline.substr(38, 8) );
        std::string const curline_zcoord( curline.substr(46, 8) );
        std::string const curline_element( base::utility::string::trim( curline.substr(76, 2) ) );

        // Containers:
        signed long const atomno( masala::base::utility::string::parse_string< signed long >( curline_atomno, true ) );
        std::array< masala::base::Real, 3 > coords{
            masala::base::utility::string::parse_string< masala::base::Real >( curline_xcoord, true ),
            masala::base::utility::string::parse_string< masala::base::Real >( curline_ycoord, true ),
            masala::base::utility::string::parse_string< masala::base::Real >( curline_zcoord, true )
        };

        // The new atom.
        masala::core::chemistry::atoms::AtomInstanceSP newatom(
            masala::make_shared< masala::core::chemistry::atoms::AtomInstance >(
                curline_atomname, atomno, curline_element
            )
        );
        pose.molecules_nonconst().add_atom( newatom, coords );
    }
}


} // namespace pdb
} // namespace io
} // namespace core
} // namespace masala
