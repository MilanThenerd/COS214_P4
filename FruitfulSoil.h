#ifndef FRUITFULSOIL_H
#define FRUITFULSOIL_H

#include "SoilState.h"
#include "DrySoil.h"
#include "FloodedSoil.h"

/**
 * @class FruitfulSoil
 * @brief Represents the fruitful soil state in a crop field.
 *
 * The FruitfulSoil class is a derived class of SoilState and represents the fruitful soil state
 * in a crop field. It provides methods to simulate rain, harvest crops, and get the name of the soil state.
 */
class FruitfulSoil : public SoilState
{
public:
  /**
   * @brief Harvests crops from the fruitful soil.
   *
   * @return The amount of crops harvested.
   */
  int harvestCrops() const override;

  /**
   * @brief Simulates rain on the fruitful soil.
   *
   * @return A pointer to the new SoilState after rain.
   */
  SoilState *rain() override;

  /**
   * @brief Gets the name of the fruitful soil state.
   *
   * @return The name of the fruitful soil state.
   */
  std::string getName() const override;
};

#endif // FRUITFULSOIL_H