#ifndef FARMUNIT_H
#define FARMUNIT_H

#include <string>

/**
 * @class FarmUnit
 * @brief Abstract base class representing a unit in a farm.
 *
 * The FarmUnit class provides an interface for different types of farm units.
 * It includes methods for getting the total capacity, leftover capacity, crop type,
 * adding crops, and removing crops.
 */
class FarmUnit
{
protected:
  std::string cropType; ///< The type of crop in the farm unit.
  int totalCapacity;    ///< The total capacity of the farm unit.
  int currentStored;    ///< The current amount of crops stored in the farm unit.

public:
  /**
   * @brief Virtual destructor for FarmUnit.
   */
  virtual ~FarmUnit() = default;

  /**
   * @brief Gets the total capacity of the farm unit.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @return The total capacity of the farm unit.
   */
  virtual int getTotalCapacity() const = 0;

  /**
   * @brief Gets the leftover capacity of the farm unit.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @return The leftover capacity of the farm unit.
   */
  virtual int getLeftoverCapacity() const = 0;

  /**
   * @brief Gets the crop type of the farm unit.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @return The crop type of the farm unit.
   */
  virtual std::string getCropType() const = 0;

  /**
   * @brief Adds crops to the farm unit.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @param cropAmount The amount of crops to add.
   */
  virtual void addCrops(int cropAmount) = 0;

  /**
   * @brief Removes crops from the farm unit.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @param cropAmount The amount of crops to remove.
   * @return The amount of crops removed.
   */
  virtual int removeCrops(int cropAmount) = 0;
};

#endif // FARMUNIT_H