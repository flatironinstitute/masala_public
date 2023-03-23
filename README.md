# Masala

## Description

Project Masala is an open-source successor to the Rosetta software suite, combining the best physics-based, statistics-based, and machine learning-based methods for heteropolymer structure prediction, design, analysis, and modelling.

## Author

The Masala project was started by Vikram K. Mulligan, a Research Scientist in the Center for Computational Biology, at the Flatiron Institute.  For questions, e-mail vmulligan@flatironinstitute.org.

## Building

To build the core Masala libraries:

1.  Clone the git repository (`git clone git@github.com:flatironinstitute/masala_dev.git`).
2.  Clone all of the needed submodules (`cd masala_dev && git submodule update --init`).
3.  Run the `buildme.sh` script.

After building, you will likely want to pull and build the standard Masala plugins repository, and possibly the Garam Masala GUI.

## Licence

Masala is released under an AGPL version 3 licence.  This licence permits anyone to use the software for any purpose (not-for-profit or commercial), as well as to modify the software and incorporate it into derivative works.  The one stipulation is that if any modified version or derivative work is distributed, or users are given access to it over a network, then the source code must be made available under an AGPL licence (version 3 or later).  This ensures that the software remains free and open-source.  For full details, see the LICENCE file.
