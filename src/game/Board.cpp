#include "Board.h"

int Board::create_board_id(){
    int board_id = rand();
    return board_id;
}

crow::json::wvalue Board::board_to_json(vector<std::string> &board_vector) {
    // Converts the board to json prior to a response
    std::vector<crow::json::wvalue> board_vector_json;
    for (int i = 0; i < 9; i++){
        board_vector_json.push_back(board_vector[i]);
    }
    crow::json::wvalue json(board_vector_json);
    return json;
}

bool Board::check_bounds(int &move)
{
    if (move > 9 || move < 1){
        return false;
    }
    return true;
}

bool Board::check_location(int &move, vector<std::string> &board_vector)
{
    if (board_vector[move-1] == "X" || board_vector[move-1] == "O") {
        return false;
    }
    return true;
}

std::pair<bool, std::string> Board::check_move(int &move, vector<std::string> &board_vector){
    if (check_bounds(move) == true && check_location(move, board_vector) == true){
        return make_pair(true, "Valid move");
    }
    else if (check_bounds(move) == false && check_location(move, board_vector) == true){
        return make_pair(false, "Move not in bounds");
    }
    else if (check_bounds(move) == true && check_location(move, board_vector) == false){
        return make_pair(false, "Spot full");
    }
    else{
        return make_pair(false, "Move not in bounds and spot full");
    }
}

std::pair<bool, std::string> Board::check_winner(vector<std::string>  &board_vector, std::string &player, int &move_counter) {
    // Function to enforce the rules of Tic Tac Toe. Checks if there is a winner

    // ------------ Initialize Variables ------------

    int board_size = 3;
    int i = 0;
    int j = 0;
    int z = 0;
    int k = board_size -1;
    int space[board_size][board_size];

    // ------------ Create Grid ------------

    for (int i=0; i<board_size; i++){
        for (int j=0; j<board_size; j++){
            if (board_vector[z] == "X") { 
                space[i][j] = 88;
            }
            else if (board_vector[z] == "O") {
                space[i][j] = 79;
            }
            else {
                space[i][j] = stoi(board_vector[z]);
            }
            z+=1;
        }
    }

    // ------------ Player -----------------
    int player_int;
    string player_output;
    if (player == "O") {
        player_output = "X";
        player_int = 88;
    }
    else {
        player_output = "O";
        player_int = 79;
    }

    // ------------ Logic ------------
    bool gameover = false;
    bool win_by_diag_1 = true;
    bool win_by_diag_2 = true;

    if (move_counter == 0) {
        gameover = true;
    return make_pair(gameover, "Tie Game!");
    }

    for (int i=0; i<board_size; i++){
        bool win_by_row = true;
        bool win_by_column = true;

        for (int j=0; j<board_size; j++){
            // Check win by row
            if (win_by_row == true){
                if (space[i][j] != player_int) {
                    win_by_row = false;
                }
            }
            // Check win by column
            if (win_by_column == true){
                if (space[j][i] != player_int){
                    win_by_column = false;
                }
            }
        }
        // Check win by diagonol
        if (win_by_diag_1 == true){
            if (space[i][i] != player_int){
                win_by_diag_1 = false;
            }
        }
        if (win_by_diag_2 == true){
            if (space[i][k] != player_int){
                win_by_diag_2 = false;
            }
        }
        k -= 1;
        // Check if won by row or column
        if (win_by_row == true || win_by_column == true){
            gameover = true;
            return make_pair(gameover, player_output + " Won by row or column");
        }
    }
            // Check if won by diagonol
    if (win_by_diag_1 == true || win_by_diag_2 == true){
        gameover = true;
        return make_pair(gameover, player_output + " Won by diagonol");
    }
    return make_pair(false,"");
}
