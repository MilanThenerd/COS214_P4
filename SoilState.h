#ifndef SOILSTATE_H
#define SOILSTATE_H

#include <string>
#include <cstdlib>
#include <ctime>

class SoilState
{
  public:
    virtual ~SoilState() = default;

    virtual SoilState* rain() = 0;
    virtual int harvestCrops() const = 0;
    virtual std::string getName() const = 0;
};
#endif
