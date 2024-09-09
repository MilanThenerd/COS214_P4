#ifndef CROPFIELD_H
#define CROPFIELD_H

#include "FarmUnit.h"
#include "SoilState.h"
#include "DrySoil.h"
#include "FarmTraversalBFS.h"
#include "Publisher.h"
#include <cstdlib>

class Publisher;

/**
 * @class CropField
 * @brief Represents a crop field in a farm.
 *
 * The CropField class is a derived class of FarmUnit and represents a crop field in a farm.
 * It contains information about the soil state, fertilizer amount, farm iterator, and publisher.
 * It provides methods to get the total capacity, crop type, soil state name, increase production,
 * harvest crops, get leftover capacity, notify delivery, notify fertilizer, add crops, remove crops,
 * set soil state, and simulate rain.
 */
class CropField : public FarmUnit
{
private:
  SoilState *soilState;        ///< The current soil state of the crop field.
  int fertilizerAmount = 10;   ///< The amount of fertilizer in the crop field.
  FarmTraversal *farmIterator; ///< Iterator for traversing the farm.
  Publisher *publisher;        ///< Publisher for notifying changes.

public:
  /**
   * @brief Constructs a CropField object.
   *
   * @param crop The type of crop in the field.
   * @param capacity The total capacity of the crop field.
   * @param publisher Pointer to the publisher for notifying changes.
   */
  CropField(std::string crop, int capacity, Publisher *publisher);

  /**
   * @brief Gets the total capacity of the crop field.
   *
   * @return The total capacity of the crop field.
   */
  int getTotalCapacity() const override;

  /**
   * @brief Gets the crop type in the crop field.
   *
   * @return The crop type in the crop field.
   */
  std::string getCropType() const override;

  /**
   * @brief Gets the name of the current soil state.
   *
   * @return The name of the current soil state.
   */
  std::string getSoilStateName() const;

  /**
   * @brief Increases the production of the crop field.
   */
  void increaseProduction();

  /**
   * @brief Harvests the crops from the crop field.
   */
  void harvest();

  /**
   * @brief Gets the leftover capacity of the crop field.
   *
   * @return The leftover capacity of the crop field.
   */
  int getLeftoverCapacity() const override;

  /**
   * @brief Notifies the delivery of crops.
   */
  void notifyDelivery();

  /**
   * @brief Notifies the addition of fertilizer.
   */
  void notifyFertilizer();

  /**
   * @brief Adds crops to the crop field.
   *
   * @param cropAmount The amount of crops to add.
   */
  void addCrops(int cropAmount) override;

  /**
   * @brief Removes crops from the crop field.
   *
   * @param cropAmount The amount of crops to remove.
   * @return The amount of crops removed.
   */
  int removeCrops(int cropAmount) override;

  /**
   * @brief Sets the soil state of the crop field.
   *
   * @param soilState Pointer to the new soil state.
   */
  void setState(SoilState *soilState);

  /**
   * @brief Simulates rain on the crop field.
   */
  void rain();

  /**
   * @brief Destroys the CropField object.
   */
  ~CropField();
};

#endif // CROPFIELD_H