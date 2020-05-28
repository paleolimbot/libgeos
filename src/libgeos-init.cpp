
#include "geos_c.h"
#include <R.h>
#include <Rinternals.h>

extern "C" {

SEXP libgeos_geos_version() {
  SEXP out = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(out, 0, Rf_mkChar(GEOSversion()));
  UNPROTECT(1);
  return out;
}

static const R_CallMethodDef CallEntries[] = {
  {"libgeos_geos_version", (DL_FUNC) &libgeos_geos_version, 0},
  {"GEOSversion", (DL_FUNC) &GEOSversion, 0},
  {NULL, NULL, 0}
};

void R_init_libgeos(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  /* used by external packages linking to internal xts code from C */
  R_RegisterCCallable("libgeos", "libgeos_geos_version", (DL_FUNC) &libgeos_geos_version);
  R_RegisterCCallable("libgeos", "GEOSversion", (DL_FUNC) &GEOSversion);
}

}
