#pragma once

#include <cstdint>

template <typename T>
struct Vector2d
{
public:
    T x = 0;
    T y = 0;
};

template<typename T>
Vector2d<T> operator+(const Vector2d<T> &left, const Vector2d<T> &right)
{
    return 
    {
        .x = static_cast<T>(left.x + right.x),
        .y = static_cast<T>(left.y + right.y)
    };
}

template<typename T>
bool operator==(const Vector2d<T> &left, const Vector2d<T> &right)
{
    return (left.x == right.x && left.y == right.y);
}

template<typename T>
bool operator!=(const Vector2d<T> &left, const Vector2d<T> &right)
{
    return (left.x != right.x || left.y != right.y);
}