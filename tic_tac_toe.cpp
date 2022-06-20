#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <unordered_map>

class Board{
    public:
        Board();
        Board(int inBoard);
        int board_size;
        char space[3][3];
        unordered_map<int, char> location_map;
        int getGameBoard(int board_size);
        void initializeBoard();
        void printGameBoard(char space[][3]);
        void takeMove(char player);
        void submitMove(int move, char player);
        bool isMoveValid(int move, char player);
        bool valid;
        bool valid_bounds;
        bool valid_location;
        bool checkbounds(int move);
        bool check_location(int move, char player);
};

Board::Board(){
    board_size = 3;
}

Board::Board(int inBoard){
    board_size = inBoard; // Don't need this but wanted to experiment with constructor overloading
}

int Board::getGameBoard(int board_size){
    int user_board_size;
    cout << "Pick a board_size (3 by default): ";
    cin >> user_board_size;
    if (user_board_size == 3){ // Come back and add more sizes later
        return user_board_size;
    }
    else {
        return board_size;
    }
}

void Board::printGameBoard(char space[][3]){
    string vertical_lines = "      |      |      \n";
    string horizantal_lines =  "______|______|______\n";
    switch (board_size){
        case 3:
            for (int i=0; i<board_size; i++){
                cout<< vertical_lines;
                for (int j=0; j<board_size; j++){
                    cout<< "   " << space[i][j] << "   ";
                }
                cout << "   \n";
                cout << horizantal_lines;
            }
            cout << vertical_lines;
    }
}

void Board::initializeBoard(){
    char space[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    board_size = getGameBoard(board_size);
    printGameBoard(space);
}

void Board::submitMove(int move, char player){
    switch (move) {
        case 1:
            space[0][0] = location_map[move];
        case 2:
            space[0][1] = location_map[move];
        case 3:
            space[0][2] = location_map[move];
        case 4:
            space[1][0] = location_map[move];
        case 5:
            space[1][1] = location_map[move];
        case 6:
            space[1][2] = location_map[move];
        case 7:
            space[2][0] = location_map[move];
        case 8:
            space[2][1] = location_map[move];
        case 9:
            space[2][2] = location_map[move];
    }
}

void Board::takeMove(char player){
    int move;
    while(valid == false){
        cout<< "Player " << player << "Turn \n";
        if (player == 'A'){
            cout<< "Choose a location to place a X \n";
        }
        else{
            cout<< "Choose a location to place an O \n";
        }
        cin >> move;
        if (isMoveValid(move, player) == true){
            valid = true;
        }
    }
    //submitMove();
}

bool Board::isMoveValid(int move, char player){
    if (checkbounds(move) == true && check_location(move, player) == true){
        return true;
    }
    else{
        return false;
    }
}

bool Board::checkbounds(int move){
    valid_bounds = false;
    if (0 > move || move > 10){
        cout<< "Out of range try again \n";
    }
    else{
        valid_bounds = true;
    }
    return valid_bounds;
}

bool Board::check_location(int move, char player){
    //auto& location_map = location_maps;
    if (location_map.find(move) != location_map.end()){
        location_map[move] = player;
        return true;
    }
    else {
        return false;
    }
}


int main(){
    bool game_over;
    Board my_board; 
    my_board.initializeBoard(); //Pass in default board size
    while(game_over == false) {
        switch (player) {
            case 'A':
                int j; // Take move....
        }
    }
    myboard.takeMove();

}


// Check location using map
// Store User Input location in map if the key has not been defined (location is free)
// Value will be either X or O
// Set MultiDynamic array location to X or O


// Make variables private