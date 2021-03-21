
source_rcpp_libgeos <- function(code, header = '', cache = tempfile(), ..., env = parent.frame()) {
  head <- '
    #include <Rcpp.h>
    // [[Rcpp::depends(libgeos)]]
    #define LIBGEOS_USE_RCPP
    #include "libgeos-v1.hpp"
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

  # compile with C++11 to help with exception handling on Windows i386
  current_flags <- Sys.getenv("PKG_CXXFLAGS")
  Sys.setenv("PKG_CXXFLAGS" = "-std=c++11")
  on.exit(Sys.setenv("PKG_CXXFLAGS" = current_flags))

  Rcpp::sourceCpp(code = paste0(header, '\n\n', head, code), env = env, cacheDir = cache, ...)
  cache
}
