#ifndef __TRIAL_H__
#define __TRIAL_H__

// #include <iostream>
// using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif
 

const char*  get_my_name();
char string_[10] = {"abcdefgh"};


#ifdef __cplusplus
}
#endif


// extern "C" const char*  get_my_name();
// extern "C" char string_[10];



class MyObj {
public:
    const char* get_name();
};

#endif // __TRIAL_H__