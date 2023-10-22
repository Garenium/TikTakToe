#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char* argv[]){
    srand(time(NULL));

   char arr[9] = {'-','-','-','-','-','-','-','-','-'};
    int history[9] = { 0 };

    //history_index 0 is NOT inclusive. First move is 1
    int history_index = 0;
    int index;


    while(true){

        index = rand() % 9;
        //Keep trying to find the index that is not 
        /* for(size_t i = history_index; i = 0; --i){ */
        /*     index = rand() % 9; */
        /* } */

        arr[index] = 'O';

        for(size_t i = 0; i < 9; ++i){
          std::cout << arr[i];
          if((i+1) % 3 == 0){
             std::cout << "\n";
          }
        }

        std::cout << "Index: "<< index << "\n---------------"<< std::endl;

        const auto start = std::chrono::high_resolution_clock::now();
        std::this_thread::sleep_for(2000ms);
        const auto end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::milli> elapsed = end - start;

    }

    return 0;
}
