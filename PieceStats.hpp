#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

#include "MoveCode.hpp"


struct PieceStats
{
public:
    std::string name;
    Vector2d<int8_t> position {};
    int8_t code = 0;
    int8_t number = 0;
    std::unordered_set<MoveCode> moveCodes {};
};

bool operator==(const PieceStats& left, const PieceStats& right);

template<>
struct std::hash<PieceStats>
{
    std::size_t operator()(const PieceStats& ps) const noexcept;
};