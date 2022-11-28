#include <stdio.h>


extern const char* get_my_name(); 
extern char string_[10];

int main(int argc, char** argv) 
{
    printf("%s\n", get_my_name());
    printf("%s\n", string_);
    return 0;
}




