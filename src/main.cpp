#include "game/Board.h"

int main(int argc, char* argv[]) {
    crow::SimpleApp app;
    std::map<int, Board> game;
    std::vector<int> board_ID_vector;
    map<int, Board> game_waiting_map;
    int count = 0;

    CROW_ROUTE(app, "/NewGame").methods("POST"_method, HTTPMethod::GET)
    ([&game, &count, &board_ID_vector, &game_waiting_map](const crow::request &req){
        count += 1;
        //auto it = game_waiting_map.find(stoi(req.body));
        //if (it != game_waiting_map.end()) {
            //Private Match is found
        //    game[it->first] = it->second;
        //}
        if (count == 1) {
            // First Player
            // Create Board Object
            Board board;
            board.player = "X";
            board.board_id = board.create_board_id();
            for (int i = 1; i <= 9; i++){
                std::string s = std::to_string(i);
                board.board_vector.push_back(s);
            }
            // Initialize Variables
            board.gameover = false;
            board.move_counter = board.board_vector.size();
            std::vector<crow::json::wvalue> boardIDDebug;
            boardIDDebug.push_back(to_string(board.board_id));
            boardIDDebug.push_back("Count" + to_string(count));
            // Seperate cookie from private lobby response
            //crow::json::rvalue parsedJson = crow::json::load(req.body);
            std::size_t found = req.body.find("$");
            boardIDDebug.push_back("Found: " + to_string(found));
            boardIDDebug.push_back("Length of data:" + to_string(req.body.length()));
            if (found!=std::string::npos){
                string cookie = req.body.substr(0, found);
                string isPrivateLobby = req.body.substr(found+1, req.body.length()-1);
                board.store_cookie(cookie);
                boardIDDebug.push_back("Cookie: " + cookie);
                boardIDDebug.push_back("isPrivateLobby: " + isPrivateLobby);
                if (isPrivateLobby == "false") {
                    game[board.board_id] = board;
                    board_ID_vector.push_back(board.board_id);
                }
                else {
                    game_waiting_map[board.board_id] = board;
                    count = 0;
                }
            }
            crow::json::wvalue sendboardIDDebug = boardIDDebug;
            return crow::response(sendboardIDDebug);
        }
        else if (count == 2){
            // Second Player and check to see if the name is different than first user
            if (req.body!=game[board_ID_vector.back()].cookie_vector[0]){ 
                count = 0; //Reset counter
                std::vector<crow::json::wvalue> boardIDDebug;
                boardIDDebug.push_back(to_string(game[board_ID_vector.back()].board_id));
                //boardIDDebug.push_back("Size of vector before second player:" + to_string(game[board_ID_vector.back()].cookie_vector.size()));
                for ( const auto &iter : game) {
                    boardIDDebug.push_back(iter.first);
                }
                boardIDDebug.push_back("Incoming board ID Vector: ");
                for (int i = 0; i < board_ID_vector.size(); i++) {
                    boardIDDebug.push_back(board_ID_vector[i]);
                }
                std::size_t found = req.body.find("$");
                string cookie = req.body.substr(0, found);
                game[board_ID_vector.back()].store_cookie(cookie);
                crow::json::wvalue sendboardIDDebug = boardIDDebug;
                return crow::response(sendboardIDDebug);
            }
            else {
                count = 1;
                std::vector<crow::json::wvalue> boardIDDebug;
                boardIDDebug.push_back("error");
                boardIDDebug.push_back("Count" + to_string(count));
                crow::json::wvalue sendboardIDDebug = boardIDDebug;
                return crow::response(sendboardIDDebug);
            }
        }
    });

    CROW_ROUTE(app, "/GetBoard/<int>")
    // Send board to client
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
    ([&game](int client_board_id){
        auto it = game.find(client_board_id);
        if (it == game.end()){
            auto res = crow::response(400, "Could not find game ");
            res.add_header("Content-type", "text/plain");
            return res;
        }
        else{
            std::vector<crow::json::wvalue> playerIDvector;
            // Send back both symbol (X, O) and player cookie ID
            playerIDvector.push_back(it->second.player);
            playerIDvector.push_back(it->second.cookie_map[it->second.player]);
            crow::json::wvalue sendTurn = playerIDvector;
            return crow::response(sendTurn);
        }
    });


    CROW_ROUTE(app, "/TakeMove/<int>/<int>").methods("POST"_method, HTTPMethod::GET)
    // Take the integer move of the player. Update board
    ([&game](const crow::request &req, int move, int client_board_id){
        auto it = game.find(client_board_id);
        std::string cookie = req.body;
        if (it == game.end()){
            auto res = crow::response(400, "Could not find game ");
            res.add_header("Content-type", "text/plain");
            return res;
        }
        else if (cookie == it->second.cookie_map[it->second.player]){ // Check if the correct player is sending the move
            //res.set_header("Content-Type", "text/plain");
            //res.write(it->second.player);
            //res.write(it->second.cookie_map[it->second.player]);
            pair<bool, string> p = it->second.check_move(move, it->second.board_vector);
            if (p.first == true){
                it->second.board_vector[move-1] = it->second.player;
                if (it->second.player == "X") {
                    it->second.player = "O";
                }
                else {
                    it->second.player = "X";
                }
                it->second.move_counter -= 1;
                auto res = crow::response("Valid Move");
                res.add_header("Content-type", "text/plain");
                return res;
            }
            else {
                auto res = crow::response(p.second + "Please try again");
                res.add_header("Content-type", "text/plain");
                return res;
            }
        }
        else{
            std::vector<crow::json::wvalue> storeMoveDebug;
            storeMoveDebug.push_back("Wait for your turn! ");
            for (int i = 0; i < it->second.cookie_vector.size(); i++) {
                storeMoveDebug.push_back(it->second.cookie_vector[i]);
            }
            crow::json::wvalue MoveDebug = storeMoveDebug;
            return crow::response(MoveDebug);
            // The backend cookie map is having problems. Want to look inside Cookie vector to see what is going on
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
            pair<bool, string> p = it->second.check_winner(it->second.board_vector, it->second.player, it->second.move_counter);
            if (p.first == true){
                it->second.gameover = true;
                res.write("Game is over. ");
            }
            else{
                it->second.gameover = false;
                res.write("Game is not over.");
            }
            res.write(p.second);
            res.end();
        }
    });


    app.port(4000).multithreaded().run();
}
