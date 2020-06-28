
#ifndef LIBGEOS_H
#define LIBGEOS_H

#include <Rinternals.h>
#include <R_ext/Rdynload.h>

extern const char* (*GEOSversion)();

void libgeos_init_api();

#endif
