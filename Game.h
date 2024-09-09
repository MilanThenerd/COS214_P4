#ifndef GAME_H
#define GAME_H

#include "FarmUnitDecorator.h"
#include "ExtraBarnDecorator.h"
#include "FertilizerDecorator.h"
#include "FarmTraversalBFS.h"
#include "FarmTraversalDFS.h"
#include "CropField.h"
#include "Coords.h"
#include "Publisher.h"
#include "Barn.h"
#include "TruckFactory.h"

#include <thread>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <memory>
#include <map>
#include <cmath>
#define USE_GUI = 1
#ifdef USE_GUI
#include <SFML/Graphics.hpp>
#endif

/**
 * @enum TextAlign
 * @brief Enumeration for text alignment options.
 */
enum TextAlign
{
  TopLeft,     ///< Align text to the top-left corner.
  TopRight,    ///< Align text to the top-right corner.
  BottomLeft,  ///< Align text to the bottom-left corner.
  BottomRight, ///< Align text to the bottom-right corner.
  TopCenter    ///< Align text to the top-center.
};

/**
 * @class Game
 * @brief Represents the main game logic and state.
 *
 * The Game class manages the farm simulation, including the farm map, trucks, and user interface.
 * It provides methods to run the game, display the window, handle events, and manage the farm units.
 */
class Game
{
private:
  int width;                                    ///< The width of the game window.
  int height;                                   ///< The height of the game window.
  int tileSize = 64;                            ///< The size of each tile in the farm map.
  int currentIndex = 0;                         ///< The current index for traversal.
  int currentDay = 1;                           ///< The current day in the simulation.
  std::vector<std::vector<FarmUnit *>> farmMap; ///< The farm map consisting of farm units.
  std::thread runThread;                        ///< The thread for running the game loop.
  FarmTraversal *farmIterator;                  ///< Iterator for traversing the farm.
  FarmTraversal *weatherIterator;               ///< Iterator for traversing the weather.
  Publisher *publisher;                         ///< Publisher for managing trucks and orders.
  TruckFactory *factory;                        ///< Factory for creating trucks.
  bool isPaused = false;                        ///< Flag indicating if the game is paused.
  int gold = 0;                                 ///< The amount of gold in the game.

#ifdef USE_GUI
  std::map<std::string, std::shared_ptr<sf::Texture>> textureMap; ///< Map of textures for the GUI.
  std::map<std::string, sf::Sprite> spriteMap;                    ///< Map of sprites for the GUI.
  bool isDraggingBarnButton = false;                              ///< Flag indicating if the barn button is being dragged.
  bool isDraggingFertilizerButton = false;                        ///< Flag indicating if the fertilizer button is being dragged.
  bool isDraggingBigBarnButton = false;                           ///< Flag indicating if the big barn button is being dragged.
  sf::Vector2f barnButtonPosition;                                ///< Position of the barn button.
  sf::Vector2f fertilizerButtonPosition;                          ///< Position of the fertilizer button.
  sf::Vector2f bigBarnButtonPosition;                             ///< Position of the big barn button.
  sf::Vector2f originalBarnButtonPosition;                        ///< Original position of the barn button.
  sf::Vector2f originalFertilizerButtonPosition;                  ///< Original position of the fertilizer button.
  sf::Vector2f originalBigBarnButtonPosition;                     ///< Original position of the big barn button.
  sf::Vector2f dragOffset;                                        ///< Offset for dragging buttons.
  sf::Font font;                                                  ///< Font for displaying text in the GUI.

  /**
   * @brief Loads textures for the GUI.
   */
  void loadTextures();

  /**
   * @brief Loads a texture and creates a sprite.
   *
   * @param key The key for the texture.
   * @param filename The filename of the texture.
   * @return True if the texture was loaded successfully, false otherwise.
   */
  bool loadTextureAndCreateSprite(const std::string &key, const std::string &filename);

  /**
   * @brief Displays the farm in the GUI.
   *
   * @param window Reference to the render window.
   */
  void displayFarm(sf::RenderWindow &window);

  /**
   * @brief Displays the road in the GUI.
   *
   * @param window Reference to the render window.
   */
  void displayRoad(sf::RenderWindow &window);

  /**
   * @brief Draws a sprite in the GUI.
   *
   * @param window Reference to the render window.
   * @param sprite The sprite to draw.
   * @param x The x-coordinate to draw the sprite.
   * @param y The y-coordinate to draw the sprite.
   */
  void drawSprite(sf::RenderWindow &window, const sf::Sprite &sprite, int x, int y);

  /**
   * @brief Displays text in the GUI.
   *
   * @param window Reference to the render window.
   * @param text The text to display.
   * @param fontsize The font size of the text.
   * @param col The color of the text.
   * @param x The x-coordinate to display the text.
   * @param y The y-coordinate to display the text.
   * @param align The alignment of the text.
   */
  void displayText(sf::RenderWindow &window, std::string text, int fontsize, sf::Color col, int x, int y, TextAlign align);

  /**
   * @brief Displays the user interface in the GUI.
   *
   * @param window Reference to the render window.
   */
  void displayUI(sf::RenderWindow &window);

  /**
   * @brief Displays the trucks in the GUI.
   *
   * @param window Reference to the render window.
   */
  void displayTrucks(sf::RenderWindow &window);

  /**
   * @brief Initializes the text settings for the GUI.
   */
  void initText();

  /**
   * @brief Initializes the user interface for the GUI.
   *
   * @param window Reference to the render window.
   */
  void initUi(sf::RenderWindow &window);

  /**
   * @brief Handles mouse events in the GUI.
   *
   * @param event The mouse event to handle.
   */
  void handleMouse(sf::Event event);

  /**
   * @brief Handles events in the GUI.
   *
   * @param window Reference to the render window.
   */
  void handleEvents(sf::RenderWindow &window);

  /**
   * @brief Checks if a position is over a farm unit.
   *
   * @param position The position to check.
   * @return True if the position is over a farm unit, false otherwise.
   */
  bool isOverFarmUnit(const sf::Vector2f &position);

  /**
   * @brief Gets the coordinates of a farm unit from a position.
   *
   * @param position The position to get the coordinates from.
   * @return The coordinates of the farm unit.
   */
  sf::Vector2i getFarmUnitCoords(const sf::Vector2f &position);

#endif
  /**
   * @brief Sets a farm unit at the specified coordinates.
   *
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @param unit Pointer to the farm unit to set.
   */
  void setUnit(int x, int y, FarmUnit *unit);

  /**
   * @brief Gets the farm unit at the specified coordinates.
   *
   * @param x The x-coordinate.
   * @param y The y-coordinate.
   * @return Pointer to the farm unit at the specified coordinates.
   */
  FarmUnit *getUnit(int x, int y);

  /**
   * @brief Simulates rain in the farm.
   */
  void rain();

  /**
   * @brief Handles the publisher for managing trucks and orders.
   */
  void handlePublisher();

  /**
   * @brief Moves the trucks in the farm.
   */
  void moveTrucks();

public:
  /**
   * @brief Constructs a Game object.
   *
   * @param width The width of the game window.
   * @param height The height of the game window.
   */
  Game(int width, int height);

  /**
   * @brief Runs the game loop.
   */
  void run();

  /**
   * @brief Displays the game window.
   */
  void displayWindow();

  /**
   * @brief Destroys the Game object.
   */
  ~Game();
};

#endif