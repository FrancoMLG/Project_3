#include <iostream>
#include <vector>
#include <tuple>
#include <sstream>
#include <fstream>

int main()
{
    std::vector<std::tuple<std::string, std::string, int, std::string, std::string>> players;
    std::string name, school, position, conference, tempRank, line;
    int rank;
    std::ifstream inFile;
    std::stringstream in;
    inFile.open("playerList.txt");
    while(std::getline(inFile, line))
    {
        in.clear();
        in.str(line);
        std::getline(in, name, '_');
        std::getline(in, school, '_');
        std::getline(in, tempRank, '_');
        rank = std::stoi(tempRank);
        std::getline(in, position, '_');
        std::getline(in, conference);
        players.emplace_back(name,school,rank,position,conference);
    }
    inFile.close();
    return 0;
}
