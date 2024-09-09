#ifndef EXTRABARNDECORATOR_H
#define EXTRABARNDECORATOR_H

#include "FarmUnitDecorator.h"
#include "CropField.h"

/**
 * @class ExtraBarnDecorator
 * @brief Decorator class for adding extra barn functionality to a FarmUnit.
 *
 * The ExtraBarnDecorator class is a derived class of FarmUnitDecorator and adds
 * extra barn-related functionality to a FarmUnit. It provides methods to get the total capacity,
 * crop type, soil state name, harvest crops, get leftover capacity, notify delivery, add crops,
 * remove crops, simulate rain, and get the wrapped unit.
 */
class ExtraBarnDecorator : public FarmUnitDecorator
{
public:
  /**
   * @brief Constructs an ExtraBarnDecorator object.
   *
   * @param unit Pointer to the farm unit to be decorated.
   */
  ExtraBarnDecorator(FarmUnit *unit);

  /**
   * @brief Gets the total capacity of the farm unit.
   *
   * @return The total capacity of the farm unit.
   */
  int getTotalCapacity() const override;

  /**
   * @brief Gets the crop type of the farm unit.
   *
   * @return The crop type of the farm unit.
   */
  std::string getCropType() const override;

  /**
   * @brief Gets the name of the soil state of the farm unit.
   *
   * @return The name of the soil state of the farm unit.
   */
  std::string getSoilStateName() const;

  /**
   * @brief Harvests the crops from the farm unit.
   */
  void harvest();

  /**
   * @brief Gets the leftover capacity of the farm unit.
   *
   * @return The leftover capacity of the farm unit.
   */
  int getLeftoverCapacity() const override;

  /**
   * @brief Notifies the delivery of crops.
   */
  void notifyDelivery();

  /**
   * @brief Adds crops to the farm unit.
   *
   * @param cropAmount The amount of crops to add.
   */
  void addCrops(int cropAmount) override;

  /**
   * @brief Removes crops from the farm unit.
   *
   * @param cropAmount The amount of crops to remove.
   * @return The amount of crops removed.
   */
  int removeCrops(int cropAmount) override;

  /**
   * @brief Simulates rain on the farm unit.
   */
  void rain();

  /**
   * @brief Gets the wrapped farm unit.
   *
   * @return Pointer to the wrapped farm unit.
   */
  FarmUnit *getWrappedUnit() { return unit; }

  /**
   * @brief Destroys the ExtraBarnDecorator object.
   */
  ~ExtraBarnDecorator();
};

#endif // EXTRABARNDECORATOR_H