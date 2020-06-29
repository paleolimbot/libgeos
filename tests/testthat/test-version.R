
test_that("libgeos_version() works", {
  expect_identical(libgeos_version(), "3.8.1-CAPI-1.13.3")
})

test_that("GEOSversion() can be called from Rcpp", {
  source_rcpp_libgeos('
    // [[Rcpp::export]]
    std::string version() {
      libgeos_init_api();
      return GEOSversion();
    }
  ')

  expect_identical(version(), libgeos_version())
})
