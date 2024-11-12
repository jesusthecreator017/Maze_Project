#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define TOP_WALL 0x01    // 0001
#define RIGHT_WALL 0x02  // 0010
#define BOTTOM_WALL 0x04 // 0100
#define LEFT_WALL 0x08   // 1000

typedef struct cell{
  int x;
  int y;
  int distance;
  bool visited;
  unsigned char data;
  unsigned char walls;
} Cell;

typedef struct stack{
    int top;
    unsigned capacity;
    Cell** data; // Array of Cell Pointers
} Stack;

typedef struct queue{
    Cell** data; // Array of Cell Pointers
    unsigned capacity;
    int back;
    int front; 
} Queue;

typedef struct maze{
    Cell*** map;
    unsigned size;
    int startX;
    int startY;
    int endX;
    int endY;
} Maze;

// Initialization
Cell* initCell(int x, int y);
Stack* initStack(unsigned capacity);
Queue* initQueue(unsigned capacity);
Maze* initMaze(unsigned size, int sX, int sY, int eX, int eY);

// Rendering
void displayMaze(Maze* maze);
void displayMazeDistances(Maze* maze);

// Checks
bool isValidMove(int x, int y, int size);
bool isEmpty(Stack* stack);
bool isFull(Stack* stack);
bool isQueueEmpty(Queue* queue);
bool isQueueFull(Queue* queue);

// Operations 
void resetVisited(Maze* maze);

void stackPush(Stack* stack, Cell* item);
Cell* stackPop(Stack* stack);
Cell* stackPeek(Stack* stack);

void enqueue(Queue* queue, Cell* item);
void dequeue(Queue* queue);
Cell* queuePeek(Queue* queue);

#endif