
Sys.setenv("R_TESTS" = "")
requireNamespace("libgeos", quietly = TRUE)
Rcpp::sourceCpp(code = '
#include <Rcpp.h>
// [[Rcpp::depends(libgeos)]]
#include "libgeos.h"
#include "libgeos.c"

// [[Rcpp::export]]
std::string version() {
  libgeos_init_api();
  return GEOSversion();
}
')

version() == "3.8.1-CAPI-1.13.3"
