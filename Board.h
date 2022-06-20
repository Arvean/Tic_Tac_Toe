#include <iostream>
using namespace std;
#include <string>
#include <map>
#include <unordered_map>
#include <iterator>
#include <vector>

class Board{
    // Tic-Tac-Toe Board Class definitino. This class will make
    // and print user specified dimensioned square board, take moves by two players,
    // enforce the rules of the game, and determine a result (win, tie)
    public:
        Board();
        Board(int inBoard);
        void printGameBoard();
        void createGrid();
        void takeMove(char player);
        bool check_winner(char player);
        vector<char> players;
    private:
        int board_size;
        int grid_size;
        int move;
        bool player_winner;
        map<int, char> grid;
        void submitMove(int move, char player);
        bool isMoveValid(int move, char player);
        bool valid;
        bool valid_bounds;
        bool checkbounds(int move);
        bool check_location(int move, char player);
};