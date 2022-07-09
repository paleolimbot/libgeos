
test_that("libgeos_version() works", {
  expect_identical(libgeos_version(), "3.11.0-CAPI-1.17.0")
})

test_that("libgeos can be linked to", {
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
  code_file_shell <- gsub("\\\\+", "/", code_file)

  r_exec <- file.path(R.home("bin"), "R")
  system(paste(r_exec, "CMD SHLIB", shQuote(code_file_shell)), ignore.stdout = TRUE)

  shlib_file <- gsub("\\.c$", .Platform$dynlib.ext, code_file)
  dyn.load(shlib_file)

  expect_identical(.Call("libgeos_test_version"), libgeos_version())

  unlink(c(code_file, shlib_file))
})
