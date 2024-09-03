#ifndef GAME_H
#define GAME_H

#include "FarmUnit.h"
#include "CropField.h"
#include "Barn.h"

#include <thread>
#include <vector>
#include <memory>
#include <map>
#include <SFML/Graphics.hpp>

class Game
{
  private:
    int width;
    int height;
    const int tileSize = 64;
    std::vector<std::vector<FarmUnit*>> farmMap;
    std::map<std::string, std::shared_ptr<sf::Texture>> textureMap;
    std::map<std::string, sf::Sprite> spriteMap;
    std::thread runThread;
    void loadTextures();
    bool loadTextureAndCreateSprite(const std::string& key, const std::string& filename);
  public:
    Game(int width , int height);
    void run();
    void setUnit(int x, int y, FarmUnit* unit);
    FarmUnit* getUnit(int x, int y) const;
    void displayWindow();
    ~Game();
};
#endif