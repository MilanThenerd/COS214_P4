#ifndef GAME_H
#define GAME_H

#include "FarmUnit.h"
#include "FarmTraversal.h"
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
#include <cmath>

#ifdef USE_GUI
#include <SFML/Graphics.hpp>
#endif

class Game
{
  private:
    int width;
    int height;
    int tileSize = 64;
    bool bfstraversal = true;
    int currentIndex;
    std::vector<std::vector<FarmUnit*>> farmMap;
    std::thread runThread;
    FarmTraversal* farmIterator;

    #ifdef USE_GUI
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::map<std::string, sf::Sprite> spriteMap;
    void loadTextures();
    bool loadTextureAndCreateSprite(const std::string& key, const std::string& filename);
    void displayFarm(sf::RenderWindow& window);
    void displayRoad(sf::RenderWindow& window);
    #endif
    bool isWithinBounds(int x , int y) const;
    void setUnit(int x, int y, FarmUnit* unit);
    FarmUnit* getUnit(int x , int y);
    
  public:
    Game(int width , int height);
    void setIteratorType(bool);
    void run();
    void displayWindow();
    ~Game();
};
#endif