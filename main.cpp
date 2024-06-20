#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <typeinfo>

typedef void (*func_ptr)();

struct Function {
    std::string Name;
    std::string ReturnType;
};

extern "C" __declspec(dllexport) Function* calling_function(void* function_ptr_t[], int len) {
    Function* bozo = new Function[len];
    for (int i = 0; i < len; i++) {
        const char* a = (char*)(function_ptr_t);
        bozo[i].Name = a;
        bozo[i].ReturnType = typeid(function_ptr_t).name();
    }
    return bozo;
}

extern "C" __declspec(dllexport) void** identify_function(int len) {
    void* func;
    void* lmao;
    size_t bytes_increase = reinterpret_cast<char*>(&func) - reinterpret_cast<char*>(&lmao);

    void** func_pointers = new void*[len];
    for (int i = 0; i < len; ++i) {
        func_pointers[i] = reinterpret_cast<void*>(reinterpret_cast<char*>(&lmao) + i * bytes_increase);
    }

    return func_pointers;
}
