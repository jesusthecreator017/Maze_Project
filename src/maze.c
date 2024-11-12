#include "maze.h"

// Initialization
Cell* initCell(int x, int y){
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    cell->x = x;
    cell->y = y;
    cell->data = '#'; // ƒ
    cell->visited = false;
    cell->walls = TOP_WALL | RIGHT_WALL | BOTTOM_WALL | LEFT_WALL;
    return cell;
}

Stack* initStack(unsigned capacity){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->data = (Cell**)malloc(sizeof(Cell*) * capacity);
    return stack;
}

Maze* initMaze(unsigned size, int sX, int sY, int eX, int eY){
    Maze* maze = (Maze*)malloc(sizeof(Maze));
    maze->size = size;
    maze->startX = sX;
    maze->startY = sY;
    maze->endX = eX;
    maze->endY = eY;

    maze->map = (Cell***)malloc(sizeof(Cell**) * size);
    for(int i = 0; i < size; i++){
        maze->map[i] = (Cell**)malloc(sizeof(Cell*) * size);
        for(int j = 0; j < size; j++){
            maze->map[i][j] = initCell(i, j);
        }
    }
    return maze;
}

// Rendering
void displayMaze(Maze* maze){
    system("clear");
    // Main loop
    for(int i = 0; i < maze->size; i++){
        // Draw Top Walls
        for(int j = 0; j < maze->size; j++){
            printf("+");
            if(maze->map[i][j]->walls & TOP_WALL){
                printf("---");
            } else {
                printf("   ");
            }
        }
        printf("+\n");

        // Print vertical walls
        for(int j = 0; j < maze->size; j++){
            if(maze->map[i][j]->walls & LEFT_WALL){
                printf("|");
            } else {
                printf(" ");
            }
            printf(" %c ", maze->map[i][j]->data);
        }
        if(maze->map[i][maze->size - 1]->walls & RIGHT_WALL){
            printf("|\n");
        } else {
            printf(" \n");
        }
    }

    for(int i = 0; i < maze->size; i++){
        printf("+");
        if(maze->map[maze->size - 1][i]->walls & BOTTOM_WALL){
            printf("---");
        } else {
            printf("   ");
        }
    }
    printf("+\n");
    usleep(50000);
}

// Checks
bool isValidMove(int x, int y, int size){
    return x >= 0 && x < size && y >= 0 && y < size;
}

bool isEmpty(Stack* stack){
    return stack->top == -1 ? true : false;
}

bool isFull(Stack* stack){
    return stack->top == stack->capacity - 1 ? true : false;
}

// Operations
void stackPush(Stack* stack, Cell* item){
    if(isFull(stack)){
        printf("Stack is Full (PUSH).\n");
        return;
    }
    stack->data[++stack->top] = item;
}

Cell* stackPop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty (POP).\n");
        return NULL;
    }
    return stack->data[stack->top--];
}

Cell* stackPeek(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty (PEEK).\n");
        return NULL;
    }
    return stack->data[stack->top];
}