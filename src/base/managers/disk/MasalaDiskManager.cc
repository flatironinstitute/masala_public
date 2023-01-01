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

/// @file src/base/managers/disk/MasalaDiskManager.cc
/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/disk/MasalaDiskManager.hh>

// STL headers:
#include <string>
#include <fstream> //This is the only place in the Masala codebase where this header is permitted to be included.

namespace masala {
namespace base {
namespace managers {
namespace disk {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Instantiate the static singleton and get a handle to it.
MasalaDiskManagerHandle
MasalaDiskManager::get_instance() {
    static const MasalaDiskManager disk_manager;
    return &disk_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaDiskManager".
std::string
MasalaDiskManager::class_name() const {
    return "MasalaDiskManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::disk".
std::string
MasalaDiskManager::class_namespace() const {
    return "masala::base::managers::disk";
}

/// @brief Write a string to an ASCII file.
/// @details TRIGGERS WRITE TO DISK!
void
MasalaDiskManager::write_ascii_file(
    std::string const & file_name,
    std::string const & file_contents
) const {
    std::lock_guard< std::mutex > lock( disk_io_mutex_);
    std::ofstream filehandle( file_name );
    filehandle << file_contents;
    filehandle.close();
}

/// @brief Read the contents of an ASCII file to a vector of strings.
std::vector< std::string >
MasalaDiskManager::read_ascii_file_to_string_vector(
    std::string const & file_name
) const {
    std::vector< std::string > outvec;
    std::lock_guard< std::mutex > lock( disk_io_mutex_);
    std::ifstream filehandle( file_name );
    std::string stringbuf;
    while( !filehandle.eof() ) {
        outvec.push_back( std::string() );
        std::getline( filehandle, outvec[outvec.size() - 1] );
    }
    filehandle.close();
    return outvec;
}

} // namespace disk
} // namespace managers
} // namespace base
} // namespace masala
