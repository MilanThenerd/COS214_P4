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
    FarmTraversal(std::vector<std::vector<FarmUnit*>>& farmMap, int startX , int startY, bool type);
    void initialize();

    void insert(int x , int y , FarmUnit*);
    FarmUnit* firstFarm();
    FarmUnit* currentFarm();
    FarmUnit* next();
    FarmUnit* get(int x , int y);
    bool isDone() const;
    bool hasNext() const;
    int getIndex(FarmUnit* unit) const;
    int length = 0;
    std::vector<Coords> path;
    size_t currentIndex;

  private:
    bool contains(int x , int y) const;
    bool isWithinBounds(int x, int y) const;
    void bfsTraversal();
    void dfsTraversal();
    
    std::vector<std::vector<FarmUnit*>>& farmMap;
    bool type;
    int startX;
    int startY;

    std::unordered_set<Coords> visited;
    std::queue<Coords> bfsQueue;
    std::stack<Coords> dfsStack;

};
#endif