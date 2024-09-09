#ifndef FARMTRAVERSAL_H
#define FARMTRAVERSAL_H

#include "FarmUnit.h"
#include "Coords.h"
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>

/**
 * @class FarmTraversal
 * @brief Abstract base class for traversing a farm map.
 *
 * The FarmTraversal class provides an interface for different traversal strategies
 * (e.g., BFS, DFS) for a farm map. It includes methods for initializing the traversal,
 * getting the first, current, and next farm units, checking traversal status, and
 * managing the traversal path.
 */
class FarmTraversal
{
public:
  /**
   * @brief Constructs a FarmTraversal object.
   *
   * @param farmMap Reference to the farm map.
   * @param startX The starting x-coordinate for the traversal.
   * @param startY The starting y-coordinate for the traversal.
   */
  FarmTraversal(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);

  /**
   * @brief Virtual destructor for FarmTraversal.
   */
  virtual ~FarmTraversal() = default;

  /**
   * @brief Initializes the traversal.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   */
  virtual void initialize() = 0;

  /**
   * @brief Gets the first farm unit in the traversal.
   *
   * @return Pointer to the first farm unit.
   */
  FarmUnit *firstFarm();

  /**
   * @brief Gets the current farm unit in the traversal.
   *
   * @return Pointer to the current farm unit.
   */
  FarmUnit *currentFarm();

  /**
   * @brief Gets the next farm unit in the traversal.
   *
   * @return Pointer to the next farm unit.
   */
  FarmUnit *next();

  /**
   * @brief Gets the farm unit at the specified coordinates.
   *
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @return Pointer to the farm unit at the specified coordinates.
   */
  FarmUnit *get(int x, int y);

  /**
   * @brief Checks if the traversal is done.
   *
   * @return True if the traversal is done, false otherwise.
   */
  bool isDone() const;

  /**
   * @brief Checks if there are more farm units to traverse.
   *
   * @return True if there are more farm units to traverse, false otherwise.
   */
  bool hasNext() const;

  /**
   * @brief Gets the index of a farm unit in the traversal path.
   *
   * @param unit Pointer to the farm unit.
   * @return The index of the farm unit in the traversal path.
   */
  int getIndex(FarmUnit *unit) const;

  /**
   * @brief Gets the length of the traversal path.
   *
   * @return The length of the traversal path.
   */
  int getLength() const;

  /**
   * @brief Gets the current index in the traversal path.
   *
   * @return The current index in the traversal path.
   */
  int getCurrentIndex() const;

  /**
   * @brief Gets the traversal path.
   *
   * @return A vector of coordinates representing the traversal path.
   */
  std::vector<Coords> getPath() const;

protected:
  /**
   * @brief Checks if the specified coordinates are in the visited set.
   *
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @return True if the coordinates are in the visited set, false otherwise.
   */
  bool contains(int x, int y) const;

  /**
   * @brief Checks if the specified coordinates are within the bounds of the farm map.
   *
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @return True if the coordinates are within bounds, false otherwise.
   */
  bool isWithinBounds(int x, int y) const;

  std::vector<std::vector<FarmUnit *>> &farmMap; ///< Reference to the farm map.
  int startX;                                    ///< The starting x-coordinate for the traversal.
  int startY;                                    ///< The starting y-coordinate for the traversal.
  std::unordered_set<Coords> visited;            ///< Set of visited coordinates.
  std::vector<Coords> path;                      ///< Traversal path.
  std::size_t currentIndex;                      ///< Current index in the traversal path.
};

#endif // FARMTRAVERSAL_H