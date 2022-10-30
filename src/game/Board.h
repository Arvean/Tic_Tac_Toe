#ifndef BOARD_H
#define BOARD_H

#include "crow.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <stdlib.h> 
#include <unordered_map>

using namespace std;
using namespace crow;
using namespace crow::mustache;


class Board {

    public:
        int create_board_id();
        crow::json::wvalue board_to_json(vector<std::string> &board_vector);
        bool check_bounds(int &move);
        bool check_location(int &move, vector<std::string> &board_vector);
        std::pair<bool, std::string> check_move(int &move, vector<std::string> &board_vector);
        std::pair<bool, std::string> check_winner(vector<std::string>  &board_vector, std::string &player);
        string player_1;
        string player_2;
        string player;
        bool gameover;
        int board_id;
        std::vector<std::string> board_vector;

};

#endif BOARD_H