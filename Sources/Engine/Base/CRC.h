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

#ifndef SE_INCL_CRC_H
#define SE_INCL_CRC_H
#ifdef PRAGMA_ONCE
  #pragma once
#endif

extern ENGINE_API uint32_t crc_aulCRCTable[256];

// begin crc calculation
inline void CRC_Start(uint32_t &ulCRC) { ulCRC = 0xFFFFFFFF; };

// add data to a crc value
inline void CRC_AddBYTE( uint32_t &ulCRC, uint8_t ub)
{
  ulCRC = (ulCRC>>8)^crc_aulCRCTable[(uint8_t)(ulCRC)^ub];
};

inline void CRC_AddWORD( uint32_t &ulCRC, uint8_t uw)
{
  CRC_AddBYTE(ulCRC, (uint8_t)(uw>> 8));
  CRC_AddBYTE(ulCRC, (uint8_t)(uw>> 0));
};

inline void CRC_AddLONG( uint32_t &ulCRC, uint32_t ul)
{
  CRC_AddBYTE(ulCRC, (uint8_t)(ul>>24));
  CRC_AddBYTE(ulCRC, (uint8_t)(ul>>16));
  CRC_AddBYTE(ulCRC, (uint8_t)(ul>> 8));
  CRC_AddBYTE(ulCRC, (uint8_t)(ul>> 0));
};

inline void CRC_AddFLOAT(uint32_t &ulCRC, FLOAT f)
{
  CRC_AddLONG(ulCRC, *(uint32_t*)&f);
};

// add memory block to a CRC value
inline void CRC_AddBlock(uint32_t &ulCRC, uint8_t *pubBlock, uint32_t ulSize)
{
  for( INDEX i=0; i<ulSize; i++) CRC_AddBYTE( ulCRC, pubBlock[i]);
};

// end crc calculation
inline void CRC_Finish(uint32_t &ulCRC) { ulCRC ^= 0xFFFFFFFF; };

#endif  /* include-once check. */

