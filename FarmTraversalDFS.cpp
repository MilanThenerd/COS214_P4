#include "FarmTraversalDFS.h"

void FarmTraversalDFS::initialize()
{
  if (!isWithinBounds(startX, startY)) 
  {
    return;
  }
  dfsStack.push({startX, startY});
  visited.insert({startX, startY});

  while (!dfsStack.empty()) 
  {
    Coords current = dfsStack.top();
    dfsStack.pop();
    path.push_back(current);

    std::vector<Coords> neighbors = {{current.x+1, current.y}, {current.x-1, current.y}, {current.x, current.y+1}, {current.x, current.y-1}};
    for (const Coords& neighbor : neighbors) 
    {
      int nx = neighbor.x;
      int ny = neighbor.y;
      if (isWithinBounds(nx, ny) && visited.find(neighbor) == visited.end()) 
      {
        dfsStack.push(neighbor);
        visited.insert(neighbor);
      }
    }
  }
}