#ifndef BFS_H
#define BFS_H

#include "maze.h"

void solveMazeBFS(Maze* maze, Queue* queue);
void calculateDistance(Maze* maze, Queue* queue);
bool isConnectedNeighbor(Cell* cellOne, Cell* cellTwo);

#endif