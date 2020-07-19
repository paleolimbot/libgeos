
test_that("libgeos_version() works", {
  expect_match(libgeos_version(), "3\\.8\\.[0-9]+")
})

test_that("GEOSversion() can be called from Rcpp", {
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
