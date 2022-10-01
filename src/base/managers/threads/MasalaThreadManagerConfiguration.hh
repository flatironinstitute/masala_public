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

/// @file src/base/managers/threads/MasalaThreadManagerConfiguration.hh
/// @brief A container of configuration settings for the MasalaThreadManager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_hh
#define Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_hh

// Parent header
#include <base/managers/configuration/ConfigurationBase.hh>

// Project headers:
#include <base/managers/threads/MasalaThreadManagerConfiguration.fwd.hh>

// Base headers
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.fwd.hh>

// STL headers
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief A container of configuration settings for the MasalaThreadManager singleton.
class MasalaThreadManagerConfiguration : public masala::base::managers::configuration::ConfigurationBase {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaThreadManagerConfiguration() = delete;

    /// @brief MasalaConfigurationManager-authorized constructor.
    /// @details The MasalaConfigurationManagerAuthorization object is an object that only the
    /// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
    /// ConfigurationBase-derived object.
    MasalaThreadManagerConfiguration( masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey );

    /// @brief Copy constructor.
    MasalaThreadManagerConfiguration( MasalaThreadManagerConfiguration const & src ) = default;

    /// @brief Default destructor.
    ~MasalaThreadManagerConfiguration() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared_ptr to the copy.
    MasalaThreadManagerConfigurationSP clone() const;

    /// @brief Deep operation: make an independent copy of this object and return a shared_ptr to the copy.
    MasalaThreadManagerConfigurationSP deep_clone() const;

    /// @brief Returns "MasalaThreadManagerConfiguration".
    std::string class_name() const override;

    /// @brief Returns "masala::base::managers::threads".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////


private:

////////////////////////////////////////////////////////////////////////////////
// Data
////////////////////////////////////////////////////////////////////////////////

};

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_hh
