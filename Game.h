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
#include <cmath>

#ifdef USE_GUI
#include <SFML/Graphics.hpp>
#endif

class Game
{
  private:
    int width;
    int height;
    int tileSize = 213;
    bool bfstraversal = true;
    std::vector<std::vector<FarmUnit*>> farmMap;
    int currentIndex;
    std::thread runThread;
    std::vector<Coords> bfsPath;
    std::vector<Coords> dfsPath;

    #ifdef USE_GUI
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::map<std::string, sf::Sprite> spriteMap;
    void loadTextures();
    bool loadTextureAndCreateSprite(const std::string& key, const std::string& filename);
    void displayFarm(sf::RenderWindow& window);
    void displayRoad(sf::RenderWindow& window);
    #endif
    void bfsTraversal(int startX , int startY);
    void dfsTraversal(int startX , int startY);
    bool isWithinBounds(int x , int y) const;
    
  public:
    Game(int width , int height);
    void run();
    void setUnit(int x, int y, FarmUnit* unit);
    FarmUnit* getUnit(int x, int y) const;
    FarmUnit* firstFarm();
    FarmUnit* next();
    bool isDone() const;
    FarmUnit* currentFarm() const;
    void displayWindow();
    ~Game();
};
#endif