#ifndef GAME_HPP_
#define GAME_HPP_
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
class Game {
public:
    Game();
    void parse(std::string tfile);
    void parseHeader(std::string line);
    void parseMoves(std::string line);
    std::string getWinner();
    const std::string getLoser() const;
    std::string getMonth();
    bool getDraw();
    std::string getType();
    std::string getResult();
    std::string getWhite();
    std::string getBlack();
    bool find(const std::string& type, const std::string& value);
    int indexOf(std::string str);
    void printGame();
private:
    std::vector<std::string> list;
    std::vector<std::string> enums;
    std::vector<std::string> moves;


};

#endif
