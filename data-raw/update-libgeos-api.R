
library(tidyverse)

capi_header <- read_file("src/geos_include/geos_c.h")

version_defs_chr <- read_lines(capi_header)[54:76]

function_defs_chr <- capi_header %>%
  str_extract_all(
    regex(
      "extern\\s*[A-Za-z0-9_ ]+\\s*GEOS_DLL[^;]+;",
      multiline = TRUE,
      dotall = TRUE
    )
  ) %>%
  .[[1]] %>%
  str_replace_all(regex("\\s+"), " ")

typedefs_chr <- capi_header %>%
  str_extract_all(regex("typedef[^;]+;", multiline = TRUE)) %>%
  .[[1]]

enums_chr <- capi_header %>%
  str_extract_all(regex("\nenum[^;]+;", multiline = TRUE)) %>%
  .[[1]] %>%
  str_trim()

function_defs <- tibble(
  # move pointer spec to be with type to the left, remove extern
  def = function_defs_chr %>%
    str_replace("\\s+GEOS_DLL\\s+\\*", "* GEOS_DLL ") %>%
    str_remove("extern\\s+"),

  name = def %>% str_extract("[A-Za-z0-9_]+\\s*\\(") %>% str_remove("\\($") %>% str_trim(),

  return_type = str_extract(def, "^[A-Za-z0-9_ ]+\\*?\\s*GEOS_DLL") %>%
    str_remove("\\s*GEOS_DLL$"),

  args = str_extract(def, "\\([^\\)]*\\)") %>%
    str_remove_all("[\\(\\)]") %>%
    str_split("\\s*,\\s*"),

  arg_types = map(args, str_replace, "(\\**)\\s+(\\**)[a-zA-Z0-9_]+$", "\\1\\2"),

  n_args = map_int(args, length)
)

function_header_defs <- function_defs %>%
  mutate(
    # declare function pointers
    arg_types = map_chr(arg_types, paste0, collapse = ", "),
    pointer_def = glue::glue("{return_type} (*{name})({arg_types})"),
    header_def = glue::glue("extern {pointer_def};"),
    impl_def = glue::glue("{pointer_def} = NULL;"),
    init_def = glue::glue('  {name} = ({return_type} (*)({arg_types})) R_GetCCallable("libgeos", "{name}");'),
    register_def = glue::glue('    R_RegisterCCallable("libgeos", "{name}", (DL_FUNC) &{name});')
  ) %>%
  filter((name %in% c("GEOSversion")) | str_detect(name, "_r$"))

libgeos_h <- with(
  rlang::list2(
    !!!function_header_defs,
    typedefs_chr = typedefs_chr,
    enums_chr = enums_chr,
    version_defs_chr = version_defs_chr
  ),
  glue::glue(
'

// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#ifndef LIBGEOS_H
#define LIBGEOS_H

#ifndef __cplusplus
# include <stddef.h> /* for size_t definition */
#else
# include <cstddef>
using std::size_t;
#endif

// the runtime version of libgeos
#define LIBGEOS_VERSION_INT(major, minor, patch) (patch + minor * 100 + major * 10000)
extern int (*libgeos_version_int)();

{ paste0(version_defs_chr, collapse = "\n") }

{ paste0(typedefs_chr, collapse = "\n") }

{ paste0(enums_chr, collapse = "\n") }

{ paste0(header_def, collapse = "\n") }

void libgeos_init_api();

#endif

'
  )
)

libgeos_c <- with(
  function_header_defs,
  glue::glue(
    '

// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#include "libgeos.h"

#include <Rinternals.h>
#include <R_ext/Rdynload.h>

int (*libgeos_version_int)() = NULL;

{ paste0(impl_def, collapse = "\n") }

void libgeos_init_api() {{
  libgeos_version_int = (int (*)()) R_GetCCallable("libgeos", "libgeos_version_int");

{ paste0(init_def, collapse = "\n") }
}}

'
  )
)

libgeos_init_c <- with(
  function_header_defs,
  glue::glue(
    '

// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

{ paste(version_defs_chr, collapse = "\n") }

// we need a utility function to get the runtime version in a form that is
// queryable from the inst/include/libgeos.c, because future GEOS versions
// will add to the C API. The ability to do a runtime check around R_GetCCallable()
// lets newer packages link to multiple versions of libgeos.
#define LIBGEOS_VERSION_INT(major, minor, patch) (patch + minor * 100 + major * 10000)

int libgeos_version_int() {{
  return LIBGEOS_VERSION_INT(GEOS_VERSION_MAJOR, GEOS_VERSION_MINOR, GEOS_VERSION_PATCH);
}}

// whereas libgeos.h contains declarations for function *pointers*
// these are the declarations for the functions in geos_c.h
// we cannnot include geos_c.h because the magic defines GEOS
// uses create problems for the LTO build of R-devel
{ paste0(typedefs_chr, collapse = "\n") }

#define GEOS_DLL
{ paste0(def, collapse = "\n") }

// need at least one function passed to R to avoid a NOTE
SEXP libgeos_geos_version() {{
  SEXP out = PROTECT(Rf_allocVector(STRSXP, 1));
  SET_STRING_ELT(out, 0, Rf_mkChar(GEOSversion()));
  UNPROTECT(1);
  return out;
}}

static const R_CallMethodDef CallEntries[] = {{
  {{"libgeos_geos_version", (DL_FUNC) &libgeos_geos_version, 0}},
  {{NULL, NULL, 0}}
}};


void R_init_libgeos(DllInfo *dll) {{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  /* used by external packages linking to libgeos from C */
  R_RegisterCCallable("libgeos", "libgeos_version_int", (DL_FUNC) &libgeos_version_int);
{ paste0(register_def, collapse = "\n") }
}}

'
  )
)

# write auto-generated files!
write_file(libgeos_h, "inst/include/libgeos.h")
write_file(libgeos_c, "inst/include/libgeos.c")
write_file(libgeos_init_c, "src/libgeos-init.c")
