
<!-- README.md is generated from README.Rmd. Please edit that file -->

# libgeos

<!-- badges: start -->

[![Lifecycle:
experimental](https://img.shields.io/badge/lifecycle-experimental-orange.svg)](https://www.tidyverse.org/lifecycle/#experimental)
<!-- badges: end -->

The goal of libgeos is to provide access to the GEOS C API for
high-performance geometry operations within the R package framework.
This package contains a copy of the GEOS sources rather than linking to
the installed GEOS version. This is functionally impractical, since
binaries of the GEOS library is widely available. Thus, this package is
more of an excercise than anything else.

## Installation

You can install the development version of libgeos from
[GitHub](https://github.com/) with:

``` r
# install.packages("remotes")
remotes::install_github("paleolimbot/libgeos")
```

## Example

This package only exists for its exported C API, for which headers are
provided to make calling these functions from Rcpp or another package as
easy as possible.

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
#> [1] "3.8.1-CAPI-1.13.3"
```
