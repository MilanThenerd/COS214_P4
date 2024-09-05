#include "Game.h"
#include <iostream>

Game::Game(int width , int height) : width(width) , height(height)
{
  farmMap.resize(width, std::vector<FarmUnit*>(height, nullptr));
  const float baseTileSize = 64.0f;
  const int referenceMapSize = 10;
  if (width > 0 && height > 0)
  {
    float mapSizeFactor = static_cast<float>(referenceMapSize) / std::max<float>(width, height);
    tileSize = baseTileSize * mapSizeFactor;
    tileSize = std::max<float>(tileSize, baseTileSize / 2);
    tileSize = std::min<float>(tileSize, baseTileSize * 2);
  }

  #ifdef USE_GUI
  loadTextures();
  #endif
  this->farmIterator = new FarmTraversal(this->farmMap,0,0,true);
  for(int x = 0 ; x < width ; x++)
  {
    for(int y = 0 ; y < height ; y++)
    {
      setUnit(x , y , new CropField("Corn" , 100));
    }
  }
  #ifdef USE_GUI
  this->runThread = std::thread(&Game::run, this);
  this->displayWindow();
  #else
    //this->run();
  #endif

}

void Game::run()
{
  while (true) 
  {
      currentIndex = (currentIndex + 1) % (int)farmIterator->length;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

#ifdef USE_GUI

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
  if(!loadTextureAndCreateSprite("Vertical", "Vertical.png"))
  {
    std::cerr << "Failed to load Vertical texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("Horisontal", "Horisontal.png"))
  {
    std::cerr << "Failed to load Horisontal texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("TopLeft", "TopLeft.png"))
  {
    std::cerr << "Failed to load TopLeft texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("BottomLeft", "BottomLeft.png"))
  {
    std::cerr << "Failed to load BottomLeft texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("TopRight", "TopRight.png"))
  {
    std::cerr << "Failed to load TopRight texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("BottomRight", "BottomRight.png"))
  {
    std::cerr << "Failed to load BottomRight texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("Barn", "Barn.png"))
  {
    std::cerr << "Failed to load Barn texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("TruckLeft", "TruckLeft.png"))
  {
    std::cerr << "Failed to load TruckLeft texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("TruckRight", "TruckRight.png"))
  {
    std::cerr << "Failed to load TruckRight texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("TruckDown", "TruckDown.png"))
  {
    std::cerr << "Failed to load TruckDown texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("TruckUp", "TruckUp.png"))
  {
    std::cerr << "Failed to load TruckUp texture" << std::endl;
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

void Game::displayWindow()
{
  sf::RenderWindow window(sf::VideoMode((width+4) * tileSize, (height+4) * tileSize), "Pixel Art Grid");
  window.setFramerateLimit(60);
  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
      {
        window.close();
      }
      if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) 
      {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        int x = (mousePos.x / tileSize) - 2;
        int y = (mousePos.y / tileSize) - 2;
        FarmUnit* unit = getUnit(x, y);
        CropField* cropField = dynamic_cast<CropField*>(unit);
        CropField* currentCropField = dynamic_cast<CropField*>(farmIterator->currentFarm());
        if (cropField && currentCropField && cropField == currentCropField)
        {
          if(!cropField->hasExtraBarn())
          {
            cropField->addExtraBarn();
          }
          else
          {
            cropField->removeExtraBarn();
          }
        }
      }
    }
    window.clear(sf::Color::Blue);
    displayFarm(window);
    displayRoad(window);
    window.display();
  }
}

void Game::displayFarm(sf::RenderWindow& window)
{
  farmIterator->firstFarm();
  while(farmIterator->hasNext())
  {
    FarmUnit* unit = farmIterator->currentFarm();
    int x = farmIterator->path[farmIterator->currentIndex].x;
    int y = farmIterator->path[farmIterator->currentIndex].y;
    CropField* cropField = dynamic_cast<CropField*>(unit);
    if (cropField)
    {
      std::string soilStateName = cropField->getSoilStateName();
      auto it = spriteMap.find(soilStateName);
      if (it != spriteMap.end())
      {
        sf::Sprite sprite = it->second;
        sprite.setPosition((x+2) * tileSize, (y+2) * tileSize);
        sf::Vector2u textureSize = sprite.getTexture()->getSize();
        sprite.setScale(
          static_cast<float>(tileSize) / textureSize.x, 
          static_cast<float>(tileSize) / textureSize.y
        );
        window.draw(sprite);
        if(currentIndex == farmIterator->getIndex(unit))
        {
          sf::RectangleShape highlight(sf::Vector2f(tileSize, tileSize));
          highlight.setPosition((x+2) * tileSize +5, (y+2) * tileSize+5);
          highlight.setFillColor(sf::Color::Transparent);
          highlight.setOutlineThickness(5);
          highlight.setOutlineColor(sf::Color::Yellow);
          highlight.setSize(sf::Vector2f(tileSize - 10, tileSize - 10));
          window.draw(highlight);
        }
        if(cropField->hasExtraBarn())
        {
          sf::Sprite barn = spriteMap.find("Barn")->second;
          barn.setPosition((x+2) * tileSize, (y+2) * tileSize);
          sf::Vector2u textureSize = sprite.getTexture()->getSize();
          barn.setScale(
              static_cast<float>(tileSize) / textureSize.x, 
              static_cast<float>(tileSize) / textureSize.y
          );
          window.draw(barn);
        }
      }
      else
      {
        std::cerr << "Unknown soil state: " << soilStateName << std::endl;
      }
    }
    farmIterator->next();
  }
}

void Game::displayRoad(sf::RenderWindow& window)
{
  for(int x = 0 ; x < width+2 ; x++)
  {
    for(int y = 0 ; y < height+2 ; y++)
    {
      if(x == 0 || y == 0 || x == width+1 || y == height+1)
      {
        auto it = spriteMap.find("Dry");
        if(x == 0 && y ==0)
        {
          it = spriteMap.find("TopLeft");
        }
        else if(x == 0 && y == height+1)
        {
          it = spriteMap.find("BottomLeft");
        }
        else if(y == 0 && x == width+1)
        {
          it = spriteMap.find("TopRight");
        }
        else if(y == height+1 && x == width+1)
        {
          it = spriteMap.find("BottomRight");
        }
        else if((x == 0 || x == width+1) && y > 0 && y < height+1)
        {
          it = spriteMap.find("Vertical");
        }
        else if((y == 0 || y == height+1) && x > 0 && x < width+1)
        {
          it = spriteMap.find("Horisontal");
        }
        
        if (it != spriteMap.end())
        {
          sf::Sprite sprite = it->second;
          sprite.setPosition((x+1) * tileSize, (y+1) * tileSize);
          sf::Vector2u textureSize = sprite.getTexture()->getSize();
          sprite.setScale(
              static_cast<float>(tileSize) / textureSize.x, 
              static_cast<float>(tileSize) / textureSize.y
          );
          window.draw(sprite);
        }
      }
    }
  }
}

#endif
void Game::setUnit(int x, int y, FarmUnit* unit)
{
    farmIterator->insert(x , y , unit);
}

FarmUnit* Game::getUnit(int x , int y)
{
  return farmIterator->get(x , y);
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