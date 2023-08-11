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

/// @file src/base/managers/engine/MasalaDataRepresentationCreator.hh
/// @brief A pure virtual base class for creators for data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationCreator_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationCreator_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginCreator.hh>
#include <base/managers/engine/MasalaDataRepresentationAPI.fwd.hh>
#include <base/managers/engine/MasalaDataRepresentationManager.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A pure virtual base class for creators for data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationCreator : public masala::base::managers::plugin_module::MasalaPluginCreator {

    friend class masala::base::managers::engine::MasalaDataRepresentationManager;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationCreator() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationCreator( MasalaDataRepresentationCreator const & ) = delete;

    /// @brief Destructor.
    ~MasalaDataRepresentationCreator() override = default;

    /// @brief Get the class name, static version.
    /// @returns "MasalaDataRepresentationCreator".
    static
    std::string
    class_name_static();

    /// @brief Get the class namespace, static version.
    /// @returns "masala::base::managers::engine".
    static
    std::string
    class_namespace_static();

    /// @brief Get the class namespace and name, static version.
    /// @returns "masala::base::managers::engine::MasalaDataRepresentationCreator".
    static
    std::string
    class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Creators must implement a create_data_representation() function.  Under the
    /// hood this just calls create_plugin_object().
    MasalaDataRepresentationAPISP
    create_data_representation() const;

    /// @brief Get the categories that this data representation plugin falls into.
    /// @details Categories are hierarchical, with the hierarchy represented as a vector of
    /// strings.  One data representation category can be classified into multiple categories.
    virtual
    std::vector< std::vector< std::string > >
    get_data_representation_categories() const = 0;

    /// @brief Get the MasalaEngines that with which this data representation plugin
    /// is DEFINITELY compatible.  (There may be other engines with which it is also
    /// compatible, so this is not necessarily an exhaustive list.)
    /// @note The list is by full name (i.e. namespace + name), so for instance
    /// "specialized_masala_plugins::optimizers::SpecializedChargeOptimizer".
    virtual
    std::vector< std::string >
    get_compatible_masala_engines() const = 0;

    /// @brief Get the MasalaEngines that with which this data representation plugin
    /// is DEFINITELY NOT compatible.  (There may be other engines with which it is also
    /// not compatible, so this is not necessarily an exhaustive list.)
    /// @details The default implementation returns an empty list.
    /// @note The list is by full name (i.e. namespace + name), so for instance
    /// "specialized_masala_plugins::optimizers::SpecializedChargeOptimizer".
    virtual
    std::vector< std::string >
    get_incompatible_masala_engines() const = 0;

    /// @brief Get the properties that this MasalaDataRepresentation has.  (Note that this can be
    /// a non-exhaustive list.  If one data representation says it has the property
    /// "linearly-scaling", another could also be linearly scaling despite not listing this.)
    virtual
    std::vector< std::string >
    get_present_data_representation_properties() const = 0;

    /// @brief Get the properties of this MasalaDataRepresentation that might possibly be present.
	/// @details Obviously, this is a non-exhuastive list.
    virtual
	std::vector< std::string >
	get_possibly_present_data_representation_properties() const = 0;

    /// @brief Get the properties that this MasalaDataRepresentation DEFINITELY lacks.
    /// Note that this is inevitably a non-exhaustive list.
    virtual
    std::vector< std::string >
    get_absent_data_representation_properties() const = 0;

    /// @brief Get the properties of this MasalaDataRepresentation that might possibly be absent.
	/// @details Obviously, this is a non-exhuastive list.
    virtual
	std::vector< std::string >
	get_possibly_absent_data_representation_properties() const = 0;

};

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationCreator_hh