#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include "debug.cpp"

char arr[3][3] = {
    '-','-','-',
    '-','-','-',
    '-','-','-'
};

/* char arr[9] = {'-','-','-', '-','-','-', '-','-','-' }; */

int movements[9] = { 0 };
std::random_device rd;
std::default_random_engine generator(rd()); 

void help(){
    const char* help_grid = "0,0|0,1|0,2\n------------\n1,0|1,1|1,2\n------------\n2,0|2,1|2,2";

    std::cout << help_grid << '\n' << std::endl;
    std::cout << "Syntax:\n coordinate x|y\n" << std::endl;
}

void printArray(){
    for(size_t i = 0; i < 9; ++i){
        std::cout << arr[i];
    }
    std::cout << '\n' << std::endl;
}


void printXO(){
    for(size_t i = 0; i < 3; ++i){
        for(size_t j = 0; j < 3; ++j){
            std::cout << arr[i][j];
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}

void computer_move(char x_or_o){
    std::uniform_int_distribution<int> distribution(0,2);
    int row_index = distribution(generator);
    int col_index = distribution(generator);
    printf("Computer: row: %d, column: %d\n", row_index, col_index);
    arr[row_index][col_index] = x_or_o;
    printXO();
}


int main(int argc, char* argv[]){

    /* srand(time(NULL)); */
    std::uniform_int_distribution<int> distribution_x_or_o(0,1);

    //Variables
    std::string user_input = "";
    bool i_start = false;
    bool h_help = false;
    const char* ptr = NULL;
    //0 is o 
    //1 is x 
    char x_or_o = 0;

    int c = 0;
    while((c = getopt(argc,argv,"ih")) != -1){
        switch(c){
            case 'i':
                i_start = true;
                break;
            case 'h':
                h_help = true;
                break;
        }
    }

    if(h_help == true){
        std::cout << "\nHELP:" << std::endl;
        help();
    }
    
    //Print the XO grid  
    std::cout << "The Grid:" << std::endl;
    printXO();
    
    //Don't prompt if you want to start immediately
    if(i_start == false){
        bool prompt_i_start = true;
        std::cout << "Do you want to start? (Y/n)" << std::endl;
        std::cin >> user_input;
        std::cout << '\n';

        (user_input[0] == 'y' || user_input[0] == 'Y') ? prompt_i_start = true : prompt_i_start = false;

        if(prompt_i_start == false){
            x_or_o = distribution_x_or_o(generator);
            x_or_o == 0 ? x_or_o = 'O' : x_or_o = 'X';
            computer_move(x_or_o);
        }
    }

    while(true){
        std::cout << "User: ";
        std::cin >> user_input;

        if(user_input[0] != '\n' && strspn(user_input.c_str(), "xXoO") == 1){
            std::cout << "Correct input" << std::endl;
            return 0;
        }
        else{
            std::cout << "Please retry again..." << std::endl;
        }
    }

    return 0;
}
