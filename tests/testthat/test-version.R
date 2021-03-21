
test_that("libgeos_version() works", {
  expect_identical(libgeos_version(), "3.9.1-CAPI-1.14.2")
})

test_that("libgeos can be linked to", {
  # basic test for linking
  Sys.setenv(
    PKG_CPPFLAGS = paste0("-I", system.file("include", package = "libgeos"))
  )

  code <- '
  #include "libgeos.h"
  #include "libgeos.c"

  SEXP libgeos_test_version() {
    libgeos_init_api();
    return Rf_mkString(GEOSversion());
  }

  '

  code_file <- tempfile(fileext = ".c")
  writeLines(code, code_file)

  r_exec <- file.path(R.home("bin"), "R")
  system(paste(r_exec, "CMD SHLIB", shQuote(code_file)), ignore.stdout = TRUE)

  shlib_file <- gsub("\\.c$", .Platform$dynlib.ext, code_file)
  dyn.load(shlib_file)

  expect_identical(.Call("libgeos_test_version"), libgeos_version())
})
