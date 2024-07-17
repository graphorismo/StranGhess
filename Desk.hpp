#include <cstdint>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>

#include "Cursor.hpp"
#include "Piece.hpp"
#include "Vector2d.hpp"


enum class DeskState
{
    UNKNOWN = 0,

    WHITE_TURN,
    BLACK_TURN
};


class Desk
{
public:
    std::vector<std::vector<char>> GetPlacement();
    void UpdateByInputingSymbol(char symbol);
    Cursor GetCursor();

    class FileParser
    {
    public:
        FileParser(std::string dirPath);
        Desk LoadDesk();

    private:
        std::ifstream inputFile;
        std::string directoryPath;
        std::string line;
        std::vector<std::string> lineTokens;
        
        std::unordered_map<int, std::string> binds;
    };
   
private:
    int8_t height = 0;
    int8_t width = 0;
    DeskState deskState = DeskState::WHITE_TURN;
    std::unordered_map<Vector2d<int8_t>, Piece> placement;
    Cursor cursor;

    
    void ChangeCursorState();

};