#include <iostream>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <random>
#include "debug.cpp"

char arr[3][3] = {
    {'-','-','-'},
    {'-','-','-'},
    {'-','-','-'}
};

const char arrRef[3][3] = {
    {'1', '2', '3'},   
    { '4', '5', '6'},
    {'7', '8', '9'},
};


int movements[9] = { 0 };
std::random_device rd;
std::default_random_engine generator(rd()); 

void help(){
    const char* help_grid = "1|2|3\n-----\n4|5|6\n-----\n7|8|9";

    std::cout << help_grid << '\n' << std::endl;
    /* std::cout << "Syntax:\n coordinate x|y\n" << std::endl; */
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


bool validate_user_move_inp(std::string& user_input){
    bool isValid = false;

    if(user_input.length() == 1 && user_input[0] != '\n' && strspn(user_input.c_str(), "123456789") == 1){
        std::cout << "DEBUG: Input is valid" << std::endl;
        return true;
    }

    return false;
}


void user_select_xo(char* computer_xo){

    std::string user_input = "";
    char selected_input = '\0';
    while(*computer_xo != 'X' || *computer_xo != 'O'){
        std::cout << "X or O? (X is default): ";
        std::getline(std::cin, user_input); 

        std::cout << std::endl;

        
        if(user_input.length() == 0){
            user_input = "X";
        }

        selected_input = std::toupper(user_input[0]);

        if(selected_input == 'X'){ *computer_xo = 'O'; break; }
        else if(selected_input == 'O') { *computer_xo = 'X'; break; }
        else { std::cout << "Please try again..." << std::endl; continue; }

    }

}


void computer_move(const char* computer_xo){
    //loop the arr to check if the game is won by the user or by the player

    //use/take that info to determine the next move
    
    while(true){
        std::uniform_int_distribution<int> distribution(0,2);
        int row_index = distribution(generator);
        int col_index = distribution(generator);
        /* printf("Computer:\nRow: %d, Column: %d\n", row_index, col_index); */

        //If the square has already been selected, loop back to generate
        //a new coordinate
        if(arr[row_index][col_index] == '-'){
            arr[row_index][col_index] = *computer_xo;
            break;
        }
        else{
            std::cout << "TODO: Debug computer_move()" << std::endl;
            /* continue; */
            exit(0);
        }
    }
    
}

bool player_move(char* player_square_no, const char* player_xo){

    //Make sure if the square input is valid
    int targetRow = 0;
    int targetCol = 0;
    bool validMove = false;
    

    bool foundCoordinate = false;
    //Find the coordinates for the player_square_no
    for(int i = 0; i < 3 && !foundCoordinate; i++){
        for(int j = 0; j < 3; j++ ){
            if(*player_square_no == arrRef[i][j]){
                targetRow = i;
                targetCol = j;
                foundCoordinate = true;
            }
        }
    }

    //If the coordinates have not been selected before, mute the value to 
    //either x or o (for the player)
    if(arr[targetRow][targetCol] == '-'){
        arr[targetRow][targetCol] = *player_xo;
        validMove = true;
    }
    else{
        std::cout << "Square *" << *player_square_no << "* is filled. Try another square." << std::endl;
    }

    return validMove;
}



int main(int argc, char* argv[]){

    //VARIABLES
    std::uniform_int_distribution<int> distribution_x_or_o(0,1);
    //Variables
    std::string user_input = "";
    bool i_start = false;
    bool h_help = false;
    const char* ptr = NULL;
    char computer_xo = 0;
    char player_xo = 0;

    //COMMAND LINE ARGS
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

    //WELCOME 
    //Print the XO grid  
    std::cout << "The Grid (emtpy):" << std::endl;
    printXO();
    
    //PREPARATION
    //Don't prompt if you want to start immediately
    if(i_start == false){
        std::cout << std::endl;
        bool prompt_i_start = true;
        std::cout << "Do you want to start? (Y/n): ";
        std::getline(std::cin, user_input);

        std::cout << std::endl;

        if (user_input.empty() || user_input[0] == 'y' || user_input[0] == 'Y')    
            prompt_i_start = true ;
        else 
            prompt_i_start = false;


        if(prompt_i_start == false){
            computer_xo = distribution_x_or_o(generator);
            computer_xo == 0 ? computer_xo = 'O' : computer_xo = 'X';
            computer_move(&computer_xo);
            printXO();
        }
        else{
            user_select_xo(&computer_xo);
        }
    }
    else{
        user_select_xo(&computer_xo);
    }

    if(computer_xo == 'O') { player_xo = 'X'; }
    else if (computer_xo == 'X') {player_xo = 'O'; }

    std::cout << "You have selected: "<< player_xo << std::endl;
    std::cout << "Computer has selected: " << computer_xo << '\n' << std::endl;

    //START THE GAME (PROMPT THE USER FOR A MOVE)

    while(true){
        std::cout << "User " << "(" << player_xo << ")" << ": ";
        std::cin >> user_input;

        if(validate_user_move_inp(user_input)){
            /* std::cout << "Correct input" << std::endl; */
            char square_no = user_input[0];
            if(player_move(&square_no, &player_xo)){
                computer_move(&computer_xo);
                printXO();            
            }
            /* return 0; */
        }
        else{
            std::cout << "Please retry again..." << std::endl;
        }
    }

    return 0;
}
