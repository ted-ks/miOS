CC=i586-elf-gcc
LN=i586-elf-ld
AS=i586-elf-as
OBJ=build

CFLAGS=-ffreestanding -O2 -Wall -Wextra -c -std=gnu99 -Wno-cpp -I. -I./include/ 

CFLAGSL=-ffreestanding -O2 -nostdlib -lgcc

myos.bin : kbd.o gdt.o idt.o isrs.o irq.o printk.o kernel.o kheap.o paging.o clib.o ordered_array.o screen.o timer.o boot.o shell.o ds.o linker.ld
	   $(CC) -T linker.ld *.o $(CFLAGSL) -o myos.bin

kernel.o : kernel.c *.h
	   $(CC) $(CFLAGS) kernel.c -o kernel.o

clib.o   : clib.c *.h
	   $(CC) $(CFLAGS) clib.c -o clib.o

screen.o : screen.c *.h
	   $(CC) $(CFLAGS) screen.c -o screen.o

ds.o   : ds.c *.h
	   $(CC) $(CFLAGS) ds.c -o ds.o

printk.o : printk.c *.h
	   $(CC) $(CFLAGS) printk.c -o printk.o

gdt.o    : gdt.c *.h
	   $(CC) $(CFLAGS) gdt.c -o gdt.o

paging.o : ./mem/paging.c *.h
	   $(CC) $(CFLAGS) ./mem/paging.c -o paging.o

idt.o    : idt.c *.h
	   $(CC) $(CFLAGS) idt.c -o idt.o

kbd.o    : kbd.c *.h
	   $(CC) $(CFLAGS) kbd.c -o kbd.o

isrs.o   : isrs.c *.h
	   $(CC) $(CFLAGS) isrs.c -o isrs.o

shell.o   : shell.c *.h
	   $(CC) $(CFLAGS) shell.c -o shell.o

irq.o   : irq.c *.h
	   $(CC) $(CFLAGS) irq.c -o irq.o

timer.o : timer.c *.h
	   $(CC) $(CFLAGS) timer.c -o timer.o

kheap.o : ./mem/kheap.c *.h
	   $(CC) $(CFLAGS) ./mem/kheap.c -o kheap.o

ordered_array.o : ./utils/ordered_map.c *.h
	   $(CC) $(CFLAGS) ./utils/ordered_map.c -o ordered_array.o

boot.o	 : boot.s
	   $(AS) boot.s -o boot.o
       

clean	 : *.o
	   rm -rf *.o
