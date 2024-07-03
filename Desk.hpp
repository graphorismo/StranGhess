#include <cstdint>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>


struct DeskData
{

};


class Desk
{
public:

    class FileParser
    {
    public:
        FileParser(std::string dirPath);
        DeskData LoadFromDirectory();
        
    private:
        std::ifstream inputFile;
        std::string directoryPath;
        std::string line;
        std::vector<std::string> lineTokens;
        std::vector<std::vector<int8_t>> placement;
        std::unordered_map<int, std::string> binds;
    };

    void LoadFromDirectory(std::string dirPath);
   
   

};