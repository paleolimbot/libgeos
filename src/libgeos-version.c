
// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#include <Rinternals.h>

// to avoid #include "geos_c.h"
const char* GEOSversion();

SEXP libgeos_geos_version() {
  SEXP out = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(out, 0, Rf_mkChar(GEOSversion()));
  UNPROTECT(1);
  return out;
}
