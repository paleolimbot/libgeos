
// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#include <Rinternals.h>

SEXP libgeos_geos_version() {
  SEXP out = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(out, 0, Rf_mkChar("3.8.1-CAPI-1.13.3"));
  UNPROTECT(1);
  return out;
}
