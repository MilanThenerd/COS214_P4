#ifndef REGULARSOIL_H
#define REGULARSOIL_H

#include "SoilState.h"
#include "DrySoil.h"
#include "FruitfulSoil.h"

/**
 * @class RegularSoil
 * @brief Represents the regular soil state in a crop field.
 *
 * The RegularSoil class is a derived class of SoilState and represents the regular soil state
 * in a crop field. It provides methods to simulate rain, harvest crops, and get the name of the soil state.
 */
class RegularSoil : public SoilState
{
public:
    /**
     * @brief Harvests crops from the regular soil.
     *
     * @return The amount of crops harvested.
     */
    int harvestCrops() const override;

    /**
     * @brief Simulates rain on the regular soil.
     *
     * @return A pointer to the new SoilState after rain.
     */
    SoilState *rain() override;

    /**
     * @brief Gets the name of the regular soil state.
     *
     * @return The name of the regular soil state.
     */
    std::string getName() const override;
};

#endif // REGULARSOIL_H