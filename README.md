
<!-- README.md is generated from README.Rmd. Please edit that file -->

# libgeos

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
![R-CMD-check](https://github.com/paleolimbot/libgeos/workflows/R-CMD-check/badge.svg)
<!-- badges: end -->

The goal of libgeos is to provide access to the
[GEOS](https://trac.osgeo.org/geos/) C API for high-performance geometry
operations within the R package framework. This package contains a copy
of the GEOS library, modified slightly to eliminate errors on all the
platorms checked by CRAN and GitHub actions. This means you don’t have
to install anything (other than the package) to take advantage of GEOS
functions in R. It also means you don’t need a configure script if
you’re writing a package that needs GEOS functionality (just
`LinkingTo: libgeos`). Because GEOS is license under the LGPL,
dynamically linking to GEOS (e.g., through the C API exposed in this
package) is generally allowed from a package with any license. See the
[geos R package](https://paleolimbot.github.io/geos) for an R API to
GEOS.

## Installation

You can install the released version of libgeos from
[CRAN](https://cran.r-project.org/) with:

``` r
install.packages("libgeos")
```

To install a binary on supported Linux platforms, you can use [RStudio
Package Manager’s public instance](https://packagemanager.rstudio.com/)
(see
[here](https://packagemanager.rstudio.com/client/#/repos/1/overview) for
how to configure on your platform).

You can install the development version of libgeos from
[GitHub](https://github.com/) with:

``` r
# install.packages("remotes")
remotes::install_github("paleolimbot/libgeos")
```

## Example

This package only exists for its exported C API. You can link to libgeos
from a package by specifying `LinkingTo: libgeos` and `Imports: libgeos`
in your DESCRIPTION. You can link to libgeos interactively from Rcpp
using `// [[Rcpp::depends(libgeos)]]`:

``` cpp
#include <Rcpp.h>

// Packages will also need LinkingTo: libgeos
// [[Rcpp::depends(libgeos)]]

// needed in every file that uses GEOS functions
#include "libgeos.h"

// needed exactly once in your package or Rcpp script
// contains all the function pointers and the
// implementation of the function to initialize them
// (`libgeos_init_api()`)
#include "libgeos.c"

// this function needs to be called once before any GEOS functions
// are called (e.g., in .onLoad() for your package)
// [[Rcpp::export]]
void cpp_libgeos_init_api() {
  libgeos_init_api();
}

// regular C or C++ code that uses GEOS functions!
// [[Rcpp::export]]
std::string version() {
  return GEOSversion();
}
```

``` r
cpp_libgeos_init_api()
version()
#> [1] "3.9.1-CAPI-1.14.2"
```

You can link to libegeos interactively from cpp11 using
`[[cpp11::linking_to(libgeos)]]`:

``` cpp
#include <cpp11.hpp>

// needed in every file that uses GEOS functions
#include "libgeos.h"

// needed exactly once in your package or Rcpp script
// contains all the function pointers and the
// implementation of the function to initialize them
// (`libgeos_init_api()`)
#include "libgeos.c"

// this function needs to be called once before any GEOS functions
// are called (e.g., in .onLoad() for your package)
[[cpp11::linking_to(libgeos)]]
[[cpp11::register]]
void cpp_libgeos_init_api() {
  libgeos_init_api();
}

// regular C or C++ code that uses GEOS functions!
[[cpp11::register]]
std::string version() {
  return GEOSversion();
}
```

``` r
cpp_libgeos_init_api()
version()
#> [1] "3.9.1-CAPI-1.14.2"
```
