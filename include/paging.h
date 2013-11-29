#ifndef PAGE_H
#define PAGE_H


struct page_t
{
    uint32_t present    : 1;
    uint32_t rw         : 1;
    uint32_t user       : 1;
    uint32_t accessed   : 1;
    uint32_t dirty      : 1;
    uint32_t unused     : 7;
    uint32_t frame      : 20;
};

struct page_table_t
{
    struct page_t pages[1024];
};

struct page_directory_t
{
    struct page_table_t *tables[1024];
    uint32_t tablesPhysical[1204];

    uint32_t physicalAddr;
};

void init_paging();
void switch_page_directory(struct page_directory_t *dir);

struct page_t *get_page(uint32_t address, int make, struct page_directory_t *dir);

void page_fault(struct regs *r) ;



#endif
