#ifndef FERTILIZERDECORATOR_H
#define EXTRABARNDECORATOR_H

#include "FarmUnitDecorator.h"
#include "ExtraBarnDecorator.h"

class FertilizerDecorator : public FarmUnitDecorator
{
  private:
    int fertlizer = 0;
  public:
    FertilizerDecorator(FarmUnit* unit);
    int getTotalCapacity() const override;
    std::string getCropType() const override;
    std::string getSoilStateName() const;
    void increaseProduction();
    void harvest();
    int getLeftoverCapacity() const;
    void notify();
    void addCrops(int cropAmount) override;
    int removeCrops(int cropAmount) override;
    void rain();
    ~FertilizerDecorator();
};
#endif