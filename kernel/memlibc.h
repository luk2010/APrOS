///////////////////////////////////////////////////////////////////
/**
    @file memlibc.h
    
    Regroup every mem function.
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
#ifndef APROS_MEMLIBC_H
#define APROS_MEMLIBC_H

#include <kernel/base.h>

///////////////////////////////////////////////////////////////////
/**
 *  Copy bytes from memory area src into dest, stopping after the first 
 *  occurrence of byte c (converted to an unsigned char) is copied, 
 *  or after n bytes are copied, whichever comes first. If copying 
 *  takes place between objects that overlap, the behavior is undefined.
 *  
 *  @return A pointer to the byte after the copy of c in dest, or a null 
 *  pointer if c was not found in the first n bytes of src.
**/
///////////////////////////////////////////////////////////////////
void *memccpy(void *dst, const void *src, int c, size_t n);


#endif // APROS_MEMLIBC_H

