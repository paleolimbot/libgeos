
test_that("Rcpp error handler works without segfaulting", {
  cache <- source_rcpp_libgeos('
    // [[Rcpp::export]]
    void wkt_validate_catch(CharacterVector wkt) {
      LibGEOSHandle handle;
      LibGEOSWKTReader reader(handle);

      try {
        for (R_xlen_t i = 0; i < wkt.size(); i++) {
          LibGEOSGeometry geom = reader.read(wkt[i]);
        }
      } catch(std::exception& e) {
        Rcout << "Converting error to stdout: " << e.what();
      }
    }

    // [[Rcpp::export]]
    void wkt_validate(CharacterVector wkt) {
      LibGEOSHandle handle;
      LibGEOSWKTReader reader(handle);
      for (R_xlen_t i = 0; i < wkt.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkt[i]);
      }
    }
  ')

  source_rcpp_libgeos_init()

  # make sure it's possible to catch exceptions coming from the error handler
  expect_silent(wkt_validate_catch("POINT EMPTY"))
  expect_output(wkt_validate_catch("NOPE1"), "ParseException")

  unlink(cache, recursive = TRUE)
})

test_that("Rcpp API readers and writers work as expected", {
  cache <- source_rcpp_libgeos('
    // [[Rcpp::export]]
    CharacterVector wkt_wkt(CharacterVector wkt) {
      CharacterVector output(wkt.size());

      LibGEOSHandle handle;
      LibGEOSWKTReader reader(handle);
      LibGEOSWKTWriter writer(handle);
      writer.setTrim(true);
      writer.setOutputDimension(3);
      writer.setRoundingPrecision(16);

      for (R_xlen_t i = 0; i < wkt.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkt[i]);
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

    // [[Rcpp::export]]
    List wkt_wkb(CharacterVector wkt) {
      List output(wkt.size());

      LibGEOSHandle handle;
      LibGEOSWKTReader reader(handle);
      LibGEOSWKBWriter writer(handle);
      writer.setByteOrder(1);
      writer.setIncludeSRID(true);
      writer.setOutputDimension(3);

      for (R_xlen_t i = 0; i < wkt.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkt[i]);
        output[i] = writer.write(geom.get());
      }

      return output;
    }

    // [[Rcpp::export]]
    List wkb_wkb(List wkb) {
      List output(wkb.size());

      LibGEOSHandle handle;
      LibGEOSWKBReader reader(handle);
      LibGEOSWKBWriter writer(handle);
      writer.setByteOrder(1);
      writer.setIncludeSRID(true);
      writer.setOutputDimension(3);

      for (R_xlen_t i = 0; i < wkb.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkb[i]);
        output[i] = writer.write(geom.get());
      }

      return output;
    }

    // [[Rcpp::export]]
    CharacterVector wkb_wkt(List wkb) {
      CharacterVector output(wkb.size());

      LibGEOSHandle handle;
      LibGEOSWKBReader reader(handle);
      LibGEOSWKTWriter writer(handle);
      writer.setTrim(true);
      writer.setOutputDimension(3);
      writer.setRoundingPrecision(16);

      for (R_xlen_t i = 0; i < wkb.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkb[i]);
        output[i] = writer.write(geom.get());
      }

      return output;
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
        LibGEOSGeometry geom = reader.readHex(as<std::string>(hex[i]));
        output[i] = writer.write(geom.get());
      }

      return output;
    }

    // [[Rcpp::export]]
    CharacterVector hex_hex(CharacterVector hex) {
      CharacterVector output(hex.size());

      LibGEOSHandle handle;
      LibGEOSWKBReader reader(handle);
      LibGEOSWKBWriter writer(handle);
      writer.setByteOrder(1);
      writer.setIncludeSRID(true);
      writer.setOutputDimension(3);

      for (R_xlen_t i = 0; i < hex.size(); i++) {
        LibGEOSGeometry geom = reader.readHex(as<std::string>(hex[i]));
        output[i] = writer.writeHex(geom.get());
      }

      return output;
    }
  ')

  expect_error(wkt_wkt("POINT (30 10)"), "LibGEOS API was not initialized")
  source_rcpp_libgeos_init()

  expect_identical(wkt_wkt("POINT (30 10)"), "POINT (30 10)")
  expect_identical(wkb_wkt(wkt_wkb("POINT (30 10)")), "POINT (30 10)")
  expect_identical(wkb_wkt(wkb_wkb((wkt_wkb("POINT (30 10)")))), "POINT (30 10)")
  expect_identical(hex_wkt(wkt_hex("POINT (30 10)")), "POINT (30 10)")
  expect_identical(hex_wkt(hex_hex((wkt_hex("POINT (30 10)")))), "POINT (30 10)")

  unlink(cache, recursive = TRUE)
})

test_that("deleters are called", {
  cache <- source_rcpp_libgeos("
    // [[Rcpp::export]]
    CharacterVector wkt_wkt(CharacterVector wkt) {
      CharacterVector output(wkt.size());

      LibGEOSHandle handle;
      LibGEOSWKTReader reader(handle);
      LibGEOSWKTWriter writer(handle);

      for (R_xlen_t i = 0; i < wkt.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkt[i]);
        output[i] = writer.write(geom.get());
      }

      return output;
    }

    // [[Rcpp::export]]
    CharacterVector wkt_wkt_prep(CharacterVector wkt) {
      CharacterVector output(wkt.size());

      LibGEOSHandle handle;
      LibGEOSWKTReader reader(handle);
      LibGEOSWKTWriter writer(handle);

      for (R_xlen_t i = 0; i < wkt.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkt[i]);
        geom.getPrepared();
        output[i] = writer.write(geom.get());
      }

      return output;
    }

    // [[Rcpp::export]]
    List wkb_wkb(List wkb) {
      List output(wkb.size());

      LibGEOSHandle handle;
      LibGEOSWKBReader reader(handle);
      LibGEOSWKBWriter writer(handle);

      for (R_xlen_t i = 0; i < wkb.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkb[i]);
        output[i] = writer.write(geom.get());
      }

      return output;
    }
  ", header = "#define LIBGEOS_DEBUG_MEMORY")

  source_rcpp_libgeos_init()
  expect_output(
    wkt_wkt("POINT EMPTY"),
    paste(
      "GEOS_init_r()",
      "GEOSWKTReader_create_r()",
      "GEOSWKTWriter_create_r()",
      "LibGEOSGeometry(GEOSGeometry*)",
      "GEOSGeom_destroy_r()",
      "GEOSWKTWriter_destroy_r()",
      "GEOSWKTReader_destroy_r()",
      "GEOS_finish_r()",
      sep = "\n"
    ), fixed = TRUE
  )

  expect_output(
    expect_error(wkt_wkt("NOPE4"), class = "LibGEOSRcppException"),
    paste(
      "GEOS_init_r()",
      "GEOSWKTReader_create_r()",
      "GEOSWKTWriter_create_r()",
      "GEOSWKTWriter_destroy_r()",
      "GEOSWKTReader_destroy_r()",
      "GEOS_finish_r()",
      sep = "\n"
    ), fixed = TRUE
  )

  expect_output(
    wkt_wkt_prep("POINT EMPTY"),
    paste(
      "GEOS_init_r()",
      "GEOSWKTReader_create_r()",
      "GEOSWKTWriter_create_r()",
      "LibGEOSGeometry(GEOSGeometry*)",
      "GEOSPrepare_r()",
      "GEOSGeom_destroy_r()",
      "GEOSPreparedGeom_destroy_r()",
      "GEOSWKTWriter_destroy_r()",
      "GEOSWKTReader_destroy_r()",
      "GEOS_finish_r()",
      sep = "\n"
    ), fixed = TRUE
  )

  expect_output(
    wkb_wkb(
      # LINESTRING EMPTY
      list(as.raw(c(0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00)))
    ),
    paste(
      "GEOS_init_r()",
      "GEOSWKBReader_create_r()",
      "GEOSWKBWriter_create_r()",
      "LibGEOSGeometry(GEOSGeometry*)",
      "GEOSGeom_destroy_r()",
      "GEOSWKBWriter_destroy_r()",
      "GEOSWKBReader_destroy_r()",
      "GEOS_finish_r()",
      sep = "\n"
    ), fixed = TRUE
  )

  expect_output(
    expect_error(wkb_wkb(list(raw(0))), class = "LibGEOSRcppException"),
    paste(
      "GEOS_init_r()",
      "GEOSWKBReader_create_r()",
      "GEOSWKBWriter_create_r()",
      "GEOSWKBWriter_destroy_r()",
      "GEOSWKBReader_destroy_r()",
      "GEOS_finish_r()",
      sep = "\n"
    ),
    fixed = TRUE
  )

  unlink(cache, recursive = TRUE)
})

test_that("buffer params work", {
  cache <- source_rcpp_libgeos("
    // [[Rcpp::export]]
    CharacterVector wkt_buffer(CharacterVector wkt, double distance) {
      CharacterVector output(wkt.size());

      LibGEOSHandle handle;
      LibGEOSWKTReader reader(handle);
      LibGEOSWKTWriter writer(handle);
      writer.setTrim(true);

      LibGEOSBufferParams params(handle);
      params.setEndCapStyle(GEOSBufCapStyles::GEOSBUF_CAP_ROUND);
      params.setJoinStyle(GEOSBufJoinStyles::GEOSBUF_JOIN_ROUND);
      params.setMitreLimit(1);
      params.setQuadrantSegments(2);
      params.setSingleSided(false);

      for (R_xlen_t i = 0; i < wkt.size(); i++) {
        LibGEOSGeometry geom = reader.read(wkt[i]);
        LibGEOSGeometry buffered = LibGEOSGeometry(
          handle,
          GEOSBufferWithParams_r(handle.get(), geom.get(), params.get(), distance)
        );
        output[i] = writer.write(buffered.get());
      }

      return output;
    }
  ")

  source_rcpp_libgeos_init()

  expect_match(wkt_buffer("POINT (0 0)", 10), "^POLYGON \\(\\(")

  unlink(cache, recursive = TRUE)
})

