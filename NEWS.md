# libgeos (development version)

# libgeos 3.11.0-1

* Update to GEOS 3.10.0 (#13)

# libgeos 3.10.0-1

* Update to GEOS 3.10.0 (#9)

# libgeos 3.9.1-1

* Update to GEOS 3.9.1 (#3).
* Added an exported callable `libgeos_version_int()` that can be used
  to resolve runtime/compile-time differences 
  when loading the exported GEOS callables (#4).
* Removed C++ helpers and simplified linking tests (#4).
* Simplified pattern for removing references to `std::cerr` from
  GEOS sources (#5).

# libgeos 3.8.1-4

* Backported facilities for checking runtime versions during package
  load from the future version 3.9.1-1.

# libgeos 3.8.1-3

* Fixed warnings from the link-time optimizer, which reported naming 
  conflicts between the C++ header types and the abstract C types 
  used in the header API.

# libgeos 3.8.1-2

* Removed the ability to link to system 'GEOS', as with extensive testing
  it was determined that the enitre API could not be guaranteed to function
  on all platforms when linking occurred.
* Fixed the type definitions in the internal C API header such that they
  could be properly identified by the sanitizer.

# libgeos 3.8.1-1

Added the ability to link to system 'GEOS' if a copy with version >3.8.0
was installed.


# libgeos 3.8.1-0

Initial version using GEOS 3.8.1.
