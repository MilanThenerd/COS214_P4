#ifndef GAME_H
#define GAME_H

#include "FarmUnitDecorator.h"
#include "ExtraBarnDecorator.h"
#include "FertilizerDecorator.h"
#include "FarmTraversalBFS.h"
#include "FarmTraversalDFS.h"
#include "CropField.h"
#include "Coords.h"
#include <thread>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include "Barn.h"
#include <memory>
#include <map>
#include <cmath>
#define USE_GUI = 1
#ifdef USE_GUI
#include <SFML/Graphics.hpp>
#endif

enum TextAlign
{
  TopLeft,
  TopRight,
  BottomLeft,
  BottomRight,
  TopCenter
};

class Game
{
private:
  int width;
  int height;
  int tileSize = 64;
  int currentIndex = 0;
  int currentDay = 1;
  std::vector<std::vector<FarmUnit *>> farmMap;
  std::thread runThread;
  FarmTraversal *farmIterator;
  FarmTraversal *weatherIterator;
  bool isPaused = false;
  int gold = 0;

#ifdef USE_GUI
  std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
  std::map<std::string, sf::Sprite> spriteMap;
  bool isDraggingBarnButton = false;
  bool isDraggingFertilizerButton = false;
  bool isDraggingBigBarnButton = false;
  sf::Vector2f barnButtonPosition;
  sf::Vector2f fertilizerButtonPosition;
  sf::Vector2f bigBarnButtonPosition;
  sf::Vector2f originalBarnButtonPosition;
  sf::Vector2f originalFertilizerButtonPosition;
  sf::Vector2f originalBigBarnButtonPosition;
  sf::Vector2f dragOffset;
  sf::Font font;

  void loadTextures();
  bool loadTextureAndCreateSprite(const std::string &key, const std::string &filename);
  void displayFarm(sf::RenderWindow &window);
  void displayRoad(sf::RenderWindow &window);
  void drawSprite(sf::RenderWindow &window, const sf::Sprite &sprite, int x, int y);
  void displayText(sf::RenderWindow &window, std::string text, int fontsize, sf::Color col, int x, int y, TextAlign align);
  void displayUI(sf::RenderWindow &window);
  void initText();
  void initUi(sf::RenderWindow &window);
  void handleMouse(sf::Event event);
  void handleEvents(sf::RenderWindow &window);
  bool isOverFarmUnit(const sf::Vector2f &position);
  sf::Vector2i getFarmUnitCoords(const sf::Vector2f &position);

#endif
  void setUnit(int x, int y, FarmUnit *unit);
  FarmUnit *getUnit(int x, int y);
  void rain();

public:
  Game(int width, int height);
  void run();
  void displayWindow();
  ~Game();
};

#endif