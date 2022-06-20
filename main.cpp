#include "Board.h"

int main(){
    bool game_over;
    bool player_winner;
    bool winner_1;
    bool winner_2;
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
        my_board.printGameBoard();
        switch(player){
            case 'X':
                my_board.printGameBoard();
                my_board.takeMove(player);
                winner_1 = my_board.check_winner(player);
                player = player_2;
                if (winner_1 == true){
                    game_over = true;
                    my_board.printGameBoard();
                    cout<< "Player X is a winner! \n1";
                }
            case 'O':
                my_board.printGameBoard();
                my_board.takeMove(player);
                winner_2 = my_board.check_winner(player);
                player = player_1;
                if (winner_2 == true){
                    game_over = true;
                    my_board.printGameBoard();
                    cout<< "Player O is a winner! \n1";
                }
        }
    }
}