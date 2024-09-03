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
    for(int x = 0 ; x < width ; x++)
    {
      for(int y = 0 ; y < height ; y++)
      {
        FarmUnit* unit = this->getUnit(x,y);
        CropField* cropField = dynamic_cast<CropField*>(unit);
        if (cropField)
        {
          cropField->harvest();
          cropField->rain();
        }
      }
    }
    std::cout << getBFSBestTraversal() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(20000));
  }
}

int Game::getBFSBestTraversal()
{
  int bestX = 0;
  int bestY = 0;
  int best = 0;
  for(int x = 0 ; x < width ; x++)
  {
    for(int y = 0 ; y < height ; y++)
    {
      if(x == 0 || x == width-1 || y == 0 || y == height-1)
      {
         if(this->bfsTruckTraversal(x,y) >= best)
         {
            best = bfsTruckTraversal(x,y);
            bestX = x;
            bestY = y;
         }
      }
    }
  }
  return this->bfsTruckTraversal(bestX , bestY);
}

int Game::bfsTruckTraversal(int startX, int startY)
{
  if (!isWithinBounds(startX, startY) || !isTraversable(startX, startY)) 
  {
    return 0;
  }
  std::unordered_set<Coords> visited;
  std::queue<Coords> queue;
  queue.push({startX, startY});
  visited.insert({startX, startY});
  bfsPath.clear();
  int amountCrops = 0;
  while (!queue.empty()) 
  {
    Coords current = queue.front();
    queue.pop();
    int x = current.x;
    int y = current.y;
    bfsPath.push_back(current);
    FarmUnit* unit = getUnit(x, y);
    if (unit) 
    {
      CropField* cropField = dynamic_cast<CropField*>(unit);
      if (cropField) 
      {
        int amount = cropField->removeCrops(1000);
        cropField->addCrops(amount);
        amountCrops += amount;
      }
    }
    std::vector<Coords> neighbors = {{x+1, y}, {x-1, y}, {x, y+1}, {x, y-1}};
    for (const Coords& neighbor : neighbors) 
    {
      int nx = neighbor.x;
      int ny = neighbor.y;
      if (isWithinBounds(nx, ny) && isTraversable(nx, ny) && visited.find(neighbor) == visited.end()) 
      {
        queue.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
  return amountCrops;
}

bool Game::isWithinBounds(int x, int y) const 
{
  return x >= 0 && x < width && y >= 0 && y < height;
}

bool Game::isTraversable(int x, int y) const
{
  FarmUnit* unit = getUnit(x, y);
  if (!unit) return false;
  CropField* cropField = dynamic_cast<CropField*>(unit);
  if (cropField) 
  {
    std::string soilState = cropField->getSoilStateName();
    return soilState != "Flooded";
  }
  return false; 
}

void Game::displayTraversal(sf::RenderWindow& window)
{
  sf::Font font;
  if(!font.loadFromFile("lovedays.ttf"))
  {
    return;
  }
  int index = 1;
  for (const Coords& coord : bfsPath) 
  {
    sf::CircleShape circle(tileSize / 4);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition((coord.x + 2) * tileSize + tileSize / 2, (coord.y + 2) * tileSize + tileSize / 2);
    window.draw(circle);

    sf::Text text;
    text.setFont(font);
    text.setString(std::to_string(index));
    text.setCharacterSize(14);
    text.setFillColor(sf::Color::White);
    text.setPosition((coord.x + 2) * tileSize + tileSize / 2, (coord.y + 2) * tileSize + tileSize / 2);
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.width / 2, textRect.height / 2);
    text.setPosition((coord.x + 2) * tileSize + tileSize / 2 + tileSize / 4, 
                     (coord.y + 2) * tileSize + tileSize / 2 + tileSize / 4);

    window.draw(text);

    ++index;
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

void Game::displayWindow()
{
  sf::RenderWindow window(sf::VideoMode((width+4) * tileSize, (height+4) * tileSize), "Pixel Art Grid");
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
    window.clear(sf::Color::Blue);
    displayFarm(window);
    displayRoad(window);
    displayTraversal(window);
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