
/*
 * Line clipping flags
 */
#define LCF_REMOVED   (0x00L)  // the entire edge is invisible
#define LCF_UNCLIPPED (0x80L)  // this point remains unclipped
#define LCF_NEAR      (0x01L)  // this point is clipped at near plane
#define LCF_FAR       (0x02L)  // this point is clipped at far plane
#define LCF_LEFT      (0x04L)  // this point is clipped at left plane
#define LCF_RIGHT     (0x08L)  // this point is clipped at right plane
#define LCF_TOP       (0x10L)  // this point is clipped at top plane
#define LCF_BOTTOM    (0x20L)  // this point is clipped at bottom plane

#define LCF_EDGEREMOVED (0x0000L)   // used for testing if entire edge is removed
// shifts used for clip flags for start/end vertex
#define LCS_VERTEX0 (0)
#define LCS_VERTEX1 (8)
// masks used for clip flags for start/end vertex
#define LCM_VERTEX0 (0x00FFL)
#define LCM_VERTEX1 (0xFF00L)
// creating line clip flags for start/end vertex
#define LCFVERTEX0(lcf) ((lcf)<<LCS_VERTEX0)
#define LCFVERTEX1(lcf) ((lcf)<<LCS_VERTEX1)

// asm shortcuts
#define O offset
#define Q qword ptr
#define D dword ptr
#define W  word ptr
#define B  byte ptr

/*
 * Intersecting object (works on edges)
 */
class ENGINE_API CIntersector {
private:
  FLOAT ci_fX0;   // relative coordinates of point
  FLOAT ci_fY0;
  INDEX ci_ct;
public:
  // constructor
  inline CIntersector(FLOAT fX0=0.0f, FLOAT fY0=0.0f)
    : ci_fX0(fX0), ci_fY0(fY0), ci_ct(0) {};

  inline void Clear(void) { ci_ct = 0;}; // Clears intersection count
  inline void AddEdge( FLOAT fedgx1, FLOAT fedgy1, FLOAT fedgx2, FLOAT fedgy2); // Checks for intersection
  inline BOOL IsIntersecting() { return (ci_ct % 2) != 0; };  // Do we have intersection?
};

// inline functions implementation

/////////////////////////////////////////////////////////////////////
//  CIntersector
/////////////////////////////////////////////////////////////////////
/*
 * Checks for intersection of edge with +x axis
 */
ENGINE_API inline void CIntersector::AddEdge( FLOAT fedgx1, FLOAT fedgy1, FLOAT fedgx2, FLOAT fedgy2)
{
  // transform edge relative to the origin
  fedgx1-=ci_fX0; fedgy1-=ci_fY0;
  fedgx2-=ci_fX0; fedgy2-=ci_fY0;

  if( fedgy1 > 0)
  {
    if( fedgy2 > 0) return;

    if( fedgx1 <= 0)
    {
      if( fedgx2 <= 0) return;
    }
    else if( fedgx2 > 0)
    {
      ci_ct ++;
      return;
    }
  }
  else
  {
    if( fedgy2 <= 0) return;

    if( fedgx1 <= 0)
    {
      if( fedgx2 <= 0) return;
    }
    else if( fedgx2 > 0)
    {
      ci_ct ++;
      return;
    }
  }
  // here we calculate x coordinate of edge and +x axis intersection point
  FLOAT a, b;
  a = (fedgy2 - fedgy1)/(fedgx2 - fedgx1);
  b = fedgy1 - a*fedgx1;
  if( -b/a < 0) return;     // no intersection, intersection coordinate x is left from 0
  ci_ct ++;
}

/* rcg10042001 !!! FIXME */
#ifdef _MSC_VER
  #define ASMOPT 1
#endif

// how much are the clip planes offset inside frustum
#define CLIPPLANE_EPSILON (1E-3f)

/*
 * Clip a line by a single plane -- helper function.
 */
inline BOOL ClipLineByNearPlane(FLOAT3D &v0, FLOAT3D &v1, FLOAT fPlaneDistance, 
                            ULONG &ulCode0, ULONG &ulCode1, ULONG ulCodeClip)
{
  // calculate point distances from clip plane
  FLOAT fDistance0 = -fPlaneDistance-v0(3);
  FLOAT fDistance1 = -fPlaneDistance-v1(3);
  if (fDistance0<=0) {
    // if both are back
    if (fDistance1<=0) {
      // no line remains
      return FALSE;
    // if first is back, second front
    } else {
      // clip first
      FLOAT fDivisor = 1.0f/(fDistance0-fDistance1);
      FLOAT fFactor = fDistance0*fDivisor;
      v0(1) = v0(1)-(v0(1)-v1(1))*fFactor;
      v0(2) = v0(2)-(v0(2)-v1(2))*fFactor;
      v0(3) = -fPlaneDistance;
      // mark that first was clipped
      ulCode0 = LCFVERTEX0(ulCodeClip);
      // line remains
      return TRUE;
    }
  } else {
    // if first is front, second back
    if (fDistance1<=0) {
      // clip second
      FLOAT fDivisor = 1.0f/(fDistance0-fDistance1);
      FLOAT fFactor = fDistance1*fDivisor;
      v1(1) = v1(1)-(v0(1)-v1(1))*fFactor;
      v1(2) = v1(2)-(v0(2)-v1(2))*fFactor;
      v1(3) = -fPlaneDistance;
      // mark that second was clipped
      ulCode1 = LCFVERTEX1(ulCodeClip);
      // line remains
      return TRUE;
    // if both are front
    } else {
      // line remains unclipped
      return TRUE;
    }
  }
}

/*
 * Clip a line by a single plane -- helper function.
 */
inline BOOL ClipLineByFarPlane(FLOAT3D &v0, FLOAT3D &v1, FLOAT fPlaneDistance, 
                            ULONG &ulCode0, ULONG &ulCode1, ULONG ulCodeClip)
{
  // calculate point distances from clip plane
  FLOAT fDistance0 = fPlaneDistance+v0(3);
  FLOAT fDistance1 = fPlaneDistance+v1(3);
  if (fDistance0<=0) {
    // if both are back
    if (fDistance1<=0) {
      // no line remains
      return FALSE;
    // if first is back, second front
    } else {
      // clip first
      FLOAT fDivisor = 1.0f/(fDistance0-fDistance1);
      FLOAT fFactor = fDistance0*fDivisor;
      v0(1) = v0(1)-(v0(1)-v1(1))*fFactor;
      v0(2) = v0(2)-(v0(2)-v1(2))*fFactor;
      v0(3) = -fPlaneDistance;
      // mark that first was clipped
      ulCode0 = LCFVERTEX0(ulCodeClip);
      // line remains
      return TRUE;
    }
  } else {
    // if first is front, second back
    if (fDistance1<=0) {
      // clip second
      FLOAT fDivisor = 1.0f/(fDistance0-fDistance1);
      FLOAT fFactor = fDistance1*fDivisor;
      v1(1) = v1(1)-(v0(1)-v1(1))*fFactor;
      v1(2) = v1(2)-(v0(2)-v1(2))*fFactor;
      v1(3) = -fPlaneDistance;
      // mark that second was clipped
      ulCode1 = LCFVERTEX1(ulCodeClip);
      // line remains
      return TRUE;
    // if both are front
    } else {
      // line remains unclipped
      return TRUE;
    }
  }
}

static inline void MakeClipPlane(const FLOAT3D &vN, FLOAT fD, FLOATplane3D &pl)
{
  FLOAT fOoL = 1.0f/vN.Length();
  pl = FLOATplane3D(vN*fOoL, fD*fOoL);
}

#undef ASMOPT

#undef O
#undef Q
#undef D
#undef W
#undef B
