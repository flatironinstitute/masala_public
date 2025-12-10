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

/// @file src/base/managers/database/elements/ElementType.fwd.hh
/// @brief Forward declarations for a class that describes a particular element.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_database_elements_ElementType_fwd_hh
#define Masala_src_base_managers_database_elements_ElementType_fwd_hh

#include <base/managers/memory/util.hh>

namespace masala {
namespace base {
namespace managers {
namespace database {
namespace elements {

    class ElementType;

    using ElementTypeSP = MASALA_SHARED_POINTER< ElementType >;
    using ElementTypeCSP = MASALA_SHARED_POINTER< ElementType const >;
    using ElementTypeWP = MASALA_WEAK_POINTER< ElementType >;
    using ElementTypeCWP = MASALA_WEAK_POINTER< ElementType const >;

    /// @brief The element type, as an enum.
    /// @details We use the atomic symbol, and explicitly associate with it the
    /// atomic number.  This enum can be cast to a masala::base::Size to give the atomic number.
    /// @note In the comments, I give the IUPAC name (e.g. "sulfur") and then any
    /// variants (e.g. "sulphur") in brackets.
    enum class ElementTypeEnum {
        INVALID_ELEMENT_TYPE = -1,
        UNKNOWN_ELEMENT_TYPE = 0,

        // Keep the above two first.

        ELEMENT_H = 1, // hydrogen
        ELEMENT_He = 2, // helium


        ELEMENT_Li = 3, // lithium
        ELEMENT_Be = 4, // beryllium
        ELEMENT_B = 5, // boron
        ELEMENT_C = 6, // carbon
        ELEMENT_N = 7, // nitrogen
        ELEMENT_O = 8, // oxygen
        ELEMENT_F = 9, // fluorine
        ELEMENT_Ne = 10, // neon


        ELEMENT_Na = 11, // sodium
        ELEMENT_Mg = 12, // magnesium
        ELEMENT_Al = 13, // aluminum (or aluminium)
        ELEMENT_Si = 14, // silicon
        ELEMENT_P = 15, // phosphorus
        ELEMENT_S = 16, // sulfur (or sulphur)
        ELEMENT_Cl = 17, // chlorine
        ELEMENT_Ar = 18, // argon


        ELEMENT_K = 19, // potassium
        ELEMENT_Ca = 20, // calcium
        ELEMENT_Sc = 21, // scandium
        ELEMENT_Ti = 22, // titanium
        ELEMENT_V = 23, // vanadium
        ELEMENT_Cr = 24, // chromium
        ELEMENT_Mn = 25, // manganese
        ELEMENT_Fe = 26, // iron
        ELEMENT_Co = 27, // cobalt
        ELEMENT_Ni = 28, // nickel
        ELEMENT_Cu = 29, // copper
        ELEMENT_Zn = 30, // zinc
        ELEMENT_Ga = 31, // gallium
        ELEMENT_Ge = 32, // germanium
        ELEMENT_As = 33, // arsenic
        ELEMENT_Se = 34, // selenium
        ELEMENT_Br = 35, // bromine
        ELEMENT_Kr = 36, // krypton


        ELEMENT_Rb = 37, // rubidium
        ELEMENT_Sr = 38, // strontium
        ELEMENT_Y = 39, // yttrium
        ELEMENT_Zr = 40, // zirconium
        ELEMENT_Nb = 41, // niobium
        ELEMENT_Mo = 42, // molybdenum
        ELEMENT_Tc = 43, // technitium
        ELEMENT_Ru = 44, // ruthenium
        ELEMENT_Rh = 45, // rhodium
        ELEMENT_Pd = 46, // palladium
        ELEMENT_Ag = 47, // silver
        ELEMENT_Cd = 48, // cadmium
        ELEMENT_In = 49, // indium
        ELEMENT_Sn = 50, // tin
        ELEMENT_Sb = 51, // antimony
        ELEMENT_Te = 52, // tellurium
        ELEMENT_I = 53, // iodine
        ELEMENT_Xe = 54, // xenon


        ELEMENT_Cs = 55, // caesium (or cesium)
        ELEMENT_Ba = 56, // barium

        ELEMENT_La = 57, // lanthanum
        ELEMENT_Ce = 58, // cerium
        ELEMENT_Pr = 59, // praseodymium
        ELEMENT_Nd = 60, // neodymium
        ELEMENT_Pm = 61, // promethium
        ELEMENT_Sm = 62, // samarium
        ELEMENT_Eu = 63, // eruopium
        ELEMENT_Gd = 64, // gadolinium
        ELEMENT_Tb = 65, // terbium
        ELEMENT_Dy = 66, // dysprosium
        ELEMENT_Ho = 67, // holmium
        ELEMENT_Er = 68, // erbium
        ELEMENT_Tm = 69, // thulium
        ELEMENT_Yb = 70, // ytterbium
        ELEMENT_Lu = 71, // lutetium

        ELEMENT_Hf = 72, // hafnium
        ELEMENT_Ta = 73, // tantalum
        ELEMENT_W = 74, // tungsten
        ELEMENT_Re = 75, // rhenium
        ELEMENT_Os = 76, // osmium
        ELEMENT_Ir = 77, // iridium
        ELEMENT_Pt = 78, // platinum
        ELEMENT_Au = 79, // gold
        ELEMENT_Hg = 80, // mercury
        ELEMENT_Tl = 81, // thallium
        ELEMENT_Pb = 82, // lead
        ELEMENT_Bi = 83, // bismuth
        ELEMENT_Po = 84, // polonium
        ELEMENT_At = 85, // astatine
        ELEMENT_Rn = 86, // radon


        ELEMENT_Fr = 87, // francium
        ELEMENT_Ra = 88, // radium

        ELEMENT_Ac = 89, // actinium
        ELEMENT_Th = 90, // thorium
        ELEMENT_Pa = 91, // protactinium
        ELEMENT_U = 92, // uranium
        ELEMENT_Np = 93, // neptunium
        ELEMENT_Pu = 94, // plutonium
        ELEMENT_Am = 95, // americium
        ELEMENT_Cm = 96, // curium
        ELEMENT_Bk = 97, // berkelium
        ELEMENT_Cf = 98, // californium
        ELEMENT_Es = 99, // einsteinium
        ELEMENT_Fm = 100, // fermium
        ELEMENT_Md = 101, // mendelevium
        ELEMENT_No = 102, // nobelium
        ELEMENT_Lr = 103, // lawrencium

        ELEMENT_Rf = 104, // rutherfordium
        ELEMENT_Db = 105, // dubnium
        ELEMENT_Sg = 106, // seaborgium
        ELEMENT_Bh = 107, // bohrium
        ELEMENT_Hs = 108, // hassium
        ELEMENT_Mt = 109, // meitnerium
        ELEMENT_Ds = 110, // darmstadtium
        ELEMENT_Rg = 111, // roentgenium
        ELEMENT_Cn = 112, // copernicium
        ELEMENT_Nh = 113, // nihonium
        ELEMENT_Fl = 114, // flerovium
        ELEMENT_Mc = 115, // moscovium
        ELEMENT_Lv = 116, // livermorium
        ELEMENT_Ts = 117, // tennessine
        ELEMENT_Og = 118, // oganesson

        NUM_KNOWN_ELEMENTS = ELEMENT_Og // keep last

    };

    /// @brief Given an element enum, get the element name.
    /// @returns "UNKNOWN" for out-of-range values.
    std::string
    element_name_from_enum(
        ElementTypeEnum const element_type
    );

    /// @brief Given an element name, get the element enum.
    /// @returns INVALID_ELEMENT_TYPE for names that can't be parsed.
    ElementTypeEnum
    element_enum_from_name(
        std::string const & element_name
    );

} // namespace elements
} // namespace database
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_database_elements_ElementType_fwd_hh
