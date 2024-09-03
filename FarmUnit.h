#ifndef FARMUNIT_H
#define FARMUNIT_H

#include <string>

class FarmUnit
{
  protected:
    std::string cropType;
    int totalCapacity;
    int currentStored;
  public:
    virtual ~FarmUnit() = default;
    virtual int getTotalCapacity() const = 0;
    virtual int getLeftoverCapacity() const = 0;
    virtual std::string getCropType() const = 0;
    virtual void addCrops(int cropAmount) = 0;
    virtual int removeCrops(int cropAmount) = 0;
};
#endif