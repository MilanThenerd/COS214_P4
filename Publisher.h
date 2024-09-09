#ifndef PUBLISHER_H
#define PUBLISHER_H

#include "Truck.h"
#include "DeliveryTruck.h"
#include "FertilizerTruck.h"
#include "FarmUnit.h"

#include <queue>
#include <vector>

/**
 * @class Publisher
 * @brief Manages trucks and farm unit orders in the farm simulation.
 *
 * The Publisher class is responsible for managing a collection of trucks and a queue of farm unit orders.
 * It provides methods to add trucks and orders, handle orders, check the status of the queue and trucks,
 * remove trucks, and get the list of trucks.
 */
class Publisher
{
private:
  std::vector<Truck *> truckVector;                         ///< Vector of trucks managed by the publisher.
  std::queue<std::pair<FarmUnit *, std::string>> queueFarm; ///< Queue of farm unit orders.

public:
  /**
   * @brief Constructs a Publisher object.
   */
  Publisher();

  /**
   * @brief Adds a farm unit order to the queue.
   *
   * @param unit Pointer to the farm unit.
   * @param orderType The type of order.
   */
  void add(FarmUnit *unit, std::string orderType);

  /**
   * @brief Adds a truck to the collection.
   *
   * @param unit Pointer to the truck.
   */
  void add(Truck *unit);

  /**
   * @brief Handles the next order in the queue.
   *
   * @return True if an order was handled, false otherwise.
   */
  bool handle();

  /**
   * @brief Checks if there are any orders in the queue.
   *
   * @return True if the queue is not empty, false otherwise.
   */
  bool hasQueue() const;

  /**
   * @brief Checks if there are any trucks in the collection.
   *
   * @return True if there are trucks in the collection, false otherwise.
   */
  bool hasTruck() const;

  /**
   * @brief Removes a truck from the collection.
   *
   * @param truck Pointer to the truck to remove.
   */
  void removeTruck(Truck *truck);

  /**
   * @brief Gets the list of trucks.
   *
   * @return Reference to the vector of trucks.
   */
  std::vector<Truck *> &getTrucks();
};

#endif // PUBLISHER_H