
#include "libgeos.h"

GEOSContextHandle_t (*GEOS_init_r)() = NULL;
void (*GEOS_finish_r)(GEOSContextHandle_t) = NULL;
const char* (*GEOSversion)() = NULL;

void libgeos_init_api() {
  GEOS_init_r = (GEOSContextHandle_t (*)()) R_GetCCallable("libgeos", "GEOS_init_r");
  GEOS_finish_r = (void (*)(GEOSContextHandle_t)) R_GetCCallable("libgeos", "GEOS_finish_r");
  GEOSversion = (const char* (*)()) R_GetCCallable("libgeos", "GEOSversion");
}
