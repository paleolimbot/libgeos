
test_that("libgeos_version() works", {
  expect_identical(libgeos_version(), "3.8.1-CAPI-1.13.3")
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
  ')

  expect_identical(version(), libgeos_version())

  unlink(cache, recursive = TRUE)
})
