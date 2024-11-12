#include "maze.h"

// Initialization
Cell* initCell(int x, int y){
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    cell->x = x;
    cell->y = y;
    cell->distance = 0;
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

Queue* initQueue(unsigned capacity){
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = 0;
    queue->back = 0;
    queue->data = (Cell**)malloc(sizeof(Cell*) * capacity);
    return queue;
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
    usleep(10000);
}

void displayMazeDistances(Maze* maze){
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
            if(maze->map[i][j]->distance >= 0 && maze->map[i][j]->distance < 10){
                printf(" %d ", maze->map[i][j]->distance);
            } else if(maze->map[i][j]->distance >= 10 && maze->map[i][j]->distance < 100){
                printf(" %d", maze->map[i][j]->distance);
            } else if(maze->map[i][j]->distance >= 100 && maze->map[i][j]->distance < 1000){
                printf("%d", maze->map[i][j]->distance);
            } else {
                printf(" %c ", maze->map[i][j]->data);
            }
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
    usleep(10000);
}

// Checks
bool isValidMove(int x, int y, int size){
    return x >= 0 && x < size && y >= 0 && y < size;
}

bool isEmpty(Stack* stack){
    return stack->top == -1;
}

bool isFull(Stack* stack){
    return stack->top == stack->capacity - 1;
}

bool isQueueEmpty(Queue* queue){
    return queue->front == queue->back;
}

bool isQueueFull(Queue* queue){
    return (queue->back + 1) % queue->capacity == queue->front;
}

// Operations
void resetVisited(Maze* maze){
    for(int i = 0; i < maze->size; i++){
        for(int j = 0; j < maze->size; j++){
            maze->map[i][j]->visited = false;
        }
    }
}

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

void enqueue(Queue* queue, Cell* item){
    if(isQueueFull(queue)){
        printf("Queue is Full.\n");
        return;
    }
    queue->data[queue->back] = item;
    queue->back = (queue->back + 1) % queue->capacity;
}

void dequeue(Queue* queue){
    if(isQueueEmpty(queue)){
        printf("Queue is Empty\n");
        return;
    }
    queue->front = (queue->front + 1) % queue->capacity;
}

Cell* queuePeek(Queue* queue){
    if(isQueueEmpty(queue)){
        printf("Queue is Empty.\n");
        return NULL;
    }
    return queue->data[queue->front];
}