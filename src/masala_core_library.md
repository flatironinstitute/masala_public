\mainpage Masala Core library

\image html Masala_logo_v3_sm.png width=512px

## Description

The Masala Core library version 1.6 defines the plugin system, the API definition system, and static singletons for managing shared resources like memory, output loggers (tracers), disk i/o, CPU threads, and MPI processes.  It also defines base classes for certain types of Masala plugin modules.

## Authors

- Vikram K. Mulligan, Ph.D., Research Scientist, Center for Computational Biology, Flatiron Institute (vmulligan@flatironinstitute.org).
- Tristan Zaborniak, Ph.D. Candidate, Department of Computer Science, University of Victoria (tzaborniak@flatironinstitute.org).
- Noora Azadvari, Ph.D. Candidate, Department of Bioengineering, University of Oregon (eazadvar@uoregon.edu).
- Qiyao Zhu, Ph.D., Flatiron Research Fellow, Center for Computational Biology, Flatiron Institute (qzhu@flatironinstitute.org).
- S.M. Bargeen A. Turzo, Ph.D., Flatiron Research Fellow, Center for Computational Biology, Flatiron Institute (bturzo@flatironinstitute.org).
- P. Douglas Renfrew, Ph.D., Research Scientist, Center for Computatinoal Biology, Flatiron Institute (pdrenfrew@flatironinstitute.org).

## Library organization

This library is divided into hand-written sub-libraries and auto-generated API sub-libraries.  All sub-libraries are in appropriately named sub-directories of the src/ directory; all namespaces start with masala, and then follow the directory structure.  The namespaces of the hand-written sub-libraries are:

- \link masala::base \endlink
- \link masala::numeric \endlink
- \link masala::core \endlink

The corresponding auto-generated libraries are in the following namespaces:

- \link masala::numeric_api \endlink
- \link masala::core_api \endlink

## Linking this library

If you link this library at compilation time, it is _only_ safe to directly call functions or instantiate classes in the auto-generated API namespaces, or in the \link masala::base \endlink namespace.  These have stable APIs that will be preserved in future versions of the Standard Masala Plugins library, or deprecated in a manner that provides ample warning.  Handwritten sub-libraries other than the base sub-libarry are _not_ part of the API, and can change without warning.

## Version history

* Version 1.6: Fix an occasional bug when applications that link Masala terminate, caused by the order in which Masala's singletons (particularly the thread manager and the tracer manager) are destroyed.
* Version 1.5: Update buildscripts to remove language feature incompatible with Python older than version 3.9 (tuple type hinting).
* Version 1.4: Minor adjustments to generate\_library\_api.py for compatibility with the Masala SYCL loop closure plugins.
* Version 1.3: Introduction of the HilbertIndexedMatrix for more efficient searches of data in matrices with fewer cache misses.
* Version 1.2: Small tweak to element names in the ElementType enum class, to avoid name conflicts with "I" (which is often used for identitiy matrices).
* Version 1.1: Small bugfix to RVL optimizer base classes.  (A float-float comparison could sometimes fail due to machine precision limits.)
* Version 1.0: Initial non-beta release.  Infrastructure for the plugin system, CPU thread management, CFN optimizer base classes, and RVL optimizer base classes fully implemented.
