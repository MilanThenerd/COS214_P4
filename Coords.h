#ifndef COORDS_H
#define COORDS_H

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

struct Coords {
    int x;
    int y;
    Coords(int x, int y) : x(x), y(y) {}
    bool operator==(const Coords& other) const {
        return x == other.x && y == other.y;
    }
};

namespace std {
    template<>
    struct hash<Coords> {
        size_t operator()(const Coords& pos) const {
            return hash<int>()(pos.x) ^ hash<int>()(pos.y);
        }
    };
}

#endif