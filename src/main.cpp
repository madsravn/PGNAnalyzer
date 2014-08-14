#include <iostream>
#include "Game.hpp"

int main() {
    std::cout << "Hello, world!" << std::endl;
    Game p;
    p.parse("/home/mads/projects/PGNAnalyzer/games/game1.pgn");
    return 0;
}
