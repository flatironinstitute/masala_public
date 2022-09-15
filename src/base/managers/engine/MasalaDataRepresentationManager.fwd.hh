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

/// @file src/base/managers/engine/MasalaDataRepresentationManager.fwd.hh
/// @brief Forward declarations for a static singleton for managing available data representaitons.
/// @details Modules may register and retrieve data representations by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationManager_fwd_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationManager_fwd_hh

namespace masala {
namespace base {
namespace managers {
namespace engine {

    class MasalaDataRepresentationManager;

    /// Note that singletons define no shared pointers or weak pointers.  Nonconst to allow
    /// lazy loading of data.
    using MasalaDataRepresentationManagerHandle = MasalaDataRepresentationManager *;

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationManager_fwd_hh