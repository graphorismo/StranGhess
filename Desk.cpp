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
    std::ifstream inputFile (directoryPath+"/placement.json");
    nlohmann::json fileAsJson = nlohmann::json::parse(inputFile);
    inputFile.close();

    for(auto i = 0; i < fileAsJson["placement"].size(); ++i)
    {
        auto line = fileAsJson["placement"][i];
        int8_t y = fileAsJson["placement"].size();
        for (auto j = 0; j < line.size(); ++j)
        {
            int8_t x = line.size();
            auto position = Vector2d<int8_t>{y, x};
            newDesk.placement.insert({position, EMPTY_PIECE});
            newDesk.placement[position].position = position;
            int8_t code = line[j];
            newDesk.placement[position].code = code;

            if( code != 0 
                && fileAsJson["binds"].find(std::to_string(code)) != fileAsJson["binds"].end())
            {
               newDesk.placement[position].name = fileAsJson["binds"][std::to_string(code)];
            }
            
        }

        for (auto vectToPiece :newDesk.placement)
        {
            auto piece = vectToPiece.second;
            if (piece.code == 0) continue;
            inputFile.open(directoryPath+"/"+piece.name+".json");
            auto pieceJson = nlohmann::json::parse(inputFile);
            inputFile.close();

        }

    }

    return newDesk;
}