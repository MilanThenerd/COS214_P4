#ifndef FARMTRAVERSALBFS_H
#define FARMTRAVERSALBFS_H

#include "FarmTraversal.h"

class FarmTraversalBFS : public FarmTraversal
{
  public:
    FarmTraversalBFS(std::vector<std::vector<FarmUnit*>>& farmMap, int startX , int startY);
  private:
    std::queue<Coords> bfsQueue;
    void initialize();
};
#endif