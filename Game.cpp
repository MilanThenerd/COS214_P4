#include "Game.h"
#include <iostream>

Game::Game(int width , int height) : width(width) , height(height)
{
  farmMap.resize(width, std::vector<FarmUnit*>(height, nullptr));
  #ifdef USE_GUI
  loadTextures();
  #endif
  for(int x = 0 ; x < width ; x++)
  {
    for(int y = 0 ; y < height ; y++)
    {
      setUnit(x , y , new CropField("Corn" , 100));
    }
  }
  dfsTraversal(0,0);
  bfsTraversal(0,0);
  #ifdef USE_GUI
  this->runThread = std::thread(&Game::run, this);
  this->displayWindow();
  #else
    // this->run();
  #endif

}

void Game::run()
{
  while (true) 
  {
    if(this->isDone())
    {
      bfstraversal = !bfstraversal;
      firstFarm();
    }
    else
    {
      next();
    }
    // Manage(currentFarm());
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
}

void Game::bfsTraversal(int startX, int startY)
{
  if (!isWithinBounds(startX, startY)) 
  {
    return;
  }
  std::unordered_set<Coords> visited;
  std::queue<Coords> queue;
  queue.push({startX, startY});
  visited.insert({startX, startY});
  bfsPath.clear();
  while (!queue.empty()) 
  {
    Coords current = queue.front();
    queue.pop();
    int x = current.x;
    int y = current.y;
    bfsPath.push_back(current);
    std::vector<Coords> neighbors = {{x+1, y}, {x-1, y}, {x, y+1}, {x, y-1}};
    for (const Coords& neighbor : neighbors) 
    {
      int nx = neighbor.x;
      int ny = neighbor.y;
      if (isWithinBounds(nx, ny) && visited.find(neighbor) == visited.end()) 
      {
        queue.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
}

void Game::dfsTraversal(int startX, int startY)
{
  if (!isWithinBounds(startX, startY)) 
  {
    return;
  }
  std::unordered_set<Coords> visited;
  std::stack<Coords> stack;
  stack.push({startX, startY});
  visited.insert({startX, startY});
  dfsPath.clear();

  while (!stack.empty()) 
  {
    Coords current = stack.top();
    stack.pop();

    int x = current.x;
    int y = current.y;
    dfsPath.push_back(current);
    std::vector<Coords> neighbors = {{x+1, y}, {x-1, y}, {x, y+1}, {x, y-1}};
    for (const Coords& neighbor : neighbors) 
    {
      int nx = neighbor.x;
      int ny = neighbor.y;
      if (isWithinBounds(nx, ny) && visited.find(neighbor) == visited.end()) 
      {
        stack.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
}

bool Game::isWithinBounds(int x, int y) const 
{
  return x >= 0 && x < width && y >= 0 && y < height;
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
        int x = (mousePos.x / tileSize) - 2; // Convert pixel position to grid position
        int y = (mousePos.y / tileSize) - 2;
        if (isWithinBounds(x, y))
        {
          FarmUnit* unit = getUnit(x, y);
          CropField* cropField = dynamic_cast<CropField*>(unit);
          CropField* currentCropField = dynamic_cast<CropField*>(currentFarm());
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
    }


    window.clear(sf::Color::Blue);
    displayFarm(window);
    displayRoad(window);
    // displayTraversal(window);
    // displayHUD(window);
    window.display();
  }
}

void Game::displayFarm(sf::RenderWindow& window)
{
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
          sprite.setPosition((x+2) * tileSize, (y+2) * tileSize);
          window.draw(sprite);

          CropField* currentCropField = dynamic_cast<CropField*>(currentFarm());
          if(currentCropField && cropField == currentCropField)
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
            window.draw(barn);
          }
        }
        else
        {
          std::cerr << "Unknown soil state: " << soilStateName << std::endl;
        }
      }
    }
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
          window.draw(sprite);
        }
      }
    }
  }
}

#endif
void Game::setUnit(int x, int y, FarmUnit* unit)
{
    delete farmMap[x][y];
    farmMap[x][y] = unit;
}

FarmUnit* Game::getUnit(int x, int y) const
{
    return farmMap[x][y];
}

FarmUnit* Game::firstFarm()
{
  if(bfstraversal)
  {
    if(bfsPath.empty())
    {
      return nullptr;
    }
    currentIndex = 0;
    return getUnit(bfsPath[currentIndex].x ,bfsPath[currentIndex].x);
  }
  else
  {
    if(dfsPath.empty())
    {
      return nullptr;
    }
    currentIndex = 0;
    return getUnit(dfsPath[currentIndex].x ,dfsPath[currentIndex].x);
  }
  return nullptr;
}

FarmUnit* Game::next()
{
  if(bfstraversal)
  {
    if (currentIndex + 1 >= (int)bfsPath.size()) 
    {
        return nullptr;
    }
    currentIndex++;
    return getUnit(bfsPath[currentIndex].x, bfsPath[currentIndex].y);
  }
  else
  {
    if (currentIndex + 1 >= (int)dfsPath.size()) 
    {
        return nullptr;
    }
    currentIndex++;
    return getUnit(dfsPath[currentIndex].x, dfsPath[currentIndex].y);
  }
  return nullptr;
}

bool Game::isDone() const 
{
  if(bfstraversal)
  {
    return currentIndex >= (int)bfsPath.size()-1;
  }
  else
  {
    return currentIndex >= (int)dfsPath.size()-1;
  }
}

FarmUnit* Game::currentFarm() const 
{  
  if(bfstraversal)
  {
    if (currentIndex >= (int)bfsPath.size()) 
    {
        return nullptr;
    }
    return getUnit(bfsPath[currentIndex].x, bfsPath[currentIndex].y);
  }
  else
  {
    if (currentIndex >= (int)dfsPath.size()) 
    {
        return nullptr;
    }
    return getUnit(dfsPath[currentIndex].x, dfsPath[currentIndex].y);
  }
  return nullptr;
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