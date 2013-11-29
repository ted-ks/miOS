#include "system.h"
#include "ordered_array.h"


int8_t standard_lessthan_predicate(type_t a, type_t b)
{
    return (a<b)?1:0;
}

struct ordered_tree_t create_ordered_array(uint32_t max_size, lessthan_predicate_t less_than)
{
    struct ordered_tree_t to_ret;

    to_ret.array = (void*)kmalloc(max_size * sizeof(type_t));
    memset(to_ret.array, 0, max_size * sizeof(type_t));

    to_ret.size = 0;
    to_ret.max_size = max_size;
    to_ret.lessthan = less_than;
    return to_ret;
}

struct ordered_tree_t place_ordered_array(void *addr, uint32_t max_size, lessthan_predicate_t less_than)
{
    struct ordered_tree_t to_ret;
    to_ret.array = (type_t*)addr;
    memset(to_ret.array, 0, sizeof(type_t) * max_size);

    to_ret.size = 0 ;
    to_ret.max_size = max_size;
    to_ret.lessthan = less_than;
    return to_ret;
}

void destroy_ordered_array(struct ordered_tree_t *array)
{
    kfree(array->array);
}

void insert_ordered_array(type_t item, struct ordered_tree_t *array)
{

    uint32_t iterator;

    ASSERT(array->lessthan);

    while(iterator < array->size && array->lessthan(array->array[iterator], item))
        iterator++;

    if(iterator == array->size)
        array->array[array->size+1] = item;
   
    else
    {
        type_t tmp = array->array[iterator];
        array->array[iterator] = item;

        while(iterator<array->size)        
        {
            iterator++;
            type_t tmp2 = array->array[iterator];
            array->array[iterator] = tmp;
            tmp = tmp2;
        }
        array->size++;
    }             
}

type_t lookup_ordered_array(uint32_t i, struct ordered_tree_t *array)
{
    ASSERT(i < array->size);
    return array->array[i];
}

void remove_ordered_array(uint32_t i, struct ordered_tree_t *array)
{
    while(i<array->size)
    {
        array->array[i] = array->array[i+1];
        i++;
    }

    array->size--;
}



