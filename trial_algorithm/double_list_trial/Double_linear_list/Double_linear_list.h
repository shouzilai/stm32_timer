#ifndef __DOUBLE_LINEAR_LIST_H__
#define __DOUBLE_LINEAR_LIST_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "../common.h"


#define DOUBLE_LINEAR_LIST_DATA_SIZE  128
#define DOUBLE_LINEAR_TABLE_MAX_DATA  5


struct double_linear_list;
struct list_registration_table;

typedef struct double_linear_list double_list_t, *double_list_p;
typedef struct list_registration_table list_register_t, *list_register_p;

struct double_linear_list {
    uint32_t val;
    uint32_t data_len;
    uint8_t *data;

//#####################################################################################
    trie_task_p task;
    void* argument;     // 接收数据列表数组
//#####################################################################################

    double_list_p next;
    double_list_p last;
    list_register_p last_table;

};

struct list_registration_table {
    double_list_p* table;          // 整体栈
    uint8_t add_pos;               // 栈顶
    uint8_t size;
    uint8_t relative_stack_bottom; // 移动性栈底
};

double_list_p list_registeration_peek(list_register_p register_p, uint8_t num);


int double_list_index(double_list_p d_list_p);

double_list_p double_list_guard(double_list_p d_list_p);

double_list_p double_list_tail(double_list_p d_list_p);





double_list_p double_list_init(double_list_p d_list_p, uint8_t table_size, void *extrnal_data_p);

int double_list_deinit(double_list_p d_list_p);

double_list_p double_list_add(double_list_p head_list_p, uint32_t val, uint8_t* data, uint32_t len);

int double_list_delete(double_list_p d_list_p, uint32_t val);

int double_list_node_exchange(double_list_p d_list_p1, double_list_p d_list_p2);

int double_list_node_count(double_list_p d_list_p);

int double_list_quick_order(double_list_p d_list_p, int sort);

int _double_list_data_add(double_list_p d_list_p, int val, uint8_t* data, int cmd);

int _double_list_data_subtruct(double_list_p d_list_p, int val, int index);

int _double_list_data_show_list(double_list_p d_list_p, int val);

#endif // __DOUBLE_LINEAR_LIST_H__

