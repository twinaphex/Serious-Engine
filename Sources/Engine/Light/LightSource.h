/* Copyright (c) 2002-2012 Croteam Ltd. 
This program is free software; you can redistribute it and/or modify
it under the terms of version 2 of the GNU General Public License as published by
the Free Software Foundation


This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. */

#ifndef SE_INCL_LIGHTSOURCE_H
#define SE_INCL_LIGHTSOURCE_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Base/Lists.h>

/*
 * Structure describing properties of a light source entity.
 */
#define LSF_DIRECTIONAL             (1L<<0)   // rays are not emanating from point, but from direction
#define LSF_CASTSHADOWS             (1L<<1)   // light can cast shadows
#define LSF_DIFFUSION               (1L<<2)   // intensity depends on angle with polygon normal
#define LSF_DARKLIGHT               (1L<<3)   // darkens polygons instead of lighting them
#define LSF_SUBSTRACTSECTORAMBIENT  (1L<<4)   // sector ambient is substract from intensity
#define LSF_NONPERSISTENT           (1L<<5)   // not saved (can change during game)
#define LSF_LENSFLAREONLY           (1L<<6)   // no light, only lens flare
#define LSF_DYNAMIC                 (1L<<7)   // dynamic light (fast frequent caching, no shadows)

class ENGINE_API CLightSource
{
public:
// implementation:
  // constructor
  CLightSource(void);
  // destructor
  ~CLightSource(void);
  CListHead ls_lhLayers;        // list of shadow map layers of this light source
  class CEntity *ls_penEntity;  // the entity of this light source

  uint32_t ls_ulFlags;                 // various flags

  RANGE ls_rHotSpot;                // distance before intensity starts to fall off
  RANGE ls_rFallOff;                // distance before intensity reaches zero

  COLOR ls_colColor;                // light color
  COLOR ls_colAmbient;              // ambient color (for directional lights only)
  uint8_t ls_ubLightAnimationObject;  // light animation - 0 for non animating lights
  uint8_t ls_ubPolygonalMask;         // mask for casting rays only through some polygons

  float ls_fNearClipDistance;       // clip plane distance near light
  float ls_fFarClipDistance;        // clip plane distance near polygon

  class CLensFlareType *ls_plftLensFlare;   // type of lens flare to use or NULL for none
  CAnimObject *ls_paoLightAnimation;  // animobject for light animating
  CAnimObject *ls_paoAmbientLightAnimation;  // animobject for light animating

  // test if a polygon has a layer from this light source
  bool PolygonHasLayer(CBrushPolygon &bpo);

  // set layer parameters
  void SetLayerParameters(CBrushShadowLayer &bsl, CBrushPolygon &bpo, class CLightRectangle &lr);
  // update layer parameters
  void UpdateLayer(CBrushShadowLayer &bsl);
  // add a layer to a polygon
  void AddLayer(CBrushPolygon &bpo);
  // update layer parameters
  void UpdateLayer(CBrushPolygon &bpo);
  // uncache all influenced shadow maps, but keep shadow layers
  void UncacheShadowMaps(void);
  // discard all linked shadow layers
  void DiscardShadowLayers(void);
  // find all shadow maps that should have layers from this light source
  void FindShadowLayers(bool bSelectedOnly);
  void FindShadowLayersDirectional(bool bSelectedOnly);
  void FindShadowLayersPoint(bool bSelectedOnly);
  // update shadow map on all terrains in world
  void UpdateTerrains(CPlacement3D plOld, CPlacement3D plNew);
  void UpdateTerrains(void);

// interface:
  // set properties of the light source without discarding shadows
  void SetLightSourceWithNoDiscarding(const CLightSource &lsOriginal);
  // set properties of the light source and discard shadows if neccessary
  void SetLightSource(const CLightSource &lsOriginal);
  // get color of light acounting for possible animation
  COLOR GetLightColor(void) const;
  void  GetLightColor( uint8_t &ubR, uint8_t &ubG, uint8_t &ubB) const;
  COLOR GetLightAmbient(void) const;
  void  GetLightAmbient( uint8_t &ubAR, uint8_t &ubAG, uint8_t &ubAB) const;
  inline void GetLightColorAndAmbient( COLOR &colLight, COLOR &colAmbient) const {
    colLight   = GetLightColor();
    colAmbient = GetLightAmbient();
  }
  inline void GetLightColorAndAmbient( uint8_t &ubR,  uint8_t &ubG,  uint8_t &ubB,
                                       uint8_t &ubAR, uint8_t &ubAG, uint8_t &ubAB) const {
    GetLightColor(   ubR,  ubG,  ubB);
    GetLightAmbient( ubAR, ubAG, ubAB);
  }
  // read/write from a stream
  void Read_t( CTStream *pstrm);        // throw char *
  void Write_t( CTStream *pstrm);       // throw char *
};


#endif  /* include-once check. */

