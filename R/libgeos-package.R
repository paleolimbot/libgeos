#' @keywords internal
"_PACKAGE"

# The following block is used by usethis to automatically manage
# roxygen namespace tags. Modify with care!
## usethis namespace: start
#' @useDynLib libgeos, .registration = TRUE
#' @importFrom Rcpp sourceCpp
## usethis namespace: end
NULL

#' GEOS version information
#'
#' @return The version string returned by `GEOSversion();`
#' @export
#'
#' @examples
#' libgeos_verisoin()
#'
libgeos_version <- function() {
  .Call("_libgeos_geos_version")
}
