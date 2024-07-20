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
    CursorState state = CursorState::FREE;
    Vector2d<int8_t> position = {0,0};
    Piece pickedPiece = EMPTY_PIECE;
};