#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>

// Coords structure to represent grid coordinates
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
