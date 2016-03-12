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

#ifndef SE_INCL_COLOR_H
#define SE_INCL_COLOR_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

#include <Engine/Math/Functions.h>

// color definition constants (in CroTeam RGBA format)
#define C_BLACK     0x00000000UL
#define C_vdGRAY    0x1F1F1F00UL
#define C_dGRAY     0x3F3F3F00UL
#define C_mdGRAY    0x5F5F5F00UL
#define C_GRAY      0x7F7F7F00UL
#define C_mlGRAY    0x9F9F9F00UL
#define C_lGRAY     0xBFBFBF00UL
#define C_vlGRAY    0xDFDFDF00UL
#define C_WHITE     0xFFFFFF00UL

#define C_vdRED     0x3F000000UL
#define C_dRED      0x7F000000UL
#define C_mdRED     0xBF000000UL
#define C_RED       0xFF000000UL
#define C_mlRED     0xFF3F3F00UL
#define C_lRED      0xFF7F7F00UL
#define C_vlRED     0xFFBFBF00UL

#define C_vdGREEN   0x003F0000UL
#define C_dGREEN    0x007F0000UL
#define C_mdGREEN   0x00BF0000UL
#define C_GREEN     0x00FF0000UL
#define C_mlGREEN   0x3FFF3F00UL
#define C_lGREEN    0x7FFF7F00UL
#define C_vlGREEN   0xBFFFBF00UL

#define C_vdBLUE    0x00003F00UL
#define C_dBLUE     0x00007F00UL
#define C_mdBLUE    0x0000BF00UL
#define C_BLUE      0x0000FF00UL
#define C_mlBLUE    0x3F3FFF00UL
#define C_lBLUE     0x7F7FFF00UL
#define C_vlBLUE    0xBFBFFF00UL

#define C_vdCYAN    0x003F3F00UL
#define C_dCYAN     0x007F7F00UL
#define C_mdCYAN    0x00BFBF00UL
#define C_CYAN      0x00FFFF00UL
#define C_mlCYAN    0x3FFFFF00UL
#define C_lCYAN     0x7FFFFF00UL
#define C_vlCYAN    0xBFFFFF00UL

#define C_vdMAGENTA 0x3F003F00UL
#define C_dMAGENTA  0x7F007F00UL
#define C_mdMAGENTA 0xBF00BF00UL
#define C_MAGENTA   0xFF00FF00UL
#define C_mlMAGENTA 0xFF3FFF00UL
#define C_lMAGENTA  0xFF7FFF00UL
#define C_vlMAGENTA 0xFFBFFF00UL

#define C_vdYELLOW  0x3F3F0000UL
#define C_dYELLOW   0x7F7F0000UL
#define C_mdYELLOW  0xBFBF0000UL
#define C_YELLOW    0xFFFF0000UL
#define C_mlYELLOW  0xFFFF3F00UL
#define C_lYELLOW   0xFFFF7F00UL
#define C_vlYELLOW  0xFFFFBF00UL

#define C_vdORANGE  0x5F1F0000UL
#define C_dORANGE   0x7F3F0000UL
#define C_mdORANGE  0x9F5F0000UL
#define C_ORANGE    0xFF7F3F00UL
#define C_mlORANGE  0xFF9F5F00UL
#define C_lORANGE   0xFFBF7F00UL
#define C_vlORANGE  0xFFFF9F00UL

#define C_vdBROWN   0x3F1F0000UL
#define C_dBROWN    0x5F3F0F00UL
#define C_mdBROWN   0x7F5F1F00UL
#define C_BROWN     0x8C271700UL
#define C_mlBROWN   0xBF3F0F00UL
#define C_lBROWN    0xBF7F1F00UL
#define C_vlBROWN   0xBFBF3F00UL

#define C_vdPINK    0x9A545400UL
#define C_dPINK     0xAA646400UL
#define C_mdPINK    0xBA747400UL
#define C_PINK      0xC8787800UL
#define C_mlPINK    0xD67C7C00UL
#define C_lPINK     0xE68C8C00UL
#define C_vlPINK    0xF68C8C00UL

// CT RGBA masks and shifts
#define CT_RMASK  0xFF000000UL
#define CT_GMASK  0x00FF0000UL
#define CT_BMASK  0x0000FF00UL
#define CT_AMASK  0x000000FFUL
#define CT_RSHIFT 24
#define CT_GSHIFT 16
#define CT_BSHIFT  8
#define CT_ASHIFT  0

// reversed (OpenGL) RGBA masks and shifts
#define CT_rRMASK  0x000000FFUL
#define CT_rGMASK  0x0000FF00UL
#define CT_rBMASK  0x00FF0000UL
#define CT_rAMASK  0xFF000000UL
#define CT_rRSHIFT  0
#define CT_rGSHIFT  8
#define CT_rBSHIFT 16
#define CT_rASHIFT 24

// global factors for saturation and stuff
extern int32_t _slTexSaturation;
extern int32_t _slTexHueShift;
extern int32_t _slShdSaturation; 
extern int32_t _slShdHueShift;


// COLOR FORMAT CONVERSION ROUTINES

// convert separate R,G and B color components to CroTeam COLOR format (uint32_t type)
__forceinline COLOR RGBToColor( uint8_t const ubR, uint8_t const ubG, uint8_t const ubB) {
  return ((uint32_t)ubR<<CT_RSHIFT) | ((uint32_t)ubG<<CT_GSHIFT) | ((uint32_t)ubB<<CT_BSHIFT);
}
// convert CroTeam COLOR format to separate R,G and B color components
__forceinline void ColorToRGB( COLOR const col, uint8_t &ubR, uint8_t &ubG, uint8_t &ubB) {
  ubR = (col&CT_RMASK)>>CT_RSHIFT;
  ubG = (col&CT_GMASK)>>CT_GSHIFT;
  ubB = (col&CT_BMASK)>>CT_BSHIFT;
}
// combine CroTeam COLOR format from separate R,G and B color components
__forceinline COLOR RGBAToColor( uint8_t const ubR, uint8_t const ubG, uint8_t const ubB, uint8_t const ubA) {
  return ((uint32_t)ubR<<CT_RSHIFT) | ((uint32_t)ubG<<CT_GSHIFT)
       | ((uint32_t)ubB<<CT_BSHIFT) | ((uint32_t)ubA<<CT_ASHIFT);
}
// separate CroTeam COLOR format to R,G and B color components
__forceinline void ColorToRGBA( COLOR const col, uint8_t &ubR, uint8_t &ubG, uint8_t &ubB, uint8_t &ubA) {
  ubR = (col&CT_RMASK)>>CT_RSHIFT;
  ubG = (col&CT_GMASK)>>CT_GSHIFT;
  ubB = (col&CT_BMASK)>>CT_BSHIFT;
  ubA = (col&CT_AMASK)>>CT_ASHIFT;
}

// convert HSV components to CroTeam COLOR format
ENGINE_API extern COLOR HSVToColor( uint8_t const ubH, uint8_t const ubS, uint8_t const ubV);
// convert CroTeam COLOR format to HSV components
ENGINE_API extern void  ColorToHSV( COLOR const colSrc, uint8_t &ubH, uint8_t &ubS, uint8_t &ubV);

// convert HSVA components to CroTeam COLOR format
__forceinline COLOR HSVAToColor( uint8_t const ubH, uint8_t const ubS, uint8_t const ubV, uint8_t const ubA) {
  return HSVToColor( ubH,ubS,ubV) | ((uint32_t)ubA<<CT_ASHIFT);
}
// convert CroTeam COLOR format to HSVA components
__forceinline void ColorToHSVA( COLOR const colSrc, uint8_t &ubH, uint8_t &ubS, uint8_t &ubV, uint8_t &ubA) {
  ColorToHSV( colSrc, ubH,ubS,ubV);
  ubA = (colSrc&CT_AMASK)>>CT_ASHIFT;
}

// is color gray, black or white?
ENGINE_API extern BOOL IsGray(  COLOR const col);
ENGINE_API extern BOOL IsBlack( COLOR const col);
ENGINE_API extern BOOL IsWhite( COLOR const col);

// find corresponding desaturated color (it's not same as gray!)
ENGINE_API extern COLOR DesaturateColor( COLOR const col);

// is color1 bigger than color2 (gray comparison)
ENGINE_API extern BOOL IsBigger( COLOR const col1, COLOR const col2);
// has color same hue and saturation (with little tolerance) ?
ENGINE_API extern BOOL CompareChroma( COLOR col1, COLOR col2);

// adjust color saturation and/or hue (hue shift in 0-255 range!)
ENGINE_API extern COLOR AdjustColor( COLOR const col, int32_t const slHueShift, int32_t const slSaturation);
ENGINE_API extern COLOR AdjustGamma( COLOR const col, float const fGamma);
// color lerping functions
ENGINE_API extern COLOR LerpColor( COLOR col0, COLOR col1, float fRatio);
ENGINE_API extern void  LerpColor( COLOR col0, COLOR col1, float fRatio, uint8_t &ubR, uint8_t &ubG, uint8_t &ubB);

// some fast color manipulation functions
ENGINE_API extern COLOR MulColors( COLOR col1, COLOR col2); // fast color multiply function - RES = 1ST * 2ND /255
ENGINE_API extern COLOR AddColors( COLOR col1, COLOR col2); // fast color additon function - RES = clamp (1ST + 2ND)



// converts colors between Croteam, OpenGL and DirectX

__forceinline uint32_t ByteSwap( uint32_t ul)
{
/* rcg10052001 Platform-wrappers. */
	return( ((ul << 24)            ) |
            ((ul << 8) & 0x00FF0000) |
            ((ul >> 8) & 0x0000FF00) |
            ((ul >> 24)            ) );

}

__forceinline uint32_t rgba2argb( COLOR col)
{
	return( (col << 24) | (col >> 8) );
}

__forceinline uint32_t abgr2argb( uint32_t ul)
{
	// this could be simplified, this is just a safe conversion from asm code
	ul = ( ((ul << 24)            ) |
         ((ul << 8) & 0x00FF0000) |
         ((ul >> 8) & 0x0000FF00) |
         ((ul >> 24)            ) );
	return( (ul << 24) | (ul >> 8) );
}


// multiple conversion from OpenGL color to DirectX color
extern void abgr2argb( uint32_t *pulSrc, uint32_t *pulDst, INDEX ct);


// fast memory copy of uint32_ts
inline void CopyLongs( uint32_t *pulSrc, uint32_t *pulDst, INDEX ctLongs)
{
  memcpy( pulDst, pulSrc, ctLongs*4);
}


// fast memory set of uint32_ts
inline void StoreLongs( uint32_t ulVal, uint32_t *pulDst, INDEX ctLongs)
{
  for( INDEX i=0; i<ctLongs; i++) pulDst[i] = ulVal;
}


#endif  /* include-once check. */
