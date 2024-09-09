#ifndef COORDS_H
#define COORDS_H

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <cmath>

/**
 * @struct Coords
 * @brief Represents grid coordinates.
 *
 * The Coords structure is used to represent grid coordinates with x and y values.
 * It provides methods for equality comparison and calculating the Euclidean distance
 * to another Coords object.
 */
struct Coords
{
    int x; ///< The x-coordinate.
    int y; ///< The y-coordinate.

    /**
     * @brief Constructs a Coords object.
     *
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     */
    Coords(int x, int y) : x(x), y(y) {}

    /**
     * @brief Checks if two Coords objects are equal.
     *
     * @param other The other Coords object to compare with.
     * @return True if the coordinates are equal, false otherwise.
     */
    bool operator==(const Coords &other) const
    {
        return x == other.x && y == other.y;
    }

    /**
     * @brief Calculates the Euclidean distance to another Coords object.
     *
     * @param other The other Coords object.
     * @return The Euclidean distance to the other Coords object.
     */
    int operator[](const Coords &other)
    {
        return (int)floor(sqrt(pow(x - other.x, 2) + pow(y - other.y, 2)));
    }
};

namespace std
{
    /**
     * @brief Hash function for Coords.
     *
     * Specialization of the std::hash template for Coords, allowing Coords objects
     * to be used as keys in unordered containers.
     */
    template <>
    struct hash<Coords>
    {
        /**
         * @brief Computes the hash value for a Coords object.
         *
         * @param pos The Coords object to hash.
         * @return The hash value.
         */
        size_t operator()(const Coords &pos) const
        {
            return hash<int>()(pos.x) ^ hash<int>()(pos.y);
        }
    };
}

#endif // COORDS_H