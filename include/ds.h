#ifndef DS_H

#define DS_H

/* 
   Current queues is builded only for the
   shell input 
*/ 
  
struct kernel_queue
{
    uint8_t data[512];

    int16_t kq_in;
    int16_t kq_out;
    
    uint16_t kq_max_limit;

    uint8_t (*kq_pop)(struct kernel_queue *kq);
    uint8_t (*kq_push)(struct kernel_queue *kq, uint8_t data);

    uint8_t (*is_kq_full)(struct kernel_queue *kq);
    uint8_t (*is_kq_empty)(struct kernel_queue *kq);
};

extern void init_kernel_queue(struct kernel_queue *obj);

#endif
