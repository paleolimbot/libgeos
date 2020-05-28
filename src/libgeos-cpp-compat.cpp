
#include "libgeos-cpp-compat.h"
#include <R.h>
#include <Rmath.h>
#include <iostream>
#include <cstdio>
#include <streambuf>

template <bool OUTPUT>
class Rstreambuf : public std::streambuf {
public:
  Rstreambuf(){}

protected:
  virtual std::streamsize xsputn(const char *s, std::streamsize n);
  virtual int overflow(int c = traits_type::eof());
  virtual int sync();
};

template <bool OUTPUT>
class Rostream : public std::ostream {
  typedef Rstreambuf<OUTPUT> Buffer;
  Buffer buf;
public:
  Rostream() : std::ostream( &buf ) {}
};
// #nocov start
template <> inline std::streamsize Rstreambuf<true>::xsputn(const char *s, std::streamsize num) {
  Rprintf("%.*s", num, s);
  return num;
}
template <> inline std::streamsize Rstreambuf<false>::xsputn(const char *s, std::streamsize num) {
  REprintf("%.*s", num, s);
  return num;
}

template <> inline int Rstreambuf<true>::overflow(int c) {
  if (c != traits_type::eof()) {
    char_type ch = traits_type::to_char_type(c);
    return xsputn(&ch, 1) == 1 ? c : traits_type::eof();
  }
  return c;
}
template <> inline int Rstreambuf<false>::overflow(int c) {
  if (c != traits_type::eof()) {
    char_type ch = traits_type::to_char_type(c);
    return xsputn(&ch, 1) == 1 ? c : traits_type::eof();
  }
  return c;
}

template <> inline int Rstreambuf<true>::sync() {
  ::R_FlushConsole();
  return 0;
}
template <> inline int Rstreambuf<false>::sync() {
  ::R_FlushConsole();
  return 0;
}
static Rostream<true>  Rcout;
static Rostream<false> Rcerr;

void cpp_compat_printf(const char* fmt, ...) {
  // don't know how to pass on elipses
  Rprintf(fmt);
}

void cpp_compat_abort() {
  throw std::runtime_error("abort() called");
}

void cpp_compat_exit(int code) {
  throw std::runtime_error("exit() called");
}

int cpp_compat_random() {
  // trying to match what random() would return
  // www.gnu.org/software/libc/manual/html_node/BSD-Random.html#BSD-Random
  // the RNG state is correctly managed for functions that use
  // Rcpp::export...other functions will require management of the RNGScope
  return unif_rand() * INT_MAX;
}

void cpp_compat_srandom(int seed) {
  // pretty sure this should not have any effect
  // it gets called on load here with the initiation
  // of the Random class in s2testing, so it can't
  // error out
}

std::ostream& cpp_compat_cerr = Rcerr;
std::ostream& cpp_compat_cout = Rcout;
