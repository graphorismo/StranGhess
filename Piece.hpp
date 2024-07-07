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
    std::unordered_set<MoveCode> moveCodes {};
};

const Piece EMPTY_PIECE = 
{
    .name = "",
    .position = {-1, -1},
    .code = 0,
    .number = 0,
    .moveCodes = {}
};

bool operator==(const Piece& left, const Piece& right)
{
    return (left.code == right.code);
}

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