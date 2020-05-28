
test_that("libgeos_version() works", {
  expect_identical(libgeos_version(), "3.8.1-CAPI-1.13.3")
})
