#include "system.h"
#include "screen.h"
#include "printk.h"
#include "irq.h"

int timer_ticks = 0;


void timer_phase(uint16_t hz)
{
    uint16_t divisor = 1193180/hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}


void timer_uptime()
{
    uint16_t minutes = timer_ticks/(60);
    printk("\nKernel up For %d Seconds", minutes);
}

void timer_handler(struct regs *r)
{
    timer_ticks++;

/*    if (timer_ticks %(60) == 0)
        timer_uptime();*/
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
    timer_phase(65);
}

