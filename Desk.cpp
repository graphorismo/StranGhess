#include <fstream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#include "Desk.hpp"
#include "PieceStats.hpp"
#include "nlohmann/json.hpp"

void Desk::LoadFromDirectory(std::string dirPath)
{
    FileParser parser {dirPath};
    data = parser.LoadFromDirectory(); 
}

Desk::FileParser::FileParser(std::string dirPath)
:directoryPath(dirPath)
{

}

DeskData Desk::FileParser::LoadFromDirectory()
{
    std::ifstream inputFile {directoryPath};
    nlohmann::json fileAsJson = nlohmann::json::parse(inputFile);
    for(auto line : fileAsJson["placement"])
    {
        
    }
    return {};
}