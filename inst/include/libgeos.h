
#ifndef LIBGEOS_H
#define LIBGEOS_H

#include <Rinternals.h>
#include <R_ext/Rdynload.h>

typedef struct GEOSContextHandle_HS *GEOSContextHandle_t;
typedef void (*GEOSMessageHandler)(const char *fmt, ...);
typedef void (*GEOSMessageHandler_r)(const char *message, void *userdata);
typedef struct GEOSGeom_t GEOSGeometry;
typedef struct GEOSPrepGeom_t GEOSPreparedGeometry;
typedef struct GEOSCoordSeq_t GEOSCoordSequence;
typedef struct GEOSSTRtree_t GEOSSTRtree;
typedef struct GEOSBufParams_t GEOSBufferParams;
typedef GEOSGeometry* GEOSGeom;
typedef GEOSCoordSequence* GEOSCoordSeq;
typedef void (*GEOSQueryCallback)(void *item, void *userdata);
typedef int (*GEOSDistanceCallback)(const void *item1, const void* item2, double* distance, void* userdata);
typedef void (GEOSInterruptCallback)();
typedef struct GEOSWKTReader_t GEOSWKTReader;
typedef struct GEOSWKTWriter_t GEOSWKTWriter;
typedef struct GEOSWKBReader_t GEOSWKBReader;
typedef struct GEOSWKBWriter_t GEOSWKBWriter;

enum GEOSGeomTypes {
    GEOS_POINT,
    GEOS_LINESTRING,
    GEOS_LINEARRING,
    GEOS_POLYGON,
    GEOS_MULTIPOINT,
    GEOS_MULTILINESTRING,
    GEOS_MULTIPOLYGON,
    GEOS_GEOMETRYCOLLECTION
};
enum GEOSByteOrders {
    GEOS_WKB_XDR = 0, /* Big Endian */
    GEOS_WKB_NDR = 1 /* Little Endian */
};
enum GEOSBufCapStyles {
	GEOSBUF_CAP_ROUND=1,
	GEOSBUF_CAP_FLAT=2,
	GEOSBUF_CAP_SQUARE=3
};
enum GEOSBufJoinStyles {
	GEOSBUF_JOIN_ROUND=1,
	GEOSBUF_JOIN_MITRE=2,
	GEOSBUF_JOIN_BEVEL=3
};
enum GEOSRelateBoundaryNodeRules {
	/* MOD2 and OGC are the same rule, and is the default
	 * used by GEOSRelatePattern
	 */
	GEOSRELATE_BNR_MOD2=1,
	GEOSRELATE_BNR_OGC=1,
	GEOSRELATE_BNR_ENDPOINT=2,
	GEOSRELATE_BNR_MULTIVALENT_ENDPOINT=3,
	GEOSRELATE_BNR_MONOVALENT_ENDPOINT=4
};
enum GEOSValidFlags {
	GEOSVALID_ALLOW_SELFTOUCHING_RING_FORMING_HOLE=1
};

extern GEOSContextHandle_t (*GEOS_init_r)();
extern void (*GEOS_finish_r)(GEOSContextHandle_t);
extern const char* (*GEOSversion)();

void libgeos_init_api();

#endif
