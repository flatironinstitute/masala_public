/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/core/molecular_system/kinematics/KinematicDataRepresentationBase.hh
/// @brief Headers for a base class for Masala kinematic data representations, which facilitate kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).  This class is not intended
/// to be instantiated outside of the API system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_molecular_system_kinematics_KinematicDataRepresentationBase_hh
#define Masala_src_core_molecular_system_kinematics_KinematicDataRepresentationBase_hh

// Forward declarations:
#include <core/molecular_system/kinematics/KinematicDataRepresentationBase.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentation.hh>

namespace masala {
namespace core {
namespace molecular_system {
namespace kinematics {

/// @brief A base class for Masala kinematic data representations, which facilitate kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).  This class is not intended
/// to be instantiated outside of the API system.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class KinematicDataRepresentationBase : public masala::base::managers::engine::MasalaDataRepresentation {

	typedef masala::base::managers::engine::MasalaDataRepresentation Parent;
	typedef masala::base::managers::engine::MasalaDataRepresentationSP ParentSP;
	typedef masala::base::managers::engine::MasalaDataRepresentationCSP ParentCSP;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	KinematicDataRepresentationBase() = default;

	/// @brief Copy constructor.  Explicit due to mutex.
	KinematicDataRepresentationBase( KinematicDataRepresentationBase const & src );

	/// @brief Assignment operator.  Explicit due to mutex.
	KinematicDataRepresentationBase & operator=( KinematicDataRepresentationBase const & src );

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~KinematicDataRepresentationBase() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the class name.  Returns "KinematicDataRepresentationBase".
	std::string class_name() const override;

	/// @brief Get the class namespace.  Returns "masala::core::molecular_system::kinematics".
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS FOR PLUGINS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the category or categories for this plugin class.
	/// @returns {{ "KinematicDataRepresentation" }}.
    std::vector< std::vector< std::string > >
    get_categories() const override;

    /// @brief Get the keywords for this plugin class.
	/// @returns Returns { "kinematic_data_representation" }.
    std::vector< std::string >
    get_keywords() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// DATA REPRESENTATION CATEGORIES, COMPATIBILITY, AND PROPERTIES FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the categories that this data representation plugin falls into.
	/// @returns {{ "KinematicDataRepresentation" }}.
	std::vector< std::vector< std::string > >
	get_data_representation_categories() const override;

	/// @brief Get the keywords that this data representation plugin has.
	/// @returns Returns { "kinematic_data_representation" }.
	std::vector< std::string >
	get_data_representation_keywords() const override;

	/// @brief Get the MasalaEngines that with which this data representation plugin
	/// is DEFINITELY compatible.  (There may be other engines with which it is also
	/// compatible, so this is not necessarily an exhaustive list.)
	/// @returns An empty list right now.  May change later.
	std::vector< std::string >
	get_compatible_masala_engines() const override;

	/// @brief Get the MasalaEngines that with which this data representation plugin
	/// is DEFINITELY NOT compatible.  (There may be other engines with which it is also
	/// not compatible, so this is not necessarily an exhaustive list.)
	/// @returns An empty list right now.
	std::vector< std::string >
	get_incompatible_masala_engines() const override;

	/// @brief Get the properties that this MasalaDataRepresentation has.  (Note that this can be
	/// a non-exhaustive list.  If one data representation says it has the property
	/// "linearly-scaling", another could also be linearly scaling despite not listing this.)
	/// @returns { "kinematic_data_representation" }.
	std::vector< std::string >
	get_present_data_representation_properties() const override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Is this data representation empty?
	/// @details Must be implemented by derived classes.  Should return its value && the parent class protected_empty().  Performs no mutex-locking.
	/// @returns True if no data have been loaded into this data representation, false otherwise.
	/// @note This does not report on whether the data representation has been configured; only whether it has been loaded with data.
	bool
	protected_empty() const override;

	/// @brief Remove the data loaded in this object.  Note that this does not result in the configuration being discarded.
	/// @details Must be implemented by derived classes, and should call parent class protected_clear().  Performs no mutex-locking.
	void
	protected_clear() override;

	/// @brief Remove the data loaded in this object AND reset its configuration to defaults.
	/// @details Must be implemented by derived classes, and should call parent class protected_reset().  Performs no mutex-locking.
	void
	protected_reset() override;

	/// @brief Make this object independent by deep-cloning all of its contained objects.  Must be implemented
	/// by derived classses.  Performs no mutex-locking.
	void
	protected_make_independent() override;

	/// @brief Called by the assignment operator and the copy constructor, this copies all data.  Must be implemented by
	/// derived classes.  Performs no mutex locking.
	/// @param src The object that we are copying from.
	void
	protected_assign(
		masala::base::managers::engine::MasalaDataRepresentation const & src
	) override;

}; // class KinematicDataRepresentationBase

} // namespace kinematics
} // namespace molecular_system
} // namespace core
} // namespace masala

#endif //Masala_src_core_molecular_system_kinematics_KinematicDataRepresentationBase_hh