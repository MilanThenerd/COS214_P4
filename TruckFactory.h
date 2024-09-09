#ifndef TRUCKFACTORY_H
#define TRUCKFACTORY_H

#include "Truck.h"
#include "DeliveryTruck.h"
#include "FertilizerTruck.h"

/**
 * @class TruckFactory
 * @brief Factory class for creating and managing trucks.
 *
 * The TruckFactory class provides methods to buy, sell, and call trucks.
 * It maintains a reference to the farm map and uses it to create trucks.
 */
class TruckFactory
{
private:
  std::vector<std::vector<FarmUnit *>> map; ///< Reference to the farm map.

public:
  /**
   * @brief Constructs a TruckFactory object.
   *
   * @param map Reference to the farm map.
   */
  TruckFactory(std::vector<std::vector<FarmUnit *>> &map);

  /**
   * @brief Buys a truck of the specified type.
   *
   * @param type The type of truck to buy.
   * @return A pointer to the newly created truck.
   */
  Truck *buy(std::string type);

  /**
   * @brief Sells the specified truck.
   *
   * @param truck Pointer to the truck to sell.
   */
  void sell(Truck *truck);

  /**
   * @brief Calls the specified truck.
   *
   * @param truck Pointer to the truck to call.
   */
  void callTruck(Truck *truck);
};

#endif // TRUCKFACTORY_H