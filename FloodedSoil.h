#ifndef FLOODEDSOIL_H
#define FLOODEDSOIL_H

#include "SoilState.h"
#include "DrySoil.h"
#include "FruitfulSoil.h"

/**
 * @class FloodedSoil
 * @brief Represents the flooded soil state in a crop field.
 *
 * The FloodedSoil class is a derived class of SoilState and represents the flooded soil state
 * in a crop field. It provides methods to simulate rain, harvest crops, and get the name of the soil state.
 */
class FloodedSoil : public SoilState
{
private:
    int roundsLeft; ///< The number of rounds left in the flooded state.

public:
    /**
     * @brief Constructs a FloodedSoil object.
     *
     * @param roundsLeft The number of rounds left in the flooded state.
     */
    FloodedSoil(int roundsLeft = 2);

    /**
     * @brief Harvests crops from the flooded soil.
     *
     * @return The amount of crops harvested.
     */
    int harvestCrops() const override;

    /**
     * @brief Simulates rain on the flooded soil.
     *
     * @return A pointer to the new SoilState after rain.
     */
    SoilState *rain() override;

    /**
     * @brief Gets the name of the flooded soil state.
     *
     * @return The name of the flooded soil state.
     */
    std::string getName() const override;
};

#endif // FLOODEDSOIL_H