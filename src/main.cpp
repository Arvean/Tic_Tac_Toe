#include "game/Board.h"

int main(int argc, char* argv[]) {
    crow::SimpleApp app;
    unordered_map<int, Board> game;

    CROW_ROUTE(app, "/NewGame")
    ([&game](const request &req, response &res){
        // Create Board
        Board board;
        board.board_id = board.create_board_id();
        for (int i = 1; i <= 9; i++){
            std::string s = std::to_string(i);
            board.board_vector.push_back(s);
        }
        // Initalize Variables
        board.player_1 = "X";
        board.player_2 = "O";
        board.player = board.player_1;
        board.gameover = false;

        res.set_header("Content-Type", "text/plain");
        res.write(to_string(board.board_id));
        res.end();
        game[board.board_id] = board; //store in map
    });

    CROW_ROUTE(app, "/GetBoard/<int>")
    // Send board to client. No input variable, returns board response in json
    ([&game](int client_board_id){
        auto it = game.find(client_board_id);
        if (it == game.end()){
            auto res = crow::response(400, "Board not found");
            res.add_header("Content-type", "text/plain");
            return res;
        }
        else{
            crow::json::wvalue json = it->second.board_to_json(it->second.board_vector);
            return crow::response(json);
        }
    });

    CROW_ROUTE(app, "/Turn/<int>")
    // Print Player Turn
    ([&game](response &res, int client_board_id){
        auto it = game.find(client_board_id);
        if (it == game.end()){
            res.add_header("Content-type", "text/plain");
            res.write("Could not find game ");
            res.end();
        }
        else{
            res.set_header("Content-Type", "text/plain");
            //res.write("Player " + it->second.player + " Turn ");
            res.write(it->second.player);
            res.end();
        }
    });


    CROW_ROUTE(app, "/TakeMove/<int>/<int>")
    // Take the integer move of the player. Update board
    ([&game](response &res, int move, int client_board_id){
        auto it = game.find(client_board_id);
        if (it == game.end()){
            res.add_header("Content-type", "text/plain");
            res.write("Could not find game ");
            res.end();
        }
        else{
            res.set_header("Content-Type", "text/plain");
            //res.write("Player : " + it->second.player + ". ");
            res.write(it->second.player);
            pair<bool, string> p = it->second.check_move(move, it->second.board_vector);
            if (p.first == true){
                it->second.board_vector[move-1] = it->second.player;
                if (it->second.player == "X") {
                    it->second.player = "O";
                }
                else {
                    it->second.player = "X";
                }
                res.write("Valid Move");
            }
            else {
                res.write(p.second + "Please try again");
            }
            res.end();
        }
    });

    CROW_ROUTE(app, "/Gameover/<int>")
    // Check if the game is over. If yes, game ends. If no, game continous.
    ([&game](response &res, int client_board_id){
        auto it = game.find(client_board_id);
        if (it == game.end()){
            res.add_header("Content-type", "text/plain");
            res.write("Could not find game ");
            res.end();
        }
        else{
            res.set_header("Content-Type", "text/plain");
            pair<bool, string> p = it->second.check_winner(it->second.board_vector, it->second.player);
            if (p.first == true){
                it->second.gameover = true;
                res.write("Game is over");
            }
            else{
                it->second.gameover = false;
                res.write("Game is not over");
            }
            res.write(p.second);
            res.end();
        }
    });


    app.port(4000).multithreaded().run();
}