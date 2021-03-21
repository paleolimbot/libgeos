
#ifndef LIBGEOS_CPP_H
#define LIBGEOS_CPP_H

#include <stdexcept>
#include <cstring>
#include <sstream>

#ifdef LIBGEOS_CPP_USE_SYSTEM_GEOS
#include "geos_c.h"
#else
#include "libgeos.h"
#endif

#if defined(LIBGEOS_USE_RCPP)
#include <Rcpp.h>
#define LIBGEOS_RAW Rcpp::RawVector
#define LIBGEOS_RAW_WRITABLE Rcpp::RawVector
#elif defined(LIBGEOS_USE_CPP11)
#include <cpp11.hpp>
#define LIBGEOS_RAW cpp11::raws
#define LIBGEOS_RAW_WRITABLE cpp11::writable::raws
#else
#error Define one of 'LIBGEOS_USE_RCPP' or 'LIBGEOS_USE_CPP11'
#endif

class LibGEOSCppException: public std::runtime_error {
public:
  LibGEOSCppException(std::string msg): std::runtime_error(msg) {}
};

class LibGEOSHandle {
public:
  // not copyable
  LibGEOSHandle(const LibGEOSHandle& geom) = delete;

  LibGEOSHandle() {
    if (GEOS_init_r == NULL) {
      throw std::runtime_error("LibGEOS API was not initialized. Did you forget to call libgeos_init_api()?");
    }
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("GEOS_init_r()\n");
#endif
    this->handle = GEOS_init_r();
    GEOSContext_setNoticeMessageHandler_r(this->handle, this->handleWarning, this);
    GEOSContext_setErrorMessageHandler_r(this->handle, this->handleError, this);
  }

  GEOSContextHandle_t get() {
    return handle;
  }

private:
  std::string lastErrorMessage_;

  static void handleError(const char *message, void *userdata) {
    // throwing an exception here would be the easiest thing to do; however,
    // this exception can't be caught by the client on (at least)
    // Windows i386. Instead, we store the last error and provide
    // an overloaded checkResult() method that throws the exception
    // where it can be caught.
    ((LibGEOSHandle*) userdata)->lastErrorMessage_ = std::string(message);
  }

  static void handleWarning(const char *message, void *userdata) {
    // One could throw a true warning() here, but this could generate
    // an exception or longjmp and it's rarely used in the GEOS API anyway
    REprintf(message);
  }

public:
  std::string lastErrorMessage() {
    return this->lastErrorMessage_;
  }

  void throwLastError() {
    throw LibGEOSCppException(this->lastErrorMessage());
  }

  GEOSGeometry* checkGeometry(GEOSGeometry* geometry) {
    if (geometry == NULL) {
      this->throwLastError();
    }

    return geometry;
  }

  char checkPredicateResult(char result) {
    if (result == 2) {
      this->throwLastError();
    }

    return result;
  }

  ~LibGEOSHandle() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("GEOS_finish_r()\n");
#endif
    GEOS_finish_r(handle);
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
};


class LibGEOSGeometry {
public:
  // moveable and copyable: requires C++11
  LibGEOSGeometry(const LibGEOSGeometry& geom):
    handle(geom.handle), geometryPtr(nullptr), preparedGeometryPtr(nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("LibGEOSGeometry(GEOSGeom_clone_r())\n");
#endif
    this->geometryPtr = handle.checkGeometry(GEOSGeom_clone_r(handle.get(), geom.geometryPtr));
  }

  LibGEOSGeometry(LibGEOSGeometry&&) = default;

  LibGEOSGeometry(LibGEOSHandle& handle, GEOSGeometry* geometryPtr):
    handle(handle), geometryPtr(handle.checkGeometry(geometryPtr)), preparedGeometryPtr(nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("LibGEOSGeometry(GEOSGeometry*)\n");
#endif
  }

  GEOSGeometry* release() {
    GEOSGeometry* geometry = this->geometryPtr;
    this->geometryPtr = nullptr;
    return geometry;
  }

  const GEOSGeometry* get() {
    return this->geometryPtr;
  }

  const GEOSPreparedGeometry* getPrepared() {
    if (this->preparedGeometryPtr == nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
      Rprintf("GEOSPrepare_r()\n");
#endif
      const GEOSPreparedGeometry* prepared = GEOSPrepare_r(this->handle.get(), this->geometryPtr);
      this->preparedGeometryPtr = (GEOSPreparedGeometry*) prepared;
    }
    return this->preparedGeometryPtr;
  }

  ~LibGEOSGeometry() {
    if (this->geometryPtr != nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
      Rprintf("GEOSGeom_destroy_r()\n");
#endif
      GEOSGeom_destroy_r(this->handle.get(), this->geometryPtr);
    }

    if (this->preparedGeometryPtr != nullptr) {
#ifdef LIBGEOS_DEBUG_MEMORY
      Rprintf("GEOSPreparedGeom_destroy_r()\n");
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
    Rprintf("GEOSWKBReader_create_r()\n");
#endif
    this->reader = GEOSWKBReader_create_r(this->handle.get());
  }

  LibGEOSGeometry read(LIBGEOS_RAW raw) {
    GEOSGeometry* geometryPtr = GEOSWKBReader_read_r(this->handle.get(), this->reader, RAW(raw), raw.size());
    return LibGEOSGeometry(this->handle, this->handle.checkGeometry(geometryPtr));
  }

  LibGEOSGeometry readHex(std::string wkbstring) {
    GEOSGeometry* geometryPtr = GEOSWKBReader_readHEX_r(
        this->handle.get(),
        this->reader,
        reinterpret_cast<const unsigned char*>(wkbstring.data()),
        wkbstring.size()
      );
      return LibGEOSGeometry(this->handle, this->handle.checkGeometry(geometryPtr));
  }

  ~LibGEOSWKBReader() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("GEOSWKBReader_destroy_r()\n");
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
    Rprintf("GEOSWKTReader_create_r()\n");
#endif
    this->reader = GEOSWKTReader_create_r(this->handle.get());
  }

  LibGEOSGeometry read(const char* text) {
    GEOSGeometry* geometryPtr = GEOSWKTReader_read_r(this->handle.get(), this->reader, text);
    return LibGEOSGeometry(this->handle, this->handle.checkGeometry(geometryPtr));
  }

  ~LibGEOSWKTReader() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("GEOSWKTReader_destroy_r()\n");
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
    Rprintf("GEOSWKTWriter_create_r()\n");
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
    if (resultBuffer == NULL) {
      this->handle.throwLastError();
    }

    std::string result(resultBuffer);
    GEOSFree_r(this->handle.get(), resultBuffer);
    return result;
  }

  ~LibGEOSWKTWriter() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("GEOSWKTWriter_destroy_r()\n");
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
    Rprintf("GEOSWKBWriter_create_r()\n");
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

  LIBGEOS_RAW write(const GEOSGeometry* geometry) {
    size_t size;
    unsigned char *buf = GEOSWKBWriter_write_r(this->handle.get(), this->writer, geometry, &size);
    if (buf == NULL) {
      this->handle.throwLastError();
    }

    LIBGEOS_RAW_WRITABLE raw(size);
    memcpy(RAW(raw), buf, size);
    GEOSFree_r(this->handle.get(), buf);
    return raw;
  }

  std::string writeHex(const GEOSGeometry* geometry) {
    size_t size;
    unsigned char* hex = GEOSWKBWriter_writeHEX_r(this->handle.get(), this->writer, geometry, &size);
    if (hex == NULL) {
      this->handle.throwLastError();
    }

    std::string hexstring(reinterpret_cast<const char*>(hex), size);
    return hexstring;
  }

  ~LibGEOSWKBWriter() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("GEOSWKBWriter_destroy_r()\n");
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
    Rprintf("GEOSBufferParams_create_r()\n");
#endif
    this->params = GEOSBufferParams_create_r(this->handle.get());
  }

  const GEOSBufferParams* get() {
    return this->params;
  }

  void setEndCapStyle(int endCapStyle) {
    int result = GEOSBufferParams_setEndCapStyle_r(this->handle.get(), this->params, endCapStyle);
    this->checkSetResult(result);
  }

  void setJoinStyle(int joinStyle) {
    int result = GEOSBufferParams_setJoinStyle_r(this->handle.get(), this->params, joinStyle);
    this->checkSetResult(result);
  }

  void setMitreLimit(double mitreLimit) {
    int result = GEOSBufferParams_setMitreLimit_r(this->handle.get(), this->params, mitreLimit);
    this->checkSetResult(result);
  }

  void setQuadrantSegments(int nSegments) {
    int result = GEOSBufferParams_setQuadrantSegments_r(this->handle.get(), this->params, nSegments);
    this->checkSetResult(result);
  }

  void setSingleSided(bool singleSided) {
    int result = GEOSBufferParams_setSingleSided_r(this->handle.get(), this->params, singleSided);
    this->checkSetResult(result);
  }

  ~LibGEOSBufferParams() {
#ifdef LIBGEOS_DEBUG_MEMORY
    Rprintf("GEOSBufferParams_destroy_r()\n");
#endif
    GEOSBufferParams_destroy_r(this->handle.get(), this->params);
  }

private:
  LibGEOSHandle& handle;
  GEOSBufferParams* params;

  int checkSetResult(int result) {
    if (result == 0) {
      this->handle.throwLastError();
    }
    return result;
  }
};

#endif
