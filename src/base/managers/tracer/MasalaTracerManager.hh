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

/// @file src/base/managers/tracer/MasalaTracerManager.hh
/// @brief A static singleton for managing output to the tracer (screen and/or logfile(s)).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_tracer_MasalaTracerManager_hh
#define Masala_src_base_managers_tracer_MasalaTracerManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/tracer/MasalaTracerManager.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <map>
#include <mutex>
#include <thread>

namespace masala {
namespace base {
namespace managers {
namespace tracer {


/// @brief A static singleton for managing output to the tracer (screen and/or logfile(s)).
class MasalaTracerManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaTracerManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaTracerManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaTracerManager( MasalaTracerManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaTracerManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaTracerManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaTracerManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::tracer".
    std::string
    class_namespace() const override;

    /// @brief Check whether a particular tracer is enabled.
    /// @details If the tracer is in the list of tracers specifically enabled or disabled, the
    /// tracer's status is returned.  Otherwise, the global default is returned.
    bool
    tracer_is_enabled(
        std::string const & tracer_name
    ) const;

    /// @brief Check whether the global default for unspecified tracers is enabled or disabled.
    bool global_tracer_default() const;

    /// @brief Set whether the global default for unspecified tracers is enabled or disabled.
    void set_global_tracer_default( bool const setting );

    /// @brief Write a message to a tracer.
    /// @param tracer_name The tracer to which we are writing.
    /// @param message The text that we are writing.  This gets split by lines, with each line preceded
    /// by the tracer name.
    /// @param skip_check If true, we don't bother to check whether the tracer is enabled.  If false, we
    /// check and skip writing if the tracer is disabled.  Default false.
    void
    write_to_tracer(
        std::string const & tracer_name,
        std::string const & message,
        bool const skip_check = false
    ) const;

    /// @brief Get the string for the current thread's ID.
    std::string get_thread_id_string() const;

    /// @brief Register thread ID with the tracer manager.
    void register_thread_id( std::thread::id const system_thread_id, base::Size const masala_thread_id );

    /// @brief Unregister thread ID with the tracer manager.
    void unregister_thread_id( std::thread::id const system_thread_id );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex to lock this object.
    mutable std::mutex masala_tracer_manager_mutex_;

    /// @brief The default setting for tracers.
    /// @details Defaults to "on" ("true") for now.  Will be set from configuration file
    /// at a later time.
    bool global_tracer_default_ = true;

    /// @brief List of tracers that are either explicitly enabled or explicitly disabled.
    std::map< std::string, bool > explicitly_enabled_or_disabled_tracers_;

    /// @brief A mutex for the list of threads that this object knows about.
    mutable std::mutex thread_map_mutex_;

    /// @brief List of threads that this object knows about.
    std::map< std::thread::id, base::Size > thread_map_;

};

} // namespace tracer
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_tracer_MasalaTracerManager_hh