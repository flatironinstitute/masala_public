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

/// @file src/base/managers/engine/MasalaDataRepresentationManager.hh
/// @brief A static singleton for managing available data representaitons.
/// @details Modules may register and retrieve data representations by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationManager_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationManager.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationBase.fwd.hh>
#include <base/managers/engine/MasalaDataRepresentationCreatorBase.fwd.hh>

// STL headers:
#include <map>
#include <mutex>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A static singleton for managing available data representaitons.
/// @details Modules may register and retrieve data representations by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaDataRepresentationManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaDataRepresentationManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaDataRepresentationManager( MasalaDataRepresentationManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaDataRepresentationManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaDataRepresentationManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaDataRepresentationManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "base::managers::engine".
    std::string
    class_namespace() const override;

    /// @brief Create a data representation, by name.
    /// @details If throw_if_missing is true, this function will throw an exception if it can't
    /// find a data representation creator for the specified data representation type.  Otherwise, it will return nullptr.
    MasalaDataRepresentationBaseSP
    create_data_representation(
        std::string const & data_representation_type,
        bool const throw_if_missing = true
    ) const;

    /// @brief Register a data representation, by name.
    /// @details If throw_if_present is true, an exception is thrown if the data_representation_name is
    /// already registered.  Otherwise, this silently replaces the registered data representation.
    void
    register_data_representation(
        std::string const & data_representation_name,
        MasalaDataRepresentationCreatorBaseCSP data_representation_creator,
        bool const throw_if_present = true
    );

    /// @brief Unregister a data representation, by name.
    /// @brief If the data_representation_name data representation has not been registered,
    /// then (a) if throw_if_missing is true, an exception is thrown, or (b) if it is false,
    /// nothing happens.
    void
    unregister_data_representation(
        std::string const & data_representation_name,
        bool const throw_if_missing = true
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex to lock this object.
    mutable std::mutex masala_data_representation_manager_mutex_;

    /// @brief A map of string to data representation creator.
    std::map< std::string, MasalaDataRepresentationCreatorBaseCSP > data_representation_creators_;

};

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationManager_hh