///////////////////////////////////////////////////////////////////
/**
    @file segment.h
    
    Global and local (GDT/LDT) segment descriptor definition and
    structure. These segments map virtual addresses (ie
    data/instruction addresses, relative to these segment descriptors)
    to linear addresses (ie addresses in the paged-memory space).
**/
///////////////////////////////////////////////////////////////////
/* Copyright (C) 2013, Luk2010

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307,
   USA. 
*/
#ifndef APROS_SEGMENT_H
#define APROS_SEGMENT_H

#include <kernel/base.h>

#define APROS_SEG_NULL 0
#define APROS_SEG_KCODE 1 /* Kernel code segment. */
#define APROS_SEG_KDATA 2 /* kernel data segment. */

/**
 * Helper macro that builds a segment register's value
 */
#define APROS_BUILD_SEGMENT_REG_VALUE(desc_privilege,in_ldt,seg_index) \
  (  (((desc_privilege) & 0x3)  << 0) \
   | (((in_ldt)?1:0)            << 2) \
   | ((seg_index)               << 3) )

#endif // APROS_SEGMENT_H
