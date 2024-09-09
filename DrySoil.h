#ifndef DRYSOIL_H
#define DRYSOIL_H

#include "SoilState.h"
#include "RegularSoil.h"

/**
 * @class DrySoil
 * @brief Represents the dry soil state in a crop field.
 *
 * The DrySoil class is a derived class of SoilState and represents the dry soil state
 * in a crop field. It provides methods to simulate rain, harvest crops, and get the name of the soil state.
 */
class DrySoil : public SoilState
{
public:
    /**
     * @brief Harvests crops from the dry soil.
     *
     * @return The amount of crops harvested.
     */
    int harvestCrops() const override;

    /**
     * @brief Simulates rain on the dry soil.
     *
     * @return A pointer to the new SoilState after rain.
     */
    SoilState *rain() override;

    /**
     * @brief Gets the name of the dry soil state.
     *
     * @return The name of the dry soil state.
     */
    std::string getName() const override;
};

#endif // DRYSOIL_H