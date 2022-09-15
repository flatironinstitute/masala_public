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

/// @file src/base/managers/disk/MasalaDiskManager.hh
/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_disk_MasalaDiskManager_hh
#define Masala_src_base_managers_disk_MasalaDiskManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/disk/MasalaDiskManager.fwd.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace base {
namespace managers {
namespace disk {

/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
class MasalaDiskManager : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaDiskManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaDiskManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaDiskManager( MasalaDiskManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaDiskManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaDiskManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaDiskManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "base::managers::disk".
    std::string
    class_namespace() const override;

    /// @brief Write a string to an ASCII file.
    void
    write_ascii_file(
        std::string const & file_name,
        std::string const & file_contents
    ) const;

private: // Data

    /// @brief A mutex to ensure that one thread at a time does disk i/o.
    mutable std::mutex disk_io_mutex_;

};

} // namespace disk
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_disk_MasalaDiskManager_hh