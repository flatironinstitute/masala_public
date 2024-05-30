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

/// @file src/base/managers/engine/MasalaEngineCreator.hh
/// @brief A pure virtual base class for creators for engines.
/// @details Subclasses will be needed for each Masala engine type that a library defines.
/// These must be registered with the MasalaEngineManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngineCreator_hh
#define Masala_src_base_managers_engine_MasalaEngineCreator_hh

// Forward declarations:
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginCreator.hh>
#include <base/managers/engine/MasalaEngineAPI.fwd.hh>
#include <base/managers/engine/MasalaEngineManager.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A pure virtual base class for creators for engines.
/// @details Subclasses will be needed for each Masala engine type that a library defines.
/// These must be registered with the MasalaEngineManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineCreator : public masala::base::managers::plugin_module::MasalaPluginCreator {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaEngineCreator() = default;

	/// @brief Copy constructor, deleted.
	MasalaEngineCreator( MasalaEngineCreator const & ) = delete;

	/// @brief Destructor.
	~MasalaEngineCreator() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief The create_engine() function just calls the
    /// create_plugin_object() function under the hood.
	MasalaEngineAPISP
	create_engine() const;

    /// @brief Get the categories that this engine plugin falls into.
    /// @details Categories are hierarchical, with the hierarchy represented as a vector of
    /// strings.  One engine can be classified into multiple categories.
    virtual
    std::vector< std::vector< std::string > >
    get_engine_categories() const = 0;

}; // class MasalaEngineCreator

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaEngineCreator_hh