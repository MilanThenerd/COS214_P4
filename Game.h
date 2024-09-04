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
#include <SFML/Graphics.hpp>

class Game
{
  private:
    int width;
    int height;
    const int tileSize = 64;
    bool bfstraversal = true;
    std::vector<std::vector<FarmUnit*>> farmMap;
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::map<std::string, sf::Sprite> spriteMap;

    int currentIndex;
    std::vector<Coords> bfsPath;
    std::vector<Coords> dfsPath;

    std::thread runThread;
    
    void loadTextures();
    bool loadTextureAndCreateSprite(const std::string& key, const std::string& filename);

    void displayFarm(sf::RenderWindow& window);
    void displayRoad(sf::RenderWindow& window);
    //void displayTraversal(sf::RenderWindow& window);

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