#ifndef GAME_H
#define GAME_H

#include "FarmUnit.h"
#include "CropField.h"
#include "Barn.h"
#include "Coords.h"

#include <thread>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <memory>
#include <map>
#ifdef USE_GUI
#include <SFML/Graphics.hpp>
#endif

class Game
{
private:
  int width;
  int height;
  const int tileSize = 64;
  std::vector<std::vector<FarmUnit *>> farmMap;
  std::vector<Coords> bfsPath;
  std::thread runThread;

#ifdef USE_GUI
  void loadTextures();
  bool loadTextureAndCreateSprite(const std::string &key, const std::string &filename);
  std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
  std::map<std::string, sf::Sprite> spriteMap;
  void displayFarm(sf::RenderWindow &window);
  void displayRoad(sf::RenderWindow &window);
  void displayTraversal(sf::RenderWindow &window);
#endif

  int bfsTruckTraversal(int startX, int startY);
  int getBFSBestTraversal();
  void dfsTruckTraversal(int startX, int startY);
  bool isWithinBounds(int x, int y) const;
  bool isTraversable(int x, int y) const;

public:
  Game(int width, int height);
  void run();
  void setUnit(int x, int y, FarmUnit *unit);
  FarmUnit *getUnit(int x, int y) const;
  void displayWindow();
  ~Game();
};
#endif