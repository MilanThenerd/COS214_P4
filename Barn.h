#ifndef BARN_H
#define BARN_H

#include "FarmUnit.h"

class Barn : public FarmUnit
{
  public:
    Barn(std::string crop , int capacity);
    int getTotalCapacity() const override;
    int getLeftoverCapacity() const override;
    std::string getCropType() const override;
    void addCrops(int cropAmount) override;
    int removeCrops(int cropAmount) override;
};
#endif