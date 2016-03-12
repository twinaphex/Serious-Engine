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

#ifndef SE_INCL_FOG_INTERNAL_H
#define SE_INCL_FOG_INTERNAL_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Graphics/Fog.h>


// current fog parameters
extern bool _fog_bActive;
extern CFogParameters _fog_fp;
extern CTexParams _fog_tpLocal;
extern float _fog_fViewerH;
extern FLOAT3D _fog_vViewPosAbs;
extern FLOAT3D _fog_vViewDirAbs;
extern FLOAT3D _fog_vHDirAbs;
extern FLOAT3D _fog_vHDirView;
extern float _fog_fMulZ;
extern float _fog_fMulH;
extern float _fog_fAddH;
extern PIX _fog_pixSizeH;
extern PIX _fog_pixSizeL;
extern float _fog_fStart;
extern float _fog_fEnd;  
extern uint32_t _fog_ulAlpha;
extern uint32_t _fog_ulTexture;
extern uint8_t *_fog_pubTable;

// start fog with given parameters
extern void StartFog( CFogParameters &fp, const FLOAT3D &vViewPosAbs,
                                          const FLOATmatrix3D &mAbsToView);
// stop fog
extern void StopFog(void);


// current haze parameters
extern bool _haze_bActive;
extern CHazeParameters _haze_hp;
extern CTexParams _haze_tpLocal;
extern uint8_t *_haze_pubTable;
extern FLOAT3D _haze_vViewPosAbs;
extern FLOAT3D _haze_vViewDirAbs;
extern float _haze_fMul;
extern float _haze_fAdd;
extern PIX _haze_pixSize;
extern uint32_t _haze_ulAlpha;
extern uint32_t _haze_ulTexture;
extern float _haze_fStart;

// start haze with given parameters
extern void StartHaze( CHazeParameters &hp, const FLOAT3D &vViewPosAbs,
                                            const FLOATmatrix3D &mAbsToView);
// stop haze
extern void StopHaze(void);


// returns lineary-interpolated fog strength in fog texture
__forceinline uint32_t GetFogAlpha( const GFXTexCoord &tex)
{
  // point sampling of height
  PIX pixT = FloatToInt( tex.t * _fog_pixSizeH);
      pixT = Clamp( pixT, 0L, _fog_pixSizeH-1L) * _fog_pixSizeL;
  // linear interpolation of depth
  const PIX pixSF = FloatToInt( tex.s*(float)_fog_pixSizeL*255.499f);
  const PIX pixS1 = Clamp( (PIX)((pixSF>>8)+0), 0L, _fog_pixSizeL-1L);
  const PIX pixS2 = Clamp( (PIX)((pixSF>>8)+1), 0L, _fog_pixSizeL-1L);
  const uint32_t ulF  = pixSF & 255;
  const uint32_t ulA1 = _fog_pubTable[pixT +pixS1];
  const uint32_t ulA2 = _fog_pubTable[pixT +pixS2];
  return ((ulA1*(ulF^255)+ulA2*ulF) * _fog_ulAlpha) >>16;
}


// check if texture coord is in fog
__forceinline bool InFog( const float fT)
{
  return (fT>_fog_fStart && fT<_fog_fEnd);
}



// returns lineary-interpolated haze strength in haze texture
__forceinline uint32_t GetHazeAlpha( const float fS)
{
  // linear interpolation of depth
  const PIX pixSH = FloatToInt( fS*(float)_haze_pixSize*255.4999f);
  const PIX pixS1 = Clamp( (PIX)((pixSH>>8)+0), 0L, _haze_pixSize-1L);
  const PIX pixS2 = Clamp( (PIX)((pixSH>>8)+1), 0L, _haze_pixSize-1L);
  const uint32_t ulH  = pixSH & 255;
  const uint32_t ulA1 = _haze_pubTable[pixS1];
  const uint32_t ulA2 = _haze_pubTable[pixS2];
  return ((ulA1*(ulH^255)+ulA2*ulH) * _haze_ulAlpha) >>16;
}


// check if texture coord is in haze
__forceinline bool InHaze( const float fS)
{
  return (fS>_haze_fStart);
}


#endif  /* include-once check. */

