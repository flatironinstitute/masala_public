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

/// @file src/base/managers/configuration/MasalaConfigurationManager.hh
/// @brief A static singleton for managing global configuration for a Masala session.
/// @details The sorts of options that get set globally are defaults, which can be overridden
/// on a case-by-case basis.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_configuration_MasalaConfigurationManager_hh
#define Masala_src_base_managers_configuration_MasalaConfigurationManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/configuration/MasalaConfigurationManager.fwd.hh>

// Base headers:
#include <base/managers/configuration/ConfigurationBase.fwd.hh>
#include <base/api/names_from_types.tmpl.hh>

// STL headers:
#include <map>

namespace base {
namespace managers {
namespace configuration {


/// @brief A static singleton for managing global configuration for a Masala session.
/// @details The sorts of options that get set globally are defaults, which can be overridden
/// on a case-by-case basis.
class MasalaConfigurationManager : public base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaConfigurationManagerHandle get_instance();

private:

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaConfigurationManager() = default;

public:

    /// @brief No copy constructor.
    MasalaConfigurationManager( MasalaConfigurationManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaConfigurationManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaConfigurationManager() = default;

    /// @brief Get the name of this object.
    /// @details Returns "MasalaConfigurationManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "base::managers::configuration".
    std::string
    class_namespace() const override;

private:

};

} // namespace configuration
} // namespace managers
} // namespace base

#endif // Masala_src_base_managers_configuration_MasalaConfigurationManager_hh