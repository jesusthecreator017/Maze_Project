#ifndef DFS_H
#define DFS_H

#include "maze.h"

// Operations
void generateMazeDFS(Maze* maze, Stack* stack);
void removeWall(Cell* cellOne, Cell* cellTwo);

#endif