#include "system.h"
#include "printk.h"
#include "ds.h"

char STDOUT[500]="";
char STDIN[500]="";
extern struct kernel_queue stdin_queue;


void duplicate_shell()
{

    int stdin_len=0;
    char ch;

    printk("\nStarting Duplicate Shell!!!");
    while(1)
    {

        printk("\n#>");

        do
        {
            while(stdin_queue.is_kq_empty(&stdin_queue));
            ch = (stdin_queue.kq_pop(&stdin_queue));
            STDIN[stdin_len++] = ch;
        }while(ch != 10);

        STDIN[--stdin_len] = '\0';

        if(!strcmp(STDIN, "help"))
        {   
              printk("help\nauthor\nversion");
        }

        else if(!strcmp(STDIN, "author"))
        {   
              printk("Vishnu KS");
        }

        else if(!strcmp(STDIN, "version"))
        {   
              printk("Not counted!!");
        }

        else 
        {
            printk("Invalid Command!!");
        }
/*
        switch(strlen(STDIN))
        {
            case 6 : printk("Vishnu KS"); break;
            case 4 : printk("help\nauthor\nversion"); break;
            case 7 : printk("Not named version!!!!");break;

            default : printk("Invalid Command!!!");
        }*/



        strcpy("", STDIN);
        stdin_len=0;


    }




}
