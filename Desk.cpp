#include <cstdint>
#include <fstream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <vector>

#include "Cursor.hpp"
#include "Desk.hpp"
#include "Piece.hpp"
#include "nlohmann/json.hpp"

std::vector<std::vector<int8_t>> Desk::GetPlacement()
{
    std::vector<std::vector<int8_t>> transformedPlacement (height);
    for (auto vec : transformedPlacement) vec.resize(width);

    for(int8_t i = 0; i < height; ++i)
    {
        for (int8_t j = 0; j < width; ++j)
        {
            transformedPlacement[i][j] = placement.at({i, j}).code;
        }
    }
    return transformedPlacement;
}

void Desk::ChangeCursorState()
{
    int8_t mod = 0;
    if (deskState == DeskState::WHITE_TURN) mod = 1;
    else if (deskState == DeskState::BLACK_TURN) mod = -1;

    if (cursor.state == CursorState::FREE) 
    {
        bool didChooseRightPiece = placement.at(cursor.position).code*mod > 0;
        if (!didChooseRightPiece) return;

        auto pickedPiece = placement.at(cursor.position);
        if (pickedPiece == EMPTY_PIECE) return;

        placement[cursor.position] = EMPTY_PIECE;
        cursor.pickedPiece = pickedPiece;

        cursor.state = CursorState::WITH_PIECE;
    }
    else if (cursor.state == CursorState::WITH_PIECE)
    {
        auto targetedPiece = placement.at(cursor.position);
        auto attackingPiece = cursor.pickedPiece;

        if (attackingPiece == EMPTY_PIECE) return;

        if (targetedPiece == EMPTY_PIECE 
            || targetedPiece.code * attackingPiece.code < 0)
        {
            placement[cursor.position] = attackingPiece;
            cursor.pickedPiece = EMPTY_PIECE;
            cursor.state = CursorState::FREE;
            return;
        }
    }

}

void Desk::UpdateByInputingSymbol(char symbol)
{
    switch (symbol) 
    {
        case 'w':
            if (cursor.position.y == 0) break;
            cursor.position.y -= 1;
        break;

        case 'a':
            if (cursor.position.x == 0) break;
            cursor.position.x -= 1;
        break;
        
        case 's':
            if (cursor.position.y == height) break;
            cursor.position.y += 1;
        break;
        
        case 'd':
            if (cursor.position.x == width) break;
            cursor.position.x += 1;
        break;
        
        case 'f':
            ChangeCursorState();
        break;

        default:
        break;
        
    }
}


Desk::FileParser::FileParser(std::string dirPath)
:directoryPath(dirPath)
{

}

Desk Desk::FileParser::LoadDesk()
{
    Desk newDesk;
    std::ifstream inputFile {directoryPath};
    nlohmann::json fileAsJson = nlohmann::json::parse(inputFile);
    for(auto line : fileAsJson["placement"])
    {
        
    }
    return newDesk;
}