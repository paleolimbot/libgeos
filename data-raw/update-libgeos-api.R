
library(tidyverse)

capi_header <- read_file("inst/libgeos_include/geos_c.h")

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
  filter(name %in% c("GEOSversion", "GEOS_init_r", "GEOS_finish_r"))

libgeos_h <- with(
  rlang::list2(!!!function_header_defs, typedefs_chr = typedefs_chr, enums_chr = enums_chr),
  glue::glue(
'

#ifndef LIBGEOS_H
#define LIBGEOS_H

#include <Rinternals.h>
#include <R_ext/Rdynload.h>

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

#include "libgeos.h"

{ paste0(impl_def, collapse = "\n") }

void libgeos_init_api() {{
{ paste0(init_def, collapse = "\n") }
}}

'
  )
)

libgeos_init_cpp <- with(
  function_header_defs,
  glue::glue(
    '

#include "geos_c.h"
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

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

extern "C" {{
  void R_init_libgeos(DllInfo *dll) {{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    /* used by external packages linking to libgeos from C */
{ paste0(register_def, collapse = "\n") }
  }}
}}

'
  )
)

# write auto-generated files!
write_file(libgeos_h, "inst/include/libgeos.h")
write_file(libgeos_c, "inst/include/libgeos.c")
write_file(libgeos_init_cpp, "src/libgeos-init.cpp")
