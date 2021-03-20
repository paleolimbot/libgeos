
test_that("libgeos_version() works", {
  expect_identical(libgeos_version(), "3.9.1-CAPI-1.14.2")
})

test_that("GEOSversion() can be called from Rcpp", {
  # these tests run a bit of Rcpp code that, depending on the Rcpp version,
  # can lead to sanitizer errors that are out of my control
  skip_on_cran()

  cache <- source_rcpp_libgeos('
    // [[Rcpp::export]]
    std::string version() {
      libgeos_init_api();
      return GEOSversion();
    }

    // [[Rcpp::export]]
    int version_int() {
      libgeos_init_api();
      return libgeos_version_int();
    }
  ')

  expect_identical(version(), libgeos_version())
  expect_equal(version_int(), 1 + 9 * 100 + 3 * 10000)

  unlink(cache, recursive = TRUE)
})
