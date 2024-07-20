#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

#include "MoveCode.hpp"
#include "Vector2d.hpp"


struct Piece
{
public:
    std::string name;
    Vector2d<int8_t> position {};
    int8_t code = 0;
    bool didFirstMove = false;
    std::vector<MoveCode> attackCodes {};
    std::vector<MoveCode> moveCodes {};
    std::vector<MoveCode> firstMoveCodes {};

    bool CanMoveThatWay(Vector2d<int8_t> shift);
    bool CanAttackThatWay(Vector2d<int8_t> shift);
};

const Piece EMPTY_PIECE = 
{
    .name = "_",
    .position = {-1, -1},
    .code = 0,
    .didFirstMove = false,
    .attackCodes = {},
    .moveCodes = {},
    .firstMoveCodes = {}
};

bool operator==(const Piece& left, const Piece& right);