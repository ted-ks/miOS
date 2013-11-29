#ifndef ORDERED_ARRAY_H
#define ORDERED_ARRAY_H


typedef void* type_t;
typedef int8_t (*lessthan_predicate_t) (type_t, type_t);

struct ordered_tree_t
{
    type_t *array;
    uint32_t size;
    uint32_t max_size;
    lessthan_predicate_t lessthan;
};

int8_t standard_lessthan_predicate (type_t a, type_t b);

struct ordered_tree_t create_ordered_array(uint32_t maxsize, lessthan_predicate_t less_than);
struct ordered_tree_t place_ordered_array(void *addr, uint32_t max_size, lessthan_predicate_t lessthan);

void destroy_ordered_array(struct ordered_tree_t *array);

void insert_ordered_array(type_t item, struct ordered_tree_t *array);
type_t lookup_ordered_array(uint32_t i, struct ordered_tree_t *array);

void remove_ordered_array(uint32_t i, struct ordered_tree_t *array);



#endif
