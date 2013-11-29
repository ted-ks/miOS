#include "system.h"
#include "printk.h"


void *memmove(void *dest, const void *src, size_t size)
{

	const char *src8;
	char *dest8;

	src8 = (const char *)src;
	dest8 = (char *)dest;
	
	while(size--)
	{
	   *dest8++ = *src8++;
	}
	return dest;	
}

int strcmp(const char *a, const char *b)
{
int c = 0;
 
   while( a[c] == b[c] )
   {
      if( a[c] == '\0' || b[c] == '\0' )
         break;
      c++;
   }
   if( a[c] == '\0' && b[c] == '\0' )
      return 0;
   else
      return -1;
}

void strcpy(const char *src, char *dest)
{
   int i=0;
   while(src[i]!= '\0')
   { 
	dest[i] = src[i];
        i++;
   }  
}

void *memset16(void *dest, uint16_t val, size_t size)
{
    uint16_t *temp = (uint16_t *)dest;
    while(size--)
        *temp++ = val;
    return dest;

}

size_t strlen(const char* str)
{
	size_t ret = 0;
	while ( str[ret] != 0 )
		ret++;
	return ret;
}

void *memset(void *dest, char val, size_t size)
{
    char *temp = (char *)dest;
    while(size--)
        *temp++ = val;
    return dest;      
} 

uint8_t inportb(uint16_t _port)
{
    uint8_t rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}

void outportb (uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

void punk_assert(const char *file, int line, char *msg)
{

printk("ASSERTION-FAILED: %S:%d : %s\n", file, line, msg); while(1);
}
