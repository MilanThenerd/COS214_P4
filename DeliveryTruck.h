#ifndef DELIVERYTRUCK_H
#define DELIVERYTRUCK_H

#include "Truck.h"
#include "FarmUnit.h"
#include "CropField.h"
#include "ExtraBarnDecorator.h"
#include "FertilizerDecorator.h"

/**
 * @class DeliveryTruck
 * @brief Represents a delivery truck in the farm simulation.
 *
 * The DeliveryTruck class is a derived class of Truck and represents a delivery truck
 * that can transport crops from the farm. It provides methods to start the engine and
 * clone the truck.
 */
class DeliveryTruck : public Truck
{
public:
  /**
   * @brief Constructs a DeliveryTruck object.
   *
   * @param map Reference to the farm map.
   * @param capacity The capacity of the delivery truck.
   */
  DeliveryTruck(std::vector<std::vector<FarmUnit *>> &map, int capacity);

  /**
   * @brief Starts the engine of the delivery truck.
   */
  void startEngine() override;

  /**
   * @brief Clones the delivery truck.
   *
   * @return A pointer to the cloned delivery truck.
   */
  DeliveryTruck *clone() const override;
};

#endif // DELIVERYTRUCK_H