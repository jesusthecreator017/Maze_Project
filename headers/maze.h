#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct cell {
    int x;
    int y;
    char data;
    bool visited;
} Cell;

typedef struct stack{
    int top;
    unsigned capacity;
    Cell** data; // Array of Cell Pointers
} Stack;

typedef struct maze {
    Cell*** array; // 2D array of cells
    int size; // Width and Height
    int startX; // Start position of the maze
    int startY;
    int endX;
    int endY; // End position of the maze;
} Maze;

// Initialization
Maze* initMaze(int size, int sX, int sY, int eX, int eY);
Stack* initStack(unsigned capacity);
Cell* initCell(int x, int y, char data);

// Rendering
void displayMaze(Maze* maze);

// Operations
void generateMaze(Maze* maze, Stack* stack);
void stackPush(Stack* stack, Cell* value);
Cell* stackPop(Stack* stack);
Cell* stackPeek(Stack* stack);

// Checks
bool isValidMove(int x, int y, int size);
bool isEmpty(Stack* stack);
bool isFull(Stack* stack);


#endif