#ifndef GDT_H
#define GDT_H


struct gdt_entry
{

uint16_t limit_low;
uint16_t base_low;
uint8_t base_middle;
uint8_t access;
uint8_t granularity;
uint8_t base_high;

} __attribute__((packed));

struct gdt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));


extern struct gdt_entry gdt[3];
extern struct gdt_ptr gp;

extern void gdt_flush();
extern void gdt_set_gate(int num, uint64_t base, uint64_t limit, uint8_t access, uint8_t gran);
extern void gdt_install();

#endif
