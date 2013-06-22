///////////////////////////////////////////////////////////////////
/**
    @file idt.h
    
    IDT functions and definitions.
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
#ifndef APROS_IDT_H
#define APROS_IDT_H

#include <kernel/base.h>

/* CPU exceptions as defined by Intel. */
#define APROS_EXCEPT_BASE 0
#define APROS_EXCEPT_NUM  32
#define APROS_EXCEPT_MAX  (APROS_EXCEPT_BASE + APROS_EXCEPT_NUM - 1)

/* IRQ lines in the IDT */
#define APROS_IRQ_BASE 0
#define APROS_IRQ_NUM  32
#define APROS_IRQ_MAX  (APROS_EXCEPT_BASE + APROS_EXCEPT_NUM - 1)

/* IDT entries */
#define APROS_IDT_NUM  256
#define APROS_IDT_MAX  APROS_IDT_NUM - 1

/* Initialize every idt entries and mark them not present. */
bool apros_setup_idt();

bool apros_idt_set_handler(int index, vaddr_t handler_adress, int lowest_privilege);
void apros_idt_get_handler(int index, vaddr_t* handler_return, int* privilege_return);

#endif // APROS_IDT_H
