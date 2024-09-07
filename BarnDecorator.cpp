#include "BarnDecorator.h"

BarnDecorator::BarnDecorator(FarmUnit *unit) : FarmUnitDecorator(unit)
{
  this->barn = new Barn(this->cropType, 100);
}

BarnDecorator::~BarnDecorator()
{
  delete this->decoratedUnit;
}

int BarnDecorator::getTotalCapacity() const
{
  return this->decoratedUnit->getTotalCapacity();
}

std::string BarnDecorator::getCropType() const
{
  return this->decoratedUnit->getCropType();
}

std::string BarnDecorator::getSoilStateName() const
{
  CropField *cropField = dynamic_cast<CropField *>(this->decoratedUnit);
  if (cropField)
  {
    return cropField->getSoilStateName();
  }
  return "Not a cropfield";
}

void BarnDecorator::increaseProduction()
{
  CropField *cropField = dynamic_cast<CropField *>(this->decoratedUnit);
  if (cropField)
  {
    cropField->increaseProduction();
  }
}

void BarnDecorator::harvest()
{
  CropField *cropField = dynamic_cast<CropField *>(this->decoratedUnit);
  if (cropField)
  {
    cropField->harvest();
  }
}

int BarnDecorator::getLeftoverCapacity() const
{
  return this->decoratedUnit->getLeftoverCapacity();
}

void BarnDecorator::notify()
{
  CropField *cropField = dynamic_cast<CropField *>(this->decoratedUnit);
  if (cropField)
  {
    cropField->notify();
  }
}

void BarnDecorator::addCrops(int amount)
{
  CropField *cropField = dynamic_cast<CropField *>(this->decoratedUnit);
  if (cropField)
  {
    if (cropField->getLeftoverCapacity() > 0)
    {
      cropField->addCrops(amount - cropField->getLeftoverCapacity());
    }
    this->barn->addCrops(amount);
  }
}

int BarnDecorator::removeCrops(int amount)
{
  int total = 0;
  CropField *cropField = dynamic_cast<CropField *>(this->decoratedUnit);
  if (cropField)
  {
    total += cropField->removeCrops(amount);
    if (total != amount)
    {
      this->barn->removeCrops(amount - total);
    }
  }
  return total;
}

void BarnDecorator::rain()
{
  CropField *cropField = dynamic_cast<CropField *>(this->decoratedUnit);
  if (cropField)
  {
    cropField->rain();
  }
}