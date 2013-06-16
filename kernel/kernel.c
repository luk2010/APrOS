/**
    @file kernel.cpp
    Describe the main kernel procedure.
**/

#include <kernel/base.h>
#include <kernel/terminal.h>
 
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif
void kernel_main()
{
	terminal_initialize();
	/* Since there is no support for newlines in terminal_putchar yet, \n will
	   produce some VGA specific character instead. This is normal. */
	terminal_writestring("Hello, kernel World!\n");
}
