#include "system.h"
#include "ordered_array.h"
#include "kheap.h"

extern uint32_t end;
uint32_t placement_address = (uint32_t)&end;
uint32_t kmalloc_int(uint32_t sz, int align, uint32_t *phys)
{

  if (align == 1 && (placement_address & 0xFFFFF000)) // If the address is not already page-aligned
  {
    // Align it.
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  if (phys)
  {
    *phys = placement_address;
  }
  uint32_t tmp = placement_address;
  placement_address += sz;
  return tmp;
} 


uint32_t kmalloc_a (uint32_t sz)
{
    return kmalloc_int (sz, 1, 0);
}

uint32_t kmalloc_p (uint32_t sz, uint32_t *phys)
{
    return kmalloc_int (sz, 0, phys);
}

uint32_t kmalloc_ap (uint32_t sz, uint32_t *phys)
{
    return kmalloc_int (sz, 1, phys);
}

uint32_t kmalloc (uint32_t sz)
{
        return kmalloc_int (sz, 0, 0);
}

static int32_t find_smallest_hole(uint32_t size, uint8_t page_align, struct heap_t *heap)
{
    uint32_t iter=0;
    
    while(iter < heap->index.size)
    {
        struct header_t  *header = (struct header_t *) lookup_ordered_array(iter, &heap->index);

        if (page_align > 0)
        {
            uint32_t location = (uint32_t)header;
            int32_t offset = 0;
            int32_t hole_size = 0;

            if(((location + sizeof(struct header_t)) & 0xFFFFF000) != 0)
            {
                offset = 0x1000 - (location + sizeof (struct header_t)) % 0x1000;
            }

            hole_size = (int32_t) header->size - offset;

            if (hole_size >= (int32_t)size)
                break;                            
        }
        else if(header->size >= size)        
            break;        
        iter++;
    }

    if(heap->index.size == iter)
        return -1;
    else return iter;        
   
}

static int8_t header_t_lessthan(void *a, void *b)
{
    return (((struct header_t *) a)->size < ((struct header_t *) b)->size)? 1: 0;
}


struct heap_t *create_heap(uint32_t start, uint32_t end_addr, uint32_t max, uint8_t supervisor, uint8_t ro)
{
    struct heap_t *heap = (struct heap_t *)kmalloc(sizeof(struct heap_t));

    ASSERT(start % 0x1000);
    ASSERT(end_addr % 0x1000);

    heap->index = place_ordered_array((void *) start, HEAP_INDEX_SIZE, &header_t_lessthan);

    start += sizeof(type_t *) * HEAP_INDEX_SIZE;

    if((start & 0xFFFFF000) != 0)
    {
        start &= 0xFFFFF000;
        start += 0x1000;
    }

    heap->start_address = start;
    heap->end_address = end_addr;
    heap->max_address = max;
    heap->supervisor = supervisor;
    heap->readonly = ro;

    struct header_t *hole = (struct header_t *)start;
    hole->size = end_addr - start;
    hole->magic = HEAP_MAGIC;
    hole->is_hole = 1;

    insert_ordered_array((void *)hole, &heap->index);
    return heap;
}

void kfree(type_t d)
{
return;
}

static void expand(uint32_t new_size, struct heap_t *heap)
{



}

