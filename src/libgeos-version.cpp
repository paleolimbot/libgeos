
#include "geos_c.h"
#include <Rcpp.h>
using namespace Rcpp;

// [[Rcpp::export]]
std::string libgeos_version() {
  return GEOSversion();
}
