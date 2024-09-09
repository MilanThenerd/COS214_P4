#ifndef COORDS_H
#define COORDS_H

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <cmath>

// Coords structure to represent grid coordinates
struct Coords
{
    int x;
    int y;
    Coords(int x, int y) : x(x), y(y) {}
    bool operator==(const Coords &other) const
    {
        return x == other.x && y == other.y;
    }
    int operator[](const Coords &other)
    {
        return (int)floor(sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)));
    }
};

namespace std
{
    template <>
    struct hash<Coords>
    {
        size_t operator()(const Coords &pos) const
        {
            return hash<int>()(pos.x) ^ hash<int>()(pos.y);
        }
    };
}

#endif