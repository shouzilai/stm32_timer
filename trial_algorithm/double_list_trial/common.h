#ifndef __COMMON_H__
#define __COMMON_H__



typedef unsigned char u8_t;
typedef unsigned short u16_t;
typedef unsigned int u32_t;
typedef unsigned long long u64_t;


typedef char c8_t;
typedef short c16_t;
typedef int c32_t;
typedef long long c64_t;



typedef enum RETURN_STATUS {
    SUCCESS = 0,
    FAILURE = 1
} RE_STATUS;

typedef enum EXIST_STATE_T {
    NON_EXIST = 0x0,
    EXIST = 0x1,
    UNCERTAIN = 0x2,
} EXIST_STATE;


struct trie_task;
typedef struct trie_task trie_task_t, *trie_task_p;
//######################################################################
struct trie_task {                          // 依赖反转，依赖注入，实现结构体
    void*   (*init)(uint8_t* meg, int cmd); // 返回数据列表数组
    int     (*deinit)(void *arg);
    int     (*add)(void *arg, uint8_t* data, int cmd);
    int     (*subtruct)(void *arg, int index);
    int     (*show_list)(void *arg);
} ;
//######################################################################

#endif // __COMMON_H__

