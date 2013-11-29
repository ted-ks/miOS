#ifndef SCREEN_H
#define SCREEN_H 

#include "screen_h.h"

/* Hardware text mode color constants. */
enum vga_color
{
	COLOR_BLACK = 0,
	COLOR_BLUE = 1,
	COLOR_GREEN = 2,
	COLOR_CYAN = 3,
	COLOR_RED = 4,
	COLOR_MAGENTA = 5,
	COLOR_BROWN = 6,
	COLOR_LIGHT_GREY = 7,
	COLOR_DARK_GREY = 8,
	COLOR_LIGHT_BLUE = 9,
	COLOR_LIGHT_GREEN = 10,
	COLOR_LIGHT_CYAN = 11,
	COLOR_LIGHT_RED = 12,
	COLOR_LIGHT_MAGENTA = 13,
	COLOR_LIGHT_BROWN = 14,
	COLOR_WHITE = 15,
};

extern size_t terminal_row;
extern size_t terminal_column;
extern uint8_t terminal_color;
extern uint16_t* terminal_buffer;

/* Screen operations */

extern uint8_t make_color(enum vga_color fg, enum vga_color bg);
extern uint16_t make_vgaentry(char c, uint8_t color);
extern void terminal_initialize();
extern void terminal_setcolor(uint8_t color);
extern void terminal_putentryat(char c, uint8_t color, size_t x, size_t y);
extern void terminal_putchar(char c);
extern void terminal_writestring(const char* data);
extern void terminal_drawcircle(uint8_t x0, uint8_t y0, uint8_t _rad);
extern void terminal_welcome();
extern void terminal_scroll();
extern void terminal_clear();
extern void terminal_setcursor();
extern void terminal_putnum(uint64_t data);
#endif
