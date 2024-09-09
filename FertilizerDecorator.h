#ifndef FERTILIZERDECORATOR_H
#define FERTILIZERDECORATOR_H

#include "FarmUnitDecorator.h"
#include "CropField.h"

/**
 * @class FertilizerDecorator
 * @brief Decorator class for adding fertilizer functionality to a FarmUnit.
 *
 * The FertilizerDecorator class is a derived class of FarmUnitDecorator and adds
 * fertilizer-related functionality to a FarmUnit. It provides methods to get the total capacity,
 * crop type, soil state name, increase production, harvest crops, get leftover capacity,
 * notify delivery, notify fertilizer, add crops, remove crops, simulate rain, and get the wrapped unit.
 */
class FertilizerDecorator : public FarmUnitDecorator
{
private:
    FarmUnit *unit;       ///< Pointer to the wrapped farm unit.
    int fertilizerAmount; ///< The amount of fertilizer.

    /**
     * @brief Checks the fertilizer status and updates the farm unit accordingly.
     */
    void checkFertilizer();

public:
    /**
     * @brief Constructs a FertilizerDecorator object.
     *
     * @param unit Pointer to the farm unit to be decorated.
     */
    FertilizerDecorator(FarmUnit *unit);

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
     * @brief Increases the production of the farm unit.
     */
    void increaseProduction();

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
     * @brief Notifies the addition of fertilizer.
     */
    void notifyFertilizer();

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
     * @brief Destroys the FertilizerDecorator object.
     */
    ~FertilizerDecorator();
};

#endif // FERTILIZERDECORATOR_H