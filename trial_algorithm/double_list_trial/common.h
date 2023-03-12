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



#endif // __COMMON_H__

