#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <typeinfo>

struct Function
{
    std::string Name;
    std::string ReturnType;
};
Function* calling_function(void* function_ptr_t[], int len)
{
    Function bozo[len];
    for(int i = 0; i < len; i++)
    {
        const char* a;
        a = (char*)(function_ptr_t);
        Function b;
        b.Name = a; 
        b.ReturnType = typeid(function_ptr_t).name();
        bozo[i] = b;
    }
    return (Function*)(bozo);
}

