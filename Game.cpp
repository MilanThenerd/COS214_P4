#include "Game.h"
#include <iostream>

Game::Game(int width, int height) : width(width), height(height)
{
  farmMap.resize(width, std::vector<FarmUnit *>(height, nullptr));
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
  farmIterator = new FarmTraversalDFS(farmMap, 0, 0);
  farmIterator->initialize();
  weatherIterator = new FarmTraversalBFS(farmMap, 0, 0);
  weatherIterator->initialize();
  for (int x = 0; x < width; x++)
  {
    for (int y = 0; y < height; y++)
    {
      setUnit(x, y, new CropField("Corn", 100));
    }
  }
#ifdef USE_GUI
  this->runThread = std::thread(&Game::run, this);
  this->displayWindow();
#else
  this->run();
#endif
}

void Game::run()
{
  std::cout << "Farm size" << (int)farmIterator->getLength() << std::endl;
  while (true)
  {
    weatherIterator->firstFarm();
    do
    {
      currentIndex = (currentIndex + 1) % ((int)farmIterator->getLength() + 1);
      rain();
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    } while (currentIndex != (int)farmIterator->getLength());
    isPaused = true;

    while (isPaused)
    {
    }

    // End of day
    currentDay++;
  }
}

void Game::rain()
{
  FarmUnit *unit = weatherIterator->currentFarm();
  CropField *cropField = dynamic_cast<CropField *>(unit);
  if (cropField)
  {
    cropField->rain();
  }
  weatherIterator->next();
  if (weatherIterator->isDone())
  {
    weatherIterator->firstFarm();
  }
}

#ifdef USE_GUI

void Game::loadTextures()
{
  if (!loadTextureAndCreateSprite("Dry", "Dry.png"))
  {
    std::cerr << "Failed to load Dry texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Flooded", "Flooded.png"))
  {
    std::cerr << "Failed to load Flooded texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Fruitful", "Fruitful.png"))
  {
    std::cerr << "Failed to load Fruitful texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Vertical", "Vertical.png"))
  {
    std::cerr << "Failed to load Vertical texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Horisontal", "Horisontal.png"))
  {
    std::cerr << "Failed to load Horisontal texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("TopLeft", "TopLeft.png"))
  {
    std::cerr << "Failed to load TopLeft texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("BottomLeft", "BottomLeft.png"))
  {
    std::cerr << "Failed to load BottomLeft texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("TopRight", "TopRight.png"))
  {
    std::cerr << "Failed to load TopRight texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("BottomRight", "BottomRight.png"))
  {
    std::cerr << "Failed to load BottomRight texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Barn", "Barn.png"))
  {
    std::cerr << "Failed to load Barn texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("TruckLeft", "TruckLeft.png"))
  {
    std::cerr << "Failed to load TruckLeft texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("TruckRight", "TruckRight.png"))
  {
    std::cerr << "Failed to load TruckRight texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("TruckDown", "TruckDown.png"))
  {
    std::cerr << "Failed to load TruckDown texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("TruckUp", "TruckUp.png"))
  {
    std::cerr << "Failed to load TruckUp texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Cloud", "Cloud.png"))
  {
    std::cerr << "Failed to load Cloud texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Regular", "Regular.png"))
  {
    std::cerr << "Failed to load Regular texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Play", "Play.png"))
  {
    std::cerr << "Failed to load Play texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("FertilizerButton", "FertilizerButton.png"))
  {
    std::cerr << "Failed to load FertilizerButton texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("BarnButton", "BarnButton.png"))
  {
    std::cerr << "Failed to load BarnButton texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("Fertilizer", "Fertilizer.png"))
  {
    std::cerr << "Failed to load Fertilizer texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("BigBarn", "BigBarn.png"))
  {
    std::cerr << "Failed to load BigBarn texture" << std::endl;
  }
  if (!loadTextureAndCreateSprite("BigBarnButton", "BigBarnButton.png"))
  {
    std::cerr << "Failed to load BigBarnButton texture" << std::endl;
  }
}

bool Game::loadTextureAndCreateSprite(const std::string &key, const std::string &filename)
{
  auto texturePtr = std::make_shared<sf::Texture>();
  if (!texturePtr->loadFromFile("Art/" + filename))
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
  sf::RenderWindow window(sf::VideoMode((width + 4) * tileSize, (height + 4) * tileSize), "Pixel Art Grid");
  window.setFramerateLimit(60);

  // Load font
  if (!font.loadFromFile("Art/lovedays.ttf"))
  {
    std::cerr << "Failed to load font" << std::endl;
    return;
  }

  initText();
  initUi(window);

  while (window.isOpen())
  {
    handleEvents(window);

    window.clear(sf::Color::Blue);
    displayFarm(window);
    displayRoad(window);
    displayUI(window);
    window.display();
  }
}

void Game::handleEvents(sf::RenderWindow &window)
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed)
    {
      window.close();
    }
    else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
      handleMouse(event);
      sf::Vector2i mousePos = sf::Mouse::getPosition(window);
      sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

      // Check if the barn button is clicked
      if (spriteMap.find("BarnButton") != spriteMap.end())
      {
        sf::Sprite sprite = spriteMap["BarnButton"];
        sprite.setPosition(barnButtonPosition);
        sf::Vector2u textureSize = sprite.getTexture()->getSize();
        sprite.setScale(
            static_cast<float>(tileSize) / textureSize.x / 2,
            static_cast<float>(tileSize) / textureSize.y / 2);
        if (sprite.getGlobalBounds().contains(mousePosF))
        {
          isDraggingBarnButton = true;
          dragOffset = mousePosF - barnButtonPosition;
        }
      }

      // Check if the fertilizer button is clicked
      if (spriteMap.find("FertilizerButton") != spriteMap.end())
      {
        sf::Sprite sprite = spriteMap["FertilizerButton"];
        sprite.setPosition(fertilizerButtonPosition);
        sf::Vector2u textureSize = sprite.getTexture()->getSize();
        sprite.setScale(
            static_cast<float>(tileSize) / textureSize.x / 2,
            static_cast<float>(tileSize) / textureSize.y / 2);
        if (sprite.getGlobalBounds().contains(mousePosF))
        {
          isDraggingFertilizerButton = true;
          dragOffset = mousePosF - fertilizerButtonPosition;
        }
      }

      // Check if the bigbarn button is clicked
      if (spriteMap.find("BigBarnButton") != spriteMap.end())
      {
        sf::Sprite sprite = spriteMap["BigBarnButton"];
        sprite.setPosition(bigBarnButtonPosition);
        sf::Vector2u textureSize = sprite.getTexture()->getSize();
        sprite.setScale(
            static_cast<float>(tileSize) / textureSize.x / 2,
            static_cast<float>(tileSize) / textureSize.y / 2);
        if (sprite.getGlobalBounds().contains(mousePosF))
        {
          isDraggingBigBarnButton = true;
          dragOffset = mousePosF - bigBarnButtonPosition;
        }
      }
    }
    else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
    {
      isDraggingBarnButton = false;
      isDraggingFertilizerButton = false;
      isDraggingBigBarnButton = false;

      // Check if the barn button is over a farm unit
      sf::Vector2f barnDropPosition = barnButtonPosition - sf::Vector2f(tileSize * 2, tileSize * 2);
      if (isOverFarmUnit(barnDropPosition))
      {
        sf::Vector2i farmUnitCoords = getFarmUnitCoords(barnDropPosition);
        // Wrap farmunit in ExtraBarnDecorator
        FarmUnit *unit = getUnit(farmUnitCoords.x, farmUnitCoords.y);
        if (unit)
        {
          // Check if unit is already a barn
          if (!DecoratorHelper::hasDecorator(unit, typeid(ExtraBarnDecorator)))
          {
            farmMap[farmUnitCoords.x][farmUnitCoords.y] = new ExtraBarnDecorator(unit);
            std::cout << "Barn button dropped over farm unit at: (" << farmUnitCoords.x << ", " << farmUnitCoords.y << ")" << std::endl;
          }
        }
      }

      // Check if the fertilizer button is over a farm unit
      sf::Vector2f fertDropPosition = fertilizerButtonPosition - sf::Vector2f(tileSize * 2, tileSize * 2);
      if (isOverFarmUnit(fertDropPosition))
      {
        sf::Vector2i farmUnitCoords = getFarmUnitCoords(fertDropPosition);
        // Wrap farmunit in FertilizerDecorator
        FarmUnit *unit = getUnit(farmUnitCoords.x, farmUnitCoords.y);
        if (unit)
        {
          // Check if unit is already a fertilizer
          if (!DecoratorHelper::hasDecorator(unit, typeid(FertilizerDecorator)))
          {
            farmMap[farmUnitCoords.x][farmUnitCoords.y] = new FertilizerDecorator(unit);
            std::cout << "Fertilizer button dropped over farm unit at: (" << farmUnitCoords.x << ", " << farmUnitCoords.y << ")" << std::endl;
          }
        }
      }

      // Check if the big barn button is over a farm unit
      sf::Vector2f bbDropPosition = bigBarnButtonPosition - sf::Vector2f(tileSize * 2, tileSize * 2);
      if (isOverFarmUnit(bbDropPosition))
      {
        sf::Vector2i farmUnitCoords = getFarmUnitCoords(bbDropPosition);
        FarmUnit *unit = getUnit(farmUnitCoords.x, farmUnitCoords.y);
        Barn *bu = dynamic_cast<Barn *>(unit);
        if (!bu)
        {
          delete unit;
          farmMap[farmUnitCoords.x][farmUnitCoords.y] = new Barn(farmMap, farmUnitCoords.x, farmUnitCoords.y);
          std::cout << "Big Barn button dropped over farm unit at: (" << farmUnitCoords.x << ", " << farmUnitCoords.y << ")" << std::endl;
        }
      }

      // Snap buttons back to their original positions
      barnButtonPosition = originalBarnButtonPosition;
      fertilizerButtonPosition = originalFertilizerButtonPosition;
      bigBarnButtonPosition = originalBigBarnButtonPosition;
    }
    else if (event.type == sf::Event::MouseMoved)
    {
      if (isDraggingBarnButton)
      {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        barnButtonPosition = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) - dragOffset;
      }
      else if (isDraggingFertilizerButton)
      {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        fertilizerButtonPosition = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) - dragOffset;
      }
      else if (isDraggingBigBarnButton)
      {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bigBarnButtonPosition = sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) - dragOffset;
      }
    }
  }
}

bool Game::isOverFarmUnit(const sf::Vector2f &position)
{
  int x = static_cast<int>(position.x) / tileSize;
  int y = static_cast<int>(position.y) / tileSize;
  return (x >= 0 && x < width && y >= 0 && y < height);
}

sf::Vector2i Game::getFarmUnitCoords(const sf::Vector2f &position)
{
  int x = static_cast<int>(position.x) / tileSize;
  int y = static_cast<int>(position.y) / tileSize;
  return sf::Vector2i(x, y);
}

void Game::displayFarm(sf::RenderWindow &window)
{
  farmIterator->firstFarm();
  while (farmIterator->hasNext())
  {
    FarmUnit *unit = farmIterator->currentFarm();
    int x = farmIterator->getPath()[farmIterator->getCurrentIndex()].x;
    int y = farmIterator->getPath()[farmIterator->getCurrentIndex()].y;

    // Unwrap all decorators
    ExtraBarnDecorator *barnDecorator = nullptr;
    FertilizerDecorator *fertilizerDecorator = nullptr;
    CropField *cropField = nullptr;
    Barn *barn = nullptr;

    while (unit)
    {
      if (auto bd = dynamic_cast<ExtraBarnDecorator *>(unit))
      {
        barnDecorator = bd;
        unit = bd->getWrappedUnit();
      }
      else if (auto fd = dynamic_cast<FertilizerDecorator *>(unit))
      {
        fertilizerDecorator = fd;
        unit = fd->getWrappedUnit();
      }
      else if (auto cf = dynamic_cast<CropField *>(unit))
      {
        cropField = cf;
        break;
      }
      else if (auto cf = dynamic_cast<Barn *>(unit))
      {
        barn = cf;
        break;
      }
      else
      {
        break;
      }
    }

    // Draw the base crop field
    if (cropField)
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

    // Draw the fertilizer decorator
    if (fertilizerDecorator)
    {
      if (auto it = spriteMap.find("Fertilizer"); it != spriteMap.end())
      {
        drawSprite(window, it->second, x, y);
      }
      else
      {
        std::cerr << "Fertilizer sprite not found in spriteMap." << std::endl;
      }
    }

    // Draw the barn decorator
    if (barnDecorator)
    {
      if (auto it = spriteMap.find("Barn"); it != spriteMap.end())
      {
        drawSprite(window, it->second, x, y);
      }
      else
      {
        std::cerr << "Barn sprite not found in spriteMap." << std::endl;
      }
    }

    if (barn)
    {
      if (auto it = spriteMap.find("BigBarn"); it != spriteMap.end())
      {
        drawSprite(window, it->second, x, y);
      }
      else
      {
        std::cerr << "BigBarn sprite not found in spriteMap." << std::endl;
      }
    }

    if (currentIndex == farmIterator->getIndex(farmIterator->currentFarm()))
    {
      sf::RectangleShape highlight(sf::Vector2f(tileSize, tileSize));
      highlight.setPosition((x + 2) * tileSize + 5, (y + 2) * tileSize + 5);
      highlight.setFillColor(sf::Color::Transparent);
      highlight.setOutlineThickness(5);
      highlight.setOutlineColor(sf::Color::Yellow);
      highlight.setSize(sf::Vector2f(tileSize - 10, tileSize - 10));
      window.draw(highlight);
    }
    if (currentIndex == weatherIterator->getIndex(unit))
    {
      if (auto it = spriteMap.find("Cloud"); it != spriteMap.end())
      {
        drawSprite(window, it->second, x, y);
      }
    }
    farmIterator->next();
  }
}

void Game::drawSprite(sf::RenderWindow &window, const sf::Sprite &sprite, int x, int y)
{
  sf::Sprite tempSprite = sprite;
  tempSprite.setPosition((x + 2) * tileSize, (y + 2) * tileSize);
  sf::Vector2u textureSize = tempSprite.getTexture()->getSize();
  tempSprite.setScale(
      static_cast<float>(tileSize) / textureSize.x,
      static_cast<float>(tileSize) / textureSize.y);
  window.draw(tempSprite);
}

void Game::displayText(sf::RenderWindow &window, std::string text, int fontsize, sf::Color col, int x, int y, TextAlign align)
{
  sf::Text t;
  sf::Vector2u windowSize = window.getSize();
  t.setFont(font);
  t.setString(text);
  t.setFillColor(col);
  t.setCharacterSize(fontsize);

  sf::FloatRect textBounds = t.getLocalBounds();

  if (align == TextAlign::TopLeft)
  {
    t.setPosition(x, y);
  }
  else if (align == TextAlign::TopRight)
  {
    t.setPosition(windowSize.x - textBounds.width - x, y);
  }
  else if (align == TextAlign::BottomLeft)
  {
    t.setPosition(x, windowSize.y - textBounds.height - y);
  }
  else if (align == TextAlign::BottomRight)
  {
    t.setPosition(windowSize.x - textBounds.width - x, windowSize.y - textBounds.height - y);
  }
  else if (align == TextAlign::TopCenter)
  {
    t.setPosition((windowSize.x - textBounds.width) / 2, y);
  }

  window.draw(t);
}

void Game::displayUI(sf::RenderWindow &window)
{
  if (isPaused)
  {
    if (auto it = spriteMap.find("Play"); it != spriteMap.end())
    {
      sf::Sprite sprite = it->second;
      sprite.setPosition(0 * tileSize, 0 * tileSize);
      sf::Vector2u textureSize = sprite.getTexture()->getSize();
      sprite.setScale(
          static_cast<float>(tileSize) / textureSize.x / 2,
          static_cast<float>(tileSize) / textureSize.y / 2);
      window.draw(sprite);
    }

    // Draw barn button
    if (auto it = spriteMap.find("BarnButton"); it != spriteMap.end())
    {
      sf::Sprite sprite = it->second;
      sprite.setPosition(barnButtonPosition);
      sf::Vector2u textureSize = sprite.getTexture()->getSize();
      sprite.setScale(
          static_cast<float>(tileSize) / textureSize.x / 2,
          static_cast<float>(tileSize) / textureSize.y / 2);
      window.draw(sprite);
    }

    // Draw fertilizer button
    if (auto it = spriteMap.find("FertilizerButton"); it != spriteMap.end())
    {
      sf::Sprite sprite = it->second;
      sprite.setPosition(fertilizerButtonPosition);
      sf::Vector2u textureSize = sprite.getTexture()->getSize();
      sprite.setScale(
          static_cast<float>(tileSize) / textureSize.x / 2,
          static_cast<float>(tileSize) / textureSize.y / 2);
      window.draw(sprite);
    }

    // Draw BigBarn button
    if (auto it = spriteMap.find("BigBarnButton"); it != spriteMap.end())
    {
      sf::Sprite sprite = it->second;
      sprite.setPosition(bigBarnButtonPosition);
      sf::Vector2u textureSize = sprite.getTexture()->getSize();
      sprite.setScale(
          static_cast<float>(tileSize) / textureSize.x / 2,
          static_cast<float>(tileSize) / textureSize.y / 2);
      window.draw(sprite);
    }
  }
}

void Game::initText()
{
  if (!font.loadFromFile("Art/lovedays.ttf"))
  {
    std::cerr << "Failed to load font" << std::endl;
    return;
  }
  // dayText.setFont(font);
  // dayText.setCharacterSize(24);
  // dayText.setFillColor(sf::Color::Yellow);
}

void Game::initUi(sf::RenderWindow &window)
{
  barnButtonPosition = sf::Vector2f(0, window.getSize().y - tileSize / 2);
  fertilizerButtonPosition = sf::Vector2f(tileSize / 2, window.getSize().y - tileSize / 2);
  bigBarnButtonPosition = sf::Vector2f(tileSize, window.getSize().y - tileSize / 2);
  originalBarnButtonPosition = barnButtonPosition;
  originalFertilizerButtonPosition = fertilizerButtonPosition;
  originalBigBarnButtonPosition = bigBarnButtonPosition;
}

void Game::handleMouse(sf::Event event)
{
  // Check if mouse down on play button:
  if (event.mouseButton.x < tileSize / 2 && event.mouseButton.y < tileSize / 2)
  {
    isPaused = !isPaused;
  }
}

void Game::displayRoad(sf::RenderWindow &window)
{
  for (int x = 0; x < width + 2; x++)
  {
    for (int y = 0; y < height + 2; y++)
    {
      if (x == 0 || y == 0 || x == width + 1 || y == height + 1)
      {
        auto it = spriteMap.find("Dry");
        if (x == 0 && y == 0)
        {
          it = spriteMap.find("TopLeft");
        }
        else if (x == 0 && y == height + 1)
        {
          it = spriteMap.find("BottomLeft");
        }
        else if (y == 0 && x == width + 1)
        {
          it = spriteMap.find("TopRight");
        }
        else if (y == height + 1 && x == width + 1)
        {
          it = spriteMap.find("BottomRight");
        }
        else if ((x == 0 || x == width + 1) && y > 0 && y < height + 1)
        {
          it = spriteMap.find("Vertical");
        }
        else if ((y == 0 || y == height + 1) && x > 0 && x < width + 1)
        {
          it = spriteMap.find("Horisontal");
        }

        if (it != spriteMap.end())
        {
          sf::Sprite sprite = it->second;
          sprite.setPosition((x + 1) * tileSize, (y + 1) * tileSize);
          sf::Vector2u textureSize = sprite.getTexture()->getSize();
          sprite.setScale(
              static_cast<float>(tileSize) / textureSize.x,
              static_cast<float>(tileSize) / textureSize.y);
          window.draw(sprite);
        }
      }
    }
  }
}

#endif
void Game::setUnit(int x, int y, FarmUnit *unit)
{
  if (x < 0 || y < 0 || x >= width || y >= height)
  {
    return;
  }

  if (farmMap[x][y] == nullptr)
  {
    farmMap[x][y] = unit;
  }
}

FarmUnit *Game::getUnit(int x, int y)
{
  return farmIterator->get(x, y);
}

Game::~Game()
{
  if (runThread.joinable())
  {
    runThread.join();
  }
  for (auto &row : farmMap)
  {
    for (auto &unit : row)
    {
      delete unit;
    }
  }
}