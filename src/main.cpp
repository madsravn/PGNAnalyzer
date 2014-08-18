#include <iostream>
#include "Game.hpp"

int main() {
    Game p;
    p.parse("/home/mads/projects/PGNAnalyzer/games/game1.pgn");
    p.printGame();
    return 0;
}
