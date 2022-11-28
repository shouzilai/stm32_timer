// #include <iostream>  
// 这条语句不能随便加入，PS D:\Users\Desktop\trial_algorithm\trial_C_in_C++> gcc -o trial main.c trial.cpp
// C:\Users\fengshou\AppData\Local\Temp\cc0ZV7bL.o:trial.cpp:(.text+0x1e): undefined reference to `std::ios_base::Init::~Init()'
// C:\Users\fengshou\AppData\Local\Temp\cc0ZV7bL.o:trial.cpp:(.text+0x3f): undefined reference to `std::ios_base::Init::Init()'
#include <string>
#include "trial.hpp"

using namespace std;


// char string_[10] = {"abcdefgh"};

const char* MyObj::get_name() 
{
    return "david";
}

const char* get_my_name() 
{
    MyObj obj;
    return obj.get_name();
}