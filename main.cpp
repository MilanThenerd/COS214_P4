#include "Game.h"

#include <iostream>

int main()
{
  // CropField* crop = new CropField("Potatoes",100);
  // std::cout << crop->getTotalCapacity() << std::endl;
  // crop->addExtraBarn();
  // std::cout << crop->getTotalCapacity() << std::endl;
  // crop->addCrops(24);
  // std::cout << crop->getLeftoverCapacity() << std::endl;
  // crop->rain();
  // std::cout << crop->getSoilStateName() << std::endl;
  // crop->rain();
  // std::cout << crop->getSoilStateName() << std::endl;
  // crop->rain();
  // std::cout << crop->getSoilStateName() << std::endl;
  // crop->increaseProduction();
  // crop->harvest();
  // std::cout << crop->getLeftoverCapacity() << std::endl;
  Game* game = new Game(10,10);
  return 0;
}
