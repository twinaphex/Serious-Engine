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

#ifndef SE_INCL_WAVE_H
#define SE_INCL_WAVE_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

/*
 *  PCM Wave Input
 */
class PCMWaveInput {
private:
  // Wave data
  WAVEFORMATEX pwi_wfeWave;
  WAVEFORMATEX pwi_wfeDesired;
  uint32_t  pwi_ulRiffLength, pwi_ulDataLength;
  BOOL   pwi_bInfoLoaded,  pwi_bDataLoaded; // Status
  SWORD *pwi_pswMemory; // Memory

  /* Conversion */
  DOUBLE pwi_dRatio;
  // get and store data
  inline uint32_t GetData_t( CTStream *pCstrInput);
  inline void  StoreData( uint32_t ulData);
  void CopyData_t(   CTStream *pCstrInput);
  void ShrinkData_t( CTStream *pCstrInput);

public:
  // Check wave format
  static void CheckWaveFormat_t( WAVEFORMATEX SwfeCheck, char *pcErrorString);

  /* Constructor */
  inline PCMWaveInput(void) { pwi_bInfoLoaded = FALSE; pwi_bDataLoaded = FALSE; };
  /* Load Wave info */
  WAVEFORMATEX LoadInfo_t( CTStream *pCstrInput);
  /* Load and convert Wave data */
  void LoadData_t( CTStream *pCstrInput, SWORD *pswMemory, WAVEFORMATEX &SwfeDesired);

  /* Length in bytes / blocks / seconds */
  uint32_t  GetByteLength(void);
  uint32_t  GetDataLength(void);
  uint32_t  GetDataLength( WAVEFORMATEX SwfeDesired);
  DOUBLE GetSecondsLength(void);

  /* Buffer length in bytes */
  uint32_t DetermineBufferSize(void);
  uint32_t DetermineBufferSize( WAVEFORMATEX SwfeDesired);
};



#endif  /* include-once check. */

