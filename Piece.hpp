#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

#include "MoveCode.hpp"


struct Piece
{
public:
    std::string name;
    Vector2d<int8_t> position {};
    int8_t code = 0;
    int8_t number = 0;
    std::vector<MoveCode> attackCodes {};
    std::vector<MoveCode> moveCodes {};
    std::vector<MoveCode> firstMoveCodes {};
};

const Piece EMPTY_PIECE = 
{
    .name = "_",
    .position = {-1, -1},
    .code = 0,
    .number = 0,
    .attackCodes = {},
    .moveCodes = {},
    .firstMoveCodes = {}
};

bool operator==(const Piece& left, const Piece& right);

template<>
struct std::hash<Piece>
{
    std::size_t operator()(const Piece& ps) const noexcept
    {
        std::size_t h1 = std::hash<int8_t>{}(ps.code);
        std::size_t h2 = std::hash<int8_t>{}(ps.number);
        return h1 ^ (h2 << 1);
    }
};