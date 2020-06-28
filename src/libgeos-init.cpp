
#include "geos_c.h"
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

SEXP libgeos_geos_version() {
  SEXP out = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(out, 0, Rf_mkChar(GEOSversion()));
  UNPROTECT(1);
  return out;
}

static const R_CallMethodDef CallEntries[] = {
  {"libgeos_geos_version", (DL_FUNC) &libgeos_geos_version, 0},
  {NULL, NULL, 0}
};

extern "C" {
  void R_init_libgeos(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    /* used by external packages linking to libgeos from C */
    R_RegisterCCallable("libgeos", "GEOSversion", (DL_FUNC) &GEOSversion);
  }
}
