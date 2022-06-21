#include "Board.h"

int main(){
    // Function to create board based on an user specified dimension
    // then to run the Tic Tac Toe game
    bool game_over = false;
    bool winner_1 = false;
    bool winner_2 = false;
    int board_size;
    cout << "Welcome to Tic Tac Toe. Please specify the board size \n";
    cin >> board_size;
    Board my_board(board_size);
    my_board.createGrid();
    my_board.players = {'X', 'O'};
    char player_1 = my_board.players.at(0);
    char player_2 = my_board.players.at(1);
    char player = player_1;
    while (game_over == false){
        switch(player){
            case 'X':
                my_board.printGameBoard();
                my_board.takeMove(player);
                winner_1 = my_board.check_winner(player);
                player = player_2;
                if (winner_1 == true){
                    game_over = true;
                    my_board.printGameBoard();
                    cout<< "Player X is a winner! \n";
                }
                break;
            case 'O':
                my_board.printGameBoard();
                my_board.takeMove(player);
                winner_2 = my_board.check_winner(player);
                player = player_1;
                if (winner_2 == true){
                    game_over = true;
                    my_board.printGameBoard();
                    cout<< "Player O is a winner! \n";
                }
                break;
        }
    }
}