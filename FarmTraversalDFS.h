#ifndef FARMTRAVERSALDFS_H
#define FARMTRAVERSALDFS_H

#include "FarmTraversal.h"

class FarmTraversalDFS : public FarmTraversal
{
  public:
    FarmTraversalDFS(std::vector<std::vector<FarmUnit*>>& farmMap, int startX , int startY) : FarmTraversal(farmMap,startX,startY) { initialize();};
  private:
    std::stack<Coords> dfsStack;
    void initialize();
};
#endif