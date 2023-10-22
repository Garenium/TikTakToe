#include <iostream>
#include <ctime>
#include <random>

int main(int argc, char* argv[]){

    std::mt19937 mt(time(nullptr));
    std::cout << mt() % 1 << std::endl;

    return 0;
}
