.set ALIGN,	1<<0
.set MEMINFO,	1<<1
.set FLAGS,	ALIGN | MEMINFO
.set MAGIC,	0x1BADB002
.set CHECKSUM,	-(MAGIC + FLAGS)

.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.section .bootstrap_stack
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

.section .text
.global _start

_start:
	movl $stack_top, %esp
	call kernel_main
	cli
    
hang:
	hlt
	jmp hang

.global gdt_flush
.extern gp
gdt_flush:
    lgdt gp
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    ljmp $0x08, $flush2

flush2:
    ret    

.global idt_load
idt_load:
    lidt idtp
    ret
        
.global isr0
.global isr1
.global isr2
.global isr3
.global isr4
.global isr5
.global isr6
.global isr7
.global isr8
.global isr9
.global isr10
.global isr11
.global isr12
.global isr13
.global isr14
.global isr15
.global isr16
.global isr17
.global isr18
.global isr19
.global isr20
.global isr21
.global isr22
.global isr23
.global isr24
.global isr25
.global isr26
.global isr27
.global isr28
.global isr29
.global isr30
.global isr31

isr0:
   cli
   push $0
   push $0
   jmp isr_common_stub

isr1:
   cli
   push $0
   push $1
   jmp isr_common_stub

isr2:
   cli
   push $0
   push $2
   jmp isr_common_stub

isr3:
   cli
   push $0
   push $3
   jmp isr_common_stub

isr4:
   cli
   push $0
   push $4
   jmp isr_common_stub

isr5:
   cli
   push $0
   push $5  
   jmp isr_common_stub

isr6:
   cli
   push $0
   push $6  
   jmp isr_common_stub

isr7:
   cli
   push $0
   push $7  
   jmp isr_common_stub

isr8:
   cli
   push $8  
   jmp isr_common_stub

isr9:
   cli
   push $0
   push $9  
   jmp isr_common_stub

isr10:
   cli
   push $10  
   jmp isr_common_stub 

isr11:
   cli
   push $11  
   jmp isr_common_stub

isr12:
   cli
   push $12  
   jmp isr_common_stub
 
isr13:
   cli
   push $13  
   jmp isr_common_stub

isr14:
   cli
   push $14  
   jmp isr_common_stub
 
isr15:
   cli
   push $0
   push $15  
   jmp isr_common_stub

isr16:
   cli
   push $0
   push $16  
   jmp isr_common_stub
 
isr17:
   cli
   push $0
   push $17  
   jmp isr_common_stub

isr18:
   cli
   push $0
   push $18  
   jmp isr_common_stub
 
isr19:
   cli
   push $0
   push $19  
   jmp isr_common_stub

isr20:
   cli
   push $0
   push $20  
   jmp isr_common_stub

isr21:
   cli
   push $0
   push $21  
   jmp isr_common_stub
 
isr22:
   cli
   push $0
   push $22  
   jmp isr_common_stub

isr23:
   cli
   push $0
   push $23  
   jmp isr_common_stub

isr24:
   cli
   push $0
   push $24  
   jmp isr_common_stub

isr25:
   cli
   push $0
   push $25  
   jmp isr_common_stub

isr26:
   cli
   push $0
   push $26  
   jmp isr_common_stub

isr27:
   cli
   push $0
   push $27  
   jmp isr_common_stub

isr28:
   cli
   push $0
   push $28  
   jmp isr_common_stub

isr29:
   cli
   push $0
   push $29  
   jmp isr_common_stub
 
isr30:
   cli
   push $0
   push $30  
   jmp isr_common_stub

isr31:
   cli
   push $0
   push $31      
   jmp isr_common_stub


.extern fault_handler

isr_common_stub :
    pusha 
    push %ds
    push %es
    push %fs
    push %gs
    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax
    push %eax
    mov $fault_handler, %eax
    call *%eax
    pop %eax
    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $0x8, %esp
    iret

.global irq0
.global irq1
.global irq2
.global irq3
.global irq4
.global irq5
.global irq6
.global irq7
.global irq8
.global irq9
.global irq10
.global irq11
.global irq12
.global irq13
.global irq14
.global irq15

irq0:
    cli
    push  $0
    push  $32
    jmp irq_common_stub

irq1:
    cli
    push  $0
    push  $33
    jmp irq_common_stub

irq2:
    cli
    push  $0
    push  $34
    jmp irq_common_stub

irq3:
    cli
    push  $0x0
    push  $35
    jmp irq_common_stub

irq4:
    cli
    push  $0x0
    push  $36
    jmp irq_common_stub

irq5:
    cli
    push  $0x0
    push  $37
    jmp irq_common_stub

irq6:
    cli
    push  $0x0
    push  $38
    jmp irq_common_stub

irq7:
    cli
    push  $0x0
    push  $39
    jmp irq_common_stub

irq8:
    cli
    push  $0x0
    push  $40
    jmp irq_common_stub

irq9:
    cli
    push  $0x0
    push  $41
    jmp irq_common_stub

irq10:
    cli
    push  $0x0
    push  $42
    jmp irq_common_stub

irq11:
    cli
    push  $0x0
    push  $43
    jmp irq_common_stub

irq12:
    cli
    push  $0x0
    push  $44
    jmp irq_common_stub

irq13:
    cli
    push  $0x0
    push  $45
    jmp irq_common_stub

irq14:
    cli
    push  $0x0
    push  $46
    jmp irq_common_stub

irq15:
    cli
    push  $0x0
    push  $47
    jmp irq_common_stub

.extern irq_handler

irq_common_stub:
    pusha
    push %ds
    push %es
    push %fs
    push %gs

    mov $0x10, %ax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %esp, %eax

    push %eax
    mov $irq_handler, %eax
    call *%eax
    pop %eax

    pop %gs
    pop %fs
    pop %es
    pop %ds
    popa
    add $0x8, %esp
    iret
