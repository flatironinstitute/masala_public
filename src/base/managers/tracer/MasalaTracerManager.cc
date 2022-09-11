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

/// @file src/base/managers/tracer/MasalaTracerManager.cc
/// @brief A static singleton for managing global configuration for a Masala session.
/// @details The sorts of options that get set globally are defaults, which can be overridden
/// on a case-by-case basis.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/tracer/MasalaTracerManager.hh>

// Base headers:
#include <base/types.hh>

// Utility headers:
#include <utility/string/string_manipulation.hh>

// STL headers:
#include <string>
#include <iostream>

namespace base {
namespace managers {
namespace tracer {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaTracerManagerHandle
MasalaTracerManager::get_instance() {
    static MasalaTracerManager config_manager;
    return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaTracerManager".
std::string
MasalaTracerManager::class_name() const {
    return "MasalaTracerManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "base::managers::tracer".
std::string
MasalaTracerManager::class_namespace() const {
    return "base::managers::tracer";
}

    /// @brief Check whether a particular tracer is enabled.
    /// @details If the tracer is in the list of tracers specifically enabled or disabled, the
    /// tracer's status is returned.  Otherwise, the global default is returned.
    bool
    MasalaTracerManager::tracer_is_enabled(
        std::string const & tracer_name
    ) const {
        std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
        std::map< std::string, bool >::const_iterator it( explicitly_enabled_or_disabled_tracers_.find( tracer_name ) );
        if( it != explicitly_enabled_or_disabled_tracers_.end() ) {
            return it->second;
        }
        return global_tracer_default_;
    }

    /// @brief Check whether the global default for unspecified tracers is enabled or disabled.
    bool
    MasalaTracerManager::global_tracer_default() const {
        std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
        return global_tracer_default_;
    }

    /// @brief Set whether the global default for unspecified tracers is enabled or disabled.
    void
    MasalaTracerManager::set_global_tracer_default(
        bool const setting
    ) {
        std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );
        global_tracer_default_ = setting;
    }

/// @brief Write a message to a tracer.
/// @param tracer_name The tracer to which we are writing.
/// @param message The text that we are writing.  This gets split by lines, with each line preceded
/// by the tracer name.
/// @param skip_check If true, we don't bother to check whether the tracer is enabled.  If false, we
/// check and skip writing if the tracer is disabled.  Default false.
void
MasalaTracerManager::write_to_tracer(
    std::string const & tracer_name,
    std::string const & message,
    bool const skip_check /*= false*/
) const {
    std::lock_guard< std::mutex > lock( masala_tracer_manager_mutex_ );

    // Check whether the tracer is enabled:
    if( !skip_check ) {
        std::map< std::string, bool >::const_iterator it( explicitly_enabled_or_disabled_tracers_.find( tracer_name ) );
        if( it != explicitly_enabled_or_disabled_tracers_.end() ) {
            if( !(it->second) ) {
                return;
            }
        } else {
            if( !global_tracer_default_ ) {
                return;
            }
        }
    }

    // Write the message to the tracer.
    std::vector< std::string > const splitlines( utility::string::split_by_newlines( message ) );
    for( base::Size i(0), imax(splitlines.size()); i<imax; ++i ) {
        std::cout << tracer_name << ": " << splitlines[i] << "\n";
    }
    std::cout.flush();
}

} // namespace tracer
} // namespace managers
} // namespace base
