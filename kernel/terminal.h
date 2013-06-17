///////////////////////////////////////////////////////////////////
/**
    @file terminal.h
    
    Describes some terminal functions to print on screen
    informations.
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

#ifndef APROS_TERMINAL_H
#define APROS_TERMINAL_H

#include <kernel/base.h>

///////////////////////////////////////////////////////////////////
/** 
    Hardware text mode color constants. 
**/
///////////////////////////////////////////////////////////////////
enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

///////////////////////////////////////////////////////////////////
/** 
    Make color from background and foreground.
    @param fg : Foreground color.
    @param bg : Background color.
    @return Standard terminal color.
**/
///////////////////////////////////////////////////////////////////
uint8_t make_color(enum vga_color fg, enum vga_color bg);

///////////////////////////////////////////////////////////////////
/** 
    Make VGA character from Ascii and VGA color.
    @param c : ASCII character.
    @param color : VGA color.
    @return Standard VGA entry.
**/
///////////////////////////////////////////////////////////////////
uint16_t make_vgaentry(char c, uint8_t color);

///////////////////////////////////////////////////////////////////
/**
    Initialize terminal screen.
    @note Same as terminal_clear.
**/
///////////////////////////////////////////////////////////////////
void terminal_initialize();

///////////////////////////////////////////////////////////////////
/**
    Clear terminal screen.
    @note Same as terminal_initialize.
**/
///////////////////////////////////////////////////////////////////
void terminal_clear();

///////////////////////////////////////////////////////////////////
/**
    Change the current color writing.
    @param color : Current color activated.
**/
///////////////////////////////////////////////////////////////////
void terminal_setcolor(uint8_t color);

///////////////////////////////////////////////////////////////////
/**
    Set the entry at given position.
    @param c : Ascii character.
    @param color : Color to activate.
    @param x : Line to write.
    @param y : Column to write.
**/
///////////////////////////////////////////////////////////////////
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);

///////////////////////////////////////////////////////////////////
/**
    Add a character to the temrinal.
    @param c : Ascii character to put. Color is set by 
    terminal_setcolor.
**/
///////////////////////////////////////////////////////////////////
void terminal_putchar(char c);

///////////////////////////////////////////////////////////////////
/**
    Write a null-terminated string on the terminal.
    @param data : Ascii null-terminated string. Color is set by 
    terminal_setcolor.
**/
///////////////////////////////////////////////////////////////////
void terminal_writestring(const char* data);

///////////////////////////////////////////////////////////////////
/**
    Write a NULL-terminated string on the terminal screen.
**/
///////////////////////////////////////////////////////////////////
void terminal_printf(const char* format, ...);


#endif
