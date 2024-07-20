#pragma once

#include <cmath>
#include <cstdint>

#include <vector> // included this to be able to specialize std::hash

template <typename T>
struct Vector2d
{
public:
    T x = 0;
    T y = 0;

    bool isDirectedSimilarTo(Vector2d<T> other);
    float GetLength();
};

template<typename T>
struct std::hash<Vector2d<T>>
{
    std::size_t operator()(const Vector2d<T>& vect) const noexcept
    {
        std::size_t h1 = std::hash<int8_t>{}(vect.x);
        std::size_t h2 = std::hash<int8_t>{}(vect.y);
        return h1 ^ (h2 << 1);
    }
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
Vector2d<T> operator-(const Vector2d<T> &left, const Vector2d<T> &right)
{
    return 
    {
        .x = static_cast<T>(left.x - right.x),
        .y = static_cast<T>(left.y - right.y)
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

template<typename T>
bool Vector2d<T>::isDirectedSimilarTo(Vector2d<T> other)
{
    auto cosCos = ((x*other.x + y*other.y)*(x*other.x + y*other.y)) / ((x*x+y*y)*(other.x * other.x + other.y * other.y));
    return 1 - cosCos < 0.0001;
}

template<typename T>
float Vector2d<T>::GetLength()
{
    return std::sqrt(x*x+y*y);
}
