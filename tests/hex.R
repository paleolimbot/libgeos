
Sys.setenv(R_TESTS = "")
requireNamespace("libgeos")
Rcpp::sourceCpp(
  code = '
  #include <Rcpp.h>
  // [[Rcpp::depends(libgeos)]]
  #include "libgeos-rcpp.h"
  #include "libgeos.c"
  using namespace Rcpp;

  // [[Rcpp::export]]
  void source_rcpp_libgeos_init() {
    libgeos_init_api();
  }

  // [[Rcpp::export]]
  CharacterVector hex_wkt(CharacterVector hex) {
    CharacterVector output(hex.size());

    LibGEOSHandle handle;
    LibGEOSWKBReader reader(handle);
    LibGEOSWKTWriter writer(handle);
    writer.setTrim(true);
    writer.setOutputDimension(3);
    writer.setRoundingPrecision(16);

    for (R_xlen_t i = 0; i < hex.size(); i++) {
      LibGEOSGeometry geom = reader.readHex(hex[i]);
      output[i] = writer.write(geom.get());
    }

    return output;
  }

  // [[Rcpp::export]]
  CharacterVector wkt_hex(CharacterVector wkt) {
    CharacterVector output(wkt.size());

    LibGEOSHandle handle;
    LibGEOSWKTReader reader(handle);
    LibGEOSWKBWriter writer(handle);
    writer.setByteOrder(1);
    writer.setIncludeSRID(true);
    writer.setOutputDimension(3);

    for (R_xlen_t i = 0; i < wkt.size(); i++) {
      LibGEOSGeometry geom = reader.read(wkt[i]);
      output[i] = writer.writeHex(geom.get());
    }

    return output;
  }

  '
)

source_rcpp_libgeos_init()
wkt_hex("POINT (30 10)")
hex_wkt("01010000000000000000003E400000000000002440")
