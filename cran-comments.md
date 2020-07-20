
This submission removes the ability to link to system 'GEOS', as it was determined that the exported C API could not be guaranteed to work on all platforms if the package linked to a previously installed copy of the library. This increases check time but guarantees a specific version of 'GEOS' for future dependencies. See the forthcoming [geos package](https://paleolimbot.github.io/geos), which vectorizes the C API such that it is usable from R, and provides a reasonable test that all functions exported by 'libgeos' can be accessed by downstream packages as intended.

## Test environments

* local R installation, MacOS R 4.0.1
* GitHub actions: MacOS (R release), Windows (R oldrel and release), Ubuntu 16.04 (R release)
* win-builder (devel)
* `rhub::check_for_cran()`

## R CMD check results

* checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Dewey Dunnington <dewey@fishandwhistle.net>’
