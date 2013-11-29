
#include "system.h"
#include "screen.h"
#include "gdt.h"
#include "idt.h"
#include "isrs.h"
#include "irq.h"
#include "timer.h"
#include "kbd.h"
#include "printk.h"
#include "paging.h"
#include "shell.h"
 
/* Check if the compiler thinks if we are targeting the wrong operating system. */
/*#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 */
#if defined(__cplusplus)
extern "C" /* Use C linkage for kernel_main. */
#endif

extern void irq1();
extern void keyboard_install();
volatile int zer = 0;
void kernel_main()
{

	terminal_initialize();
    gdt_install();
    idt_install();    
    isrs_install();
    irq_install(); 
    terminal_welcome();
    __asm__ __volatile__ ("sti");
    timer_install();
    keyboard_install();
//    init_paging();

    printk("Welcome to the Pre-Alpha phase of the MyOS ###");
    //printk("Welcome to the Pre-Alpha phase of the MyOS ###!@#$^&*()_{}:?><");

    duplicate_shell();
    
    while(1);

}

