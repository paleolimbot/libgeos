
#ifndef LIBGEOS_RCPP_H
#define LIBGEOS_RCPP_H

#ifdef LIBGEOS_RCPP_USE_SYSTEM_GEOS
#include "geos_c.h"
#else
#include "libgeos.h"
#endif

#include <memory>
#include <sstream>
#include <Rcpp.h>


class LibGEOSHandle {
public:
  // not copyable
  LibGEOSHandle(const LibGEOSHandle& geom) = delete;

  LibGEOSHandle() {
    if (GEOS_init_r == NULL) {
      Rcpp::stop("LibGEOS API was not initialized. Did you forget to call libgeos_init_api()?");
    }
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOS_init_r()\n";
#endif
    this->handle = GEOS_init_r();
    GEOSContext_setNoticeHandler_r(this->handle, this->handleWarning);
    GEOSContext_setErrorHandler_r(this->handle, this->handleError);
  }

  GEOSContextHandle_t get() {
    return handle;
  }

  ~LibGEOSHandle() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOS_finish_r()\n";
#endif
    GEOS_finish_r(handle);
  }

  void warnForMismatchedVersions() {
    if (this->runtimeVersion() != this->buildVersion()) {
      std::stringstream err;
      err << "libgeos build version (" << this->buildVersion() <<
        ") is not the same as the libgeos runtime version (" << this->runtimeVersion() << ")";
      Rcpp::Function warning("warning");
      warning(err.str());
    }
  }

private:
  GEOSContextHandle_t handle;

public:

  static std::string runtimeVersion() {
    return GEOSversion();
  }

  static std::string buildVersion() {
    return GEOS_CAPI_VERSION;
  }

  static void handleError(const char *fmt, ...) {

    char buf[BUFSIZ], *p;
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    p = buf + strlen(buf) - 1;
    if(strlen(buf) > 0 && *p == '\n') *p = '\0';

    Rcpp::stop(buf);
  }

  static void handleWarning(const char *fmt, ...) {

    char buf[BUFSIZ], *p;
    va_list ap;
    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
    p = buf + strlen(buf) - 1;
    if(strlen(buf) > 0 && *p == '\n') *p = '\0';

    Rcpp::Function warning("warning");
    warning(buf);

    return;
  }
};


class LibGEOSGeometry {
public:
  // moveable and copyable: requires C++11
  LibGEOSGeometry(const LibGEOSGeometry& geom):
    handle(geom.handle), geometryPtr(nullptr), preparedGeometryPtr(nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "LibGEOSGeometry(GEOSGeom_clone_r())\n";
#endif
    this->geometryPtr = GEOSGeom_clone_r(handle.get(), geom.geometryPtr);
  }

  LibGEOSGeometry(LibGEOSGeometry&&) = default;

  LibGEOSGeometry(LibGEOSHandle& handle):
    handle(handle), geometryPtr(nullptr), preparedGeometryPtr(nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "LibGEOSGeometry(nullptr)\n";
#endif
  }
  LibGEOSGeometry(LibGEOSHandle& handle, GEOSGeometry* geometryPtr):
    handle(handle), geometryPtr(geometryPtr), preparedGeometryPtr(nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "LibGEOSGeometry(GEOSGeometry*)\n";
#endif
  }

  const GEOSGeometry* get() {
    return this->geometryPtr;
  }

  const GEOSPreparedGeometry* getPrepared() {
    if (this->preparedGeometryPtr == nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
      Rcpp::Rcout << "GEOSPrepare_r()\n";
#endif
      this->preparedGeometryPtr = (GEOSPreparedGeometry*) GEOSPrepare_r(this->handle.get(), this->geometryPtr);
    }
    return this->preparedGeometryPtr;
  }

  ~LibGEOSGeometry() {
    if (this->geometryPtr != nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
      Rcpp::Rcout << "GEOSGeom_destroy_r()\n";
#endif
      GEOSGeom_destroy_r(this->handle.get(), this->geometryPtr);
    }

    if (this->preparedGeometryPtr != nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
      Rcpp::Rcout << "GEOSPreparedGeom_destroy_r()\n";
#endif
      GEOSPreparedGeom_destroy_r(this->handle.get(), this->preparedGeometryPtr);
    }
  }

private:
  LibGEOSHandle& handle;
  GEOSGeometry* geometryPtr;
  GEOSPreparedGeometry* preparedGeometryPtr;
};


class LibGEOSWKBReader {
public:
  LibGEOSWKBReader(LibGEOSHandle& handle): handle(handle) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKBReader_create_r()\n";
#endif
    this->reader = GEOSWKBReader_create_r(this->handle.get());
  }

  LibGEOSGeometry read(Rcpp::RawVector raw) {
    GEOSGeometry* geometryPtr = GEOSWKBReader_read_r(this->handle.get(), this->reader, &(raw[0]), raw.size());
    return LibGEOSGeometry(this->handle, geometryPtr);
  }

  LibGEOSGeometry readHex(const char* text) {
    GEOSGeometry* geometryPtr = GEOSWKBReader_readHEX_r(
      this->handle.get(),
      this->reader,
      // not sure if this is the correct cast
      reinterpret_cast<const unsigned char *>(text),
      strlen(text)
    );

    return LibGEOSGeometry(this->handle, geometryPtr);
  }

  ~LibGEOSWKBReader() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKBReader_destroy_r()\n";
#endif
    GEOSWKBReader_destroy_r(this->handle.get(), this->reader);
  }

private:
  LibGEOSHandle& handle;
  GEOSWKBReader* reader;
};

class LibGEOSWKTReader {
public:
  LibGEOSWKTReader(LibGEOSHandle& handle): handle(handle) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKTReader_create_r()\n";
#endif
    this->reader = GEOSWKTReader_create_r(this->handle.get());
  }

  LibGEOSGeometry read(const char* text) {
    GEOSGeometry* geometryPtr = GEOSWKTReader_read_r(this->handle.get(), this->reader, text);
    return LibGEOSGeometry(this->handle, geometryPtr);
  }

  ~LibGEOSWKTReader() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKTReader_destroy_r()\n";
#endif
    GEOSWKTReader_destroy_r(this->handle.get(), this->reader);
  }

private:
  LibGEOSHandle& handle;
  GEOSWKTReader* reader;
};

class LibGEOSWKTWriter {
public:
  LibGEOSWKTWriter(LibGEOSHandle& handle): handle(handle) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKTWriter_create_r()\n";
#endif
    this->writer = GEOSWKTWriter_create_r(this->handle.get());
  }

  void setTrim(bool trim) {
    GEOSWKTWriter_setTrim_r(this->handle.get(), this->writer, trim);
  }

  void setRoundingPrecision(int precision) {
    GEOSWKTWriter_setRoundingPrecision_r(this->handle.get(), this->writer, precision);
  }

  void setOutputDimension(int dimension) {
    GEOSWKTWriter_setOutputDimension_r(this->handle.get(), this->writer, dimension);
  }

  std::string write(const GEOSGeometry* geometry) {
    char* resultBuffer = GEOSWKTWriter_write_r(this->handle.get(), this->writer, geometry);
    std::string result(resultBuffer);
    GEOSFree_r(this->handle.get(), resultBuffer);
    return result;
  }

  ~LibGEOSWKTWriter() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKTWriter_destroy_r()\n";
#endif
    GEOSWKTWriter_destroy_r(this->handle.get(), this->writer);
  }

private:
  LibGEOSHandle& handle;
  GEOSWKTWriter* writer;
};

class LibGEOSWKBWriter {
public:
  LibGEOSWKBWriter(LibGEOSHandle& handle): handle(handle) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKBWriter_create_r()\n";
#endif
    this->writer = GEOSWKBWriter_create_r(this->handle.get());
  }

  void setByteOrder(int endian) {
    GEOSWKBWriter_setByteOrder_r(this->handle.get(), this->writer, endian);
  }

  void setIncludeSRID(bool includeSRID) {
    GEOSWKBWriter_setIncludeSRID_r(this->handle.get(), this->writer, includeSRID);
  }

  void setOutputDimension(int dimension) {
    GEOSWKBWriter_setOutputDimension_r(this->handle.get(), this->writer, dimension);
  }

  Rcpp::RawVector write(const GEOSGeometry* geometry) {
    size_t size;
    unsigned char *buf = GEOSWKBWriter_write_r(this->handle.get(), this->writer, geometry, &size);
    Rcpp::RawVector raw(size);
    memcpy(&(raw[0]), buf, size);
    GEOSFree_r(this->handle.get(), buf);
    return raw;
  }

  std::string writeHex(const GEOSGeometry* geometry) {
    size_t size;
    unsigned char* resultBuffer = GEOSWKBWriter_writeHEX_r(this->handle.get(), this->writer, geometry, &size);

    // best I can think of for converting to char*
    char* resultBuffer2 = new char[size];
    memcpy(resultBuffer2, resultBuffer, size);
    GEOSFree_r(this->handle.get(), resultBuffer);

    std::string result(resultBuffer2);
    delete[] resultBuffer2;

    return result;
  }

  ~LibGEOSWKBWriter() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSWKBWriter_destroy_r()\n";
#endif
    GEOSWKBWriter_destroy_r(this->handle.get(), this->writer);
  }

private:
  LibGEOSHandle& handle;
  GEOSWKBWriter* writer;
};

class LibGEOSBufferParams {
public:
  LibGEOSBufferParams(LibGEOSHandle& handle): handle(handle) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSBufferParams_create_r()\n";
#endif
    this->params = GEOSBufferParams_create_r(this->handle.get());
  }

  const GEOSBufferParams* get() {
    return this->params;
  }

  void setEndCapStyle(int endCapStyle) {
    GEOSBufferParams_setSingleSided_r(this->handle.get(), this->params, endCapStyle);
  }

  void setJoinStyle(int joinStyle) {
    GEOSBufferParams_setJoinStyle_r(this->handle.get(), this->params, joinStyle);
  }

  void setMitreLimit(double mitreLimit) {
    GEOSBufferParams_setMitreLimit_r(this->handle.get(), this->params, mitreLimit);
  }

  void setQuadrantSegments(int nSegments) {
    GEOSBufferParams_setQuadrantSegments_r(this->handle.get(), this->params, nSegments);
  }

  void setSingleSided(bool singleSided) {
    GEOSBufferParams_setSingleSided_r(this->handle.get(), this->params, singleSided);
  }

  ~LibGEOSBufferParams() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rcpp::Rcout << "GEOSBufferParams_destroy_r()\n";
#endif
    GEOSBufferParams_destroy_r(this->handle.get(), this->params);
  }

private:
  LibGEOSHandle& handle;
  GEOSBufferParams* params;
};

#endif
