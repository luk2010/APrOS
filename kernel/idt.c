///////////////////////////////////////////////////////////////////
/**
    @file idt.c
    
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
#include <kernel/segment.h>
#include <kernel/idt.h>

/**
 * An entry in the IDT, or "IDTE" in the following, ie a reference to
 * a interrupt/trap routine or a task gate to handle the sw/hw
 * interrupts and exceptions.
 *
 * @see figure 5-2, intel x86 doc, vol 3
 */
struct x86_idt_entry
{
  /* Low dword */
  uint16_t offset_low;  /* 15..0, offset of the routine in the segment */
  uint16_t seg_sel;     /* 31..16, the ID of the segment */

  /* High dword */
  uint8_t reserved:5;   /* 4..0 */
  uint8_t flags:3;      /* 7..5 */
  uint8_t type:3;       /* 10..8 (interrupt gate, trap gate...) */
  uint8_t op_size:1;    /* 11 (0=16bits instructions, 1=32bits instr.) */
  uint8_t zero:1;       /* 12 */
  uint8_t dpl:2;        /* 14..13 */
  uint8_t present:1;    /* 15 */
  uint16_t offset_high; /* 31..16 */
} __attribute__((packed));


/**
 * The IDT register, which stores the address and size of the
 * IDT.
 *
 * @see Intel x86 doc vol 3, section 2.4, figure 2-4
 */
struct x86_idt_register
{
  /* The maximum IDT offset allowed to access an entry in the IDT */
  uint16_t  limit;

  /* This is not exactly a "virtual" address, ie an adddress such as
     those of instructions and data; this is a "linear" address, ie an
     address in the paged memory. However, in SOS we configure the
     segmented memory as a "flat" space: the 0-4GB segment-based (ie
     "virtual") addresses directly map to the 0-4GB paged memory (ie
     "linear"), so that the "linear" addresses are numerically equal
     to the "virtual" addresses: this base_addr will thus be the same
     as the address of the gdt array */
  uint32_t base_addr;
} __attribute__((packed, aligned (8)));


static struct x86_idt_entry    idt[APROS_IDT_NUM];

bool apros_setup_idt()
{
	struct x86_idt_register idtr;
    int i;
    
    for(i = 0; i < APROS_IDT_NUM; ++i)
    {
		struct x86_idt_entry* idte = idt + i;
		
		/* Setup an empty IDTE interrupt gate, see figure 5-2 in Intel
	 x86 doc, vol 3 */
		idte->seg_sel	= APROS_BUILD_SEGMENT_REG_VALUE(0, 0, APROS_SEG_KCODE);
		idte->reserved	= 0;
		idte->flags 	= 0;
		idte->type		= 0x6; /* Interrupt gate. */
		idte->op_size	= 1; /* 32 bits instructions. */
		idte->zero		= 0;
		
		// Disable this entry for now.
		apros_idt_set_handler(i, (vaddr_t) NULL, 0);	 
	}
	
	idtr.base_addr	= (uint32_t) idt;
	idtr.limit 		= sizeof(idt) - 1;
	
	/* Commit the IDT into CPU. */
	asm volatile ("lidt %0\n"::"m"(idtr):"memory");
	
	return true;
}

bool apros_idt_set_handler(int index, vaddr_t handler_adress, int lowest_privilege)
{
	struct x86_idt_entry* idte;
	
	if (!is_in_range(index, 0, APROS_IDT_NUM) || !(is_in_range(lowest_privilege, 0, 3)))
		return false;
		
	idte = idt + index;
	if(handler_adress != (vaddr_t) NULL)
	{
		idte->offset_low	= handler_adress & 0xffff;
		idte->offset_high	= (handler_adress >> 16) & 0xffff;
		idte->dpl			= lowest_privilege;
		idte->present		= 1;
	}
	else /* Disable this IDT entry */
    {
		idte->offset_low  = 0;
		idte->offset_high = 0;
		idte->dpl         = 0;
		idte->present     = 0;   /* No, there is no handler */
    }
    
    return true;
}

void apros_idt_get_handler(int index, vaddr_t* handler_return, int* privilege_return)
{
	if(is_in_range(index, 0, APROS_IDT_MAX))
		return;
		
	if(handler_return != NULL)
	{
		*handler_return = idt[index].offset_low | (idt[index].offset_high << 16);
	}
	if(privilege_return != NULL)
	{
		*privilege_return = idt[index].dpl;
	}
}

