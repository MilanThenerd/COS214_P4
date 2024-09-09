#ifndef BARN_H
#define BARN_H

#include "FarmTraversalBFS.h"
#include "FarmUnit.h"
#include "ExtraBarnDecorator.h"
#include <iostream>
#include "DecoratorHelper.h"

class Game;

/**
 * @class Barn
 * @brief Represents a barn in a farm.
 *
 * The Barn class is a derived class of FarmUnit and represents a barn in a farm. It contains information about its coordinates, surrounding units, and the farm map it belongs to. It also provides methods to get the total capacity, leftover capacity, crop type, add crops, remove crops, get neighbors, add neighbors, and handle neighbors.
 */
class Barn : public FarmUnit
{
private:
  Coords coords;                                 ///< Coordinates of the barn in the farm.
  FarmTraversal *iterator;                       ///< Iterator for traversing the farm.
  std::vector<FarmUnit *> surroundingUnits;      ///< List of surrounding farm units.
  std::vector<std::vector<FarmUnit *>> &farmMap; ///< Reference to the farm map.

  /**
   * @brief Sets up the barn by initializing its neighbors.
   */
  void setup();

public:
  /**
   * @brief Constructs a Barn object.
   *
   * @param farmMap Reference to the farm map.
   * @param startX The x-coordinate of the barn.
   * @param startY The y-coordinate of the barn.
   */
  Barn(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);

  /**
   * @brief Gets the total capacity of the barn.
   *
   * @return The total capacity of the barn.
   */
  int getTotalCapacity() const override;

  /**
   * @brief Gets the leftover capacity of the barn.
   *
   * @return The leftover capacity of the barn.
   */
  int getLeftoverCapacity() const override;

  /**
   * @brief Gets the crop type stored in the barn.
   *
   * @return The crop type stored in the barn.
   */
  std::string getCropType() const override;

  /**
   * @brief Adds crops to the barn.
   *
   * @param cropAmount The amount of crops to add.
   */
  void addCrops(int cropAmount) override;

  /**
   * @brief Removes crops from the barn.
   *
   * @param cropAmount The amount of crops to remove.
   * @return The amount of crops removed.
   */
  int removeCrops(int cropAmount) override;

  /**
   * @brief Gets the neighboring farm units.
   *
   * @return A vector of neighboring farm units.
   */
  std::vector<FarmUnit *> getNeighbours();

  /**
   * @brief Adds a neighboring farm unit.
   *
   * @param unit Pointer to the neighboring farm unit to add.
   */
  void addNeighbour(FarmUnit *unit);

  /**
   * @brief Handles the neighboring farm units.
   */
  void handleNeighbours();
};

#endif // BARN_H