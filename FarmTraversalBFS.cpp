#include "FarmTraversalBFS.h"

void FarmTraversalBFS::initialize()
{
  if (!isWithinBounds(startX, startY)) return;
    
  bfsQueue.push({startX, startY});
  visited.insert({startX, startY});
    
  while (!bfsQueue.empty()) 
  {
    Coords current = bfsQueue.front();
    bfsQueue.pop();
    path.push_back(current);

    std::vector<Coords> neighbors = {{current.x+1, current.y}, {current.x-1, current.y}, {current.x, current.y+1}, {current.x, current.y-1}};
    for (const Coords& neighbor : neighbors) 
    {
      int nx = neighbor.x;
      int ny = neighbor.y;
      if (isWithinBounds(nx, ny) && visited.find(neighbor) == visited.end()) 
      {
        bfsQueue.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
}