#ifndef IDT_H
#define IDT_H


struct idt_entry
{
    uint16_t base_lo;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

extern struct idt_entry idt[256];
extern struct idt_ptr idtp;

extern void idt_load();
extern void idt_install();
extern void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint8_t flags);

#endif

