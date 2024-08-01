# Masala

## Description

Project Masala is an open-source successor to the Rosetta software suite, combining the best physics-based, statistics-based, and machine learning-based methods for heteropolymer structure prediction, design, analysis, and modelling.

## Author

The Masala project was started by Vikram K. Mulligan, a Research Scientist in the Center for Computational Biology, at the Flatiron Institute.  For questions, e-mail vmulligan@flatironinstitute.org.

## Building

To build the core Masala libraries:

1.  Clone the git repository (`git clone git@github.com:flatironinstitute/masala_dev.git`).
2.  Clone all of the needed submodules (`cd masala_dev && git submodule update --init`).
3.  Masala is written in C++20. Make sure that your GCC version is 8 or higher. You can check this via `gcc --version`.
4.  Run the `buildme.sh` script.

After building, you will likely want to pull and build the standard Masala plugins repository, and possibly the Garam Masala GUI.

## Updating the build

1.  If you are on the `main` branch, pull the latest changes via `git pull`. If you are on another branch (you can check via `git branch`), update your remote branch (`git remote update origin --prune`)
2.  Delete the previous build (`./delete_build.sh`)
3.  Run the `buildme.sh` script.

## Using

In order to use Masala, the `MASALA_PATH` environment variable must be set to the directory in which Masala is installed.

### Using Masala as a standalone application

Masala applications can be written that link the Masala libraries, as with any conventional software.

### Using Masala through scripting interfaces

PyMasala and MasalaScripts XML interfaces are planned.  These will use the Masala API definitions to auto-generate bindings, ensuring a common API to access the same functionality in all languages.

### Using Masala through the GUI

The Garam Masala GUI uses the Masala API definitions to auto-generate bindings for Masala modules.

### Using Masala as a library

Masala can be used as a C++ library in two ways:

1.  By conventionally linking (at compile-time) the core Masala libraries plus any needed plugins, and calling code directly.  In this case, it is recommended to call code only from the API libraries, since these are the libraries that present a consistent API with guarantees of stability.
2.  By conventionally linking (at compile-time) the core Masala libraries, and auto-detecting and loading plugin libraries through runtime linking.  In this case, plugin objects are accessed entirely through the function pointers in their API descriptions.  This has the advantage of allowing a software project to use Masala plugins that were not available at compile time, and to take advantage of new Masala plugins without any recompilation or re-linking (but for runtime linking) needed.

## Licence

Masala is released under an AGPL version 3 licence.  This licence permits anyone to use the software for any purpose (not-for-profit or commercial), as well as to modify the software and incorporate it into derivative works.  The one stipulation is that if any modified version or derivative work is distributed, or users are given access to it over a network, then the source code must be made available under an AGPL licence (version 3 or later).  This ensures that the software remains free and open-source.  For full details, see the LICENCE file.
