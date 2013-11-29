/*  

   CLIB library function declarations

*/

#ifndef SYSTEM_H
#define SYSTEM_H

#include "system_h.h"

struct regs
{
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;    
};

#define PUNK(str) printk(str); while(1);
#define ASSERT(b)       ((b) ? (void) 0 : punk_assert (__FILE__, __LINE__, #b));

extern void *memmove(void *dest, const void *src, size_t size);
extern void *memmove(void *dest, const void *src, size_t size);
extern void *memset(void *dest, char val, size_t size);
extern uint8_t inportb(uint16_t _port);
extern void outportb (uint16_t _port, uint8_t _data);
extern size_t strlen(const char* str);
extern void *memset16(void *dest, uint16_t val, size_t size);
extern void punk_assert(const char *file, int line, char *msg);
extern void strcpy(const char *, char *);
extern int strcmp(const char *, const char *);

#endif
