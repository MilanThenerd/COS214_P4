#ifndef FARMTRAVERSAL_H
#define FARMTRAVERSAL_H

#include "FarmUnit.h"
#include "Coords.h"
#include <vector>
#include <unordered_set>
#include <queue>
#include <stack>

class FarmTraversal
{
public:
  FarmTraversal(std::vector<std::vector<FarmUnit *>> &farmMap, int startX, int startY);
  virtual ~FarmTraversal() = default;
  virtual void initialize() = 0;
  FarmUnit *firstFarm();
  FarmUnit *currentFarm();
  FarmUnit *next();
  FarmUnit *get(int x, int y);
  bool isDone() const;
  bool hasNext() const;
  int getIndex(FarmUnit *unit) const;
  int getLength() const;
  int getCurrentIndex() const;
  std::vector<Coords> getPath() const;

protected:
  bool contains(int x, int y) const;
  bool isWithinBounds(int x, int y) const;
  std::vector<std::vector<FarmUnit *>> &farmMap;
  int startX;
  int startY;
  std::unordered_set<Coords> visited;
  std::vector<Coords> path;
  std::size_t currentIndex;
};
#endif