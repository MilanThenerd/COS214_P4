#ifndef FERTILIZERDECORATOR_H
#define FERTILIZERDECORATOR_H

#include "FarmUnitDecorator.h"

class FertilizerDecorator : public FarmUnitDecorator
{
private:
    FarmUnit *unit;
    int fertilizerAmount;
    void checkFertilizer();

public:
    FertilizerDecorator(FarmUnit *unit);
    int getTotalCapacity() const;
    std::string getCropType() const;
    std::string getSoilStateName() const;
    void increaseProduction();
    void harvest();
    int getLeftoverCapacity() const;
    void notify();
    void addCrops(int cropAmount);
    int removeCrops(int cropAmount);
    void rain();
    FarmUnit *getWrappedUnit() { return unit; }
    ~FertilizerDecorator();
};
#endif