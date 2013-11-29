#ifndef IRQ_H
#define IRQ_H 

extern void *irq_routines[16];
extern void irq_install();
extern void irq_install_handler(int irq, void (*handler)(struct regs *r));
extern void irq_uninstall_handler(int irq);

#endif
