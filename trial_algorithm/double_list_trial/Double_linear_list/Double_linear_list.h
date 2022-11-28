#ifndef __DOUBLE_LINEAR_LIST_H__
#define __DOUBLE_LINEAR_LIST_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../common.h"


#define DOUBLE_LINEAR_LIST_DATA_SIZE  128


typedef struct double_linear_list {
    uint32_t val;
    uint32_t data_len;
    uint8_t *data;
    struct double_linear_list* next;
    struct double_linear_list* last;

} double_list_t, *double_list_p;


int double_list_index(double_list_p d_list_p);

double_list_p double_list_guard(double_list_p d_list_p);

double_list_p double_list_tail(double_list_p d_list_p);


double_list_p double_list_init(double_list_p d_list_p);

int double_list_deinit(double_list_p d_list_p);

double_list_p double_list_add(double_list_p head_list_p, uint32_t val, uint8_t* data, uint32_t len);

int double_list_delete(double_list_p d_list_p, uint32_t val);

int double_list_quick_order(double_list_p d_list_low, double_list_p d_list_hign, int sort);

int double_list_quick_order1(double_list_p d_list_p, int sort);

#endif // __DOUBLE_LINEAR_LIST_H__

