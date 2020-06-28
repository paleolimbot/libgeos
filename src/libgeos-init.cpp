
#include "geos_c.h"
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

extern "C" {
  void R_init_libgeos(DllInfo *dll) {
    /* used by external packages linking to libgeos from C */
    R_RegisterCCallable("libgeos", "GEOSversion", (DL_FUNC) &GEOSversion);
  }
}
