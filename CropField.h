#ifndef CROPFIELD_H
#define CROPFIELD_H

#include "FarmUnit.h"
#include "Barn.h"
#include "SoilState.h"
#include "DrySoil.h"
#include "FruitfulSoil.h"
#include "FloodedSoil.h"
#include "Publisher.h"
#include "FertilizerTruck.h"
#include "DeliveryTruck.h"

class Publisher;

#include <cstdlib>
#include <queue>

class CropField : public FarmUnit
{
  private:
    SoilState* soilState;
    bool fertilizer;
    Publisher* publisher;
  public:
    CropField(std::string crop , int capacity , Publisher* publisher);
    int getTotalCapacity() const override;
    std::string getCropType() const override;
    std::string getSoilStateName() const;
    void increaseProduction();
    void harvest();
    int getLeftoverCapacity() const;
    void notifyFertilizer();
    void notifyDelivery();
    void addCrops(int cropAmount) override;
    int removeCrops(int cropAmount) override;
    void rain();
    ~CropField();
};
#endif