#ifndef __RING_BUFFER_FIFO__
#define __RING_BUFFER_FIFO__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct{
    uint8_t *addr;
    uint16_t size;
    uint16_t wlvl;
    uint16_t free_lvl;
    uint16_t ptr_read;
    uint16_t ptr_write;
}buffer_fifo_t, *buffer_fifo_p;

int buffer_fifo_init(buffer_fifo_p fifo, uint16_t size);
int buffer_fifo_read(buffer_fifo_p fifo, uint8_t* read_buffer_addr, uint8_t read_buffer_length);
int buffer_fifo_write(buffer_fifo_p fifo, uint8_t* write_buffer_addr, uint8_t write_buffer_length);

#endif
