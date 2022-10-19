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

/// @file src/core_api/base_classes/selectors/atom_selectors/AtomSelector.hh
/// @brief Header for a pure virtual base class for AtomSelectors.
/// @details AtomSelectors select atoms in a pose based on some rule.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_hh
#define Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_hh

// Parent class:
#include <core_api/base_classes/selectors/Selector.hh>

// Forward declarations:
#include <core_api/base_classes/selectors/atom_selectors/AtomSelector.fwd.hh>

// Core API headers:
#include <core_api/base_classes/selectors/Selection.fwd.hh>
#include <core_api/base_classes/selectors/atom_selectors/AtomSelection.fwd.hh>
#include <core_api/auto_generated_api/pose/Pose_API.fwd.hh>

namespace masala {
namespace core_api {
namespace base_classes {
namespace selectors {
namespace atom_selectors {

/// @brief A pure virtual base class for AtomSelectors.
/// @details AtomSelectors select atoms in a pose based on some rule.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomSelector : public core_api::base_classes::selectors::Selector {

public:

	/// @brief Default constructor.
	AtomSelector() = default;

	/// @brief Copy constructor.
	AtomSelector( AtomSelector const & ) = default;

	/// @brief Destructor.
	~AtomSelector() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Given the current pose, generate the selection.
	/// @details Calls generate_atom_selection(), which must be implemented
	/// by derived classes.
	core_api::base_classes::selectors::SelectionCSP
	generate_selection(
		core_api::auto_generated_api::pose::Pose_API const & pose
	) const override;

	/// @brief Given the current pose, generate the atom selection.
	/// @details Pure virtual function.
	virtual
	AtomSelectionCSP
	generate_atom_selection(
		core_api::auto_generated_api::pose::Pose_API const & pose
	) const = 0;

}; // class AtomSelector

} // namespace atom_selectors
} // namespace selectors
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_selectors_atom_selectors_AtomSelector_hh