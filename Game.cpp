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
  publisher = new Publisher();
  #ifdef USE_GUI
  loadTextures();
  #endif
  setIterator(false);
  for(int x = 0 ; x < width ; x++)
  {
    for(int y = 0 ; y < height ; y++)
    {
      setUnit(x , y , new CropField("Corn" , 100 , publisher));
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
  TruckFactory* factory = new TruckFactory(this->farmMap);
  while (true) 
  {
      if(currentIndex == 0)
      {
        if(publisher->hasQueue())
        {
          if(publisher->getTrucks().size() == 0)
          {
            publisher->add(factory->buy("Delivery"));
            publisher->add(factory->buy("Fertilizer"));
          }
          publisher->handle();
          std::vector<Truck*> trucks = publisher->getTrucks();
          std::vector<std::thread> threads;
          for(Truck* truck : trucks)
          {
            if(DeliveryTruck* deliveryTruck = dynamic_cast<DeliveryTruck*>(truck))
            {
              deliveryTruck->startEngine();
            }
          }
          std::this_thread::sleep_for(std::chrono::milliseconds(10000));
          for(Truck* truck : trucks)
          {
            publisher->removeTruck(truck);
            factory->sell(truck);
          }
        }
        rain();
      }
      FarmUnit* unit = this->farmIterator->getFarmUnitByIndex(currentIndex);
      if(ExtraBarnDecorator* barnDecorator = dynamic_cast<ExtraBarnDecorator*>(unit))
      {
        barnDecorator->harvest();
      }
      else if(CropField* cropField = dynamic_cast<CropField*>(unit))
      {
        cropField->harvest();
      }
      selectingHUD = true;
      if(selectingHUD)
      {
        while(true)
        {
          if(!selectingHUD)
          {
            break;
          }
        }
      }
      if (this->farmIterator->getLength() > 0) 
      {
        currentIndex = (currentIndex + 1) % this->farmIterator->getLength();
      }
  }
}

std::string Game::getDirectionSpriteKey(Coords currentPos , Coords nextPos)
{
    if (nextPos.x > currentPos.x)
    {
        return "TruckRight";
    }
    else if (nextPos.x < currentPos.x)
    {
        return "TruckLeft";
    }
    else if (nextPos.y > currentPos.y)
    {
        return "TruckDown";
    }
    else if (nextPos.y < currentPos.y)
    {
        return "TruckUp";
    }
    return "TruckRight";
}

void Game::rain()
{
  FarmTraversal* farmIteratorRain = new FarmTraversalBFS(farmMap,0,0);
  farmIteratorRain->firstFarm();
  while(farmIteratorRain->hasNext())
  {
    FarmUnit* unit = farmIteratorRain->currentFarm();
    CropField* cropField = dynamic_cast<CropField*>(unit);
    if(cropField)
    {
      cropField->rain();
      cropField->notifyDelivery();
    }
    farmIteratorRain->next();
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
  if(!loadTextureAndCreateSprite("ButtonDFS", "ButtonDFS.png"))
  {
    std::cerr << "Failed to load ButtonDFS texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("ButtonBFS", "ButtonBFS.png"))
  {
    std::cerr << "Failed to load ButtonBFS texture" << std::endl;
  }
  if(!loadTextureAndCreateSprite("ButtonQUIT", "ButtonQUIT.png"))
  {
    std::cerr << "Failed to load ButtonQUIT texture" << std::endl;
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
  window.setFramerateLimit(15);
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
        if(x == -2 && y == -2)
        {
          window.close();
          selectingHUD = false;
        }
        else if(x == -1 && y == -2)
        {
          setIterator(false);
          selectingHUD = false;
        }
        else if(x == 0 && y == -2)
        {
          setIterator(true);
          selectingHUD = false;
        }
        else
        {
          selectingHUD = false;
        }
      }
    }
    window.clear(sf::Color::Blue);
    displayFarm(window);
    displayRoad(window);
    displayTrucks(window); 
    displayHUD(window);
    window.display();
  }
}

void Game::displayTrucks(sf::RenderWindow& window)
{
  std::vector<Truck*> trucks = publisher->getTrucks();
  for(Truck* truck : trucks)
  {
    DeliveryTruck* delivery = dynamic_cast<DeliveryTruck*>(truck);
    if(delivery)
    {
      Coords* truckPos = delivery->getPosition();
      delivery->moveTowardsNextFarmUnit(1);
      Coords* nextPos = delivery->getPosition();

      std::string spriteKey = getDirectionSpriteKey(*truckPos , *nextPos);
      auto spriteIt = spriteMap.find(spriteKey);
      if (spriteIt != spriteMap.end()) 
      {
        drawSprite(window, spriteIt->second, truckPos->x, truckPos->y);
      } 
      else 
      {
        std::cerr << "Truck sprite for direction " << spriteKey << " not found!" << std::endl;
      }
    }
  }
}

void Game::displayHUD(sf::RenderWindow& window)
{
  drawSprite(window,spriteMap.find("ButtonQUIT")->second,-2,-2);
  drawSprite(window,spriteMap.find("ButtonDFS")->second,-1,-2);
  drawSprite(window,spriteMap.find("ButtonBFS")->second,0,-2);

  FarmUnit* unit = farmIterator->getFarmUnitByIndex(currentIndex);
  int cropAmount = 0;
  if (ExtraBarnDecorator* barnDecorator = dynamic_cast<ExtraBarnDecorator*>(unit))
  {
    cropAmount = barnDecorator->getTotalCapacity() - barnDecorator->getLeftoverCapacity();
  }
  else if (CropField* cropField = dynamic_cast<CropField*>(unit))
  {
    cropAmount = cropField->getTotalCapacity() - cropField->getLeftoverCapacity();
  }
  sf::Font font;
  if(!font.loadFromFile("lovedays.ttf"))
  {
    std::cerr << "Error loading font" << std::endl;
    return;
  }
  sf::Text text;
  text.setFont(font);
  text.setString(std::to_string(cropAmount));
  text.setCharacterSize(30);
  text.setFillColor(sf::Color::White);
  float screenWidth = window.getSize().x;
  text.setPosition((screenWidth / 2) - (text.getLocalBounds().width / 2), 10);
  window.draw(text);
}

void Game::displayFarm(sf::RenderWindow& window)
{
  farmIterator->firstFarm();
  while (farmIterator->hasNext())
  {
    FarmUnit* unit = farmIterator->currentFarm();
    int x = farmIterator->getPath()[farmIterator->getCurrentIndex()].x;
    int y = farmIterator->getPath()[farmIterator->getCurrentIndex()].y;

    if (ExtraBarnDecorator* barnDecorator = dynamic_cast<ExtraBarnDecorator*>(unit))
    {
      std::string soilStateName = barnDecorator->getSoilStateName();
      if (auto it = spriteMap.find(soilStateName); it != spriteMap.end())
      {
        drawSprite(window, it->second, x, y);

        if (auto barnIt = spriteMap.find("Barn"); barnIt != spriteMap.end())
        {
          drawSprite(window, barnIt->second, x, y);
        }
        else
        {
          std::cerr << "Barn sprite not found in spriteMap." << std::endl;
        }
      }
      else
      {
        std::cerr << "Unknown soil state: " << soilStateName << std::endl;
      }
    }
    else if (CropField* cropField = dynamic_cast<CropField*>(unit))
    {
      std::string soilStateName = cropField->getSoilStateName();
      if (auto it = spriteMap.find(soilStateName); it != spriteMap.end())
      {
        drawSprite(window, it->second, x, y);
      }
      else
      {
        std::cerr << "Unknown soil state: " << soilStateName << std::endl;
      }
    }
    if (currentIndex == farmIterator->getIndex(unit))
    {
      sf::RectangleShape highlight(sf::Vector2f(tileSize, tileSize));
      int posX = (x + 2) * tileSize + 5;
      int posY = (y + 2) * tileSize + 5;
      highlight.setPosition(posX, posY);
      highlight.setFillColor(sf::Color::Transparent);
      highlight.setOutlineThickness(5);
      highlight.setOutlineColor(sf::Color::Yellow);
      highlight.setSize(sf::Vector2f(tileSize - 10, tileSize - 10));
      window.draw(highlight);
      displayHUD(window);
    }
  farmIterator->next();
  }
}

void Game::drawSprite(sf::RenderWindow& window, const sf::Sprite& sprite, int x, int y)
{
    sf::Sprite tempSprite = sprite;
    tempSprite.setPosition((x + 2) * tileSize, (y + 2) * tileSize);
    sf::Vector2u textureSize = tempSprite.getTexture()->getSize();
    tempSprite.setScale(
        static_cast<float>(tileSize) / textureSize.x,
        static_cast<float>(tileSize) / textureSize.y
    );
    window.draw(tempSprite);
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
    this->farmIterator->insert(x , y , unit);
}

FarmUnit* Game::getUnit(int x , int y)
{
  return this->farmIterator->get(x , y);
}

void Game::setIterator(bool type)
{
  currentIndex = 0;
  if(type)
  {
    this->farmIterator = new FarmTraversalBFS(farmMap,0,0);
  }
  else
  {
    this->farmIterator = new FarmTraversalDFS(farmMap,0,0);
  }
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