#ifndef FARMTRAVERSALBFS_H
#define FARMTRAVERSALBFS_H

#include "FarmTraversal.h"
#include <queue>

/**
 * @class FarmTraversalBFS
 * @brief Implements breadth-first search (BFS) traversal for a farm map.
 *
 * The FarmTraversalBFS class is a derived class of FarmTraversal and implements
 * breadth-first search (BFS) traversal for a farm map. It provides methods to initialize
 * the traversal and manage the BFS queue.
 */
class FarmTraversalBFS : public FarmTraversal
{
public:
  /**
   * @brief Constructs a FarmTraversalBFS object.
   *
   * @param farmMap Reference to the farm map.
   * @param startX The starting x-coordinate for the traversal.
   * @param startY The starting y-coordinate for the traversal.
   */
  FarmTraversalBFS(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);

private:
  std::queue<Coords> bfsQueue; ///< Queue for managing BFS traversal.

  /**
   * @brief Initializes the BFS traversal.
   */
  void initialize();
};

#endif // FARMTRAVERSALBFS_H