#pragma once

#include <cstdint>
#include <unordered_set>

#include "Vector2d.hpp"

struct MoveCode
{
    Vector2d<int8_t> shift {};
    bool isSlide = false;
};

bool operator==(const MoveCode& left, const MoveCode& right);
bool operator!=(const MoveCode& left, const MoveCode& right);

template<>
struct std::hash<MoveCode>
{
    std::size_t operator()(const MoveCode& mvcode) const noexcept;
};