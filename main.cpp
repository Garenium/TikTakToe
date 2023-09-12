#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


const char arr[9] = {'-','-','-','-','-','-','-','-','-',};

void printXO(){
    for(size_t i = 0; i < 3; ++i){
        for(size_t y = 0; y < 3; ++y){
            std::cout << arr[i];
        }
        std::cout << '\n';
    }
    std::cout << std::endl;
}


void help(){
    const char* help_grid = "0|1|2\n3|4|5\n6|7|8";
    std::cout << help_grid << '\n' << std::endl;
    std::cout << "Syntax:\n coordinate x|y\n" << std::endl;
}

int main(int argc, char* argv[]){

    //Variables
    std::string user_input = "";
    bool i_start = false;
    bool h_help = false;
    const char* ptr = NULL;
    //0 is o 
    //1 is x 
    int x_or_o = 0;
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
            std::cout << "Computer: " << std::endl;
            printXO();
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
