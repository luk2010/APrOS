///////////////////////////////////////////////////////////////////
/**
    @file strlib.c
    
    Regroup every str function.
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

#include <kernel/strlib.h>

size_t strlen(const char *s)
{
	const char *ss = s;
	while (*ss)
		ss++;
	return ss - s;
}

int vsnprintf(char *buff, size_t len, const char * format, va_list ap)
{
  size_t i, result;
  
  if (!buff || !format)
    return -1;
  
#define PUTCHAR(thechar) \
  do { \
    if (result < len-1) \
      *buff++ = (thechar);  \
    result++; \
  } while (0)
  
  result = 0;
  for(i=0 ; format[i] != '\0' ; i++){
    switch (format[i])
      {
      case '%':
	i++;
	switch(format[i])
	  {
	  case '%':
	    {
	      PUTCHAR('%');
	      break;
	    }
	  case 'i':;
	  case 'd':
	    {
	      int integer = va_arg(ap,int);
	      int cpt2 = 0;
	      char buff_int[16];
	      
	      if (integer<0)
		PUTCHAR('-');
	      /* Ne fait pas integer = -integer ici parce que INT_MIN
		 n'a pas d'equivalent positif (int = [-2^31, 2^31-1]) */
	      
	      do {
		int m10 = integer%10;
		m10 = (m10 < 0)? -m10:m10;
		buff_int[cpt2++]=(char)('0'+ m10);
		integer=integer/10;
	      } while(integer!=0);
	      
	      for(cpt2 = cpt2 - 1 ; cpt2 >= 0 ; cpt2--)
		PUTCHAR(buff_int[cpt2]);
	      
	      break;
	    }
	    
	  case 'c':
	    {
	      int value = va_arg(ap,int);
	      PUTCHAR((char)value);
	      break;
	    }
	    
	  case 's':
	    {
	      char *string = va_arg(ap,char *);
	      if (! string)
		string = "(null)";
	      for( ; *string != '\0' ; string++)
		PUTCHAR(*string);
	      break;
	    }

	  case 'x':
	    {
	      unsigned int hexa = va_arg(ap,int);
	      unsigned int nb;
	      int i, had_nonzero = 0;
	      for(i=0 ; i < 8 ; i++)
		{
		  nb = (unsigned int)(hexa << (i*4));
		  nb = (nb >> 28) & 0xf;
		  // Skip the leading zeros
		  if (nb == 0)
		    {
		      if (had_nonzero)
			PUTCHAR('0');
		    }
		  else
		    {
		      had_nonzero = 1;
		      if (nb < 10)
			PUTCHAR('0'+nb);
		      else
			PUTCHAR('a'+(nb-10));
		    }
		}
	      if (! had_nonzero)
		PUTCHAR('0');
	      break;
	    }
	    break;
	
	  default:
            PUTCHAR('%');
	    PUTCHAR(format[i]);
	  }
	break;
	
      default:
        PUTCHAR(format[i]);
      }
  }
  
  *buff = '\0';
  return result;
}

