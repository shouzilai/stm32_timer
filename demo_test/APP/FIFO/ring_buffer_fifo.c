#include "ring_buffer_fifo.h"

buffer_fifo_t fifo;

int buffer_fifo_init(buffer_fifo_p fifo, uint16_t size)
{
    if(NULL == fifo || size <= 0){
        return -1;
    }
    fifo->addr = (uint8_t *)malloc(sizeof(uint8_t)*size);
    if(NULL == fifo->addr){
        return -1;
    }
    fifo->size = size;
    fifo->wlvl = 0;
    fifo->free_lvl = size;
    fifo->ptr_read = 0;
    fifo->ptr_write = 0;
    return 0;
}

static uint8_t _buffer_fifo_read_byte(buffer_fifo_p fifo)
{
    uint8_t ret = fifo->addr[fifo->ptr_read];
    fifo->free_lvl++;
    fifo->wlvl--;
    fifo->ptr_read = (fifo->ptr_read + 1) % fifo->size;
    return ret;
}

static int _buffer_fifo_write_byte(buffer_fifo_p fifo, uint8_t data)
{
    fifo->addr[fifo->ptr_write] = data;
    fifo->free_lvl--;
    fifo->wlvl++;
    fifo->ptr_write = (fifo->ptr_write + 1) % fifo->size;
    return 0;
}

int buffer_fifo_read(buffer_fifo_p fifo, uint8_t* read_buffer_addr, uint8_t read_buffer_length)
{
    if(NULL == fifo || NULL == read_buffer_addr || 0 == read_buffer_length){
        return -1;
    }
    else if(fifo->wlvl < read_buffer_length){
        return -1;
    }
    for(int i = 0; i < read_buffer_length; i++){
        read_buffer_addr[i] = _buffer_fifo_read_byte(fifo);
    }
    return 0;
}

int buffer_fifo_write(buffer_fifo_p fifo, uint8_t* write_buffer_addr, uint8_t write_buffer_length)
{
    if(NULL == fifo || NULL == write_buffer_addr || 0 == write_buffer_length){
        return -1;
    }
    else if(fifo->free_lvl < write_buffer_length){
        return -1;
    }
    for(int i = 0; i < write_buffer_length; i++){
        _buffer_fifo_write_byte(fifo,write_buffer_addr[i]);
    }
    return 0;
}
