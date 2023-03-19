#ifndef __TRIAL_H__
#define __TRIAL_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define TRIE_DATA_SIZE          9
#define TRIE_DATA_MEG_SIZE      128

struct trie_data;

typedef struct trie_data trie_data_t, *trie_data_p;

struct trie_data {
    uint8_t* message;
    int index;
    int cmd;
} ;

void* trie_data_init(uint8_t* meg, int cmd); // 返回数据列表数组

int trie_data_deinit(void *arg);

int trie_data_add(void *arg, uint8_t* data, int cmd);

int trie_data_subtruct(void *arg, int index);

int trie_data_show_list(void *arg);

#endif