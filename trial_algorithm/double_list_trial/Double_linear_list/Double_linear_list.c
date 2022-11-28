#include "Double_linear_list.h"


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


double_list_p double_list_init(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        return NULL;
    }

    // 初始化 哨兵 成员
    d_list_p->val = 0;
    d_list_p->data_len = 0;
    d_list_p->data = NULL;
    d_list_p->next = NULL;
    d_list_p->last = NULL;
	
	printf("double_list_init success\n");
    return d_list_p;
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

    // 找到整个 双向链表 的 哨兵结点
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

    // 找到整个 双向链表 的 哨兵结点
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

    // 找到整个 双向链表 的 哨兵结点
    first_p = double_list_guard(d_list_p);
    cur_p = first_p->next;

    while (cur_p != NULL) {
        next_p = cur_p->next;
        double_list_single_delete(cur_p);
        cur_p = next_p;
    }
    // double_list_single_delete(first_p);

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

    // 找到最后一个节点并且保留 尾结点
    while (cur_p->next != NULL) {
        cur_p = cur_p->next;
    }
    last_p = cur_p;

    cur_p = (double_list_p)malloc(sizeof(double_list_t));
    if (cur_p == NULL) {
        return NULL;
    }

    // 成员做 赋值
    cur_p->val = val;
    cur_p->data_len = len;
    cur_p->data = (uint8_t*)malloc(sizeof(uint8_t) * DOUBLE_LINEAR_LIST_DATA_SIZE);
    if (cur_p->data == NULL) {
        free(cur_p);
        return NULL;
    }
    memcpy(&cur_p->data[0], data, len);

    // 节点连接上队伍
	last_p->next = cur_p;
    cur_p->last = last_p;
    cur_p->next = NULL;

    return cur_p;
}

int double_list_delete(double_list_p d_list_p, uint32_t val)
{
    if (d_list_p == NULL) {
        return FAILURE;
    }
    double_list_p first_p = d_list_p;
    double_list_p cur_p = d_list_p;

    // 找到整个 双向链表 的 哨兵结点
    first_p = double_list_guard(d_list_p);
    cur_p = first_p->next;

    // 找到对应 val 的节点
    while (cur_p) {
        if (cur_p->val == val) {
            if (cur_p->next != NULL && cur_p->last != NULL) { // 链表中间删除结点 条件一定要是与
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

static int double_list_node_exchange(double_list_p d_list_p1, double_list_p d_list_p2)
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

static int double_list_node_count(double_list_p d_list_p)
{
    if (d_list_p == NULL) {
        return -1;
    }
    int node_count = 0;
    double_list_p first_p = d_list_p;
    double_list_p cur_p = d_list_p;

    // 找到整个 双向链表 的 哨兵结点
    first_p = double_list_guard(d_list_p);    
    cur_p = first_p->next;

    while (cur_p != NULL) {
        node_count++;
        cur_p = cur_p->next;
    }

    return node_count;
}

int double_list_quick_order(double_list_p d_list_low, double_list_p d_list_hign, int sort)
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
        double_list_quick_order(first_p, d_list_low->last, 1);
        double_list_quick_order(d_list_low->next, tail_p, 1);
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

double_list_p double_find_node(double_list_p d_list_p, int val)
{
    if (d_list_p == NULL) {
        return NULL;
    }
    double_list_p first_p = d_list_p;
    double_list_p cur_p = d_list_p;

    // 找到整个 双向链表 的 哨兵结点
    first_p = double_list_guard(d_list_p);
    cur_p = first_p->next;

    // 找到对应 val 的节点
    while (cur_p) {
        if (cur_p->val == val) {
            return cur_p;
        }
        cur_p = cur_p->next;
    }

    return NULL;
}

int double_list_quick_order1(double_list_p d_list_p, int sort)
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

    cur_p = first_p->next;
    for (int i = 0; i < count && cur_p != NULL; i++) {
        last_p = cur_p;
        if (cur_p->val == data_val[i]) {
            // 保持不变
        } else {
            double_list_p temp_p = double_find_node(cur_p, data_val[i]);
            double_list_node_exchange(cur_p, temp_p);
        }
        cur_p = last_p->next;
    }    
    return SUCCESS;
}


// int double_list_quick_order(double_list_p head, double_list_p end)
// {
//     if(head == end || head->next == end) {
//         return head;
//     }
//     double_list_p lhead = head ,utail = head ,p = head->next;
//     while (p != end){
//         double_list_p next = p->next;
//         if(p->val < head->val){ // 头插
//             p->next = lhead;
//             lhead = p;
//         }
//         else { //尾插
//             utail->next = p;
//             utail = p;
//         }
//         p = next;
//     }
//     utail->next = end;
//     double_list_p node = quickSort(lhead, head);
//     head->next =  quickSort(head->next, end);
//     return node; 
//     return SUCCESS;
// }

// 归并排序
// void Merge(int *data, int low, int mid, int high, int* temp)
// {   
//    int i_start = low;
//    int i_end = mid;
//    int j_start = mid + 1; 
//    int j_end = high;
//    int k = 0;
//    while (i_start <= i_end && j_start <= j_end )
//    {   // 大循环的条件 自己少考虑了，等于情况；测试过了，不加的话，排序错误，因为该给定序列最后元素入temp的机会；
//        // 直到另一序列为空，退出循环，接应后面的两个小循环
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
//    {   //检查左半部分是否还有未放入temp的data元素
//        temp[k] = data[i_start];
//        i_start++;
//        k++;
//    }
//    while (j_start <= j_end)
//    {   // 检查右半部分是否还有未放入temp的data元素
//        temp[k] = data[j_start];
//        j_start++;
//        k++;
//    }
//    // memcpy(data, temp, high - low + 1);
//    for (k = 0, i_start = low; i_start <= high; i_start++)// 复制数组temp到data中,temp必须给不小于data的大小，不然一直都是一个数
//        data[i_start] = temp[k++];
// }
// void MergeSort(int* data, int low, int high,int* temp)
// {
//    if (low == high)// 递归结束的条件，由于函数的 第二个函数 有加一，可能大于或等于 第三参数
//        return;
//    int mid = (low + high) / 2;// 将序列划分两半
//    MergeSort(data, low, mid,temp);// 对序列的左半部分，实现归并排序
//    MergeSort(data, mid + 1, high,temp);// 对序列的右半部分，实现归并排序
//    Merge(data, low, mid, high,temp);// 实现一次归并排序
// }