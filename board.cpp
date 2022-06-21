#include "Board.h"

// Tic Tac Toe Board class class definition

Board::Board(){
    // Board constructor. Default board size if no parameter is specified by user
    // is 3X3.
    board_size = 3;
}

Board::Board(int inBoard){
    // User specified board constructor
    board_size = inBoard; // Constructor Overloading
}

void Board::createGrid(){
    // Create the grid based on the board size specified in the constructor
    grid_size = board_size * board_size;
    for (int i=0; i<grid_size; i++){
        char c = i;
        grid[i] = c;
        cout << "Key: " << i << "\n";
    }
}

void Board::printGameBoard(){
    // Create and display the Game Board. Inputs the map grid
    // outputs the board
    int i = 0;
    int j = 0;
    int k = 0;
    char space[board_size][board_size];
    char store[grid_size];
    for (auto const& [key, val] : grid){
        store[i] = val;
        i+=1;
    }
    for (int i=0; i<board_size; i++){
        for (int j=0; j<board_size; j++){
            space[i][j] = store[k];
            k+=1;
            }
    }
    string vertical_line = "        |";
    string last_vertical = "        \n";
    string horizantal_line = "________|";
    string last_horizantal = "________\n";
        for (int i=0; i<board_size; i++){
            for (int k=0; k<board_size-1; k++){
                cout<< vertical_line;
            }
            cout << last_vertical;
            for (int j=0; j<board_size; j++){
                int output = int(space[i][j]); // No way to print char so converted ascii O and X to strings
                if (output == 79){
                    cout<< "    " << 'O' << "    ";
                }
                else if (output == 88){
                    cout<< "    " << 'X' << "    ";
                }
                else if (output > 9){
                    cout<< "   " << output << "    ";
                }
                else{
                    cout<< "    " << output << "    ";
                }
            }
            cout << "     \n";
            for (int k=0; k<board_size-1; k++){
                cout<< horizantal_line;
            }
            cout << last_horizantal;
        }
        cout << vertical_line;
        cout << last_vertical;
}

void Board::takeMove(char player){
    //Take the move (int) and check if the move is legal. If move legal,
    // update the grid with the move
    while(valid == false){
        cout<< "Player " << player << " Turn \n";
        if (player == 'X'){
            cout<< "Choose a location to place a X \n";
        }
        else{
            cout<< "Choose a location to place an O \n";
        }
        cin >> move;
        if (isMoveValid(move, player)){
            valid = true;
        }
        else{
            cout<< "Invalid move please try again \n";
        }
    }
    grid[move] = player; //Update grid if the move is valid
    valid = false;
}

bool Board::isMoveValid(int move, char player){
    // Check if the move is within the boundaries of the grid. Check if the grid where the move
    // is requested is already occupied. Return a boolean (true) if both coniditions are satisified
    if (checkbounds(move) == true && check_location(move, player) == true){
        return true;
    }
    else{
        return false;
    }
}

bool Board::checkbounds(int move){
    // Takes the move (int) and check if the move is within the boundaries of the grid
    valid_bounds = false;
    if (move < 0 || move >= grid_size){
        cout<< "Out of range try again \n";
    }
    else{
        valid_bounds = true;
    }
    return valid_bounds;
}

bool Board::check_location(int move, char player){
    // Check if location is occupied. Return true if it is not occupied
    if (find(players.begin(), players.end(), grid[move]) != players.end()){
        cout<< "Space full! Pick another space!";
        return false;
    }
    else{
        return true;
    }
}

bool Board::check_winner(char player){
    // Return true if there is a winner. Checks a win by row, column, and diagnol
    bool win_by_row;
    bool win_by_column;
    bool win_by_diag_1;
    bool win_by_diag_2;
    bool check_diag_1 = true;
    bool check_diag_2 = true;
    //----------------------------------------------------------
    // Copied code from printGameBoard because I did not know how to 
    // pass in a multidimensional array as a parameter. Note to come back
    // to this
    int space[board_size][board_size];
    int store[grid_size];
    win_by_diag_1 = true;
    win_by_diag_2 = true;
    int i = 0;
    int j = 0;
    int z = 0;
    int k = board_size -1;

    for (auto const& [key, val] : grid){
        cout << "Key: " << key<< " Value: " << int(val) << "\n";
        store[i] = val;
        i+=1;
    }

    for (int i=0; i<board_size; i++){
        for (int j=0; j<board_size; j++){
            space[i][j] = int(store[z]);
            z+=1;
            }
    }
    //----------------------------------------------------------

    for (int i=0; i<board_size; i++){
        win_by_row = true;
        win_by_column = true;
        bool check_row = true;
        bool check_column = true;

        for (int j=0; j<board_size; j++){
            // Check win by row
            if (win_by_row == true && check_row == true){
                if (space[i][j] != int(player)) {
                    win_by_row = false;
                    check_row = false;
                }
            }
            // Check win by column
            if (win_by_column == true && check_column == true){
                if (space[j][i] != int(player)){
                    win_by_column = false;
                    check_column = false;
                }
            }
        }
        // Check win by diagnol
        if (win_by_diag_1 == true && check_diag_1 == true){
            if (space[i][i] != int(player)){
                win_by_diag_1 = false;
                check_diag_1 = false;
            }
        }

        if (win_by_diag_2 == true && check_diag_2 == true){
            if (space[i][k] != int(player)){
                win_by_diag_2 = false;
                check_diag_2 = false;
            }
        }
        k -= 1;
        // Check if won by row or column
        if (win_by_row == true || win_by_column == true){
            printf("Won by row or column \n");
            player_winner = true;
            return player_winner;
        }
    }
    // Check if won by diagnol
    if (win_by_diag_1 == true || win_by_diag_2 == true){
        printf("Won by diagnol \n");
        player_winner = true;
        return player_winner;
    }
    cout << "YANDI! \n";
    return false;
}