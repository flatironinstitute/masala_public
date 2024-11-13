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

/// @file src/base/managers/engine/MasalaEngine.hh
/// @brief A base class for Masala engines, which perform hard calculations of a given type using
/// a given method.
/// @details Subclasses will be defined for kinematic calculations, packing calculations, minimization
/// calculations, etc.  Each of these in turn will have subclasses for performing these using different
/// math libraries, optimizers, hardware, etc.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngine_hh
#define Masala_src_base_managers_engine_MasalaEngine_hh

// Forward declarations:
#include <base/managers/engine/MasalaEngine.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPlugin.hh>
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A base class for Masala engines, which perform hard calculations of a given type using
/// a given method.
/// @details Subclasses will be defined for kinematic calculations, packing calculations, minimization
/// calculations, etc.  Each of these in turn will have subclasses for performing these using different
/// math libraries, optimizers, hardware, etc.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngine : public masala::base::managers::plugin_module::MasalaPlugin {

    friend class MasalaEngineCreator;

protected:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR -- PROTECTED
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaEngine() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

	/// @brief Copy constructor.
	MasalaEngine( MasalaEngine const & ) = default;

	/// @brief Destructor.
	~MasalaEngine() override = default;

	/// @brief Get the namespace and name of this class ("masala::base::managers::engine::MasalaEngine").
	static
    std::string
    class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// ENGINE PUBLIC METHODS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Categories for engines.
    /// @details Like plugin categories, engine categories are hierarchical.  The hieraruchy
    /// is important for deciding what engines are equvalent. For instance, if I had
    /// "Solver"->"KinematicSolver"->"AnalyticKinematicSolver", I could request only the analytic
    /// kinematic solvers, all kinematic solvers, or all solvers in general.
    /// @note An engine may exist in more than one hierarchical category.  The outer vector is
    /// a list of hierarchical categories, and the inner vector is the particular hierarchical
    /// category, from most general to most specific.  Also note that this function is pure
    /// virtual, and must be defined for instantiable Engine subclasses.
    virtual
    std::vector< std::vector < std::string > >
    get_engine_categories() const = 0;

    /// @brief Get the keywords for engines.
    virtual
    std::vector< std::string >
    get_engine_keywords() const = 0;

    /// @brief Is a particular data representation INcompatible with this engine?  Returns true to signal
    /// incompatibility, false otherwise.
    /// @details Default implementation always returns false.  May be overridden to allow engines to perform
    /// runtime checks to assess whether a particular data representation will definitely NOT work with this
    /// engine.
    /// @note If this function returns false, it is not a guarantee that a data representation will work with
    /// this engine, or work efficiently with this engine.
    virtual
    bool
    data_representation_is_incompatible_with_engine(
        MasalaDataRepresentationCreator const & representation
    ) const;

}; // class MasalaEngine

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaEngine_hh