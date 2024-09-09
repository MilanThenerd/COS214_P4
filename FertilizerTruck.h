#ifndef FERTILIZERTRUCK_H
#define FERTILIZERTRUCK_H

#include "Truck.h"
#include "FarmUnit.h"
#include "CropField.h"
#include "FertilizerDecorator.h"

/**
 * @class FertilizerTruck
 * @brief Represents a fertilizer truck in the farm simulation.
 *
 * The FertilizerTruck class is a derived class of Truck and represents a fertilizer truck
 * that can transport and apply fertilizer to crop fields. It provides methods to start the engine
 * and clone the truck.
 */
class FertilizerTruck : public Truck
{
public:
  /**
   * @brief Constructs a FertilizerTruck object.
   *
   * @param map Reference to the farm map.
   * @param capacity The capacity of the fertilizer truck.
   */
  FertilizerTruck(std::vector<std::vector<FarmUnit *>> &map, int capacity);

  /**
   * @brief Starts the engine of the fertilizer truck.
   */
  void startEngine() override;

  /**
   * @brief Clones the fertilizer truck.
   *
   * @return A pointer to the cloned fertilizer truck.
   */
  FertilizerTruck *clone() const override;
};

#endif // FERTILIZERTRUCK_H