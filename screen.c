
#include "system.h"
#include "screen.h"

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 24;

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;

uint8_t make_color(enum vga_color fg, enum vga_color bg)
{
	return fg | bg << 4;
}
 
uint16_t make_vgaentry(char c, uint8_t color)
{
	uint16_t c16 = c;
	uint16_t color16 = color;
	return c16 | color16 << 8;
}

void terminal_setcursor()
{
    uint16_t temp;
    temp = terminal_column + terminal_row * VGA_WIDTH;
    outportb(0x3D4, 14);
    outportb(0x3D5, temp >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, temp);
}

void terminal_initialize()
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = make_color(COLOR_LIGHT_GREY, COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for ( size_t y = 0; y < VGA_HEIGHT; y++ )
	{
		for ( size_t x = 0; x < VGA_WIDTH; x++ )
		{
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = make_vgaentry(' ', terminal_color);
		}
	}
    size_t temp = 24 * 80 + 0;
    uint16_t tval = make_vgaentry(' ', make_color(COLOR_BLUE, COLOR_BLUE));
    memset16(terminal_buffer + temp, tval, 80);


}

void terminal_return()
{
    if (terminal_column >= VGA_WIDTH)
    {
        terminal_column = 0;
        terminal_row += 1;
    }
}

void terminal_scroll()
{
    if(terminal_row >= VGA_HEIGHT)
    {
        memmove(terminal_buffer, terminal_buffer + VGA_WIDTH, (VGA_HEIGHT-1) * VGA_WIDTH * sizeof(uint16_t));
        terminal_row = VGA_HEIGHT-1;
        uint16_t tval = make_vgaentry(' ', terminal_color);
        memset16(terminal_buffer + VGA_WIDTH*terminal_row, tval, 80);
    }
}

void terminal_setcolor(uint8_t color)
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y)
{
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = make_vgaentry(c, color);
}
 
void terminal_putchar(char c)
{
    
	if(c == '\n')
	{
	   terminal_column = 0;	   
       terminal_row += 1;
	}
    else if(c == '\t')
    {
        terminal_column += 3;
    }
    else if(c == '\b')
    {
        terminal_column -= 1;
        terminal_putentryat(' ', terminal_color, terminal_column, terminal_row);
    }
	else
	{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
    terminal_column += 1;
	}
    terminal_return();
    terminal_scroll();
    terminal_setcursor();	
}

void terminal_putnum(uint64_t n)
{
    uint8_t r;
    while(n)
    {
        r = n%10;
        terminal_putchar((char)r+'0');
        n /= 10;
    }
}
 
void terminal_writestring(const char* data)
{
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putchar(data[i]);
}

void terminal_drawcircle(uint8_t x0, uint8_t y0, uint8_t _rad)
{
  int x = _rad, y = 0;
  int radiusError = 1-x;
  int color = make_color(COLOR_BLUE, COLOR_BLUE);
 
  while(x >= y)
  {
    terminal_putentryat(' ', color, x + x0, y + y0);
    terminal_putentryat(' ', color, y + x0, x + y0);
    terminal_putentryat(' ', color, -x + x0, y + y0);
    terminal_putentryat(' ', color, -y + x0, x + y0);
    terminal_putentryat(' ', color, -x + x0, -y + y0);
    terminal_putentryat(' ', color, -y + x0, -x + y0);
    terminal_putentryat(' ', color, x + x0, -y + y0);
    terminal_putentryat(' ', color, y + x0, -x + y0);
 
    y++;
        if(radiusError<0)
                radiusError+=2*y+1;
        else
        {
                x--;
                radiusError+=2*(y-x+1);
        }
  }	
	

}

void terminal_welcome()
{
	size_t rad = 7;

	size_t i = 0;
	for(i=0; i<rad; i++)
	{
		terminal_drawcircle(40, 10, i);		
	}
	size_t color = make_color(COLOR_RED, COLOR_BLUE);
	const char *data = "Welcome to MyOs";
	size_t datalen = strlen(data);
	for ( size_t i = 0; i < datalen; i++ )
		terminal_putentryat(data[i], color, 33+i, 1);
    terminal_column = 0;
    terminal_row = 18;
    terminal_setcursor();
}


void terminal_clear()
{
    size_t i = 0;
    for(; i < VGA_HEIGHT; i++)
        memset16(terminal_buffer + i * VGA_WIDTH, make_vgaentry(' ', terminal_color), VGA_WIDTH);

    terminal_column = 0;
    terminal_row = 0;
    terminal_setcursor();
}




