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

/// @file src/base/MasalaObject.hh
/// @brief A base class for all Masala derived classes.  This allows the possibility of having a
/// generic MasalaObject pointer or shared pointer.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_MasalaObject_hh
#define Masala_src_base_MasalaObject_hh

// Forward declarations.
#include <base/MasalaObject.fwd.hh>
#include <base/api/MasalaObjectAPIDefinition.fwd.hh>

namespace base {

/// @brief A base class for all Masala derived classes.  This allows the possibility of having a
/// generic MasalaObject pointer or shared pointer.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObject {

public:

	/// @brief Default constructor.
	MasalaObject() = default;

	/// @brief Copy constructor.
	MasalaObject( MasalaObject const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~MasalaObject() = 0;

	/// @brief Every class can name itself.
	virtual std::string class_name() const = 0;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS (OVERRIDABLE)
////////////////////////////////////////////////////////////////////////////////

	/// @brief Does this object return an API definition?
	/// @details By default, returns false.  Derived classes might, though.
	bool has_api_definition() const;

	/// @brief Get an object describing the API for this object.
	/// @details Default implementation returns nullptr.  May be overridden by
	/// derived objects.
	virtual
	MasalaObjectAPIDefinitionCSP
	get_api_definition() const;


}; // class MasalaObject

} //namespace base

#endif //Masala_src_base_MasalaObject_hh