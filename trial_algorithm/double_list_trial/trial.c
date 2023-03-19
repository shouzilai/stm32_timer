#include <stdio.h>
#include <assert.h>
#include "trial.h"
#include "common.h"


void* trie_data_init(uint8_t* meg, int cmd)
{
    if (meg == NULL) {
        return NULL;
    }
    trie_data_p* data_ps = NULL;
    trie_data_p data_p = NULL;

    // 1.数据块 （数组）分配
    data_ps = (trie_data_p*)calloc(TRIE_DATA_SIZE, sizeof(trie_data_t));
    memset(data_ps, 0x0, TRIE_DATA_SIZE * sizeof(trie_data_t));
    assert(data_ps != NULL);

    // 2.首条数据 分配
    data_ps[0] = (trie_data_p)malloc(sizeof(trie_data_t));
    assert(data_ps[0] != NULL);
    data_p = (trie_data_p)data_ps[0];

    // 3.首条数据内容 分配
    data_p->message = (uint8_t*)calloc(TRIE_DATA_MEG_SIZE, sizeof(uint8_t));
    assert(data_p->message != NULL);

    // 4.首条数据 成员初始化
    memcpy(data_p->message, meg, strlen(meg));
    data_p->index = 0;
    data_p->cmd = cmd;

    printf("trie data init --- %s\n", data_p->message);
    return data_ps;
}

int trie_data_deinit(void *arg)
{
    if (arg == NULL) {
        return FAILURE;
    }
    trie_data_p* data_ps = (trie_data_p*)arg;
    trie_data_p data_p = NULL;

    for (int i = 0; i < TRIE_DATA_SIZE; i++) {
        data_p = data_ps[i];
        if (data_p == NULL) {
            continue;
        }
        if (data_p->message != NULL) {
            free(data_p->message);
            data_p->message = NULL;
        }
        free(data_p);
        data_p = NULL;
    }
    free(data_ps);

    printf("trie data deinit\n");
    return SUCCESS;
}

static int trie_data_single_deinit(trie_data_p* data_s, int index)
{
    if (data_s == NULL) {
        return FAILURE;
    }
    trie_data_p* data_ps = data_s;
    trie_data_p data_p = NULL;

    
    if (data_ps[index] != NULL) {
        if (data_ps[index]->message != NULL) {
            free(data_ps[index]->message);  // 1.数据成员 回收
        }
        free(data_ps[index]);               // 2.数据 回收
    }
    memset(&data_ps[index], 0x0, sizeof(trie_data_p));

    return SUCCESS;
}

static int trie_data_single_init(trie_data_p* data_s, uint8_t* meg, int cmd, int index)
{
    if (data_s == NULL) {
        return FAILURE;
    }
    trie_data_p* data_ps = data_s;
    trie_data_p data_p = NULL;

    // 1.数据 分配
    data_ps[index] = (trie_data_p)malloc(sizeof(trie_data_t));
    assert(data_ps[index] != NULL);
    data_p = (trie_data_p)data_ps[index];

    // 2.数据成员 分配
    data_p->message = (uint8_t*)calloc(TRIE_DATA_MEG_SIZE, sizeof(uint8_t));
    assert(data_p->message != NULL);

    // 3.数据成员 初始化
    printf("meg length is %d\n", strlen(meg));
    memcpy(data_p->message, meg, strlen(meg));
    data_p->index = index;
    data_p->cmd = cmd;

    return SUCCESS;
}

int trie_data_add(void *arg, uint8_t* data, int cmd)
{
    if (arg == NULL || data == NULL || cmd < 0) {
        return FAILURE;
    }
    uint8_t temp = 0;
    int l_index = 0, i = 0; // 上一次添加数据使用的索引
    trie_data_p* data_ps = (trie_data_p*)arg;
    trie_data_p data_p = NULL;

    l_index = 0;
    for (i = 0; i < TRIE_DATA_SIZE; i++) {
        if (data_ps[i] != NULL) {
            printf("%d ", data_ps[i]->index);
            l_index = l_index < data_ps[i]->index ? data_ps[i]->index : l_index;// 找到最大的index
        }
    }
    l_index = (l_index == TRIE_DATA_SIZE -1) ? 1 : l_index + 1;

    trie_data_single_init(data_ps, data, cmd, l_index);

    printf("trie data add\n");
    return SUCCESS;
}

int trie_data_subtruct(void *arg, int index)
{
    if (arg == NULL || index < 0) {
        return FAILURE;
    }
    uint8_t temp = 0;
    int l_index = 0, i = 0; // 上一次添加数据使用的索引
    trie_data_p* data_ps = (trie_data_p*)arg;
    trie_data_p data_p = NULL;

    trie_data_single_deinit(data_ps, index);

    printf("trie data subtruct\n");
}

int trie_data_show_list(void *arg)
{
    if (arg == NULL) {
        return FAILURE;
    }
    uint8_t temp = 0;
    int l_index = 0; // 上一次添加数据使用的索引
    trie_data_p* data_ps = (trie_data_p*)arg;
    trie_data_p data_p = NULL;

    for (int i = 0; i < TRIE_DATA_SIZE; i++) {
        if (data_ps[i] != NULL) {
            printf("index:%d, cmd:%d\n", data_ps[i]->index, data_ps[i]->cmd);
            for (int j = 0; j < TRIE_DATA_MEG_SIZE; j++) {
                printf("%c", data_ps[i]->message[j]);
            }
            printf("\n");
        }
    }
}


