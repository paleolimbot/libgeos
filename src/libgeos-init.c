
// generated automatically by data-raw/update-libgeos-api.R - do not edit by hand!
#include <Rinternals.h>
#include <R_ext/Rdynload.h>

#ifndef GEOS_VERSION_MAJOR
#define GEOS_VERSION_MAJOR 3
#endif
#ifndef GEOS_VERSION_MINOR
#define GEOS_VERSION_MINOR 8
#endif
#ifndef GEOS_VERSION_PATCH
#define GEOS_VERSION_PATCH 1
#endif
#ifndef GEOS_VERSION
#define GEOS_VERSION "3.8.1"
#endif
#ifndef GEOS_JTS_PORT
#define GEOS_JTS_PORT "1.13.0"
#endif

#define GEOS_CAPI_VERSION_MAJOR 1
#define GEOS_CAPI_VERSION_MINOR 13
#define GEOS_CAPI_VERSION_PATCH 3
#define GEOS_CAPI_VERSION "3.8.1-CAPI-1.13.3"

#define GEOS_CAPI_FIRST_INTERFACE GEOS_CAPI_VERSION_MAJOR
#define GEOS_CAPI_LAST_INTERFACE (GEOS_CAPI_VERSION_MAJOR+GEOS_CAPI_VERSION_MINOR)

// we need a utility function to get the runtime version in a form that is
// queryable from the inst/include/libgeos.c, because future GEOS versions
// will add to the C API. The ability to do a runtime check around R_GetCCallable()
// lets newer packages link to multiple versions of libgeos.
#define LIBGEOS_VERSION_INT(major, minor, patch) (patch + minor * 100 + major * 10000)

int libgeos_version_int() {
  return LIBGEOS_VERSION_INT(GEOS_VERSION_MAJOR, GEOS_VERSION_MINOR, GEOS_VERSION_PATCH);
}

// whereas libgeos.h contains declarations for function *pointers*
// these are the declarations for the functions in geos_c.h
// we cannnot include geos_c.h because the magic defines GEOS
// uses create problems for the LTO build of R-devel
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

#define GEOS_DLL
GEOSContextHandle_t GEOS_DLL initGEOS_r( GEOSMessageHandler notice_function, GEOSMessageHandler error_function);
void GEOS_DLL finishGEOS_r(GEOSContextHandle_t handle);
GEOSContextHandle_t GEOS_DLL GEOS_init_r();
void GEOS_DLL GEOS_finish_r(GEOSContextHandle_t handle);
GEOSMessageHandler GEOS_DLL GEOSContext_setNoticeHandler_r(GEOSContextHandle_t extHandle, GEOSMessageHandler nf);
GEOSMessageHandler GEOS_DLL GEOSContext_setErrorHandler_r(GEOSContextHandle_t extHandle, GEOSMessageHandler ef);
GEOSMessageHandler_r GEOS_DLL GEOSContext_setNoticeMessageHandler_r(GEOSContextHandle_t extHandle, GEOSMessageHandler_r nf, void *userData);
GEOSMessageHandler_r GEOS_DLL GEOSContext_setErrorMessageHandler_r(GEOSContextHandle_t extHandle, GEOSMessageHandler_r ef, void *userData);
const char* GEOS_DLL GEOSversion();
GEOSGeometry* GEOS_DLL GEOSGeomFromWKT_r(GEOSContextHandle_t handle, const char *wkt);
char* GEOS_DLL GEOSGeomToWKT_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOS_getWKBOutputDims_r(GEOSContextHandle_t handle);
int GEOS_DLL GEOS_setWKBOutputDims_r(GEOSContextHandle_t handle, int newDims);
int GEOS_DLL GEOS_getWKBByteOrder_r(GEOSContextHandle_t handle);
int GEOS_DLL GEOS_setWKBByteOrder_r(GEOSContextHandle_t handle, int byteOrder);
GEOSGeometry* GEOS_DLL GEOSGeomFromWKB_buf_r(GEOSContextHandle_t handle, const unsigned char *wkb, size_t size);
unsigned char* GEOS_DLL GEOSGeomToWKB_buf_r(GEOSContextHandle_t handle, const GEOSGeometry* g, size_t *size);
GEOSGeometry* GEOS_DLL GEOSGeomFromHEX_buf_r(GEOSContextHandle_t handle, const unsigned char *hex, size_t size);
unsigned char* GEOS_DLL GEOSGeomToHEX_buf_r(GEOSContextHandle_t handle, const GEOSGeometry* g, size_t *size);
GEOSCoordSequence* GEOS_DLL GEOSCoordSeq_create_r( GEOSContextHandle_t handle, unsigned int size, unsigned int dims);
GEOSCoordSequence* GEOS_DLL GEOSCoordSeq_clone_r( GEOSContextHandle_t handle, const GEOSCoordSequence* s);
void GEOS_DLL GEOSCoordSeq_destroy_r(GEOSContextHandle_t handle, GEOSCoordSequence* s);
int GEOS_DLL GEOSCoordSeq_setX_r(GEOSContextHandle_t handle, GEOSCoordSequence* s, unsigned int idx, double val);
int GEOS_DLL GEOSCoordSeq_setY_r(GEOSContextHandle_t handle, GEOSCoordSequence* s, unsigned int idx, double val);
int GEOS_DLL GEOSCoordSeq_setZ_r(GEOSContextHandle_t handle, GEOSCoordSequence* s, unsigned int idx, double val);
int GEOS_DLL GEOSCoordSeq_setXY_r(GEOSContextHandle_t handle, GEOSCoordSequence* s, unsigned int idx, double x, double y);
int GEOS_DLL GEOSCoordSeq_setXYZ_r(GEOSContextHandle_t handle, GEOSCoordSequence* s, unsigned int idx, double x, double y, double z);
int GEOS_DLL GEOSCoordSeq_setOrdinate_r(GEOSContextHandle_t handle, GEOSCoordSequence* s, unsigned int idx, unsigned int dim, double val);
int GEOS_DLL GEOSCoordSeq_getX_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int idx, double *val);
int GEOS_DLL GEOSCoordSeq_getY_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int idx, double *val);
int GEOS_DLL GEOSCoordSeq_getZ_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int idx, double *val);
int GEOS_DLL GEOSCoordSeq_getXY_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int idx, double *x, double *y);
int GEOS_DLL GEOSCoordSeq_getXYZ_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int idx, double *x, double *y, double *z);
int GEOS_DLL GEOSCoordSeq_getOrdinate_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int idx, unsigned int dim, double *val);
int GEOS_DLL GEOSCoordSeq_getSize_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int *size);
int GEOS_DLL GEOSCoordSeq_getDimensions_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, unsigned int *dims);
int GEOS_DLL GEOSCoordSeq_isCCW_r(GEOSContextHandle_t handle, const GEOSCoordSequence* s, char* is_ccw);
double GEOS_DLL GEOSProject_r(GEOSContextHandle_t handle, const GEOSGeometry *g, const GEOSGeometry *p);
GEOSGeometry* GEOS_DLL GEOSInterpolate_r(GEOSContextHandle_t handle, const GEOSGeometry *g, double d);
double GEOS_DLL GEOSProjectNormalized_r(GEOSContextHandle_t handle, const GEOSGeometry *g, const GEOSGeometry *p);
GEOSGeometry* GEOS_DLL GEOSInterpolateNormalized_r( GEOSContextHandle_t handle, const GEOSGeometry *g, double d);
GEOSGeometry* GEOS_DLL GEOSBuffer_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double width, int quadsegs);
GEOSBufferParams* GEOS_DLL GEOSBufferParams_create_r( GEOSContextHandle_t handle);
void GEOS_DLL GEOSBufferParams_destroy_r( GEOSContextHandle_t handle, GEOSBufferParams* parms);
int GEOS_DLL GEOSBufferParams_setEndCapStyle_r( GEOSContextHandle_t handle, GEOSBufferParams* p, int style);
int GEOS_DLL GEOSBufferParams_setJoinStyle_r( GEOSContextHandle_t handle, GEOSBufferParams* p, int joinStyle);
int GEOS_DLL GEOSBufferParams_setMitreLimit_r( GEOSContextHandle_t handle, GEOSBufferParams* p, double mitreLimit);
int GEOS_DLL GEOSBufferParams_setQuadrantSegments_r( GEOSContextHandle_t handle, GEOSBufferParams* p, int quadSegs);
int GEOS_DLL GEOSBufferParams_setSingleSided_r( GEOSContextHandle_t handle, GEOSBufferParams* p, int singleSided);
GEOSGeometry* GEOS_DLL GEOSBufferWithParams_r( GEOSContextHandle_t handle, const GEOSGeometry* g, const GEOSBufferParams* p, double width);
GEOSGeometry* GEOS_DLL GEOSBufferWithStyle_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double width, int quadsegs, int endCapStyle, int joinStyle, double mitreLimit);
GEOSGeometry* GEOS_DLL GEOSSingleSidedBuffer_r( GEOSContextHandle_t handle, const GEOSGeometry* g, double width, int quadsegs, int joinStyle, double mitreLimit, int leftSide);
GEOSGeometry* GEOS_DLL GEOSOffsetCurve_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double width, int quadsegs, int joinStyle, double mitreLimit);
GEOSGeometry* GEOS_DLL GEOSGeom_createPoint_r( GEOSContextHandle_t handle, GEOSCoordSequence* s);
GEOSGeometry* GEOS_DLL GEOSGeom_createPointFromXY_r( GEOSContextHandle_t handle, double x, double y);
GEOSGeometry* GEOS_DLL GEOSGeom_createEmptyPoint_r( GEOSContextHandle_t handle);
GEOSGeometry* GEOS_DLL GEOSGeom_createLinearRing_r( GEOSContextHandle_t handle, GEOSCoordSequence* s);
GEOSGeometry* GEOS_DLL GEOSGeom_createLineString_r( GEOSContextHandle_t handle, GEOSCoordSequence* s);
GEOSGeometry* GEOS_DLL GEOSGeom_createEmptyLineString_r( GEOSContextHandle_t handle);
GEOSGeometry* GEOS_DLL GEOSGeom_createEmptyPolygon_r( GEOSContextHandle_t handle);
GEOSGeometry* GEOS_DLL GEOSGeom_createPolygon_r( GEOSContextHandle_t handle, GEOSGeometry* shell, GEOSGeometry** holes, unsigned int nholes);
GEOSGeometry* GEOS_DLL GEOSGeom_createCollection_r( GEOSContextHandle_t handle, int type, GEOSGeometry* *geoms, unsigned int ngeoms);
GEOSGeometry* GEOS_DLL GEOSGeom_createEmptyCollection_r( GEOSContextHandle_t handle, int type);
GEOSGeometry* GEOS_DLL GEOSGeom_clone_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
void GEOS_DLL GEOSGeom_destroy_r(GEOSContextHandle_t handle, GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSEnvelope_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSIntersection_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
GEOSGeometry* GEOS_DLL GEOSConvexHull_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSMinimumRotatedRectangle_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSMinimumWidth_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSMinimumClearanceLine_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSMinimumClearance_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double* distance);
GEOSGeometry* GEOS_DLL GEOSDifference_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
GEOSGeometry* GEOS_DLL GEOSSymDifference_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
GEOSGeometry* GEOS_DLL GEOSBoundary_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSUnion_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
GEOSGeometry* GEOS_DLL GEOSUnaryUnion_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSCoverageUnion_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSUnionCascaded_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSPointOnSurface_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSGetCentroid_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSMinimumBoundingCircle_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double* radius, GEOSGeometry** center);
GEOSGeometry* GEOS_DLL GEOSNode_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSClipByRect_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double xmin, double ymin, double xmax, double ymax);
GEOSGeometry* GEOS_DLL GEOSPolygonize_r(GEOSContextHandle_t handle, const GEOSGeometry *const geoms[], unsigned int ngeoms);
GEOSGeometry* GEOS_DLL GEOSPolygonize_valid_r(GEOSContextHandle_t handle, const GEOSGeometry *const geoms[], unsigned int ngems);
GEOSGeometry* GEOS_DLL GEOSPolygonizer_getCutEdges_r( GEOSContextHandle_t handle, const GEOSGeometry * const geoms[], unsigned int ngeoms);
GEOSGeometry* GEOS_DLL GEOSPolygonize_full_r(GEOSContextHandle_t handle, const GEOSGeometry* input, GEOSGeometry** cuts, GEOSGeometry** dangles, GEOSGeometry** invalidRings);
GEOSGeometry* GEOS_DLL GEOSBuildArea_r( GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSLineMerge_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSReverse_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSSimplify_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double tolerance);
GEOSGeometry* GEOS_DLL GEOSTopologyPreserveSimplify_r( GEOSContextHandle_t handle, const GEOSGeometry* g, double tolerance);
GEOSGeometry* GEOS_DLL GEOSGeom_extractUniquePoints_r( GEOSContextHandle_t handle, const GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSSharedPaths_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
GEOSGeometry* GEOS_DLL GEOSSnap_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2, double tolerance);
GEOSGeometry* GEOS_DLL  GEOSDelaunayTriangulation_r( GEOSContextHandle_t handle, const GEOSGeometry *g, double tolerance, int onlyEdges);
GEOSGeometry* GEOS_DLL  GEOSVoronoiDiagram_r( GEOSContextHandle_t extHandle, const GEOSGeometry *g, const GEOSGeometry *env, double tolerance, int onlyEdges);
int GEOS_DLL GEOSSegmentIntersection_r( GEOSContextHandle_t extHandle, double ax0, double ay0, double ax1, double ay1, double bx0, double by0, double bx1, double by1, double* cx, double* cy);
char GEOS_DLL GEOSDisjoint_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSTouches_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSIntersects_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSCrosses_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSWithin_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSContains_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSOverlaps_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSEquals_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSEqualsExact_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2, double tolerance);
char GEOS_DLL GEOSCovers_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSCoveredBy_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
const GEOSPreparedGeometry* GEOS_DLL GEOSPrepare_r( GEOSContextHandle_t handle, const GEOSGeometry* g);
void GEOS_DLL GEOSPreparedGeom_destroy_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* g);
char GEOS_DLL GEOSPreparedContains_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedContainsProperly_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedCoveredBy_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedCovers_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedCrosses_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedDisjoint_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedIntersects_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedOverlaps_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedTouches_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
char GEOS_DLL GEOSPreparedWithin_r(GEOSContextHandle_t handle, const GEOSPreparedGeometry* pg1, const GEOSGeometry* g2);
GEOSSTRtree* GEOS_DLL GEOSSTRtree_create_r( GEOSContextHandle_t handle, size_t nodeCapacity);
void GEOS_DLL GEOSSTRtree_insert_r(GEOSContextHandle_t handle, GEOSSTRtree *tree, const GEOSGeometry *g, void *item);
void GEOS_DLL GEOSSTRtree_query_r(GEOSContextHandle_t handle, GEOSSTRtree *tree, const GEOSGeometry *g, GEOSQueryCallback callback, void *userdata);
const GEOSGeometry* GEOS_DLL GEOSSTRtree_nearest_r(GEOSContextHandle_t handle, GEOSSTRtree *tree, const GEOSGeometry* geom);
const void* GEOS_DLL GEOSSTRtree_nearest_generic_r(GEOSContextHandle_t handle, GEOSSTRtree *tree, const void* item, const GEOSGeometry* itemEnvelope, GEOSDistanceCallback distancefn, void* userdata);
void GEOS_DLL GEOSSTRtree_iterate_r(GEOSContextHandle_t handle, GEOSSTRtree *tree, GEOSQueryCallback callback, void *userdata);
char GEOS_DLL GEOSSTRtree_remove_r(GEOSContextHandle_t handle, GEOSSTRtree *tree, const GEOSGeometry *g, void *item);
void GEOS_DLL GEOSSTRtree_destroy_r(GEOSContextHandle_t handle, GEOSSTRtree *tree);
char GEOS_DLL GEOSisEmpty_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
char GEOS_DLL GEOSisSimple_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
char GEOS_DLL GEOSisRing_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
char GEOS_DLL GEOSHasZ_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
char GEOS_DLL GEOSisClosed_r(GEOSContextHandle_t handle, const GEOSGeometry *g);
char GEOS_DLL GEOSRelatePattern_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2, const char *pat);
char* GEOS_DLL GEOSRelate_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
char GEOS_DLL GEOSRelatePatternMatch_r(GEOSContextHandle_t handle, const char *mat, const char *pat);
char* GEOS_DLL GEOSRelateBoundaryNodeRule_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2, int bnr);
char GEOS_DLL GEOSisValid_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
char* GEOS_DLL GEOSisValidReason_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
char GEOS_DLL GEOSisValidDetail_r(GEOSContextHandle_t handle, const GEOSGeometry* g, int flags, char** reason, GEOSGeometry** location);
GEOSGeometry* GEOS_DLL GEOSMakeValid_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
char* GEOS_DLL GEOSGeomType_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGeomTypeId_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGetSRID_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
void GEOS_DLL GEOSSetSRID_r(GEOSContextHandle_t handle, GEOSGeometry* g, int SRID);
void* GEOS_DLL GEOSGeom_getUserData_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
void GEOS_DLL GEOSGeom_setUserData_r(GEOSContextHandle_t handle, GEOSGeometry* g, void* userData);
int GEOS_DLL GEOSGetNumGeometries_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
const GEOSGeometry* GEOS_DLL GEOSGetGeometryN_r( GEOSContextHandle_t handle, const GEOSGeometry* g, int n);
int GEOS_DLL GEOSNormalize_r(GEOSContextHandle_t handle, GEOSGeometry* g);
GEOSGeometry* GEOS_DLL GEOSGeom_setPrecision_r( GEOSContextHandle_t handle, const GEOSGeometry *g, double gridSize, int flags);
double GEOS_DLL GEOSGeom_getPrecision_r( GEOSContextHandle_t handle, const GEOSGeometry *g);
int GEOS_DLL GEOSGetNumInteriorRings_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGeomGetNumPoints_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGeomGetX_r(GEOSContextHandle_t handle, const GEOSGeometry *g, double *x);
int GEOS_DLL GEOSGeomGetY_r(GEOSContextHandle_t handle, const GEOSGeometry *g, double *y);
int GEOS_DLL GEOSGeomGetZ_r(GEOSContextHandle_t handle, const GEOSGeometry *g, double *z);
const GEOSGeometry* GEOS_DLL GEOSGetInteriorRingN_r( GEOSContextHandle_t handle, const GEOSGeometry* g, int n);
const GEOSGeometry* GEOS_DLL GEOSGetExteriorRing_r( GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGetNumCoordinates_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
const GEOSCoordSequence* GEOS_DLL GEOSGeom_getCoordSeq_r( GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGeom_getDimensions_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGeom_getCoordinateDimension_r(GEOSContextHandle_t handle, const GEOSGeometry* g);
int GEOS_DLL GEOSGeom_getXMin_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double* value);
int GEOS_DLL GEOSGeom_getYMin_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double* value);
int GEOS_DLL GEOSGeom_getXMax_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double* value);
int GEOS_DLL GEOSGeom_getYMax_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double* value);
GEOSGeometry* GEOS_DLL GEOSGeomGetPointN_r(GEOSContextHandle_t handle, const GEOSGeometry *g, int n);
GEOSGeometry* GEOS_DLL GEOSGeomGetStartPoint_r(GEOSContextHandle_t handle, const GEOSGeometry *g);
GEOSGeometry* GEOS_DLL GEOSGeomGetEndPoint_r(GEOSContextHandle_t handle, const GEOSGeometry *g);
int GEOS_DLL GEOSArea_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double *area);
int GEOS_DLL GEOSLength_r(GEOSContextHandle_t handle, const GEOSGeometry* g, double *length);
int GEOS_DLL GEOSDistance_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2, double *dist);
int GEOS_DLL GEOSDistanceIndexed_r(GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2, double *dist);
int GEOS_DLL GEOSHausdorffDistance_r(GEOSContextHandle_t handle, const GEOSGeometry *g1, const GEOSGeometry *g2, double *dist);
int GEOS_DLL GEOSHausdorffDistanceDensify_r(GEOSContextHandle_t handle, const GEOSGeometry *g1, const GEOSGeometry *g2, double densifyFrac, double *dist);
int GEOS_DLL GEOSFrechetDistance_r(GEOSContextHandle_t handle, const GEOSGeometry *g1, const GEOSGeometry *g2, double *dist);
int GEOS_DLL GEOSFrechetDistanceDensify_r(GEOSContextHandle_t handle, const GEOSGeometry *g1, const GEOSGeometry *g2, double densifyFrac, double *dist);
int GEOS_DLL GEOSGeomGetLength_r(GEOSContextHandle_t handle, const GEOSGeometry *g, double *length);
GEOSCoordSequence* GEOS_DLL GEOSNearestPoints_r( GEOSContextHandle_t handle, const GEOSGeometry* g1, const GEOSGeometry* g2);
int GEOS_DLL GEOSOrientationIndex_r(GEOSContextHandle_t handle, double Ax, double Ay, double Bx, double By, double Px, double Py);
GEOSWKTReader* GEOS_DLL GEOSWKTReader_create_r( GEOSContextHandle_t handle);
void GEOS_DLL GEOSWKTReader_destroy_r(GEOSContextHandle_t handle, GEOSWKTReader* reader);
GEOSGeometry* GEOS_DLL GEOSWKTReader_read_r(GEOSContextHandle_t handle, GEOSWKTReader* reader, const char *wkt);
GEOSWKTWriter* GEOS_DLL GEOSWKTWriter_create_r( GEOSContextHandle_t handle);
void GEOS_DLL GEOSWKTWriter_destroy_r(GEOSContextHandle_t handle, GEOSWKTWriter* writer);
char* GEOS_DLL GEOSWKTWriter_write_r(GEOSContextHandle_t handle, GEOSWKTWriter* writer, const GEOSGeometry* g);
void GEOS_DLL GEOSWKTWriter_setTrim_r(GEOSContextHandle_t handle, GEOSWKTWriter *writer, char trim);
void GEOS_DLL GEOSWKTWriter_setRoundingPrecision_r(GEOSContextHandle_t handle, GEOSWKTWriter *writer, int precision);
void GEOS_DLL GEOSWKTWriter_setOutputDimension_r(GEOSContextHandle_t handle, GEOSWKTWriter *writer, int dim);
int GEOS_DLL GEOSWKTWriter_getOutputDimension_r(GEOSContextHandle_t handle, GEOSWKTWriter *writer);
void GEOS_DLL GEOSWKTWriter_setOld3D_r(GEOSContextHandle_t handle, GEOSWKTWriter *writer, int useOld3D);
GEOSWKBReader* GEOS_DLL GEOSWKBReader_create_r( GEOSContextHandle_t handle);
void GEOS_DLL GEOSWKBReader_destroy_r(GEOSContextHandle_t handle, GEOSWKBReader* reader);
GEOSGeometry* GEOS_DLL GEOSWKBReader_read_r(GEOSContextHandle_t handle, GEOSWKBReader* reader, const unsigned char *wkb, size_t size);
GEOSGeometry* GEOS_DLL GEOSWKBReader_readHEX_r( GEOSContextHandle_t handle, GEOSWKBReader* reader, const unsigned char *hex, size_t size);
GEOSWKBWriter* GEOS_DLL GEOSWKBWriter_create_r( GEOSContextHandle_t handle);
void GEOS_DLL GEOSWKBWriter_destroy_r(GEOSContextHandle_t handle, GEOSWKBWriter* writer);
unsigned char* GEOS_DLL GEOSWKBWriter_write_r( GEOSContextHandle_t handle, GEOSWKBWriter* writer, const GEOSGeometry* g, size_t *size);
unsigned char* GEOS_DLL GEOSWKBWriter_writeHEX_r( GEOSContextHandle_t handle, GEOSWKBWriter* writer, const GEOSGeometry* g, size_t *size);
int GEOS_DLL GEOSWKBWriter_getOutputDimension_r( GEOSContextHandle_t handle, const GEOSWKBWriter* writer);
void GEOS_DLL GEOSWKBWriter_setOutputDimension_r( GEOSContextHandle_t handle, GEOSWKBWriter* writer, int newDimension);
int GEOS_DLL GEOSWKBWriter_getByteOrder_r(GEOSContextHandle_t handle, const GEOSWKBWriter* writer);
void GEOS_DLL GEOSWKBWriter_setByteOrder_r(GEOSContextHandle_t handle, GEOSWKBWriter* writer, int byteOrder);
char GEOS_DLL GEOSWKBWriter_getIncludeSRID_r(GEOSContextHandle_t handle, const GEOSWKBWriter* writer);
void GEOS_DLL GEOSWKBWriter_setIncludeSRID_r(GEOSContextHandle_t handle, GEOSWKBWriter* writer, const char writeSRID);
void GEOS_DLL GEOSFree_r(GEOSContextHandle_t handle, void *buffer);

// defined in libgeos-version.c, where it is safe to #include geos_c.h
SEXP libgeos_geos_version();

static const R_CallMethodDef CallEntries[] = {
  {"libgeos_geos_version", (DL_FUNC) &libgeos_geos_version, 0},
  {NULL, NULL, 0}
};


void R_init_libgeos(DllInfo *dll) {
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  /* used by external packages linking to libgeos from C */
    R_RegisterCCallable("libgeos", "libgeos_version_int", (DL_FUNC) &libgeos_version_int);
    R_RegisterCCallable("libgeos", "initGEOS_r", (DL_FUNC) &initGEOS_r);
    R_RegisterCCallable("libgeos", "finishGEOS_r", (DL_FUNC) &finishGEOS_r);
    R_RegisterCCallable("libgeos", "GEOS_init_r", (DL_FUNC) &GEOS_init_r);
    R_RegisterCCallable("libgeos", "GEOS_finish_r", (DL_FUNC) &GEOS_finish_r);
    R_RegisterCCallable("libgeos", "GEOSContext_setNoticeHandler_r", (DL_FUNC) &GEOSContext_setNoticeHandler_r);
    R_RegisterCCallable("libgeos", "GEOSContext_setErrorHandler_r", (DL_FUNC) &GEOSContext_setErrorHandler_r);
    R_RegisterCCallable("libgeos", "GEOSContext_setNoticeMessageHandler_r", (DL_FUNC) &GEOSContext_setNoticeMessageHandler_r);
    R_RegisterCCallable("libgeos", "GEOSContext_setErrorMessageHandler_r", (DL_FUNC) &GEOSContext_setErrorMessageHandler_r);
    R_RegisterCCallable("libgeos", "GEOSversion", (DL_FUNC) &GEOSversion);
    R_RegisterCCallable("libgeos", "GEOSGeomFromWKT_r", (DL_FUNC) &GEOSGeomFromWKT_r);
    R_RegisterCCallable("libgeos", "GEOSGeomToWKT_r", (DL_FUNC) &GEOSGeomToWKT_r);
    R_RegisterCCallable("libgeos", "GEOS_getWKBOutputDims_r", (DL_FUNC) &GEOS_getWKBOutputDims_r);
    R_RegisterCCallable("libgeos", "GEOS_setWKBOutputDims_r", (DL_FUNC) &GEOS_setWKBOutputDims_r);
    R_RegisterCCallable("libgeos", "GEOS_getWKBByteOrder_r", (DL_FUNC) &GEOS_getWKBByteOrder_r);
    R_RegisterCCallable("libgeos", "GEOS_setWKBByteOrder_r", (DL_FUNC) &GEOS_setWKBByteOrder_r);
    R_RegisterCCallable("libgeos", "GEOSGeomFromWKB_buf_r", (DL_FUNC) &GEOSGeomFromWKB_buf_r);
    R_RegisterCCallable("libgeos", "GEOSGeomToWKB_buf_r", (DL_FUNC) &GEOSGeomToWKB_buf_r);
    R_RegisterCCallable("libgeos", "GEOSGeomFromHEX_buf_r", (DL_FUNC) &GEOSGeomFromHEX_buf_r);
    R_RegisterCCallable("libgeos", "GEOSGeomToHEX_buf_r", (DL_FUNC) &GEOSGeomToHEX_buf_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_create_r", (DL_FUNC) &GEOSCoordSeq_create_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_clone_r", (DL_FUNC) &GEOSCoordSeq_clone_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_destroy_r", (DL_FUNC) &GEOSCoordSeq_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_setX_r", (DL_FUNC) &GEOSCoordSeq_setX_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_setY_r", (DL_FUNC) &GEOSCoordSeq_setY_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_setZ_r", (DL_FUNC) &GEOSCoordSeq_setZ_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_setXY_r", (DL_FUNC) &GEOSCoordSeq_setXY_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_setXYZ_r", (DL_FUNC) &GEOSCoordSeq_setXYZ_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_setOrdinate_r", (DL_FUNC) &GEOSCoordSeq_setOrdinate_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getX_r", (DL_FUNC) &GEOSCoordSeq_getX_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getY_r", (DL_FUNC) &GEOSCoordSeq_getY_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getZ_r", (DL_FUNC) &GEOSCoordSeq_getZ_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getXY_r", (DL_FUNC) &GEOSCoordSeq_getXY_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getXYZ_r", (DL_FUNC) &GEOSCoordSeq_getXYZ_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getOrdinate_r", (DL_FUNC) &GEOSCoordSeq_getOrdinate_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getSize_r", (DL_FUNC) &GEOSCoordSeq_getSize_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_getDimensions_r", (DL_FUNC) &GEOSCoordSeq_getDimensions_r);
    R_RegisterCCallable("libgeos", "GEOSCoordSeq_isCCW_r", (DL_FUNC) &GEOSCoordSeq_isCCW_r);
    R_RegisterCCallable("libgeos", "GEOSProject_r", (DL_FUNC) &GEOSProject_r);
    R_RegisterCCallable("libgeos", "GEOSInterpolate_r", (DL_FUNC) &GEOSInterpolate_r);
    R_RegisterCCallable("libgeos", "GEOSProjectNormalized_r", (DL_FUNC) &GEOSProjectNormalized_r);
    R_RegisterCCallable("libgeos", "GEOSInterpolateNormalized_r", (DL_FUNC) &GEOSInterpolateNormalized_r);
    R_RegisterCCallable("libgeos", "GEOSBuffer_r", (DL_FUNC) &GEOSBuffer_r);
    R_RegisterCCallable("libgeos", "GEOSBufferParams_create_r", (DL_FUNC) &GEOSBufferParams_create_r);
    R_RegisterCCallable("libgeos", "GEOSBufferParams_destroy_r", (DL_FUNC) &GEOSBufferParams_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSBufferParams_setEndCapStyle_r", (DL_FUNC) &GEOSBufferParams_setEndCapStyle_r);
    R_RegisterCCallable("libgeos", "GEOSBufferParams_setJoinStyle_r", (DL_FUNC) &GEOSBufferParams_setJoinStyle_r);
    R_RegisterCCallable("libgeos", "GEOSBufferParams_setMitreLimit_r", (DL_FUNC) &GEOSBufferParams_setMitreLimit_r);
    R_RegisterCCallable("libgeos", "GEOSBufferParams_setQuadrantSegments_r", (DL_FUNC) &GEOSBufferParams_setQuadrantSegments_r);
    R_RegisterCCallable("libgeos", "GEOSBufferParams_setSingleSided_r", (DL_FUNC) &GEOSBufferParams_setSingleSided_r);
    R_RegisterCCallable("libgeos", "GEOSBufferWithParams_r", (DL_FUNC) &GEOSBufferWithParams_r);
    R_RegisterCCallable("libgeos", "GEOSBufferWithStyle_r", (DL_FUNC) &GEOSBufferWithStyle_r);
    R_RegisterCCallable("libgeos", "GEOSSingleSidedBuffer_r", (DL_FUNC) &GEOSSingleSidedBuffer_r);
    R_RegisterCCallable("libgeos", "GEOSOffsetCurve_r", (DL_FUNC) &GEOSOffsetCurve_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createPoint_r", (DL_FUNC) &GEOSGeom_createPoint_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createPointFromXY_r", (DL_FUNC) &GEOSGeom_createPointFromXY_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createEmptyPoint_r", (DL_FUNC) &GEOSGeom_createEmptyPoint_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createLinearRing_r", (DL_FUNC) &GEOSGeom_createLinearRing_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createLineString_r", (DL_FUNC) &GEOSGeom_createLineString_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createEmptyLineString_r", (DL_FUNC) &GEOSGeom_createEmptyLineString_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createEmptyPolygon_r", (DL_FUNC) &GEOSGeom_createEmptyPolygon_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createPolygon_r", (DL_FUNC) &GEOSGeom_createPolygon_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createCollection_r", (DL_FUNC) &GEOSGeom_createCollection_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_createEmptyCollection_r", (DL_FUNC) &GEOSGeom_createEmptyCollection_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_clone_r", (DL_FUNC) &GEOSGeom_clone_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_destroy_r", (DL_FUNC) &GEOSGeom_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSEnvelope_r", (DL_FUNC) &GEOSEnvelope_r);
    R_RegisterCCallable("libgeos", "GEOSIntersection_r", (DL_FUNC) &GEOSIntersection_r);
    R_RegisterCCallable("libgeos", "GEOSConvexHull_r", (DL_FUNC) &GEOSConvexHull_r);
    R_RegisterCCallable("libgeos", "GEOSMinimumRotatedRectangle_r", (DL_FUNC) &GEOSMinimumRotatedRectangle_r);
    R_RegisterCCallable("libgeos", "GEOSMinimumWidth_r", (DL_FUNC) &GEOSMinimumWidth_r);
    R_RegisterCCallable("libgeos", "GEOSMinimumClearanceLine_r", (DL_FUNC) &GEOSMinimumClearanceLine_r);
    R_RegisterCCallable("libgeos", "GEOSMinimumClearance_r", (DL_FUNC) &GEOSMinimumClearance_r);
    R_RegisterCCallable("libgeos", "GEOSDifference_r", (DL_FUNC) &GEOSDifference_r);
    R_RegisterCCallable("libgeos", "GEOSSymDifference_r", (DL_FUNC) &GEOSSymDifference_r);
    R_RegisterCCallable("libgeos", "GEOSBoundary_r", (DL_FUNC) &GEOSBoundary_r);
    R_RegisterCCallable("libgeos", "GEOSUnion_r", (DL_FUNC) &GEOSUnion_r);
    R_RegisterCCallable("libgeos", "GEOSUnaryUnion_r", (DL_FUNC) &GEOSUnaryUnion_r);
    R_RegisterCCallable("libgeos", "GEOSCoverageUnion_r", (DL_FUNC) &GEOSCoverageUnion_r);
    R_RegisterCCallable("libgeos", "GEOSUnionCascaded_r", (DL_FUNC) &GEOSUnionCascaded_r);
    R_RegisterCCallable("libgeos", "GEOSPointOnSurface_r", (DL_FUNC) &GEOSPointOnSurface_r);
    R_RegisterCCallable("libgeos", "GEOSGetCentroid_r", (DL_FUNC) &GEOSGetCentroid_r);
    R_RegisterCCallable("libgeos", "GEOSMinimumBoundingCircle_r", (DL_FUNC) &GEOSMinimumBoundingCircle_r);
    R_RegisterCCallable("libgeos", "GEOSNode_r", (DL_FUNC) &GEOSNode_r);
    R_RegisterCCallable("libgeos", "GEOSClipByRect_r", (DL_FUNC) &GEOSClipByRect_r);
    R_RegisterCCallable("libgeos", "GEOSPolygonize_r", (DL_FUNC) &GEOSPolygonize_r);
    R_RegisterCCallable("libgeos", "GEOSPolygonize_valid_r", (DL_FUNC) &GEOSPolygonize_valid_r);
    R_RegisterCCallable("libgeos", "GEOSPolygonizer_getCutEdges_r", (DL_FUNC) &GEOSPolygonizer_getCutEdges_r);
    R_RegisterCCallable("libgeos", "GEOSPolygonize_full_r", (DL_FUNC) &GEOSPolygonize_full_r);
    R_RegisterCCallable("libgeos", "GEOSBuildArea_r", (DL_FUNC) &GEOSBuildArea_r);
    R_RegisterCCallable("libgeos", "GEOSLineMerge_r", (DL_FUNC) &GEOSLineMerge_r);
    R_RegisterCCallable("libgeos", "GEOSReverse_r", (DL_FUNC) &GEOSReverse_r);
    R_RegisterCCallable("libgeos", "GEOSSimplify_r", (DL_FUNC) &GEOSSimplify_r);
    R_RegisterCCallable("libgeos", "GEOSTopologyPreserveSimplify_r", (DL_FUNC) &GEOSTopologyPreserveSimplify_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_extractUniquePoints_r", (DL_FUNC) &GEOSGeom_extractUniquePoints_r);
    R_RegisterCCallable("libgeos", "GEOSSharedPaths_r", (DL_FUNC) &GEOSSharedPaths_r);
    R_RegisterCCallable("libgeos", "GEOSSnap_r", (DL_FUNC) &GEOSSnap_r);
    R_RegisterCCallable("libgeos", "GEOSDelaunayTriangulation_r", (DL_FUNC) &GEOSDelaunayTriangulation_r);
    R_RegisterCCallable("libgeos", "GEOSVoronoiDiagram_r", (DL_FUNC) &GEOSVoronoiDiagram_r);
    R_RegisterCCallable("libgeos", "GEOSSegmentIntersection_r", (DL_FUNC) &GEOSSegmentIntersection_r);
    R_RegisterCCallable("libgeos", "GEOSDisjoint_r", (DL_FUNC) &GEOSDisjoint_r);
    R_RegisterCCallable("libgeos", "GEOSTouches_r", (DL_FUNC) &GEOSTouches_r);
    R_RegisterCCallable("libgeos", "GEOSIntersects_r", (DL_FUNC) &GEOSIntersects_r);
    R_RegisterCCallable("libgeos", "GEOSCrosses_r", (DL_FUNC) &GEOSCrosses_r);
    R_RegisterCCallable("libgeos", "GEOSWithin_r", (DL_FUNC) &GEOSWithin_r);
    R_RegisterCCallable("libgeos", "GEOSContains_r", (DL_FUNC) &GEOSContains_r);
    R_RegisterCCallable("libgeos", "GEOSOverlaps_r", (DL_FUNC) &GEOSOverlaps_r);
    R_RegisterCCallable("libgeos", "GEOSEquals_r", (DL_FUNC) &GEOSEquals_r);
    R_RegisterCCallable("libgeos", "GEOSEqualsExact_r", (DL_FUNC) &GEOSEqualsExact_r);
    R_RegisterCCallable("libgeos", "GEOSCovers_r", (DL_FUNC) &GEOSCovers_r);
    R_RegisterCCallable("libgeos", "GEOSCoveredBy_r", (DL_FUNC) &GEOSCoveredBy_r);
    R_RegisterCCallable("libgeos", "GEOSPrepare_r", (DL_FUNC) &GEOSPrepare_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedGeom_destroy_r", (DL_FUNC) &GEOSPreparedGeom_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedContains_r", (DL_FUNC) &GEOSPreparedContains_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedContainsProperly_r", (DL_FUNC) &GEOSPreparedContainsProperly_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedCoveredBy_r", (DL_FUNC) &GEOSPreparedCoveredBy_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedCovers_r", (DL_FUNC) &GEOSPreparedCovers_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedCrosses_r", (DL_FUNC) &GEOSPreparedCrosses_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedDisjoint_r", (DL_FUNC) &GEOSPreparedDisjoint_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedIntersects_r", (DL_FUNC) &GEOSPreparedIntersects_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedOverlaps_r", (DL_FUNC) &GEOSPreparedOverlaps_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedTouches_r", (DL_FUNC) &GEOSPreparedTouches_r);
    R_RegisterCCallable("libgeos", "GEOSPreparedWithin_r", (DL_FUNC) &GEOSPreparedWithin_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_create_r", (DL_FUNC) &GEOSSTRtree_create_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_insert_r", (DL_FUNC) &GEOSSTRtree_insert_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_query_r", (DL_FUNC) &GEOSSTRtree_query_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_nearest_r", (DL_FUNC) &GEOSSTRtree_nearest_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_nearest_generic_r", (DL_FUNC) &GEOSSTRtree_nearest_generic_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_iterate_r", (DL_FUNC) &GEOSSTRtree_iterate_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_remove_r", (DL_FUNC) &GEOSSTRtree_remove_r);
    R_RegisterCCallable("libgeos", "GEOSSTRtree_destroy_r", (DL_FUNC) &GEOSSTRtree_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSisEmpty_r", (DL_FUNC) &GEOSisEmpty_r);
    R_RegisterCCallable("libgeos", "GEOSisSimple_r", (DL_FUNC) &GEOSisSimple_r);
    R_RegisterCCallable("libgeos", "GEOSisRing_r", (DL_FUNC) &GEOSisRing_r);
    R_RegisterCCallable("libgeos", "GEOSHasZ_r", (DL_FUNC) &GEOSHasZ_r);
    R_RegisterCCallable("libgeos", "GEOSisClosed_r", (DL_FUNC) &GEOSisClosed_r);
    R_RegisterCCallable("libgeos", "GEOSRelatePattern_r", (DL_FUNC) &GEOSRelatePattern_r);
    R_RegisterCCallable("libgeos", "GEOSRelate_r", (DL_FUNC) &GEOSRelate_r);
    R_RegisterCCallable("libgeos", "GEOSRelatePatternMatch_r", (DL_FUNC) &GEOSRelatePatternMatch_r);
    R_RegisterCCallable("libgeos", "GEOSRelateBoundaryNodeRule_r", (DL_FUNC) &GEOSRelateBoundaryNodeRule_r);
    R_RegisterCCallable("libgeos", "GEOSisValid_r", (DL_FUNC) &GEOSisValid_r);
    R_RegisterCCallable("libgeos", "GEOSisValidReason_r", (DL_FUNC) &GEOSisValidReason_r);
    R_RegisterCCallable("libgeos", "GEOSisValidDetail_r", (DL_FUNC) &GEOSisValidDetail_r);
    R_RegisterCCallable("libgeos", "GEOSMakeValid_r", (DL_FUNC) &GEOSMakeValid_r);
    R_RegisterCCallable("libgeos", "GEOSGeomType_r", (DL_FUNC) &GEOSGeomType_r);
    R_RegisterCCallable("libgeos", "GEOSGeomTypeId_r", (DL_FUNC) &GEOSGeomTypeId_r);
    R_RegisterCCallable("libgeos", "GEOSGetSRID_r", (DL_FUNC) &GEOSGetSRID_r);
    R_RegisterCCallable("libgeos", "GEOSSetSRID_r", (DL_FUNC) &GEOSSetSRID_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getUserData_r", (DL_FUNC) &GEOSGeom_getUserData_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_setUserData_r", (DL_FUNC) &GEOSGeom_setUserData_r);
    R_RegisterCCallable("libgeos", "GEOSGetNumGeometries_r", (DL_FUNC) &GEOSGetNumGeometries_r);
    R_RegisterCCallable("libgeos", "GEOSGetGeometryN_r", (DL_FUNC) &GEOSGetGeometryN_r);
    R_RegisterCCallable("libgeos", "GEOSNormalize_r", (DL_FUNC) &GEOSNormalize_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_setPrecision_r", (DL_FUNC) &GEOSGeom_setPrecision_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getPrecision_r", (DL_FUNC) &GEOSGeom_getPrecision_r);
    R_RegisterCCallable("libgeos", "GEOSGetNumInteriorRings_r", (DL_FUNC) &GEOSGetNumInteriorRings_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetNumPoints_r", (DL_FUNC) &GEOSGeomGetNumPoints_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetX_r", (DL_FUNC) &GEOSGeomGetX_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetY_r", (DL_FUNC) &GEOSGeomGetY_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetZ_r", (DL_FUNC) &GEOSGeomGetZ_r);
    R_RegisterCCallable("libgeos", "GEOSGetInteriorRingN_r", (DL_FUNC) &GEOSGetInteriorRingN_r);
    R_RegisterCCallable("libgeos", "GEOSGetExteriorRing_r", (DL_FUNC) &GEOSGetExteriorRing_r);
    R_RegisterCCallable("libgeos", "GEOSGetNumCoordinates_r", (DL_FUNC) &GEOSGetNumCoordinates_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getCoordSeq_r", (DL_FUNC) &GEOSGeom_getCoordSeq_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getDimensions_r", (DL_FUNC) &GEOSGeom_getDimensions_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getCoordinateDimension_r", (DL_FUNC) &GEOSGeom_getCoordinateDimension_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getXMin_r", (DL_FUNC) &GEOSGeom_getXMin_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getYMin_r", (DL_FUNC) &GEOSGeom_getYMin_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getXMax_r", (DL_FUNC) &GEOSGeom_getXMax_r);
    R_RegisterCCallable("libgeos", "GEOSGeom_getYMax_r", (DL_FUNC) &GEOSGeom_getYMax_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetPointN_r", (DL_FUNC) &GEOSGeomGetPointN_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetStartPoint_r", (DL_FUNC) &GEOSGeomGetStartPoint_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetEndPoint_r", (DL_FUNC) &GEOSGeomGetEndPoint_r);
    R_RegisterCCallable("libgeos", "GEOSArea_r", (DL_FUNC) &GEOSArea_r);
    R_RegisterCCallable("libgeos", "GEOSLength_r", (DL_FUNC) &GEOSLength_r);
    R_RegisterCCallable("libgeos", "GEOSDistance_r", (DL_FUNC) &GEOSDistance_r);
    R_RegisterCCallable("libgeos", "GEOSDistanceIndexed_r", (DL_FUNC) &GEOSDistanceIndexed_r);
    R_RegisterCCallable("libgeos", "GEOSHausdorffDistance_r", (DL_FUNC) &GEOSHausdorffDistance_r);
    R_RegisterCCallable("libgeos", "GEOSHausdorffDistanceDensify_r", (DL_FUNC) &GEOSHausdorffDistanceDensify_r);
    R_RegisterCCallable("libgeos", "GEOSFrechetDistance_r", (DL_FUNC) &GEOSFrechetDistance_r);
    R_RegisterCCallable("libgeos", "GEOSFrechetDistanceDensify_r", (DL_FUNC) &GEOSFrechetDistanceDensify_r);
    R_RegisterCCallable("libgeos", "GEOSGeomGetLength_r", (DL_FUNC) &GEOSGeomGetLength_r);
    R_RegisterCCallable("libgeos", "GEOSNearestPoints_r", (DL_FUNC) &GEOSNearestPoints_r);
    R_RegisterCCallable("libgeos", "GEOSOrientationIndex_r", (DL_FUNC) &GEOSOrientationIndex_r);
    R_RegisterCCallable("libgeos", "GEOSWKTReader_create_r", (DL_FUNC) &GEOSWKTReader_create_r);
    R_RegisterCCallable("libgeos", "GEOSWKTReader_destroy_r", (DL_FUNC) &GEOSWKTReader_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSWKTReader_read_r", (DL_FUNC) &GEOSWKTReader_read_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_create_r", (DL_FUNC) &GEOSWKTWriter_create_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_destroy_r", (DL_FUNC) &GEOSWKTWriter_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_write_r", (DL_FUNC) &GEOSWKTWriter_write_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_setTrim_r", (DL_FUNC) &GEOSWKTWriter_setTrim_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_setRoundingPrecision_r", (DL_FUNC) &GEOSWKTWriter_setRoundingPrecision_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_setOutputDimension_r", (DL_FUNC) &GEOSWKTWriter_setOutputDimension_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_getOutputDimension_r", (DL_FUNC) &GEOSWKTWriter_getOutputDimension_r);
    R_RegisterCCallable("libgeos", "GEOSWKTWriter_setOld3D_r", (DL_FUNC) &GEOSWKTWriter_setOld3D_r);
    R_RegisterCCallable("libgeos", "GEOSWKBReader_create_r", (DL_FUNC) &GEOSWKBReader_create_r);
    R_RegisterCCallable("libgeos", "GEOSWKBReader_destroy_r", (DL_FUNC) &GEOSWKBReader_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSWKBReader_read_r", (DL_FUNC) &GEOSWKBReader_read_r);
    R_RegisterCCallable("libgeos", "GEOSWKBReader_readHEX_r", (DL_FUNC) &GEOSWKBReader_readHEX_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_create_r", (DL_FUNC) &GEOSWKBWriter_create_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_destroy_r", (DL_FUNC) &GEOSWKBWriter_destroy_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_write_r", (DL_FUNC) &GEOSWKBWriter_write_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_writeHEX_r", (DL_FUNC) &GEOSWKBWriter_writeHEX_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_getOutputDimension_r", (DL_FUNC) &GEOSWKBWriter_getOutputDimension_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_setOutputDimension_r", (DL_FUNC) &GEOSWKBWriter_setOutputDimension_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_getByteOrder_r", (DL_FUNC) &GEOSWKBWriter_getByteOrder_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_setByteOrder_r", (DL_FUNC) &GEOSWKBWriter_setByteOrder_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_getIncludeSRID_r", (DL_FUNC) &GEOSWKBWriter_getIncludeSRID_r);
    R_RegisterCCallable("libgeos", "GEOSWKBWriter_setIncludeSRID_r", (DL_FUNC) &GEOSWKBWriter_setIncludeSRID_r);
    R_RegisterCCallable("libgeos", "GEOSFree_r", (DL_FUNC) &GEOSFree_r);
}
