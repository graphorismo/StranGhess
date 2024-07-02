#include "MoveCode.hpp"
#include <vector>

bool operator==(const MoveCode& left, const MoveCode& right)
{
    if (left.isSlide != right.isSlide) return false;
    if (left.isSlide == false && !(left.shift == right.shift)) return false;
    if(left.isSlide == true && left.shift.x / right.shift.x - left.shift.y / right.shift.y > 0.001) return false;
    return true;
}

bool operator!=(const MoveCode& left, const MoveCode& right)
{
    return !(left==right);
}

std::size_t std::hash<MoveCode>::operator()(const MoveCode& mvcode) const noexcept
{
    std::size_t h1 = mvcode.shift.x;
    std::size_t h2 = mvcode.shift.y;
    std::size_t h3 = mvcode.isSlide;
    return (h2 ^ (h1 << 1))^(h3 << 2);
}
