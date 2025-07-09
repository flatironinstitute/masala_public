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

        H = 1, // hydrogen
        He = 2, // helium


        Li = 3, // lithium
        Be = 4, // beryllium
        B = 5, // boron
        C = 6, // carbon
        N = 7, // nitrogen
        O = 8, // oxygen
        F = 9, // fluorine
        Ne = 10, // neon


        Na = 11, // sodium
        Mg = 12, // magnesium
        Al = 13, // aluminum (or aluminium)
        Si = 14, // silicon
        P = 15, // phosphorus
        S = 16, // sulfur (or sulphur)
        Cl = 17, // chlorine
        Ar = 18, // argon


        K = 19, // potassium
        Ca = 20, // calcium
        Sc = 21, // scandium
        Ti = 22, // titanium
        V = 23, // vanadium
        Cr = 24, // chromium
        Mn = 25, // manganese
        Fe = 26, // iron
        Co = 27, // cobalt
        Ni = 28, // nickel
        Cu = 29, // copper
        Zn = 30, // zinc
        Ga = 31, // gallium
        Ge = 32, // germanium
        As = 33, // arsenic
        Se = 34, // selenium
        Br = 35, // bromine
        Kr = 36, // krypton


        Rb = 37, // rubidium
        Sr = 38, // strontium
        Y = 39, // yttrium
        Zr = 40, // zirconium
        Nb = 41, // niobium
        Mo = 42, // molybdenum
        Tc = 43, // technitium
        Ru = 44, // ruthenium
        Rh = 45, // rhodium
        Pd = 46, // palladium
        Ag = 47, // silver
        Cd = 48, // cadmium
        In = 49, // indium
        Sn = 50, // tin
        Sb = 51, // antimony
        Te = 52, // tellurium
        I = 53, // iodine
        Xe = 54, // xenon


        Cs = 55, // caesium (or cesium)
        Ba = 56, // barium

        La = 57, // lanthanum
        Ce = 58, // cerium
        Pr = 59, // praseodymium
        Nd = 60, // neodymium
        Pm = 61, // promethium
        Sm = 62, // samarium
        Eu = 63, // eruopium
        Gd = 64, // gadolinium
        Tb = 65, // terbium
        Dy = 66, // dysprosium
        Ho = 67, // holmium
        Er = 68, // erbium
        Tm = 69, // thulium
        Yb = 70, // ytterbium
        Lu = 71, // lutetium

        Hf = 72, // hafnium
        Ta = 73, // tantalum
        W = 74, // tungsten
        Re = 75, // rhenium
        Os = 76, // osmium
        Ir = 77, // iridium
        Pt = 78, // platinum
        Au = 79, // gold
        Hg = 80, // mercury
        Tl = 81, // thallium
        Pb = 82, // lead
        Bi = 83, // bismuth
        Po = 84, // polonium
        At = 85, // astatine
        Rn = 86, // radon


        Fr = 87, // francium
        Ra = 88, // radium

        Ac = 89, // actinium
        Th = 90, // thorium
        Pa = 91, // protactinium
        U = 92, // uranium
        Np = 93, // neptunium
        Pu = 94, // plutonium
        Am = 95, // americium
        Cm = 96, // curium
        Bk = 97, // berkelium
        Cf = 98, // californium
        Es = 99, // einsteinium
        Fm = 100, // fermium
        Md = 101, // mendelevium
        No = 102, // nobelium
        Lr = 103, // lawrencium

        Rf = 104, // rutherfordium
        Db = 105, // dubnium
        Sg = 106, // seaborgium
        Bh = 107, // bohrium
        Hs = 108, // hassium
        Mt = 109, // meitnerium
        Ds = 110, // darmstadtium
        Rg = 111, // roentgenium
        Cn = 112, // copernicium
        Nh = 113, // nihonium
        Fl = 114, // flerovium
        Mc = 115, // moscovium
        Lv = 116, // livermorium
        Ts = 117, // tennessine
        Og = 118, // oganesson

        NUM_KNOWN_ELEMENTS = Og // keep last

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