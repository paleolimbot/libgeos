
if ("rcpp_cache" %in% ls()) {
  unlink(rcpp_cache, recursive = TRUE)
  rm(rcpp_cache)
}
