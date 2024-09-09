#ifndef SOILSTATE_H
#define SOILSTATE_H

#include <string>
#include <cstdlib>
#include <ctime>

/**
 * @class SoilState
 * @brief Abstract base class representing the state of soil in a crop field.
 *
 * The SoilState class provides an interface for different soil states in a crop field.
 * It includes methods for simulating rain, harvesting crops, and getting the name of the soil state.
 */
class SoilState
{
public:
  /**
   * @brief Virtual destructor for SoilState.
   */
  virtual ~SoilState() = default;

  /**
   * @brief Simulates rain on the soil.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @return A pointer to the new SoilState after rain.
   */
  virtual SoilState *rain() = 0;

  /**
   * @brief Harvests crops from the soil.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @return The amount of crops harvested.
   */
  virtual int harvestCrops() const = 0;

  /**
   * @brief Gets the name of the soil state.
   *
   * This is a pure virtual function that must be implemented by derived classes.
   * @return The name of the soil state.
   */
  virtual std::string getName() const = 0;
};

#endif // SOILSTATE_H