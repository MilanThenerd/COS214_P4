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
    int getTotalCapacity() const override;
    std::string getCropType() const override;
    std::string getSoilStateName() const;
    void increaseProduction();
    void harvest();
    int getLeftoverCapacity() const override;
    void notify();
    void addCrops(int cropAmount) override;
    int removeCrops(int cropAmount) override;
    void rain();
    FarmUnit *getWrappedUnit() { return decoratedUnit; }
    ~FertilizerDecorator();
};
#endif