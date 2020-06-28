
#include "libgeos.h"

const char* (*GEOSversion)() = NULL;

void libgeos_init_api() {
  GEOSversion = (const char* (*)()) R_GetCCallable("libgeos", "GEOSversion");
}
