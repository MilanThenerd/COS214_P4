#ifndef GAME_H
#define GAME_H

#include "FarmUnitDecorator.h"
#include "ExtraBarnDecorator.h"
#include "FarmTraversalBFS.h"
#include "FarmTraversalDFS.h"
#include "CropField.h"
#include "Coords.h"
#include "Publisher.h"
#include "TruckFactory.h"

#include <thread>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <memory>
#include <map>
#include <cmath>
#include <atomic>

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
    bool selectingHUD = false;
    bool drawBus = false;

    std::vector<std::vector<FarmUnit*>> farmMap;
    std::atomic<bool> gameRunning;
    std::thread runThread;
    FarmTraversal* farmIterator;
    Publisher* publisher;

    #ifdef USE_GUI
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::map<std::string, sf::Sprite> spriteMap;
    void loadTextures();
    bool loadTextureAndCreateSprite(const std::string& key, const std::string& filename);
    void displayFarm(sf::RenderWindow& window);
    void displayRoad(sf::RenderWindow& window);
    void displayHUD(sf::RenderWindow& window);
    void displayTrucks(sf::RenderWindow& window);
    void drawSprite(sf::RenderWindow& window, const sf::Sprite& sprite, int x, int y);
    #endif
    void setUnit(int x, int y, FarmUnit* unit);
    FarmUnit* getUnit(int x , int y);
    void rain();
    void setIterator(bool type);
    std::string getDirectionSpriteKey(Coords currentPos , Coords nextPos);
  public:
    Game(int width , int height);
    void run();
    void displayWindow();
    ~Game();
};
#endif