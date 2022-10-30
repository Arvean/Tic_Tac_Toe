#include "crow_all.h"
#include <fstream>
#include <iostream>

using namespace std;
using namespace crow;
using namespace crow::mustache;

int main(int argc, char* argv[]) {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](const request &req, response &res){
    res.set_header("Content-Type", "text/plain");
    res.write("Hello World");
    res.end();
    });

    

}