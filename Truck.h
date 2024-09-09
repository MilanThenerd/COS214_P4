#ifndef TRUCK_H
#define TRUCK_H

#include "FarmUnit.h"
#include "Coords.h"
#include "FarmTraversalBFS.h"

#include <queue>
#include <cmath>
#include <random>

/**
 * @class Truck
 * @brief Abstract base class representing a truck in the farm simulation.
 *
 * The Truck class provides common functionality for different types of trucks
 * in the farm simulation. It includes methods for finding the shortest path,
 * moving towards the next farm unit, and getting the truck's position.
 */
class Truck
{
protected:
  int capacity;                                 ///< The capacity of the truck.
  std::vector<FarmUnit *> farmVector;           ///< Vector of farm units.
  std::vector<std::vector<FarmUnit *>> farmMap; ///< Reference to the farm map.
  std::vector<Coords> path;                     ///< Path for the truck to follow.
  FarmTraversalBFS *farmIterator;               ///< Iterator for traversing the farm.
  Coords *currentPosition;                      ///< Current position of the truck.

  /**
   * @brief Finds the shortest path for the truck.
   */
  void findShortestPath();

  /**
   * @brief Gets the coordinates of a farm unit.
   *
   * @param unit Pointer to the farm unit.
   * @return The coordinates of the farm unit.
   */
  Coords getCoords(FarmUnit *unit);

public:
  /**
   * @brief Constructs a Truck object.
   *
   * @param map Reference to the farm map.
   * @param capacity The capacity of the truck.
   */
  Truck(std::vector<std::vector<FarmUnit *>> &map, int capacity);

  /**
   * @brief Destroys the Truck object.
   */
  virtual ~Truck() {}

  /**
   * @brief Calls the truck to a specific farm unit.
   *
   * @param unit Pointer to the farm unit.
   * @return True if the truck successfully called, false otherwise.
   */
  bool callTruck(FarmUnit *unit);

  /**
   * @brief Starts the engine of the truck.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   */
  virtual void startEngine() = 0;

  /**
   * @brief Clones the truck.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @return A pointer to the cloned truck.
   */
  virtual Truck *clone() const = 0;

  /**
   * @brief Gets the path for the truck to follow.
   *
   * @return A vector of coordinates representing the path.
   */
  std::vector<Coords> getPath() const;

  /**
   * @brief Gets the next farm unit in the path.
   *
   * @return Pointer to the next farm unit.
   */
  FarmUnit *getNextFarmUnit() const;

  /**
   * @brief Moves the truck towards the next farm unit.
   *
   * @param speed The speed at which the truck moves.
   * @return True if the truck successfully moved, false otherwise.
   */
  bool moveTowardsNextFarmUnit(int speed);

  /**
   * @brief Gets the current position of the truck.
   *
   * @return Pointer to the current position of the truck.
   */
  Coords *getPosition();
};

#endif // TRUCK_H