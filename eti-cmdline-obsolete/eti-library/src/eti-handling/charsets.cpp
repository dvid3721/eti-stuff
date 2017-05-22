#
/*
 *    Copyright (C) 2015
 *    Jan van Katwijk (J.vanKatwijk@gmail.com)
 *    Lazy Chair Programming
 *
 *    This file is part of the eti library
 *    eti library is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    eti library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with DAB library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *	This charset handling was kindly added by Przemyslaw Wegrzyn	
 *	all rights acknowledged
 */
#include "charsets.h"
#include	<stdint.h>
/**
 * This table maps "EBU Latin" charset to corresponding
 * Unicode (UCS2-encoded) characters.
 * See ETSI TS 101 756 v1.6.1, Annex C
 */
static const unsigned short ebuLatinToUcs2[] = {
/* 0x00 - 0x07 */ 0x00,   0x01,   0x02,   0x03,   0x04,   0x05,   0x06,   0x07,
/* 0x08 - 0x0f */ 0x08,   0x09,   0x0a,   0x0b,   0x0c,   0x0d,   0x0e,   0x0f,
/* 0x10 - 0x17 */ 0x10,   0x11,   0x12,   0x13,   0x14,   0x15,   0x16,   0x17,
/* 0x18 - 0x1f */ 0x18,   0x19,   0x1a,   0x1b,   0x1c,   0x1d,   0x1e,   0x2d,

/* 0x20 - 0x27 */ 0x20,   0x21,   0x22,   0x23,   0xa4,   0x25,   0x26,   0x27,
/* 0x28 - 0x2f */ 0x28,   0x29,   0x2a,   0x2b,   0x2c,   0x2d,   0x2e,   0x2f,
/* 0x30 - 0x37 */ 0x30,   0x31,   0x32,   0x33,   0x34,   0x35,   0x36,   0x37,
/* 0x38 - 0x3f */ 0x38,   0x39,   0x3a,   0x3b,   0x3c,   0x3d,   0x3e,   0x3f,
/* 0x40 - 0x47 */ 0x40,   0x41,   0x42,   0x43,   0x44,   0x45,   0x46,   0x47,
/* 0x48 - 0x4f */ 0x48,   0x49,   0x4a,   0x4b,   0x4c,   0x4d,   0x4e,   0x4f,
/* 0x50 - 0x57 */ 0x50,   0x51,   0x52,   0x53,   0x54,   0x55,   0x56,   0x57,
/* 0x58 - 0x5f */ 0x58,   0x59,   0x5a,   0x5b,   0x5c,   0x5d,   0x2015, 0x5f,
/* 0x60 - 0x67 */ 0x2551, 0x61,   0x62,   0x63,   0x64,   0x65,   0x66,   0x67,
/* 0x68 - 0x6f */ 0x68,   0x69,   0x6a,   0x6b,   0x6c,   0x6d,   0x6e,   0x6f,
/* 0x70 - 0x77 */ 0x70,   0x71,   0x72,   0x73,   0x74,   0x75,   0x76,   0x77,
/* 0x78 - 0x7f */ 0x78,   0x79,   0x7a,   0x7b,   0x7c,   0x7d,   0xaf,   0x7f,

/* 0x80 - 0x87 */ 0xe1,   0xe0,   0xe9,   0xe8,   0xed,   0xec,   0xf3,   0xf2,
/* 0x88 - 0x8f */ 0xfa,   0xf9,   0xd1,   0xc7,   0x015e, 0xdf,   0xa1,   0x0132,
/* 0x90 - 0x97 */ 0xe2,   0xe4,   0xea,   0xeb,   0xee,   0xef,   0xf4,   0xf6,
/* 0x98 - 0x9f */ 0xfb,   0xfc,   0xf1,   0xe7,   0x015f, 0x011f, 0x0131, 0x0133,
/* 0xa0 - 0xa7 */ 0xaa,   0x03b1, 0xa9,   0x2030, 0x011e, 0x011b, 0x0148, 0x0151,
/* 0xa8 - 0xaf */ 0x03c0, 0x20ac, 0xa3,   0x24,   0x2190, 0x2191, 0x2192, 0x2193,
/* 0xb0 - 0xb7 */ 0xba,   0xb9,   0xb2,   0xb3,   0xb1,   0x0130, 0x0144, 0x0171,
/* 0xb8 - 0xbf */ 0xb5,   0xbf,   0xf7,   0xb0,   0xbc,   0xbd,   0xbe,   0xa7,
/* 0xc0 - 0xc7 */ 0xc1,   0xc0,   0xc9,   0xc8,   0xcd,   0xcc,   0xd3,   0xd2,
/* 0xc8 - 0xcf */ 0xda,   0xd9,   0x0158, 0x010c, 0x0160, 0x017d, 0xd0,   0x13f,
/* 0xd0 - 0xd7 */ 0xc2,   0xc4,   0xca,   0xcb,   0xce,   0xcf,   0xd4,   0xd6,
/* 0xd8 - 0xdf */ 0xdb,   0xdc,   0x0159, 0x010d, 0x0161, 0x017e, 0x0111, 0x0140,
/* 0xe0 - 0xe7 */ 0x00c3, 0x00c5, 0x00c6, 0x0152, 0x0177, 0xdd,   0xd5,   0xd8,
/* 0xe8 - 0xef */ 0xde,   0x014a, 0x0154, 0x0106, 0x015a, 0x0179, 0x0166, 0xf0,
/* 0xf0 - 0xf7 */ 0xe3,   0xe5,   0xe6,   0x0153, 0x0175, 0xfd,   0xf5,   0xf8,
/* 0xf8 - 0xff */ 0xfe,   0x014b, 0x0155, 0x0107, 0x015b, 0x017a, 0x0167, 0xff
};

std::string toStringUsingCharset (const char* buffer,
	                          CharacterSet charset, int size) {
uint16_t length = 0;
uint16_t i;

	return buffer;
//          if(size == -1)
//            length = strlen(buffer);
//          else
//            length = size;
//
//	switch (charset) {
//	   case UnicodeUcs2:
//	      s = QString::fromUtf16 ((const ushort*) buffer, length);
//	      break;
//
//	   case UnicodeUtf8:
//	      s = QString::fromUtf8 (buffer, length);
//	      break;
//
//	   case EbuLatin:
//	   default:
//	      s = QString();
//	      for (i = 0; i < length; i++) {
//	         s [i] = QChar (ebuLatinToUcs2 [((uint8_t*) buffer)[i]]);
//	      }
//	}
//
//	return s;
}
