#ifndef GAME_H
#define GAME_H

#include "FarmUnitDecorator.h"
#include "BarnDecorator.h"
#include "FarmTraversalBFS.h"
#include "FarmTraversalDFS.h"
#include "CropField.h"
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
    void drawSprite(sf::RenderWindow& window, const sf::Sprite& sprite, int x, int y);
    #endif
    void setUnit(int x, int y, FarmUnit* unit);
    FarmUnit* getUnit(int x , int y);
    void rain();
    
  public:
    Game(int width , int height);
    void run();
    void displayWindow();
    ~Game();
};
#endif