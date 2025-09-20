# Masala Core library

## Version

Masala's Core library is currently version 1.0. 

## Description

Project Masala is an open-source successor to the Rosetta software suite, combining the best physics-based, statistics-based, and machine learning-based methods for heteropolymer structure prediction, design, analysis, and modelling.

## Authors

The Masala project was started by Vikram K. Mulligan, a Research Scientist in the Center for Computational Biology, at the Flatiron Institute.  For questions, e-mail vmulligan@flatironinstitute.org.

In addition, the following individuals contributed to the development of Masala's Core library:

- Noora Azadvari, a graduate student at the University of Oregon (eazadvar@uoregon.edu).
- Tristan Zaborniak, a graduate student at the University of Victoria (tristanz@uvic.ca).
- Qiyao Zhu, a Flatiron Research Fellow in the Center for Computational Biology, Flatiron Institute (qzhu@flatironinstitute.org).
- S.M. Bargeen A. Turzo, a Flatiron Research Fellow in the Center for Computational Biology, Flatiron Institute (bturzo@flatironinstitute.org).
- Parisa Hossienzadeh, a professor at the University of Oregon (parisah@uoregon.edu).
- P. Douglas Renfrew, a Research Scientist in the Center for Computational Biology, Flatiron Institute (pdrenfrew@flatironinstitute.org).

Masala is maintained by the Biomolecular Design (BmD) Group in the Center for Computatonal Biology at the Flatiron Institute.  Vikram K. Mulligan and P. Douglas Renfrew co-head the group.

## Citing Masala

If you use Masala for work that you publish, please cite the following preprint:

**T. Zaborniak, N. Azadvari, Q. Zhu, S.M.B.A. Turzo, P. Hosseinzadeh, P.D. Renfrew, and V.K. Mulligan.  (2025).  The open-source Masala software suite: Facilitating rapid methods development for synthetic heteropolymer design. _bioRxiv_ [https://doi.org/10.1101/2025.07.02.662756 ](https://doi.org/10.1101/2025.07.02.662756).**

## Building

To build the Core Masala library:

1.  Clone the git repository (`git clone git@github.com:flatironinstitute/masala_dev.git`).
2.  Clone all of the needed submodules (`cd masala_dev && git submodule update --init`).
3.  Masala is written in C++17. Make sure that your GCC version is 8 or higher. You can check this via `gcc --version`.
4.  Masala's build scripts use `nproc` to determine the number of cores available for compilation.  On newer Macintosh operating systems, it may be necessary to set up an alias for `nproc` that runs `sysctl -n hw.logicalcpu`.
5.  Run the `buildme.sh` script.

Note that release mode is the default.  To build in debug mode, edit cmake/CMakeLists.txt and change `SET( MODE release )` to `SET( MODE debug )`.

After building, you will likely want to pull and build the standard Masala plugins repository, and possibly the Garam Masala GUI (to be released) or the quantum computing Masala plugins repository (to be released).

## Updating the build

1.  If you are on the `main` branch, pull the latest changes via `git pull`. If you are on another branch (you can check via `git branch`), update your remote branch (`git remote update origin --prune`).
2.  Optionally, delete the previous build (`./delete_build.sh`).  Under most circumstances, this should _not_ be necessary, however: CMake is quite good at only rebuilding parts that need rebuilding, which saves time.  But a clean rebuild can be a good idea if the new version that you are compiling is drastically different from old versions.
3.  Run the `buildme.sh` script.

## Building Doxygen code documentation

All source code (both manually-written sub-libraries and auto-generated API sub-libraries) is documented with Doxygen tags.  To generate Doxygen HTML documentation, first, follow the instructions above to build Masala's Core library.  Second, build Doxygen documentation with:

```
doxygen Doxyfile.src
```

(Note that Doxygen must be installed.) Documentation will be addded to the `html_docs/` directory.  Delete this directory to recompile documentation from scratch.

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

1.  By conventionally linking (at compile-time) the Core Masala library plus any needed plugins, and calling code directly.  In this case, it is recommended to call code only from the API libraries, since these are the libraries that present a consistent API with guarantees of stability.
2.  By conventionally linking (at compile-time) the Core Masala library, and auto-detecting and loading plugin libraries through runtime linking.  In this case, plugin objects are accessed entirely through the function pointers in their API descriptions.  This has the advantage of allowing a software project to use Masala plugins that were not available at compile time, and to take advantage of new Masala plugins without any recompilation or re-linking (but for runtime linking) needed.

## Licence

Masala is released under an AGPL version 3 licence.  This licence permits anyone to use the software for any purpose (not-for-profit or commercial), as well as to modify the software and incorporate it into derivative works.  The one stipulation is that if any modified version or derivative work is distributed, or users are given access to it over a network, then the source code must be made available under a GPL or AGPL licence (version 3 or later).  This ensures that the software remains free and open-source.  For full details, see the LICENCE file.
