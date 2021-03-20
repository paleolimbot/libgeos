
// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#ifndef LIBGEOS_H
#define LIBGEOS_H

#ifndef __cplusplus
# include <stddef.h> /* for size_t definition */
#else
# include <cstddef>
using std::size_t;
#endif

#ifndef GEOS_VERSION_MAJOR
#define GEOS_VERSION_MAJOR 3
#endif
#ifndef GEOS_VERSION_MINOR
#define GEOS_VERSION_MINOR 9
#endif
#ifndef GEOS_VERSION_PATCH
#define GEOS_VERSION_PATCH 1
#endif
#ifndef GEOS_VERSION
#define GEOS_VERSION "3.9.1"
#endif
#ifndef GEOS_JTS_PORT
#define GEOS_JTS_PORT "1.17.0"
#endif

#define GEOS_CAPI_VERSION_MAJOR 1
#define GEOS_CAPI_VERSION_MINOR 14
#define GEOS_CAPI_VERSION_PATCH 2
#define GEOS_CAPI_VERSION "3.9.1-CAPI-1.14.2"

#define GEOS_CAPI_FIRST_INTERFACE GEOS_CAPI_VERSION_MAJOR
#define GEOS_CAPI_LAST_INTERFACE (GEOS_CAPI_VERSION_MAJOR+GEOS_CAPI_VERSION_MINOR)

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

extern GEOSContextHandle_t (*initGEOS_r)( GEOSMessageHandler, GEOSMessageHandler);
extern void (*finishGEOS_r)(GEOSContextHandle_t);
extern GEOSContextHandle_t (*GEOS_init_r)();
extern void (*GEOS_finish_r)(GEOSContextHandle_t);
extern GEOSMessageHandler (*GEOSContext_setNoticeHandler_r)(GEOSContextHandle_t, GEOSMessageHandler);
extern GEOSMessageHandler (*GEOSContext_setErrorHandler_r)(GEOSContextHandle_t, GEOSMessageHandler);
extern GEOSMessageHandler_r (*GEOSContext_setNoticeMessageHandler_r)(GEOSContextHandle_t, GEOSMessageHandler_r, void*);
extern GEOSMessageHandler_r (*GEOSContext_setErrorMessageHandler_r)(GEOSContextHandle_t, GEOSMessageHandler_r, void*);
extern const char* (*GEOSversion)();
extern GEOSGeometry* (*GEOSGeomFromWKT_r)(GEOSContextHandle_t, const char*);
extern char* (*GEOSGeomToWKT_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOS_getWKBOutputDims_r)(GEOSContextHandle_t);
extern int (*GEOS_setWKBOutputDims_r)(GEOSContextHandle_t, int);
extern int (*GEOS_getWKBByteOrder_r)(GEOSContextHandle_t);
extern int (*GEOS_setWKBByteOrder_r)(GEOSContextHandle_t, int);
extern GEOSGeometry* (*GEOSGeomFromWKB_buf_r)(GEOSContextHandle_t, const unsigned char*, size_t);
extern unsigned char* (*GEOSGeomToWKB_buf_r)(GEOSContextHandle_t, const GEOSGeometry*, size_t*);
extern GEOSGeometry* (*GEOSGeomFromHEX_buf_r)(GEOSContextHandle_t, const unsigned char*, size_t);
extern unsigned char* (*GEOSGeomToHEX_buf_r)(GEOSContextHandle_t, const GEOSGeometry*, size_t*);
extern GEOSCoordSequence* (*GEOSCoordSeq_create_r)( GEOSContextHandle_t, unsigned int, unsigned int);
extern GEOSCoordSequence* (*GEOSCoordSeq_clone_r)( GEOSContextHandle_t, const GEOSCoordSequence*);
extern void (*GEOSCoordSeq_destroy_r)(GEOSContextHandle_t, GEOSCoordSequence*);
extern int (*GEOSCoordSeq_setX_r)(GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double);
extern int (*GEOSCoordSeq_setY_r)(GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double);
extern int (*GEOSCoordSeq_setZ_r)(GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double);
extern int (*GEOSCoordSeq_setXY_r)(GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double, double);
extern int (*GEOSCoordSeq_setXYZ_r)(GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double, double, double);
extern int (*GEOSCoordSeq_setOrdinate_r)(GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, unsigned int, double);
extern int (*GEOSCoordSeq_getX_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*);
extern int (*GEOSCoordSeq_getY_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*);
extern int (*GEOSCoordSeq_getZ_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*);
extern int (*GEOSCoordSeq_getXY_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*, double*);
extern int (*GEOSCoordSeq_getXYZ_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*, double*, double*);
extern int (*GEOSCoordSeq_getOrdinate_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, unsigned int, double*);
extern int (*GEOSCoordSeq_getSize_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int*);
extern int (*GEOSCoordSeq_getDimensions_r)(GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int*);
extern int (*GEOSCoordSeq_isCCW_r)(GEOSContextHandle_t, const GEOSCoordSequence*, char*);
extern double (*GEOSProject_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSInterpolate_r)(GEOSContextHandle_t, const GEOSGeometry*, double);
extern double (*GEOSProjectNormalized_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSInterpolateNormalized_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSBuffer_r)(GEOSContextHandle_t, const GEOSGeometry*, double, int);
extern GEOSBufferParams* (*GEOSBufferParams_create_r)( GEOSContextHandle_t);
extern void (*GEOSBufferParams_destroy_r)( GEOSContextHandle_t, GEOSBufferParams*);
extern int (*GEOSBufferParams_setEndCapStyle_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern int (*GEOSBufferParams_setJoinStyle_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern int (*GEOSBufferParams_setMitreLimit_r)( GEOSContextHandle_t, GEOSBufferParams*, double);
extern int (*GEOSBufferParams_setQuadrantSegments_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern int (*GEOSBufferParams_setSingleSided_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern GEOSGeometry* (*GEOSBufferWithParams_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSBufferParams*, double);
extern GEOSGeometry* (*GEOSBufferWithStyle_r)(GEOSContextHandle_t, const GEOSGeometry*, double, int, int, int, double);
extern GEOSGeometry* (*GEOSSingleSidedBuffer_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int, int, double, int);
extern GEOSGeometry* (*GEOSOffsetCurve_r)(GEOSContextHandle_t, const GEOSGeometry*, double, int, int, double);
extern GEOSGeometry* (*GEOSGeom_createPoint_r)( GEOSContextHandle_t, GEOSCoordSequence*);
extern GEOSGeometry* (*GEOSGeom_createPointFromXY_r)( GEOSContextHandle_t, double, double);
extern GEOSGeometry* (*GEOSGeom_createEmptyPoint_r)( GEOSContextHandle_t);
extern GEOSGeometry* (*GEOSGeom_createLinearRing_r)( GEOSContextHandle_t, GEOSCoordSequence*);
extern GEOSGeometry* (*GEOSGeom_createLineString_r)( GEOSContextHandle_t, GEOSCoordSequence*);
extern GEOSGeometry* (*GEOSGeom_createEmptyLineString_r)( GEOSContextHandle_t);
extern GEOSGeometry* (*GEOSGeom_createEmptyPolygon_r)( GEOSContextHandle_t);
extern GEOSGeometry* (*GEOSGeom_createPolygon_r)( GEOSContextHandle_t, GEOSGeometry*, GEOSGeometry**, unsigned int);
extern GEOSGeometry* (*GEOSGeom_createCollection_r)( GEOSContextHandle_t, int, GEOSGeometry**, unsigned int);
extern GEOSGeometry* (*GEOSGeom_createEmptyCollection_r)( GEOSContextHandle_t, int);
extern GEOSGeometry* (*GEOSGeom_clone_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSGeom_destroy_r)(GEOSContextHandle_t, GEOSGeometry*);
extern GEOSGeometry* (*GEOSEnvelope_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSIntersection_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSIntersectionPrec_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSConvexHull_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMinimumRotatedRectangle_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMaximumInscribedCircle_r)(GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSLargestEmptyCircle_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSMinimumWidth_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMinimumClearanceLine_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSMinimumClearance_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern GEOSGeometry* (*GEOSDifference_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSDifferencePrec_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSSymDifference_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSymDifferencePrec_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSBoundary_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSUnion_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSUnionPrec_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSUnaryUnion_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSUnaryUnionPrec_r)(GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSCoverageUnion_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSUnionCascaded_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSPointOnSurface_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSGetCentroid_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMinimumBoundingCircle_r)(GEOSContextHandle_t, const GEOSGeometry*, double*, GEOSGeometry**);
extern GEOSGeometry* (*GEOSNode_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSClipByRect_r)(GEOSContextHandle_t, const GEOSGeometry*, double, double, double, double);
extern GEOSGeometry* (*GEOSPolygonize_r)(GEOSContextHandle_t, const GEOSGeometry *const geoms[], unsigned int);
extern GEOSGeometry* (*GEOSPolygonize_valid_r)(GEOSContextHandle_t, const GEOSGeometry *const geoms[], unsigned int);
extern GEOSGeometry* (*GEOSPolygonizer_getCutEdges_r)( GEOSContextHandle_t, const GEOSGeometry * const geoms[], unsigned int);
extern GEOSGeometry* (*GEOSPolygonize_full_r)(GEOSContextHandle_t, const GEOSGeometry*, GEOSGeometry**, GEOSGeometry**, GEOSGeometry**);
extern GEOSGeometry* (*GEOSBuildArea_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSLineMerge_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSReverse_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSimplify_r)(GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSTopologyPreserveSimplify_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSGeom_extractUniquePoints_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSharedPaths_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSnap_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSDelaunayTriangulation_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int);
extern GEOSGeometry* (*GEOSVoronoiDiagram_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double, int);
extern int (*GEOSSegmentIntersection_r)( GEOSContextHandle_t, double, double, double, double, double, double, double, double, double*, double*);
extern char (*GEOSDisjoint_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSTouches_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSIntersects_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSCrosses_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSWithin_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSContains_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSOverlaps_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSEquals_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSEqualsExact_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern char (*GEOSCovers_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSCoveredBy_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern const GEOSPreparedGeometry* (*GEOSPrepare_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSPreparedGeom_destroy_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*);
extern char (*GEOSPreparedContains_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedContainsProperly_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedCoveredBy_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedCovers_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedCrosses_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedDisjoint_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedIntersects_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedOverlaps_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedTouches_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedWithin_r)(GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern GEOSCoordSequence* (*GEOSPreparedNearestPoints_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern int (*GEOSPreparedDistance_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*, double*);
extern GEOSSTRtree* (*GEOSSTRtree_create_r)( GEOSContextHandle_t, size_t);
extern void (*GEOSSTRtree_insert_r)(GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*, void*);
extern void (*GEOSSTRtree_query_r)(GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*, GEOSQueryCallback, void*);
extern const GEOSGeometry* (*GEOSSTRtree_nearest_r)(GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*);
extern const void* (*GEOSSTRtree_nearest_generic_r)(GEOSContextHandle_t, GEOSSTRtree*, const void*, const GEOSGeometry*, GEOSDistanceCallback, void*);
extern void (*GEOSSTRtree_iterate_r)(GEOSContextHandle_t, GEOSSTRtree*, GEOSQueryCallback, void*);
extern char (*GEOSSTRtree_remove_r)(GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*, void*);
extern void (*GEOSSTRtree_destroy_r)(GEOSContextHandle_t, GEOSSTRtree*);
extern char (*GEOSisEmpty_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisSimple_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisRing_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSHasZ_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisClosed_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSRelatePattern_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, const char*);
extern char* (*GEOSRelate_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSRelatePatternMatch_r)(GEOSContextHandle_t, const char*, const char*);
extern char* (*GEOSRelateBoundaryNodeRule_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, int);
extern char (*GEOSisValid_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char* (*GEOSisValidReason_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisValidDetail_r)(GEOSContextHandle_t, const GEOSGeometry*, int, char**, GEOSGeometry**);
extern GEOSGeometry* (*GEOSMakeValid_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern char* (*GEOSGeomType_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeomTypeId_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGetSRID_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSSetSRID_r)(GEOSContextHandle_t, GEOSGeometry*, int);
extern void* (*GEOSGeom_getUserData_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSGeom_setUserData_r)(GEOSContextHandle_t, GEOSGeometry*, void*);
extern int (*GEOSGetNumGeometries_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern const GEOSGeometry* (*GEOSGetGeometryN_r)( GEOSContextHandle_t, const GEOSGeometry*, int);
extern int (*GEOSNormalize_r)(GEOSContextHandle_t, GEOSGeometry*);
extern GEOSGeometry* (*GEOSGeom_setPrecision_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int);
extern double (*GEOSGeom_getPrecision_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGetNumInteriorRings_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeomGetNumPoints_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeomGetX_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeomGetY_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeomGetZ_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern const GEOSGeometry* (*GEOSGetInteriorRingN_r)( GEOSContextHandle_t, const GEOSGeometry*, int);
extern const GEOSGeometry* (*GEOSGetExteriorRing_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGetNumCoordinates_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern const GEOSCoordSequence* (*GEOSGeom_getCoordSeq_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeom_getDimensions_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeom_getCoordinateDimension_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeom_getXMin_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeom_getYMin_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeom_getXMax_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeom_getYMax_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern GEOSGeometry* (*GEOSGeomGetPointN_r)(GEOSContextHandle_t, const GEOSGeometry*, int);
extern GEOSGeometry* (*GEOSGeomGetStartPoint_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSGeomGetEndPoint_r)(GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSArea_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSLength_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSDistance_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern int (*GEOSDistanceIndexed_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern int (*GEOSHausdorffDistance_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern int (*GEOSHausdorffDistanceDensify_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double, double*);
extern int (*GEOSFrechetDistance_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern int (*GEOSFrechetDistanceDensify_r)(GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double, double*);
extern int (*GEOSGeomGetLength_r)(GEOSContextHandle_t, const GEOSGeometry*, double*);
extern GEOSCoordSequence* (*GEOSNearestPoints_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern int (*GEOSOrientationIndex_r)(GEOSContextHandle_t, double, double, double, double, double, double);
extern GEOSWKTReader* (*GEOSWKTReader_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKTReader_destroy_r)(GEOSContextHandle_t, GEOSWKTReader*);
extern GEOSGeometry* (*GEOSWKTReader_read_r)(GEOSContextHandle_t, GEOSWKTReader*, const char*);
extern GEOSWKTWriter* (*GEOSWKTWriter_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKTWriter_destroy_r)(GEOSContextHandle_t, GEOSWKTWriter*);
extern char* (*GEOSWKTWriter_write_r)(GEOSContextHandle_t, GEOSWKTWriter*, const GEOSGeometry*);
extern void (*GEOSWKTWriter_setTrim_r)(GEOSContextHandle_t, GEOSWKTWriter*, char);
extern void (*GEOSWKTWriter_setRoundingPrecision_r)(GEOSContextHandle_t, GEOSWKTWriter*, int);
extern void (*GEOSWKTWriter_setOutputDimension_r)(GEOSContextHandle_t, GEOSWKTWriter*, int);
extern int (*GEOSWKTWriter_getOutputDimension_r)(GEOSContextHandle_t, GEOSWKTWriter*);
extern void (*GEOSWKTWriter_setOld3D_r)(GEOSContextHandle_t, GEOSWKTWriter*, int);
extern GEOSWKBReader* (*GEOSWKBReader_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKBReader_destroy_r)(GEOSContextHandle_t, GEOSWKBReader*);
extern GEOSGeometry* (*GEOSWKBReader_read_r)(GEOSContextHandle_t, GEOSWKBReader*, const unsigned char*, size_t);
extern GEOSGeometry* (*GEOSWKBReader_readHEX_r)( GEOSContextHandle_t, GEOSWKBReader*, const unsigned char*, size_t);
extern GEOSWKBWriter* (*GEOSWKBWriter_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKBWriter_destroy_r)(GEOSContextHandle_t, GEOSWKBWriter*);
extern unsigned char* (*GEOSWKBWriter_write_r)( GEOSContextHandle_t, GEOSWKBWriter*, const GEOSGeometry*, size_t*);
extern unsigned char* (*GEOSWKBWriter_writeHEX_r)( GEOSContextHandle_t, GEOSWKBWriter*, const GEOSGeometry*, size_t*);
extern int (*GEOSWKBWriter_getOutputDimension_r)( GEOSContextHandle_t, const GEOSWKBWriter*);
extern void (*GEOSWKBWriter_setOutputDimension_r)( GEOSContextHandle_t, GEOSWKBWriter*, int);
extern int (*GEOSWKBWriter_getByteOrder_r)(GEOSContextHandle_t, const GEOSWKBWriter*);
extern void (*GEOSWKBWriter_setByteOrder_r)(GEOSContextHandle_t, GEOSWKBWriter*, int);
extern char (*GEOSWKBWriter_getIncludeSRID_r)(GEOSContextHandle_t, const GEOSWKBWriter*);
extern void (*GEOSWKBWriter_setIncludeSRID_r)(GEOSContextHandle_t, GEOSWKBWriter*, const char);
extern void (*GEOSFree_r)(GEOSContextHandle_t, void*);

void libgeos_init_api();

#endif
