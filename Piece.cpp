#include "Piece.hpp"
#include "MoveCode.hpp"
#include <vector>

bool operator==(const Piece& left, const Piece& right)
{
    return (left.code == right.code);
}

bool Piece::CanAttackThatWay(Vector2d<int8_t> shift)
{
    bool canAttack = false;
    for (auto attackCode : attackCodes)
    {
        if (attackCode.isSlide)
            canAttack = shift.isDirectedSimilarTo(attackCode.shift) && shift.GetLength() < attackCode.shift.GetLength();
        else 
            canAttack = shift == attackCode.shift;

        if (canAttack) break;
    }
    return canAttack;
}

bool Piece::CanMoveThatWay(Vector2d<int8_t> shift)
{
    bool canMove = false;
    std::vector<MoveCode> moveCodesBank;
    if (!didFirstMove) moveCodesBank = firstMoveCodes;
    else moveCodesBank = moveCodes;

    for (auto moveCode : moveCodesBank)
    {
        if (moveCode.isSlide)
            canMove = shift.isDirectedSimilarTo(moveCode.shift) && shift.GetLength() <= moveCode.shift.GetLength();
        else 
            canMove = shift == moveCode.shift;

        if (canMove) break;
    }
    return canMove;
    
}