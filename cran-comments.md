
This submission fixes warnings as shown on the package check page.

## Test environments

* local R installation, MacOS R 4.2.0
* GitHub actions: MacOS (R release), Windows (R oldrel and release), 
  Ubuntu 20.04 (R release, R devel)
* win-builder (devel)
* `rhub::check_for_cran()`

## R CMD check results

* checking installed package size ... NOTE
  installed size is  5.2Mb
  sub-directories of 1Mb or more:
    libs   5.1Mb

The dynamic library for this package is large; however, the purpose of this package
is specifically to provide access to this library.
