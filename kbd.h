#ifndef KBD_H
#define KBD_H

extern void keyboard_install();
extern void keyboard_handler(struct regs *r);
extern char kbdus[128];
#endif
