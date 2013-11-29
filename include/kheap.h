#ifndef KHEAP_H
#define KHEAP_H

#define KHEAP_START 0xC0000000
#define KHEAP_INITIAL_SIZE 0x100000
#define HEAP_INDEX_SIZE 0x20000
#define HEAP_MAGIC 0x123890AB 
#define HEAP_MIN_SIZE 0x70000


uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys);
uint32_t kmalloc_a (uint32_t sz);
uint32_t kmalloc (uint32_t sz);
uint32_t kmalloc_p (uint32_t sz, uint32_t *phys);
uint32_t kmalloc_ap (uint32_t sz, uint32_t *phys);

struct header_t
{
    uint32_t magic;
    uint8_t is_hole;
    uint32_t size;
};

struct footer_t
{
    uint32_t magic;
    struct header_t *header;
};

struct heap_t
{
    struct ordered_tree_t index;
    uint32_t start_address;
    uint32_t end_address;
    uint32_t max_address;
    uint8_t supervisor;
    uint8_t readonly;
};

struct heap_t *create_heap(uint32_t start, uint32_t end, uint32_t max, uint8_t supervisor, uint8_t readonly);

void *alloc(uint32_t size, uint8_t page_align, struct heap_t *heap);
void free(void *p, struct heap_t *heap);

#endif

