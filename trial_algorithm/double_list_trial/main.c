#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>

#include "common.h"
#include "Double_linear_list/Double_linear_list.h"

int main_trial()
{
    double_list_t my_double_list, *my_double_list_ptr;
    my_double_list_ptr = double_list_init(&my_double_list, 128);

    if (my_double_list_ptr == NULL) {
        printf("NULL\n");
    }
    uint8_t array[10] = {0};

    double_list_index(my_double_list_ptr);
    double_list_deinit(my_double_list_ptr);
    printf("Hello World\n");

    return 0;
}

int main()
{
    double_list_t my_double_list, *my_double_list_ptr;
    my_double_list_ptr = double_list_init(&my_double_list, 5);

    if (my_double_list_ptr == NULL) {
        printf("my_double_list_ptr NULL\n");
    }
    uint8_t array[10] = {0};
    double_list_add(my_double_list_ptr, 3, array, 10);
    double_list_add(my_double_list_ptr, 0, array, 10);
    double_list_add(my_double_list_ptr, 2, array, 10);
    double_list_add(my_double_list_ptr, 6, array, 10);
    double_list_index(my_double_list_ptr);

    for (int i = DOUBLE_LINEAR_TABLE_MAX_DATA * sizeof(double_list_p) - 1; i > -1; i--){
        // printf("cur val is %d\n", ((double_list_p)my_double_list_ptr->last_table->table + i)->val);
        printf("0x%x ", *((uint8_t*)my_double_list_ptr->last_table->table + i));
        if (i % 8 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    double_list_p *temp = my_double_list_ptr->last_table->table;
    temp += 3;
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*temp)->val, (*temp)->data_len);
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*(temp - 1))->val, (*(temp - 1))->data_len);    
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*(temp - 2))->val, (*(temp - 2))->data_len);    
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*(temp - 3))->val, (*(temp - 3))->data_len);    
    double_list_delete(my_double_list_ptr, 3);
    double_list_delete(my_double_list_ptr, 0);
    double_list_add(my_double_list_ptr, 5, array, 10);
    double_list_add(my_double_list_ptr, 4, array, 10);
    double_list_add(my_double_list_ptr, 7, array, 10);
    // double_list_p ptr = list_registeration_peek(my_double_list_ptr->last_table, 0); // 返回最新入链的成员地址
    // printf("val is %d\n", ptr->val);
    // list_registration_index(my_double_list_ptr->last_table);

    temp += 1;
    // temp = my_double_list_ptr->last_table->table[my_double_list_ptr->last_table->add_pos - 1]; // 错误的写法
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*temp)->val, (*temp)->data_len);
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*(temp - 1))->val, (*(temp - 1))->data_len);    
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*(temp - 2))->val, (*(temp - 2))->data_len);    
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*(temp - 3))->val, (*(temp - 3))->data_len);    
    printf("the last node characteristic val = %d, data_len = %d, data is :\n", (*(temp - 4))->val, (*(temp - 4))->data_len);    

    // double_list_node_exchange(my_double_list_ptr->next, my_double_list_ptr->next->next->next->next);
    // printf("size of double list is %d\n", double_list_node_count(my_double_list_ptr));
    
    // double_list_index(my_double_list_ptr);
    // double_list_quick_order(my_double_list_ptr->next, double_list_tail(my_double_list_ptr), 1);
    double_list_quick_order(my_double_list_ptr, 0);

    double_list_index(my_double_list_ptr);
    double_list_deinit(my_double_list_ptr);
    printf("Hello World\n");

    return 0;
}


// gcc -g -o trial main.c Double_linear_list/Double_linear_list.c
// valgrind --leak-check=yes ./trial
