#include "Game.h"
#include <iostream>

Game::Game(int width , int height) : width(width) , height(height)
{
  farmMap.resize(width, std::vector<FarmUnit*>(height, nullptr));
  loadTextures();
  for(int x = 0 ; x < width ; x++)
  {
    for(int y = 0 ; y < height ; y++)
    {
      setUnit(x , y , new CropField("Corn" , 100));
    }
  }
  this->runThread = std::thread(&Game::run, this);
  this->displayWindow();
}

void Game::loadTextures()
{
  if(!loadTextureAndCreateSprite("Dry", "Dry.png"))
  {
    std::cerr << "Failed to load Dry texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("Flooded", "Flooded.png"))
  {
    std::cerr << "Failed to load Flooded texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("Fruitful", "Fruitful.png"))
  {
    std::cerr << "Failed to load Fruitful texture" << std::endl;
  }
}

bool Game::loadTextureAndCreateSprite(const std::string& key, const std::string& filename) 
{   
  auto texturePtr = std::make_shared<sf::Texture>();
  if (!texturePtr->loadFromFile(filename)) 
  {
    std::cerr << "Couldn't load texture: " << filename << std::endl;
    return false;
  }
  sf::Sprite sprite(*texturePtr);
  textureMap[key] = texturePtr;
  spriteMap[key] = sprite;
  return true;
}


void Game::run()
{
  while (true) 
  {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    FarmUnit* unit = this->getUnit(5,5);
    CropField* cropField = dynamic_cast<CropField*>(unit);
    if (cropField)
    {
      cropField->rain();
    }
  }
}

void Game::displayWindow()
{
  sf::RenderWindow window(sf::VideoMode(width * tileSize, height * tileSize), "Pixel Art Grid");
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
    }
    window.clear(sf::Color::Black);
    for (int x = 0; x < width; ++x)
    {
      for (int y = 0; y < height; ++y)
      {
        FarmUnit* unit = farmMap[x][y];
        CropField* cropField = dynamic_cast<CropField*>(unit);
        if (cropField)
        {
          std::string soilStateName = cropField->getSoilStateName();
          auto it = spriteMap.find(soilStateName);
          if (it != spriteMap.end())
          {
            sf::Sprite sprite = it->second;
            sprite.setPosition(x * tileSize, y * tileSize);
            window.draw(sprite);
          }
          else
          {
            std::cerr << "Unknown soil state: " << soilStateName << std::endl;
          }
        }
      }
    }
  window.display();
  }
}


void Game::setUnit(int x, int y, FarmUnit* unit)
{
    delete farmMap[x][y];
    farmMap[x][y] = unit;
}

FarmUnit* Game::getUnit(int x, int y) const
{
    return farmMap[x][y];
}

Game::~Game()
{
  if (runThread.joinable()) 
  {
    runThread.join();
  }
  for (auto& row : farmMap)
  {
    for (auto& unit : row)
    {
      delete unit;
    }
  }
}