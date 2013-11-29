#include "printk.h"
#include "system.h"
#include "screen.h"

#include <stdarg.h>

static char buffer[1024] = {-1};
static uint32_t ptr = 0;

static void parse_num(uint32_t value, uint16_t base)
{
    uint32_t n = value/base;
    int r = value % base;
    if(r<0)
    {
        r += base;
        --n;
    }

    if(value >= base)
        parse_num(n, base);

    buffer[ptr++] = "0123456789"[r];     

}

static void parse_hex(uint32_t value)
{
    uint8_t i = 8;
    buffer[ptr++] = '0';buffer[ptr++] = 'x';
    while(i--)
    {
        buffer[ptr++] = "0123456789abcdef"[value>>(i*4)&0xF];
    }
}


void printk(const char *format, ...)
{
    int i = 0;
    ptr = 0;
    char *s;
    va_list ap;
    va_start(ap, format);

    for(;format[i];i++)
    {
        if(format[i] != '%' && format[i] != '\\')
        {
            buffer[ptr++] = format[i];
            continue;
        }
	else if(format[i] == '\\')
    {
        i++;
        switch(format[i])
        {
            case 't' : buffer[ptr++] = '\t'; break;
            case 'n' : buffer[ptr++] = '\n'; break;
            default  : buffer[ptr++] = '\\'; break;
        }
    }
	
        else if(format[i] == '%')
        {
            i++;
            switch(format[i])
            {
                case 'd' : parse_num((unsigned)va_arg(ap, int), 10); break;
                case '%' : buffer[ptr++] = '%'; break;
                case 'x' : parse_hex((unsigned)va_arg(ap, int)); break;
                case 's' : 
                           s = (char *)va_arg(ap, char *);
                           while(*s)
                               buffer[ptr++] = *s++;
                           break;
                default  : buffer[ptr++] = format[i]; break;
            }
        }
    }

    buffer[ptr] = '\0';
    va_end(ap);
    terminal_writestring(buffer);
}

