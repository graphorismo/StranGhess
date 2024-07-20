#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "Cursor.hpp"
#include "Desk.hpp"
#include "MoveCode.hpp"
#include "Piece.hpp"
#include "nlohmann/json.hpp"

std::vector<std::vector<char>> Desk::GetPlacement()
{
    std::vector<std::vector<char>> transformedPlacement (height, std::vector<char>(width, '_'));

    for(int8_t i = 0; i < height; ++i)
    {
        for (int8_t j = 0; j < width; ++j)
        {
            char symbol = placement.at({i, j}).name[0];
            auto code = placement.at({i, j}).code;

            if (code < 0) symbol = std::toupper(symbol);
            else if (code > 0) symbol = std::tolower(symbol);

            transformedPlacement[i][j] = symbol;
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
        auto pickedPiece = placement.at({cursor.position.y, cursor.position.x});
        bool didChooseRightPiece = pickedPiece.code*mod > 0;
        if (!didChooseRightPiece) return;

        if (pickedPiece == EMPTY_PIECE) return;

        placement[{cursor.position.y, cursor.position.x}] = EMPTY_PIECE;
        cursor.pickedPiece = pickedPiece;

        cursor.state = CursorState::WITH_PIECE;
    }
    else if (cursor.state == CursorState::WITH_PIECE)
    {
        auto targetedPiece = placement.at({cursor.position.y, cursor.position.x});
        auto attackingPiece = cursor.pickedPiece;

        if (attackingPiece == EMPTY_PIECE) return;

        auto shift = targetedPiece.position - attackingPiece.position;
        if (targetedPiece == EMPTY_PIECE 
            && attackingPiece.CanMoveThatWay(shift))
        {
            placement[{cursor.position.y, cursor.position.x}] = attackingPiece;
            cursor.pickedPiece = EMPTY_PIECE;
            cursor.state = CursorState::FREE;
            if (deskState == DeskState::WHITE_TURN) deskState = DeskState::BLACK_TURN;
            else deskState = DeskState::WHITE_TURN;
            return;
        }
        if (targetedPiece.code * attackingPiece.code < 0
            && attackingPiece.CanAttackThatWay(shift))
        {
            placement[{cursor.position.y, cursor.position.x}] = attackingPiece;
            cursor.pickedPiece = EMPTY_PIECE;
            cursor.state = CursorState::FREE;
            if (deskState == DeskState::WHITE_TURN) deskState = DeskState::BLACK_TURN;
            else deskState = DeskState::WHITE_TURN;
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

Cursor Desk::GetCursor()
{
    return cursor;
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

    newDesk.height = fileAsJson["placement"].size();
    newDesk.width = fileAsJson["placement"][0].size();

    for(auto i = 0; i < newDesk.height; ++i)
    {
        auto line = fileAsJson["placement"][i];
        for (auto j = 0; j < newDesk.width; ++j)
        {
            auto position = Vector2d<int8_t>{static_cast<signed char>(i), static_cast<signed char>(j)};
            newDesk.placement.insert({position, EMPTY_PIECE});
            newDesk.placement[position].position = position;
            newDesk.placement[position].code = line[j];
            int8_t code = std::abs(static_cast<int>(line[j]));

            if( code != 0 
                && fileAsJson["binds"].find(std::to_string(code)) != fileAsJson["binds"].end())
            {
               newDesk.placement[position].name = fileAsJson["binds"][std::to_string(code)];
            }
        }
    }

    std::unordered_set<int8_t> loadedPieces;
    std::unordered_map<int8_t, std::tuple<  std::vector<MoveCode>, 
                                            std::vector<MoveCode>, 
                                            std::vector<MoveCode>  > > codeToMoveCodes; //tuple for an  attack, a move and a first move
    for (auto vectToPiece :newDesk.placement)
    {
        auto piece = vectToPiece.second;
        if (piece.code == 0
            || loadedPieces.find(piece.code) != loadedPieces.end()) continue;
        inputFile.open(directoryPath+"/"+piece.name+".json");
        auto pieceJson = nlohmann::json::parse(inputFile);
        inputFile.close();
        loadedPieces.insert(piece.code);

        std::vector<MoveCode> attacks;
        std::vector<MoveCode> moves; 
        std::vector<MoveCode> firstMoves;
        for (auto moveJson : pieceJson["move"])
        {
            std::vector<int8_t> rawCode = {moveJson[0], moveJson[1], moveJson[2]};
            auto moveCode =MoveCode{static_cast<bool>(rawCode[0]), {rawCode[1], rawCode[2]}};
            moves.emplace_back(moveCode);
        }
        if (pieceJson["attack"] == "move") attacks = moves;
        else for (auto attackJson : pieceJson["move"])
        {
            std::vector<int8_t> rawCode = {attackJson[0], attackJson[1], attackJson[2]};
            auto moveCode =MoveCode{static_cast<bool>(rawCode[0]), {rawCode[1], rawCode[2]}};
            attacks.emplace_back(moveCode);
        }
        if (pieceJson.find("first move") != pieceJson.end()
            && pieceJson["first move"] != "move")
        {
            for (auto firstMoveJson : pieceJson["first move"])
            {
                std::vector<int8_t> rawCode = {firstMoveJson[0], firstMoveJson[1], firstMoveJson[2]};
                auto moveCode =MoveCode{static_cast<bool>(rawCode[0]), {rawCode[1], rawCode[2]}};
                firstMoves.emplace_back(moveCode);
            }
        }
        else firstMoves = moves;
        codeToMoveCodes.insert({piece.code, { attacks, moves, firstMoves}});
    }

    for (auto vectToPiece : newDesk.placement)
    {
        newDesk.placement[vectToPiece.first].attackCodes = 
            std::get<0>(codeToMoveCodes[std::abs(static_cast<int>(vectToPiece.second.code))]);
        newDesk.placement[vectToPiece.first].moveCodes = 
            std::get<1>(codeToMoveCodes[std::abs(static_cast<int>(vectToPiece.second.code))]);
        newDesk.placement[vectToPiece.first].firstMoveCodes = 
            std::get<2>(codeToMoveCodes[std::abs(static_cast<int>(vectToPiece.second.code))]);
    }

    return newDesk;
}