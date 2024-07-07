#pragma once

#include "Piece.hpp"
#include "Vector2d.hpp"
#include <cstdint>

enum class CursorState
{
    UNKNOWN = 0,

    FREE,
    WITH_PIECE
};

struct Cursor
{
public:
    CursorState state;
    Vector2d<int8_t> position;
    Piece pickedPiece;
};