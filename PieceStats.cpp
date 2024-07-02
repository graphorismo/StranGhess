#include "PieceStats.hpp"

bool operator==(const PieceStats& left, const PieceStats& right)
{
    return (left.code == right.code);
}

std::size_t std::hash<PieceStats>::operator()(const PieceStats& ps) const noexcept
{
    std::size_t h1 = std::hash<int8_t>{}(ps.code);
    std::size_t h2 = std::hash<int8_t>{}(ps.number);
    return h1 ^ (h2 << 1);
}