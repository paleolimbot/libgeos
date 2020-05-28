
#ifndef LIBGEOS_H
#define LIBGEOS_H

#include <Rinternals.h>

#ifdef __cplusplus
extern "C" {
#endif

inline SEXP libgeos_geos_version() {
  typedef SEXP(*Ptr_libgeos_geos_version)();
  static Ptr_libgeos_geos_version p_libgeos_geos_version = NULL;

  if (p_libgeos_geos_version == NULL) {
    p_libgeos_geos_version = (Ptr_libgeos_geos_version) R_GetCCallable("libgeos", "libgeos_geos_version");
  }

  return p_libgeos_geos_version();
}

#ifdef __cplusplus
}
#endif

#endif
