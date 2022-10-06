
// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#ifndef LIBGEOS_H
#define LIBGEOS_H

#ifndef __cplusplus
# include <stddef.h> /* for size_t definition */
#else
# include <cstddef>
using std::size_t;
#endif

/* ====================================================================== */
/* Version */
/* ====================================================================== */

/** \cond */

#ifndef GEOS_VERSION_MAJOR
#define GEOS_VERSION_MAJOR 3
#endif
#ifndef GEOS_VERSION_MINOR
#define GEOS_VERSION_MINOR 11
#endif
#ifndef GEOS_VERSION_PATCH
#define GEOS_VERSION_PATCH 0
#endif
#ifndef GEOS_VERSION
#define GEOS_VERSION "3.11.0"
#endif
#ifndef GEOS_JTS_PORT
#define GEOS_JTS_PORT "1.18.0"
#endif

#define GEOS_CAPI_VERSION_MAJOR 1
#define GEOS_CAPI_VERSION_MINOR 17
#define GEOS_CAPI_VERSION_PATCH 0
#define GEOS_CAPI_VERSION "3.11.0-CAPI-1.17.0"

#define GEOS_CAPI_FIRST_INTERFACE GEOS_CAPI_VERSION_MAJOR

// how integer versions are calculated
#define LIBGEOS_VERSION_INT(major, minor, patch) (patch + minor * 100 + major * 10000)

// the runtime version of libgeos
extern int (*libgeos_version_int)(void);

// the compile-time version of libgeos
#define LIBGEOS_VERSION_COMPILE_INT LIBGEOS_VERSION_INT(GEOS_VERSION_MAJOR, GEOS_VERSION_MINOR, GEOS_VERSION_PATCH)

typedef struct GEOSContextHandle_HS *GEOSContextHandle_t;
typedef void (*GEOSMessageHandler)(const char *fmt, ...);
typedef void (*GEOSMessageHandler_r)(const char *message, void *userdata);
typedef struct GEOSGeom_t GEOSGeometry;
typedef struct GEOSPrepGeom_t GEOSPreparedGeometry;
typedef struct GEOSCoordSeq_t GEOSCoordSequence;
typedef struct GEOSSTRtree_t GEOSSTRtree;
typedef struct GEOSBufParams_t GEOSBufferParams;
typedef struct GEOSMakeValidParams_t GEOSMakeValidParams;
typedef GEOSGeometry* GEOSGeom;
typedef GEOSCoordSequence* GEOSCoordSeq;
typedef void (*GEOSQueryCallback)(void *item, void *userdata);
typedef int (*GEOSDistanceCallback)(
    const void* item1,
    const void* item2,
    double* distance,
    void* userdata);
typedef int (*GEOSTransformXYCallback)(
    double* x,
    double* y,
    void* userdata);
typedef void (GEOSInterruptCallback)(void);
typedef struct GEOSWKTReader_t GEOSWKTReader;
typedef struct GEOSWKTWriter_t GEOSWKTWriter;
typedef struct GEOSWKBReader_t GEOSWKBReader;
typedef struct GEOSWKBWriter_t GEOSWKBWriter;
typedef struct GEOSGeoJSONReader_t GEOSGeoJSONReader;
typedef struct GEOSGeoJSONWriter_t GEOSGeoJSONWriter;
typedef void (*GEOSMessageHandler)(const char *fmt, ...);

enum GEOSGeomTypes {
    /** Point */
    GEOS_POINT,
    /** Linestring */
    GEOS_LINESTRING,
    /** Linear ring, used within polygons */
    GEOS_LINEARRING,
    /** Polygon */
    GEOS_POLYGON,
    /** Multipoint, a homogeneous collection of points */
    GEOS_MULTIPOINT,
    /** Multilinestring, a homogeneous collection of linestrings */
    GEOS_MULTILINESTRING,
    /** Multipolygon, a homogeneous collection of polygons */
    GEOS_MULTIPOLYGON,
    /** Geometry collection, a heterogeneous collection of geometry */
    GEOS_GEOMETRYCOLLECTION
};
enum GEOSWKBByteOrders {
    /** Big Endian */
    GEOS_WKB_XDR = 0,
    /** Little Endian */
    GEOS_WKB_NDR = 1
};
enum GEOSWKBFlavors {
    /** Extended */
    GEOS_WKB_EXTENDED = 1,
    /** ISO */
    GEOS_WKB_ISO = 2
};
enum GEOSBufCapStyles {

    /** End is rounded, with end point of original line in the centre of the round cap. */
	GEOSBUF_CAP_ROUND = 1,

    /** End is flat, with end point of original line at the end of the buffer */
	GEOSBUF_CAP_FLAT = 2,

    /** End is flat, with end point of original line in the middle of a square enclosing that point */
	GEOSBUF_CAP_SQUARE = 3
};
enum GEOSBufJoinStyles {
    /**
    * Join is rounded, essentially each line is terminated
    * in a round cap. Form round corner.
    */
	GEOSBUF_JOIN_ROUND = 1,
    /**
    * Join is flat, with line between buffer edges,
    * through the join point. Forms flat corner.
    */
	GEOSBUF_JOIN_MITRE = 2,
    /**
    * Join is the point at which the two buffer edges intersect.
    * Forms sharp corner.
    */
	GEOSBUF_JOIN_BEVEL = 3
};
enum GEOSRelateBoundaryNodeRules {
    /** See geos::algorithm::BoundaryNodeRule::getBoundaryRuleMod2() */
    GEOSRELATE_BNR_MOD2 = 1,
    /** Same as \ref GEOSRELATE_BNR_MOD2 */
    GEOSRELATE_BNR_OGC = 1,
    /** See geos::algorithm::BoundaryNodeRule::getBoundaryEndPoint() */
	GEOSRELATE_BNR_ENDPOINT = 2,
    /** See geos::algorithm::BoundaryNodeRule::getBoundaryMultivalentEndPoint() */
	GEOSRELATE_BNR_MULTIVALENT_ENDPOINT = 3,
    /** See geos::algorithm::BoundaryNodeRule::getBoundaryMonovalentEndPoint() */
	GEOSRELATE_BNR_MONOVALENT_ENDPOINT = 4
};
enum GEOSValidFlags
{
    /** Allow self-touching rings to form a hole in a polygon. */
	GEOSVALID_ALLOW_SELFTOUCHING_RING_FORMING_HOLE = 1
};
enum GEOSMakeValidMethods {
    /** Original method, combines all rings into
        a set of noded lines and then extracts valid
        polygons from that linework. */
    GEOS_MAKE_VALID_LINEWORK = 0,
    /** Structured method, first makes all rings valid
        then merges shells and subtracts holes from
        shells to generate valid result. Assumes that
        holes and shells are correctly categorized. */
    GEOS_MAKE_VALID_STRUCTURE = 1
};
enum GEOSPrecisionRules {
    /** The output is always valid. Collapsed geometry elements (including both polygons and lines) are removed. */
    GEOS_PREC_VALID_OUTPUT = 0,
    /** Precision reduction is performed pointwise. Output geometry may be invalid due to collapse or self-intersection. (This might be better called "GEOS_PREC_POINTWISE" - the current name is historical.) */
    GEOS_PREC_NO_TOPO = 1,
    /** Like the default mode, except that collapsed linear geometry elements are preserved. Collapsed polygonal input elements are removed. */
    GEOS_PREC_KEEP_COLLAPSED = 2
};
enum GEOSPolygonHullParameterModes {
    /** See geos::simplify::PolygonHullSimplifier::hull() */
    GEOSHULL_PARAM_VERTEX_RATIO = 1,
    /** See geos::simplify::PolygonHullSimplifier::hullByAreaDelta() */
    GEOSHULL_PARAM_AREA_RATIO = 2
};

extern GEOSContextHandle_t (*GEOS_init_r)(void);
extern void (*GEOS_finish_r)(GEOSContextHandle_t);
extern GEOSMessageHandler (*GEOSContext_setNoticeHandler_r)( GEOSContextHandle_t, GEOSMessageHandler);
extern GEOSMessageHandler (*GEOSContext_setErrorHandler_r)( GEOSContextHandle_t, GEOSMessageHandler);
extern GEOSMessageHandler_r (*GEOSContext_setNoticeMessageHandler_r)( GEOSContextHandle_t, GEOSMessageHandler_r, void*);
extern GEOSMessageHandler_r (*GEOSContext_setErrorMessageHandler_r)( GEOSContextHandle_t, GEOSMessageHandler_r, void*);
extern GEOSCoordSequence* (*GEOSCoordSeq_create_r)( GEOSContextHandle_t, unsigned int, unsigned int);
extern GEOSCoordSequence* (*GEOSCoordSeq_copyFromBuffer_r)( GEOSContextHandle_t, const double*, unsigned int, int, int);
extern GEOSCoordSequence* (*GEOSCoordSeq_copyFromArrays_r)( GEOSContextHandle_t, const double*, const double*, const double*, const double*, unsigned int);
extern int (*GEOSCoordSeq_copyToBuffer_r)( GEOSContextHandle_t, const GEOSCoordSequence*, double*, int, int);
extern int (*GEOSCoordSeq_copyToArrays_r)( GEOSContextHandle_t, const GEOSCoordSequence*, double*, double*, double*, double*);
extern GEOSCoordSequence* (*GEOSCoordSeq_clone_r)( GEOSContextHandle_t, const GEOSCoordSequence*);
extern void (*GEOSCoordSeq_destroy_r)( GEOSContextHandle_t, GEOSCoordSequence*);
extern int (*GEOSCoordSeq_setX_r)( GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double);
extern int (*GEOSCoordSeq_setY_r)( GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double);
extern int (*GEOSCoordSeq_setZ_r)( GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double);
extern int (*GEOSCoordSeq_setXY_r)( GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double, double);
extern int (*GEOSCoordSeq_setXYZ_r)( GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, double, double, double);
extern int (*GEOSCoordSeq_setOrdinate_r)( GEOSContextHandle_t, GEOSCoordSequence*, unsigned int, unsigned int, double);
extern int (*GEOSCoordSeq_getX_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*);
extern int (*GEOSCoordSeq_getY_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*);
extern int (*GEOSCoordSeq_getZ_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*);
extern int (*GEOSCoordSeq_getXY_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*, double*);
extern int (*GEOSCoordSeq_getXYZ_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, double*, double*, double*);
extern int (*GEOSCoordSeq_getOrdinate_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int, unsigned int, double*);
extern int (*GEOSCoordSeq_getSize_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int*);
extern int (*GEOSCoordSeq_getDimensions_r)( GEOSContextHandle_t, const GEOSCoordSequence*, unsigned int*);
extern int (*GEOSCoordSeq_isCCW_r)( GEOSContextHandle_t, const GEOSCoordSequence*, char*);
extern double (*GEOSProject_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSInterpolate_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern double (*GEOSProjectNormalized_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSInterpolateNormalized_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSBuffer_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int);
extern GEOSBufferParams* (*GEOSBufferParams_create_r)( GEOSContextHandle_t);
extern void (*GEOSBufferParams_destroy_r)( GEOSContextHandle_t, GEOSBufferParams*);
extern int (*GEOSBufferParams_setEndCapStyle_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern int (*GEOSBufferParams_setJoinStyle_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern int (*GEOSBufferParams_setMitreLimit_r)( GEOSContextHandle_t, GEOSBufferParams*, double);
extern int (*GEOSBufferParams_setQuadrantSegments_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern int (*GEOSBufferParams_setSingleSided_r)( GEOSContextHandle_t, GEOSBufferParams*, int);
extern GEOSGeometry* (*GEOSBufferWithParams_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSBufferParams*, double);
extern GEOSGeometry* (*GEOSBufferWithStyle_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int, int, int, double);
extern GEOSGeometry* (*GEOSDensify_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSOffsetCurve_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int, int, double);
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
extern GEOSGeometry* (*GEOSGeom_createRectangle_r)( GEOSContextHandle_t, double, double, double, double);
extern GEOSGeometry* (*GEOSGeom_clone_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSGeom_destroy_r)( GEOSContextHandle_t, GEOSGeometry*);
extern GEOSGeometry* (*GEOSEnvelope_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSIntersection_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSIntersectionPrec_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSConvexHull_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSConcaveHull_r)( GEOSContextHandle_t, const GEOSGeometry*, double, unsigned int);
extern GEOSGeometry* (*GEOSPolygonHullSimplify_r)( GEOSContextHandle_t, const GEOSGeometry*, unsigned int, double);
extern GEOSGeometry* (*GEOSPolygonHullSimplifyMode_r)( GEOSContextHandle_t, const GEOSGeometry*, unsigned int, unsigned int, double);
extern GEOSGeometry* (*GEOSConcaveHullOfPolygons_r)( GEOSContextHandle_t, const GEOSGeometry*, double, unsigned int, unsigned int);
extern GEOSGeometry* (*GEOSMinimumRotatedRectangle_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMaximumInscribedCircle_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSLargestEmptyCircle_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSMinimumWidth_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMinimumClearanceLine_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSMinimumClearance_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern GEOSGeometry* (*GEOSDifference_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSDifferencePrec_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSSymDifference_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSymDifferencePrec_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSBoundary_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSUnion_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSUnionPrec_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSUnaryUnion_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSUnaryUnionPrec_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSCoverageUnion_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSPointOnSurface_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSGetCentroid_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMinimumBoundingCircle_r)( GEOSContextHandle_t, const GEOSGeometry*, double*, GEOSGeometry**);
extern GEOSGeometry* (*GEOSNode_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSClipByRect_r)( GEOSContextHandle_t, const GEOSGeometry*, double, double, double, double);
extern GEOSGeometry* (*GEOSPolygonize_r)( GEOSContextHandle_t, const GEOSGeometry *const geoms[], unsigned int);
extern GEOSGeometry* (*GEOSPolygonize_valid_r)( GEOSContextHandle_t, const GEOSGeometry *const geoms[], unsigned int);
extern GEOSGeometry* (*GEOSPolygonizer_getCutEdges_r)( GEOSContextHandle_t, const GEOSGeometry * const geoms[], unsigned int);
extern GEOSGeometry* (*GEOSPolygonize_full_r)( GEOSContextHandle_t, const GEOSGeometry*, GEOSGeometry**, GEOSGeometry**, GEOSGeometry**);
extern GEOSGeometry* (*GEOSBuildArea_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSLineMerge_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSLineMergeDirected_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSReverse_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSimplify_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSTopologyPreserveSimplify_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSGeom_extractUniquePoints_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSharedPaths_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSSnap_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern GEOSGeometry* (*GEOSDelaunayTriangulation_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int);
extern GEOSGeometry* (*GEOSConstrainedDelaunayTriangulation_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSVoronoiDiagram_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double, int);
extern int (*GEOSSegmentIntersection_r)( GEOSContextHandle_t, double, double, double, double, double, double, double, double, double*, double*);
extern char (*GEOSDisjoint_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSTouches_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSIntersects_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSCrosses_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSWithin_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSContains_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSOverlaps_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSEquals_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSEqualsExact_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern char (*GEOSCovers_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSCoveredBy_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern const GEOSPreparedGeometry* (*GEOSPrepare_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSPreparedGeom_destroy_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*);
extern char (*GEOSPreparedContains_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedContainsProperly_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedCoveredBy_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedCovers_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedCrosses_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedDisjoint_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedIntersects_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedOverlaps_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedTouches_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern char (*GEOSPreparedWithin_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern GEOSCoordSequence* (*GEOSPreparedNearestPoints_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*);
extern int (*GEOSPreparedDistance_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*, double*);
extern char (*GEOSPreparedDistanceWithin_r)( GEOSContextHandle_t, const GEOSPreparedGeometry*, const GEOSGeometry*, double);
extern GEOSSTRtree* (*GEOSSTRtree_create_r)( GEOSContextHandle_t, size_t);
extern void (*GEOSSTRtree_insert_r)( GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*, void*);
extern void (*GEOSSTRtree_query_r)( GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*, GEOSQueryCallback, void*);
extern const GEOSGeometry* (*GEOSSTRtree_nearest_r)( GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*);
extern const void* (*GEOSSTRtree_nearest_generic_r)( GEOSContextHandle_t, GEOSSTRtree*, const void*, const GEOSGeometry*, GEOSDistanceCallback, void*);
extern void (*GEOSSTRtree_iterate_r)( GEOSContextHandle_t, GEOSSTRtree*, GEOSQueryCallback, void*);
extern char (*GEOSSTRtree_remove_r)( GEOSContextHandle_t, GEOSSTRtree*, const GEOSGeometry*, void*);
extern void (*GEOSSTRtree_destroy_r)( GEOSContextHandle_t, GEOSSTRtree*);
extern char (*GEOSisEmpty_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisSimple_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisRing_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSHasZ_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisClosed_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSRelatePattern_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, const char*);
extern char* (*GEOSRelate_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern char (*GEOSRelatePatternMatch_r)( GEOSContextHandle_t, const char*, const char*);
extern char* (*GEOSRelateBoundaryNodeRule_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, int);
extern char (*GEOSisValid_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern char* (*GEOSisValidReason_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern char (*GEOSisValidDetail_r)( GEOSContextHandle_t, const GEOSGeometry*, int, char**, GEOSGeometry**);
extern GEOSMakeValidParams* (*GEOSMakeValidParams_create_r)( GEOSContextHandle_t);
extern void (*GEOSMakeValidParams_destroy_r)( GEOSContextHandle_t, GEOSMakeValidParams*);
extern int (*GEOSMakeValidParams_setKeepCollapsed_r)( GEOSContextHandle_t, GEOSMakeValidParams*, int);
extern int (*GEOSMakeValidParams_setMethod_r)( GEOSContextHandle_t, GEOSMakeValidParams*, enum GEOSMakeValidMethods);
extern GEOSGeometry* (*GEOSMakeValid_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSMakeValidWithParams_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSMakeValidParams*);
extern GEOSGeometry* (*GEOSRemoveRepeatedPoints_r)( GEOSContextHandle_t, const GEOSGeometry*, double);
extern char* (*GEOSGeomType_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeomTypeId_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGetSRID_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSSetSRID_r)( GEOSContextHandle_t, GEOSGeometry*, int);
extern void* (*GEOSGeom_getUserData_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern void (*GEOSGeom_setUserData_r)( GEOSContextHandle_t, GEOSGeometry*, void*);
extern int (*GEOSGetNumGeometries_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern const GEOSGeometry* (*GEOSGetGeometryN_r)( GEOSContextHandle_t, const GEOSGeometry*, int);
extern int (*GEOSNormalize_r)( GEOSContextHandle_t, GEOSGeometry*);
extern GEOSGeometry* (*GEOSGeom_setPrecision_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int);
extern double (*GEOSGeom_getPrecision_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGetNumInteriorRings_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeomGetNumPoints_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeomGetX_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeomGetY_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeomGetZ_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern const GEOSGeometry* (*GEOSGetInteriorRingN_r)( GEOSContextHandle_t, const GEOSGeometry*, int);
extern const GEOSGeometry* (*GEOSGetExteriorRing_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGetNumCoordinates_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern const GEOSCoordSequence* (*GEOSGeom_getCoordSeq_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeom_getDimensions_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeom_getCoordinateDimension_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSGeom_getXMin_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeom_getYMin_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeom_getXMax_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeom_getYMax_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSGeom_getExtent_r)( GEOSContextHandle_t, const GEOSGeometry*, double*, double*, double*, double*);
extern GEOSGeometry* (*GEOSGeomGetPointN_r)( GEOSContextHandle_t, const GEOSGeometry*, int);
extern GEOSGeometry* (*GEOSGeomGetStartPoint_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSGeomGetEndPoint_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOSArea_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSLength_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern int (*GEOSDistance_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern char (*GEOSDistanceWithin_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double);
extern int (*GEOSDistanceIndexed_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern int (*GEOSHausdorffDistance_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern int (*GEOSHausdorffDistanceDensify_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double, double*);
extern int (*GEOSFrechetDistance_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double*);
extern int (*GEOSFrechetDistanceDensify_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, double, double*);
extern int (*GEOSHilbertCode_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*, unsigned int, unsigned int *code );
extern int (*GEOSGeomGetLength_r)( GEOSContextHandle_t, const GEOSGeometry*, double*);
extern GEOSCoordSequence* (*GEOSNearestPoints_r)( GEOSContextHandle_t, const GEOSGeometry*, const GEOSGeometry*);
extern GEOSGeometry* (*GEOSGeom_transformXY_r)( GEOSContextHandle_t, const GEOSGeometry*, GEOSTransformXYCallback, void*);
extern int (*GEOSOrientationIndex_r)( GEOSContextHandle_t, double, double, double, double, double, double);
extern GEOSWKTReader* (*GEOSWKTReader_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKTReader_destroy_r)(GEOSContextHandle_t, GEOSWKTReader*);
extern GEOSGeometry* (*GEOSWKTReader_read_r)( GEOSContextHandle_t, GEOSWKTReader*, const char*);
extern void (*GEOSWKTReader_setFixStructure_r)( GEOSContextHandle_t, GEOSWKTReader*, char);
extern GEOSWKTWriter* (*GEOSWKTWriter_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKTWriter_destroy_r)( GEOSContextHandle_t, GEOSWKTWriter*);
extern char* (*GEOSWKTWriter_write_r)( GEOSContextHandle_t, GEOSWKTWriter*, const GEOSGeometry*);
extern void (*GEOSWKTWriter_setTrim_r)( GEOSContextHandle_t, GEOSWKTWriter*, char);
extern void (*GEOSWKTWriter_setRoundingPrecision_r)( GEOSContextHandle_t, GEOSWKTWriter*, int);
extern void (*GEOSWKTWriter_setOutputDimension_r)( GEOSContextHandle_t, GEOSWKTWriter*, int);
extern int (*GEOSWKTWriter_getOutputDimension_r)( GEOSContextHandle_t, GEOSWKTWriter*);
extern void (*GEOSWKTWriter_setOld3D_r)( GEOSContextHandle_t, GEOSWKTWriter*, int);
extern GEOSWKBReader* (*GEOSWKBReader_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKBReader_destroy_r)( GEOSContextHandle_t, GEOSWKBReader*);
extern void (*GEOSWKBReader_setFixStructure_r)( GEOSContextHandle_t, GEOSWKBReader*, char);
extern GEOSGeometry* (*GEOSWKBReader_read_r)( GEOSContextHandle_t, GEOSWKBReader*, const unsigned char*, size_t);
extern GEOSGeometry* (*GEOSWKBReader_readHEX_r)( GEOSContextHandle_t, GEOSWKBReader*, const unsigned char*, size_t);
extern GEOSWKBWriter* (*GEOSWKBWriter_create_r)( GEOSContextHandle_t);
extern void (*GEOSWKBWriter_destroy_r)( GEOSContextHandle_t, GEOSWKBWriter*);
extern unsigned char* (*GEOSWKBWriter_write_r)( GEOSContextHandle_t, GEOSWKBWriter*, const GEOSGeometry*, size_t*);
extern unsigned char* (*GEOSWKBWriter_writeHEX_r)( GEOSContextHandle_t, GEOSWKBWriter*, const GEOSGeometry*, size_t*);
extern int (*GEOSWKBWriter_getOutputDimension_r)( GEOSContextHandle_t, const GEOSWKBWriter*);
extern void (*GEOSWKBWriter_setOutputDimension_r)( GEOSContextHandle_t, GEOSWKBWriter*, int);
extern int (*GEOSWKBWriter_getByteOrder_r)( GEOSContextHandle_t, const GEOSWKBWriter*);
extern void (*GEOSWKBWriter_setByteOrder_r)( GEOSContextHandle_t, GEOSWKBWriter*, int);
extern int (*GEOSWKBWriter_getFlavor_r)( GEOSContextHandle_t, const GEOSWKBWriter*);
extern void (*GEOSWKBWriter_setFlavor_r)( GEOSContextHandle_t, GEOSWKBWriter*, int);
extern char (*GEOSWKBWriter_getIncludeSRID_r)( GEOSContextHandle_t, const GEOSWKBWriter*);
extern void (*GEOSWKBWriter_setIncludeSRID_r)( GEOSContextHandle_t, GEOSWKBWriter*, const char);
extern GEOSGeoJSONReader* (*GEOSGeoJSONReader_create_r)( GEOSContextHandle_t);
extern void (*GEOSGeoJSONReader_destroy_r)(GEOSContextHandle_t, GEOSGeoJSONReader*);
extern GEOSGeometry* (*GEOSGeoJSONReader_readGeometry_r)( GEOSContextHandle_t, GEOSGeoJSONReader*, const char*);
extern GEOSGeoJSONWriter* (*GEOSGeoJSONWriter_create_r)( GEOSContextHandle_t);
extern void (*GEOSGeoJSONWriter_destroy_r)(GEOSContextHandle_t, GEOSGeoJSONWriter*);
extern char* (*GEOSGeoJSONWriter_writeGeometry_r)( GEOSContextHandle_t, GEOSGeoJSONWriter*, const GEOSGeometry*, int);
extern void (*GEOSFree_r)( GEOSContextHandle_t, void*);
extern const char* (*GEOSversion)(void);
extern GEOSGeometry* (*GEOSSingleSidedBuffer_r)( GEOSContextHandle_t, const GEOSGeometry*, double, int, int, double, int);
extern GEOSContextHandle_t (*initGEOS_r)( GEOSMessageHandler, GEOSMessageHandler);
extern void (*finishGEOS_r)(GEOSContextHandle_t);
extern GEOSGeometry* (*GEOSGeomFromWKT_r)( GEOSContextHandle_t, const char*);
extern char* (*GEOSGeomToWKT_r)( GEOSContextHandle_t, const GEOSGeometry*);
extern int (*GEOS_getWKBOutputDims_r)( GEOSContextHandle_t);
extern int (*GEOS_setWKBOutputDims_r)( GEOSContextHandle_t, int);
extern int (*GEOS_getWKBByteOrder_r)( GEOSContextHandle_t);
extern int (*GEOS_setWKBByteOrder_r)( GEOSContextHandle_t, int);
extern GEOSGeometry* (*GEOSGeomFromWKB_buf_r)( GEOSContextHandle_t, const unsigned char*, size_t);
extern unsigned char* (*GEOSGeomToWKB_buf_r)( GEOSContextHandle_t, const GEOSGeometry*, size_t*);
extern GEOSGeometry* (*GEOSGeomFromHEX_buf_r)( GEOSContextHandle_t, const unsigned char*, size_t);
extern unsigned char* (*GEOSGeomToHEX_buf_r)( GEOSContextHandle_t, const GEOSGeometry*, size_t*);
extern GEOSGeometry* (*GEOSUnionCascaded_r)( GEOSContextHandle_t, const GEOSGeometry*);

void libgeos_init_api(void);

#endif
