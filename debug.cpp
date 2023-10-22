#include <iostream>
class Debug{
public:
    static void printArray(const char *arr){
        for(size_t i = 0; i < 9; ++i){
            std::cout << arr[i] << std::endl;
        }
    }
};

