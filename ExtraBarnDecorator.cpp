#include "ExtraBarnDecorator.h"

ExtraBarnDecorator::ExtraBarnDecorator(FarmUnit* unit) : FarmUnitDecorator(unit)
{
  this->barn = new Barn(this->cropType,100);
}

ExtraBarnDecorator::~ExtraBarnDecorator()
{
  delete this->decoratedUnit;
}

int ExtraBarnDecorator::getTotalCapacity() const
{
  return this->decoratedUnit->getTotalCapacity();
}

std::string ExtraBarnDecorator::getCropType() const
{
  return this->decoratedUnit->getCropType();
}

std::string ExtraBarnDecorator::getSoilStateName() const
{
  CropField* cropField = dynamic_cast<CropField*>(this->decoratedUnit);
  if (cropField) 
  {
    return cropField->getSoilStateName();
  }
  return "Not a cropfield";
}

void ExtraBarnDecorator::harvest()
{
  CropField* cropField = dynamic_cast<CropField*>(this->decoratedUnit);
  if (cropField) 
  {
    cropField->harvest();
  }
}

int ExtraBarnDecorator::getLeftoverCapacity() const
{
  return this->decoratedUnit->getLeftoverCapacity();
}

void ExtraBarnDecorator::notify()
{
  CropField* cropField = dynamic_cast<CropField*>(this->decoratedUnit);
  // if (cropField) 
  // {
  //   cropField->notify();
  // }
}

void ExtraBarnDecorator::addCrops(int amount)
{
  CropField* cropField = dynamic_cast<CropField*>(this->decoratedUnit);
  if(cropField) 
  {
    if(cropField->getLeftoverCapacity() > 0)
    {
      cropField->addCrops(amount-cropField->getLeftoverCapacity());
    }
    this->barn->addCrops(amount);
  }
}

int ExtraBarnDecorator::removeCrops(int amount)
{
  int total = 0;
  CropField* cropField = dynamic_cast<CropField*>(this->decoratedUnit);
  if(cropField) 
  {
    total += cropField->removeCrops(amount);
    if(total != amount)
    {
      this->barn->removeCrops(amount-total);
    }
  }
  return total;
}

void ExtraBarnDecorator::rain()
{
  CropField* cropField = dynamic_cast<CropField*>(this->decoratedUnit);
  if(cropField) 
  {
    cropField->rain();
  }
}