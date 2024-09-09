#ifndef FARMUNITDECORATOR_H
#define FARMUNITDECORATOR_H

#include "FarmUnit.h"

/**
 * @class FarmUnitDecorator
 * @brief Abstract decorator class for adding functionality to FarmUnit objects.
 *
 * The FarmUnitDecorator class is a derived class of FarmUnit and serves as a base class
 * for decorators that add functionality to FarmUnit objects. It provides pure virtual methods
 * that must be implemented by derived classes.
 */
class FarmUnitDecorator : public FarmUnit
{
protected:
  FarmUnit *unit; ///< Pointer to the wrapped farm unit.

public:
  /**
   * @brief Constructs a FarmUnitDecorator object.
   *
   * @param unit Pointer to the farm unit to be decorated.
   */
  FarmUnitDecorator(FarmUnit *unit) : unit(unit) {}

  /**
   * @brief Virtual destructor for FarmUnitDecorator.
   */
  virtual ~FarmUnitDecorator() = default;

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

#endif // FARMUNITDECORATOR_H