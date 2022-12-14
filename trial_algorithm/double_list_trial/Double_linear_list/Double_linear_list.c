#include "Double_linear_list.h"


static int list_registration_index(list_register_p register_p)
{
    uint8_t pos = register_p->add_pos;
    double_list_p *cur_p = register_p->table;
    for (int i = DOUBLE_LINEAR_TABLE_MAX_DATA * sizeof(double_list_p) - 1; i > -1; i--){
        // printf("cur val is %d\n", ((double_list_p)my_double_list_ptr->last_table->table + i)->val);
        printf("0x%x ", *((uint8_t*)register_p->table + i));
        if (i % 4 == 0) {
            printf("val is %d", (*cur_p)->val);
            printf("\n");
            cur_p += 1;
        }
    }
    printf("\n");
}

static int list_registration_init(list_register_p register_p, uint8_t size)
{
    if (register_p == NULL || size < 0 || size > DOUBLE_LINEAR_TABLE_MAX_DATA) {
        printf("register is NULL or size given error\n");
        return FAILURE;
    }

    register_p->size = size;
    register_p->table = (list_register_p*)malloc(size * sizeof(list_register_p));
    if (register_p->table != NULL) {
        memset(register_p->table, 0x0, size * sizeof(list_register_p));
    }
    register_p->add_pos = 0;
    register_p->relative_stack_bottom = register_p->add_pos;

    return SUCCESS;
}

static int list_registration_deinit(list_register_p register_p)
{
    if (register_p == NULL) {
        printf("register is NULL\n");
        return FAILURE;
    }

    if (register_p->table != NULL) {
        free(register_p->table);
        register_p->table = NULL;
    }
    register_p->size = 0;
    register_p->add_pos = 0;
    register_p->relative_stack_bottom = register_p->add_pos;

    return SUCCESS;    
}

static int list_registration_push(list_register_p register_p, double_list_p node_p)
{
    if (register_p == NULL || node_p == NULL) {
        printf("register or node_p is NULL\n");
        return FAILURE;
    }

    uint8_t pos = register_p->add_pos;
    uint8_t size = register_p->size;
    uint8_t relate_bottom = register_p->relative_stack_bottom;
    double_list_p *cur_p = register_p->table;

    cur_p += pos;
    *cur_p = node_p;
    printf("push cur val is %d\n", (*cur_p)->val);
    if (relate_bottom == pos) {
        relate_bottom = (relate_bottom + 1) % size;
    }
    pos = (pos + 1) % size;
    register_p->add_pos = pos;
    
    return SUCCESS;
}

static int list_registration_pop(list_register_p register_p, double_list_p node_p)
{
    if (register_p == NULL || node_p == NULL) {
        printf("register or node_p is NULL\n");
        return FAILURE;
    }
    int i;
    uint8_t pos = register_p->add_pos;
    uint8_t size = register_p->size;
    uint8_t relate_bottom = register_p->relative_stack_bottom;
    double_list_p *cur_p = register_p->table;

    // for (int i = 0; i < 4; i++) {
    //     printf("cur_p is 0x%x, table is 0x%x, node_p is 0x%x\n", cur_p[i], register_p->table, node_p);
    // }
    for (i = relate_bottom; i < DOUBLE_LINEAR_TABLE_MAX_DATA; i++) {
        cur_p += i;
        if ((*cur_p)->val == node_p->val) {
            printf("pop cur is 0x%x, val is %d\n", *cur_p, node_p->val);
            memset(cur_p, 0x0, sizeof(double_list_p));
            break;
        }
        cur_p -= i;
    }

    if (i == relate_bottom) {
        // ????????????
        relate_bottom += 1;
        register_p->relative_stack_bottom = relate_bottom;
    } else if (i == DOUBLE_LINEAR_TABLE_MAX_DATA) {
        // ????????????
        memset((cur_p - i + pos - 1), 0x0, sizeof(double_list_p));
        printf("---\n");
        pos -= 1;
        register_p->add_pos = pos;
    } else {
        // ????????????
        memcpy(cur_p, (cur_p + 1), (pos - i - 1) * sizeof(double_list_p));
        memset((cur_p - i + pos - 1), 0x0, sizeof(double_list_p));
        printf("---\n");
        pos -= 1;
        register_p->add_pos = pos;
    } 
    
    return SUCCESS;
}

static int list_registration_count(list_register_p register_p)
{
    if (register_p == NULL) {
        printf("register is NULL\n");
        return -1;
    }

    int count = 0;
    uint8_t pos = register_p->add_pos;
    uint8_t size = register_p->size;
    uint8_t relate_bottom = register_p->relative_stack_bottom;
    double_list_p *cur_p = register_p->table;

    for (int i = 0; i < size * sizeof(double_list_p); i++) {
        if (i % 4 == 0) {
            if (*cur_p != NULL) {
                printf("val is %d\n", (*cur_p)->val);
                count++;
            }
            cur_p += 1;
        }        
    }

    return count;        
}

double_list_p list_registeration_peek(list_register_p register_p, uint8_t num)
{
    if (register_p == NULL) {
        printf("register is NULL\n");
        return NULL;
    }
    
    int count = 0;
    uint8_t last_pos = register_p->add_pos - 1;
    uint8_t size = register_p->size;
    uint8_t relate_bottom = register_p->relative_stack_bottom;
    double_list_p *cur_p = register_p->table;

    count = list_registration_count(register_p);
    printf("members is %d\n", count);
    if (count < num) {
        return NULL;
    }
    // *cur_p = node_p;
    for (int i = 0; i < num; i++) {
        last_pos = (last_pos - 1) % size;
    }
    cur_p += last_pos;

    return *cur_p;    
}

int list_registration_clear(list_register_p register_p)
{
    if (register_p == NULL) {
        printf("register is NULL\n");
        return FAILURE;
    }
    double_list_p *cur_p = register_p->table;
    memset(cur_p, 0x0, DOUBLE_LINEAR_TABLE_MAX_DATA * sizeof(double_list_p));
    register_p->add_pos = 0;
    register_p->relative_stack_bottom = 0;

    return SUCCESS;
}







int double_list_single_show(double_list_p d_list_p) 
{
    if (d_list_p == NULL) {
        return FAILURE;
    }
    double_list_p cur_p = d_list_p;

    printf("val = %d, data_len = %d, data is :\n", d_list_p->val, d_list_p->data_len);
    // for (int i = 0; i < cur_p->data_len; i++) {
    //     printf("%d ", cur_p->data[i]);
    // }
    // printf("\n");

    return SUCCESS;
}

int double_list_index(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        printf("double_list_index success\n");
        return FAILURE;
    }
    double_list_p frist_p = d_list_p;
    double_list_p cur_p = d_list_p;

    while (cur_p->last != NULL) {
        cur_p = cur_p->last;
    }
    frist_p = cur_p;
    cur_p = frist_p->next;

    while (cur_p != NULL) {
        frist_p = cur_p->next;
        double_list_single_show(cur_p);
        cur_p = frist_p;
    }

    return SUCCESS;
}


double_list_p double_list_init(double_list_p d_list_p, uint8_t table_size)
{
    if (d_list_p == NULL) {
        return NULL;
    }

    // ????????? ?????? ??????
    d_list_p->val = 0;
    d_list_p->data_len = 0;
    d_list_p->data = NULL;
    d_list_p->next = NULL;
    d_list_p->last = NULL;
    d_list_p->last_table = (list_register_p)malloc(sizeof(list_register_t));

    if (list_registration_init(d_list_p->last_table, table_size) == 0) {
        // memset(d_list_p->last_table->table, 0x0, 10 * sizeof(double_list_p));
        // d_list_p->last_table->add_pos = 0;
        
        printf("double_list_init success\n");
        return d_list_p;
    } else {
        return NULL;
    }

}


static int double_list_single_delete(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        return FAILURE;
    }
    if (d_list_p->data != NULL) {
        free(d_list_p->data);
        d_list_p->data = NULL;
    }
    free(d_list_p);
    d_list_p = NULL;

    return SUCCESS;
}

double_list_p double_list_guard(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        return NULL;
    }
    double_list_p cur_p = d_list_p;

    // ???????????? ???????????? ??? ????????????
    while (cur_p->last != NULL) {
        cur_p = cur_p->last;
    }
    
    return cur_p;
}


double_list_p double_list_tail(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        return NULL;
    }
    double_list_p cur_p = d_list_p;

    // ???????????? ???????????? ??? ????????????
    while (cur_p->next != NULL) {
        cur_p = cur_p->next;
    }
    printf("tail val is %d\n", cur_p->val);

    return cur_p;
}

    
int double_list_deinit(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        printf("double_list_deinit success\n");
        return FAILURE;
    }
    double_list_p first_p = d_list_p;
    double_list_p cur_p = d_list_p;
    double_list_p next_p = d_list_p;

    // ???????????? ???????????? ??? ????????????
    first_p = double_list_guard(d_list_p);
    cur_p = first_p->next;

    while (cur_p != NULL) {
        next_p = cur_p->next;
        double_list_single_delete(cur_p);
        cur_p = next_p;
    }

    // free(d_list_p->last_table->table);
    list_registration_deinit(d_list_p->last_table);

    printf("double_list_deinit success\n");
    return SUCCESS;
}


double_list_p double_list_add(double_list_p head_list_p, uint32_t val, uint8_t* data, uint32_t len)
{
    if (head_list_p == NULL || len < 0 || len > 128 || data == NULL) {
        printf("double_list_add paras error\n");
        return NULL;
    }
    double_list_p last_p = head_list_p;
    double_list_p cur_p = head_list_p;

    // 1.???????????????????????????????????? ?????????
    while (cur_p->next != NULL) {
        cur_p = cur_p->next;
    }
    last_p = cur_p;

    cur_p = (double_list_p)malloc(sizeof(double_list_t));
    if (cur_p == NULL) {
        return NULL;
    }

    // 2.????????? ??????
    cur_p->val = val;
    cur_p->data_len = len;
    cur_p->data = (uint8_t*)malloc(sizeof(uint8_t) * DOUBLE_LINEAR_LIST_DATA_SIZE);
    if (cur_p->data == NULL) {
        free(cur_p);
        return NULL;
    }
    memcpy(&cur_p->data[0], data, len);

    // 3.?????????????????????
    last_p->next = cur_p;
    cur_p->last = last_p;
    cur_p->next = NULL;

    // 4.?????????????????? ???????????? ?????????
    cur_p = double_list_guard(head_list_p);
    list_registration_push(cur_p->last_table, last_p->next);
    // cur_p->last_table->table[cur_p->last_table->add_pos++] = last_p->next;

    return cur_p;
}


int double_list_delete(double_list_p d_list_p, uint32_t val)
{
    if (d_list_p == NULL) {
        return FAILURE;
    }
    int pos = 0;
    double_list_p first_p = d_list_p;
    double_list_p cur_p = d_list_p;

    // 1.???????????? ???????????? ??? ????????????
    first_p = double_list_guard(d_list_p);
    cur_p = first_p->next;

    // 2.???????????? val ?????????
    while (cur_p) {
        if (cur_p->val == val) {
            // 2.1?????????????????? ???????????? ?????????
            list_registration_pop(first_p->last_table, cur_p);
            // if (first_p->last_table->table[first_p->last_table->add_pos - 1]->val == val) { 
            //     pos = first_p->last_table->add_pos - 1;
            //     first_p->last_table->table[pos] = NULL;
            //     first_p->last_table->add_pos = pos;
            // }
            // 2.2???????????????????????? ?????????????????? ???
            if (cur_p->next != NULL && cur_p->last != NULL) { 
                cur_p->last->next = cur_p->next;
                cur_p->next->last = cur_p->last;
                double_list_single_delete(cur_p);
            } else {
                cur_p->last->next = NULL;
                double_list_single_delete(cur_p);
            }

            break;
        }
        cur_p = cur_p->next;
    }
    return SUCCESS;
}



int double_list_node_exchange(double_list_p d_list_p1, double_list_p d_list_p2)
{
    if (d_list_p1 == NULL || d_list_p2 == NULL) {
        return FAILURE;
    }
    double_list_t temp = {0};

    temp.val = d_list_p1->val;
    temp.data_len = d_list_p1->data_len;
    temp.data = d_list_p1->data;

    d_list_p1->val = d_list_p2->val;
    d_list_p1->data_len = d_list_p2->data_len;
    d_list_p1->data = d_list_p2->data;

    d_list_p2->val      = temp.val;
    d_list_p2->data_len = temp.data_len;
    d_list_p2->data     = temp.data;
    return 0;
}


int double_list_node_count(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        return -1;
    }
    int node_count = 0;
    double_list_p first_p = d_list_p;
    double_list_p cur_p = d_list_p;

    // ???????????? ???????????? ??? ????????????
    first_p = double_list_guard(d_list_p);    
    cur_p = first_p->next;

    while (cur_p != NULL) {
        node_count++;
        cur_p = cur_p->next;
    }

    return node_count;
}


int double_list_quick_order1(double_list_p d_list_low, double_list_p d_list_hign, int sort)
{
    if (d_list_low == NULL || d_list_hign == NULL) {
        return FAILURE;
    }
    int size = 0;
    double_list_p head_p = d_list_low, first_p = d_list_low, tail_p = d_list_hign;
    double_list_p cur_p = d_list_low;
    double_list_t temp = {0};


    if (first_p == tail_p || first_p->last == tail_p) {
        return FAILURE;
    }

    if (first_p != tail_p && first_p->last != tail_p) {
        temp.val = first_p->val;
        temp.data_len = first_p->data_len;
        temp.data = first_p->data;

        while (first_p != tail_p && first_p->last != tail_p) {
            while (first_p != tail_p && first_p->last != tail_p && temp.val < tail_p->val) {
                tail_p = tail_p->last;
            }
            if (first_p != tail_p && first_p->last != tail_p) {
                printf("1111111val is first: %d, tail: %d\n", first_p->val, tail_p->val);
                double_list_node_exchange(first_p, tail_p);
                first_p = first_p->next;
            }
            while (first_p != tail_p && first_p->last != tail_p && temp.val >= first_p->val) {
                first_p = first_p->next;
            }
            if (first_p != tail_p && first_p->last != tail_p) {
                printf("2222222val is first: %d, tail: %d\n", first_p->val, tail_p->val);
                double_list_node_exchange(first_p, tail_p);
                tail_p = tail_p->last;
            }
        }
        first_p->val =      temp.val;
        first_p->data_len = temp.data_len;
        first_p->data =     temp.data; 
        double_list_quick_order1(first_p, d_list_low->last, 1);
        double_list_quick_order1(d_list_low->next, tail_p, 1);
    }
    // if (first_p != tail_p) {
    //     temp = *first_p;
    //     while (first_p < tail_p)
    //     {
    //         while(low < hign && temp < array[hign]) {
    //             hign--;
    //         }
    //         if (low < hign) {
    //             swap(&array[low++], &array[hign]);
    //         }
    //         while(low < hign && temp >= array[low]) {
    //             low++;
    //         }
    //         if (low < hign) {
    //             swap(&array[low], &array[hign--]);
    //         }
    //     }
    //     array[low] = temp;
    //     quick_sort(array, head, low - 1);
    //     quick_sort(array, low + 1, tail);        
    // }

    return SUCCESS;
}


double_list_p double_list_find_node(double_list_p d_list_p, int val)
{
    if (d_list_p == NULL) {
        return NULL;
    }
    double_list_p first_p = d_list_p;
    double_list_p cur_p = d_list_p;

    // ???????????? ???????????? ??? ????????????
    first_p = double_list_guard(d_list_p);
    cur_p = first_p->next;

    // ???????????? val ?????????
    while (cur_p) {
        if (cur_p->val == val) {
            return cur_p;
        }
        cur_p = cur_p->next;
    }

    return NULL;
}


static void quick_sort(int array[], int head, int tail)
{
    int low = head, hign = tail;
    if (low < hign) {
        int temp = array[low];
        while (low < hign) {
            while(low < hign && temp <= array[hign]) {
                hign--;
            }
            if (low < hign) {
                array[low++] = array[hign];
            }
            while(low < hign && temp > array[low]) {
                low++;
            }
            if (low < hign) {
                array[hign--] = array[low];
            }
        }
        array[low] = temp;
        quick_sort(array, head, low - 1);
        quick_sort(array, low + 1, tail);
    }
}

int double_list_quick_order(double_list_p d_list_p, int sort)
{
    if (d_list_p == NULL) {
        return -1;
    }
    int count = 0;
    double_list_p cur_p = d_list_p, first_p = d_list_p, last_p = d_list_p;
    
    count = double_list_node_count(cur_p);
    first_p = double_list_guard(cur_p);
    cur_p = first_p->next;
    int data_val[count];
    for (int i = 0; i < count; i++) {
        data_val[i] = cur_p->val;
        cur_p = cur_p->next;
    }
    quick_sort(data_val, 0, count - 1);

    for (int i = 0; i < count; i++) {
        printf("%d ", data_val[i]);
    }
    printf("\n");

    cur_p = first_p->next;
    if (sort) {
        for (int i = 0; i < count && cur_p != NULL; i++) {
            last_p = cur_p;
            if (cur_p->val == data_val[i]) {
                // ????????????
            } else {
                double_list_p temp_p = double_list_find_node(cur_p, data_val[i]);
                double_list_node_exchange(cur_p, temp_p);
            }
            cur_p = last_p->next;
        }    
    } else {
        for (int i = count - 1; i > 0 && cur_p != NULL; i--) {
            last_p = cur_p;
            if (cur_p->val == data_val[i]) {
                // ????????????
            } else {
                double_list_p temp_p = double_list_find_node(cur_p, data_val[i]);
                double_list_node_exchange(cur_p, temp_p);
            }
            cur_p = last_p->next;
        }       
    }
    return SUCCESS;
}



// ????????????
// void Merge(int *data, int low, int mid, int high, int* temp)
// {   
//    int i_start = low;
//    int i_end = mid;
//    int j_start = mid + 1; 
//    int j_end = high;
//    int k = 0;
//    while (i_start <= i_end && j_start <= j_end )
//    {   // ?????????????????? ?????????????????????????????????????????????????????????????????????????????????????????????????????????????????????temp????????????
//        // ????????????????????????????????????????????????????????????????????????
//        if (data[i_start] < data[j_start])
//        {   
//            temp[k] = data[i_start];
//            i_start++;
//            k++;
//        }
//        else
//        {
//            temp[k] = data[j_start];
//            j_start++;
//            k++;
//        }
//    }
//    while (i_start <= i_end)
//    {   //???????????????????????????????????????temp???data??????
//        temp[k] = data[i_start];
//        i_start++;
//        k++;
//    }
//    while (j_start <= j_end)
//    {   // ???????????????????????????????????????temp???data??????
//        temp[k] = data[j_start];
//        j_start++;
//        k++;
//    }
//    // memcpy(data, temp, high - low + 1);
//    for (k = 0, i_start = low; i_start <= high; i_start++)// ????????????temp???data???,temp??????????????????data???????????????????????????????????????
//        data[i_start] = temp[k++];
// }
// void MergeSort(int* data, int low, int high,int* temp)
// {
//    if (low == high)// ??????????????????????????????????????? ??????????????? ????????????????????????????????? ????????????
//        return;
//    int mid = (low + high) / 2;// ?????????????????????
//    MergeSort(data, low, mid,temp);// ?????????????????????????????????????????????
//    MergeSort(data, mid + 1, high,temp);// ?????????????????????????????????????????????
//    Merge(data, low, mid, high,temp);// ????????????????????????
// }