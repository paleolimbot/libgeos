
source_rcpp_libgeos <- function(code, header = '', cache = tempfile(), ..., env = parent.frame()) {
  head <- '
    #include <Rcpp.h>
    // [[Rcpp::depends(libgeos)]]
    #include "libgeos-rcpp.h"
    #include "libgeos.c"
    using namespace Rcpp;

    // [[Rcpp::export]]
    void source_rcpp_libgeos_init() {
      libgeos_init_api();
    }

  '
  requireNamespace("libgeos", quietly = TRUE)
  if (!dir.exists(cache)) {
    dir.create(cache)
  }
  Rcpp::sourceCpp(code = paste0(header, '\n\n', head, code), env = env, cacheDir = cache, ...)
  cache
}
