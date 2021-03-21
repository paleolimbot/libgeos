
#include "libgeos-cpp-compat.h"
#include <iostream>
#include <R.h>
#include <Rinternals.h>

class RcerrBuffer: public std::streambuf {
public:
  RcerrBuffer() {}

protected:
  virtual std::streamsize xsputn(const char *s, std::streamsize n) {
    REprintf("%.*s", n, s);
    return n;
  }

  virtual int overflow(int c = traits_type::eof()) {
    if (c != traits_type::eof()) {
      char_type ch = traits_type::to_char_type(c);
      return xsputn(&ch, 1) == 1 ? c : traits_type::eof();
    }
    return c;
  }

  virtual int sync() {
    R_FlushConsole();
    return 0;
  }
};

class RcerrStream: public std::ostream {
  RcerrBuffer buf;
public:
  RcerrStream(): std::ostream(&buf) {}
};

static RcerrStream Rcerr;
std::ostream& cpp_compat_cerr = Rcerr;
