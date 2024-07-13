#include "Piece.hpp"

bool operator==(const Piece& left, const Piece& right)
{
    return (left.code == right.code);
}