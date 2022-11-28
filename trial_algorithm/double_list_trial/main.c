#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "common.h"
#include "Double_linear_list/Double_linear_list.h"



int main()
{
    double_list_t my_double_list, *my_double_list_ptr;
    my_double_list_ptr = double_list_init(&my_double_list);

	if (my_double_list_ptr == NULL) {
		printf("NULL\n");
	}
    uint8_t array[10] = {0};
    double_list_add(my_double_list_ptr, 3, array, 10);
    double_list_add(my_double_list_ptr, 0, array, 10);
    double_list_add(my_double_list_ptr, 2, array, 10);
    double_list_add(my_double_list_ptr, 1, array, 10);
    double_list_add(my_double_list_ptr, 8, array, 10);
    double_list_add(my_double_list_ptr, 7, array, 10);
    double_list_add(my_double_list_ptr, 5, array, 10);
    double_list_add(my_double_list_ptr, 6, array, 10);
    double_list_index(my_double_list_ptr);

    // double_list_delete(my_double_list_ptr, 1);
    // double_list_delete(my_double_list_ptr, 0);
    // double_list_delete(my_double_list_ptr, 2);
    // double_list_delete(my_double_list_ptr, 3);
    
    // double_list_node_exchange(my_double_list_ptr->next, my_double_list_ptr->next->next->next->next);
    // printf("size of double list is %d\n", double_list_node_count(my_double_list_ptr));
    
    // double_list_index(my_double_list_ptr);
    // double_list_quick_order(my_double_list_ptr->next, double_list_tail(my_double_list_ptr), 1);
    double_list_quick_order1(my_double_list_ptr, 1);

    double_list_index(my_double_list_ptr);
    double_list_deinit(my_double_list_ptr);
    printf("Hello World\n");

    return 0;
} 


// gcc -o trial main.c .\Double_linear_list\Double_linear_list.c
