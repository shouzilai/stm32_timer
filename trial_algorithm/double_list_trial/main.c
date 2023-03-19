#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
// #include <sys/ipc.h>
// #include <sys/shm.h>

#include "common.h"
#include "trial.h"
#include "Double_linear_list/Double_linear_list.h"

const trie_task_t trial_t = {
    trie_data_init, trie_data_deinit, trie_data_add, trie_data_subtruct, trie_data_show_list
};

int main_trial()
{
    double_list_t my_double_list, *my_double_list_ptr;
    my_double_list_ptr = double_list_init(&my_double_list, 128, (void*)&trial_t);

    if (my_double_list_ptr == NULL) {
        printf("NULL\n");
    }
    uint8_t array[10] = {0};

    double_list_index(my_double_list_ptr);
    double_list_deinit(my_double_list_ptr);
    printf("Hello World\n");

    return 0;
}

int main_double_list()
{
    double_list_t my_double_list, *my_double_list_ptr;
    my_double_list_ptr = double_list_init(&my_double_list, 5, (void*)&trial_t);

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

int main()
{
    double_list_t my_double_list, *my_double_list_ptr;
    my_double_list_ptr = double_list_init(&my_double_list, 5, (void*)&trial_t);
    char str__[10] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    uint8_t data_[10] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36};
    uint8_t *ptr = data_;

    if (my_double_list_ptr == NULL) {
        printf("my_double_list_ptr NULL\n");
    }
    uint8_t array[10] = {0};
    double_list_add(my_double_list_ptr, 3, array, 10);
    double_list_add(my_double_list_ptr, 1, array, 10);
    double_list_add(my_double_list_ptr, 2, array, 10);
    double_list_add(my_double_list_ptr, 6, array, 10);
    
    _double_list_data_add(my_double_list_ptr, 3, str__, 0x1);
    _double_list_data_add(my_double_list_ptr, 3, ptr, 0x1);
    _double_list_data_add(my_double_list_ptr, 3, "la la la!", 0x1);
    _double_list_data_show_list(my_double_list_ptr, 3);

    _double_list_data_subtruct(my_double_list_ptr, 3, 1);
    _double_list_data_show_list(my_double_list_ptr, 3);
    _double_list_data_add(my_double_list_ptr, 3, "xi xi xi!", 0x1);
    _double_list_data_show_list(my_double_list_ptr, 3);

    double_list_deinit(my_double_list_ptr);
    printf("Hello World\n");
    return SUCCESS;
}

int main1()
{
    char *str_1 = "123456";
    char *str_2 = "123456";
    char *str_3 = "12345";

    printf("%d\n", strcmp(str_1, str_2));
    printf("%d\n", strcmp(str_2, str_3));
    printf("%d\n", strcmp(str_1, str_3));

    printf("%d\n", strcmp(str_2, str_1));
    printf("%d\n", strcmp(str_3, str_2));
    printf("%d\n", !strcmp(str_3, str_1));


    return 0;
}

// gcc -g -o trial main.c Double_linear_list/Double_linear_list.c trial.c
// valgrind --leak-check=yes ./trial
