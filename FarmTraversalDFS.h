#ifndef FARMTRAVERSALDFS_H
#define FARMTRAVERSALDFS_H

#include "FarmTraversal.h"
#include <stack>

/**
 * @class FarmTraversalDFS
 * @brief Implements depth-first search (DFS) traversal for a farm map.
 *
 * The FarmTraversalDFS class is a derived class of FarmTraversal and implements
 * depth-first search (DFS) traversal for a farm map. It provides methods to initialize
 * the traversal and manage the DFS stack.
 */
class FarmTraversalDFS : public FarmTraversal
{
public:
  /**
   * @brief Constructs a FarmTraversalDFS object.
   *
   * @param farmMap Reference to the farm map.
   * @param startX The starting x-coordinate for the traversal.
   * @param startY The starting y-coordinate for the traversal.
   */
  FarmTraversalDFS(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);

private:
  std::stack<Coords> dfsStack; ///< Stack for managing DFS traversal.

  /**
   * @brief Initializes the DFS traversal.
   */
  void initialize();
};

#endif // FARMTRAVERSALDFS_H