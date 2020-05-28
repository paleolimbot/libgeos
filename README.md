
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

(currently this package does nothing)

``` r
libgeos::libgeos_version()
#> [1] "3.8.1-CAPI-1.13.3"
```

(but you can theoretically call it from Rcpp…)

``` cpp
#include <Rcpp.h>

// [[Rcpp::depends(libgeos)]]
#include "libgeos.h"


// [[Rcpp::export]]
SEXP version() {
  return libgeos_geos_version();
}
```

``` r
version()
#> [1] "3.8.1-CAPI-1.13.3"
```
