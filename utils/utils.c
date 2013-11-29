#include "system.h"
#include "utils.h"

void panic_assert (const char *file, int line, char *msg)
{
        printk ("ASSERTION-FAILED: %s:%d : %s\n", file, line, msg);
        while(1);
}
