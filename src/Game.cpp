#include "Game.hpp"
#include <regex>


Game::Game() {
    enums = {"Event", "Site", "Date", "White", "Black", "Result", "WhiteElo", "BlackElo", "TimeControl", "Termination"};
    list = {"","","","","","","","","",""};
}


bool
Game::find(const std::string& type, const std::string& value) {
    int index = indexOf(type);
    if(index != -1) {
        if(list.at(index) == value) {
            return true;
        }
    }
    return false;
}

int
Game::indexOf(std::string str) {
    unsigned int resultIndex = std::find(enums.begin(),enums.end(), str) - enums.begin();
    if(resultIndex < enums.size()) {
        return resultIndex;
    }
    return -1;
}

void
Game::printGame() {
    for(const auto& m : moves) {
        std::cout << m << ", ";
    }
    std::cout << std::endl;
}

std::string
Game::getType() {
    int index = indexOf("TimeControl");
    if(index < 0) {
        std::cout << "ERROR" << std::endl;
        return "";
    }
    return list.at(index);
}

std::string
Game::getResult() {
    int index = indexOf("Result");
    return list.at(index);
}

std::string
Game::getBlack() {
    int index = indexOf("Black");
    return list.at(index);
}

std::string
Game::getWhite() {
    int index = indexOf("White");
    return list.at(index);
}

bool
Game::getDraw() {
    int index = indexOf("Result");
    if(list.at(index) == "½-½") {
        return true;
    }
    return false;
}


std::string
Game::getMonth() {
    std::string date = list.at(2);
    if(date == "") {
        return "";
    }
    std::string month = date.substr(0,date.find_last_of("."));
    return month;
}


std::string
Game::getWinner() {
    int resultIndex = std::find(enums.begin(),enums.end(), "Result") - enums.begin();
    std::string result = list.at(resultIndex);
    if(result == "0-1") {
        int blackResult = std::find(enums.begin(),enums.end(), "Black") - enums.begin(); 
        return list.at(blackResult);
    }
    if(result == "1-0") {
        int whiteResult = std::find(enums.begin(),enums.end(), "White") - enums.begin();
        return list.at(whiteResult);
    }
    // Either there's an error or the game was draw
    return "";

}

const std::string
Game::getLoser() const {
    int resultIndex = std::find(enums.begin(), enums.end(), "Result") - enums.begin();
    std::string result = list.at(resultIndex);
    if(result == "0-1") {
        int whiteResult = std::find(enums.begin(), enums.end(), "White") - enums.begin();
        return list.at(whiteResult);
    }
    if(result == "1-0") {
        int blackResult = std::find(enums.begin(), enums.end(), "Black") - enums.begin();
        return list.at(blackResult);
    }
    // Either there's an error or the game was draw

    return "";
}


// Removing whitespace at the start and end of the string.
std::string trim(std::string s) {
    std::regex reg("^[[:space:]]*(.*)[[:space:]]*$");
    std::smatch result;
    if(std::regex_search(s, result, reg)) {
        return result.str(1);
    }
    return s;
}

void
Game::parse(std::string tfile) {
    std::ifstream file;
    std::string line;
    std::string game;
    file.open(tfile);
    if(file.is_open()) {
        while(file.good()) {
            std::getline(file,line);
            std::cout << line << std::endl;
            line = trim(line);
            if(line.length() > 0) {
                if(line.at(0) == '[') {
                    parseHeader(line);
                } else {
                    parseMoves(line);
                }
            }
        }
        file.close();
    }
}



//TODO: Make decent. Currently doesn't work with commented PGN files (maybe more)
void
Game::parseHeader(std::string line) {
    std::istringstream str(line);
    // Is it a STRtag? 
    if(line.at(0) == '[') {
        char a;
        str >> a;
        std::string event;
        str >> event;
        //std::cout << event << std::endl;
        unsigned int index = std::find(enums.begin(),enums.end(), event) - enums.begin();
        //std::cout << index << std::endl;
        if(index < enums.size()) {
            str >> std::ws;
            str >> a;
            std::string name;
            // Change to a more stringstream friendly way
            std::getline(str,name);
            std::string::size_type end = name.find_first_of("\"");
            name = name.substr(0,end);
            //std::cout << name << std::endl << std::endl;
            list.at(index) = name;
        }
    } 
    
}

std::string removeComments(std::string line) {
    std::regex clampedcomment("\\{(.*?)\\}");
    std::regex rolcomment(";(.*)$");
    line = std::regex_replace(line, clampedcomment, " ");
    line = std::regex_replace(line, rolcomment, "");
    return line;
}

void
Game::parseMoves(std::string line) {
    // it's chess notation or an "empty" line. do something with it later.
    line = removeComments(line);
    std::istringstream str(line);
    std::string move;
    while(str >> move) {
        std::string tmp = "";
        if(move.find(".") != std::string::npos) {
            tmp = move.substr(move.find(".")+1);
        } else {
            tmp = move;
        }
        // TODO: Is this a complete list?
        std::size_t pos = tmp.find_first_of("+#!?");
        moves.push_back(tmp.substr(0, pos));
    }
    // TODO: Check if it is an actual move
    std::string lastmove = moves.at(moves.size()-1);
    if(lastmove == "0-1" || lastmove == "1-0" || lastmove == "½-½" || lastmove == "1/2-1/2") {
        moves.pop_back();
    }
    
}



