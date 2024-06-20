#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <typeinfo>

typedef void (*func_ptr)();

struct Function {
    std::string Name;
    std::string ReturnType;
    std::string Value;
};

extern "C" __declspec(dllexport) Function* calling_function(void* function_ptr_t[], int len) {
    Function* functions = new Function[len];
    for (int i = 0; i < len; i++) {
        functions[i].Name = "Function " + std::to_string(i);
        functions[i].ReturnType = typeid(function_ptr_t[i]).name();

        func_ptr func = reinterpret_cast<func_ptr>(function_ptr_t[i]);
        if (std::string(functions[i].ReturnType).find("int") != std::string::npos) {
            int result;
            func_ptr func = reinterpret_cast<func_ptr>(function_ptr_t[i]);
            result = reinterpret_cast<int(*)()>(func)();
            functions[i].Value = std::to_string(result);
        } else if (std::string(functions[i].ReturnType).find("void") != std::string::npos) {
            functions[i].Value = "void";
        } else {
            functions[i].Value = "Unknown";
        }
    }
    return functions;
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
