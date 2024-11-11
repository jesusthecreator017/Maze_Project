#include "maze.h"

// Initialization
Cell* initCell(int x, int y, char data){
    Cell* cell = (Cell*)malloc(sizeof(Cell));
    cell->x = x;
    cell->y = y;
    cell->visited = false;
    cell->data = data;
    return cell;
}

Maze* initMaze(int size, int sX, int sY, int eX, int eY){
    Maze* maze = (Maze*)malloc(sizeof(Maze));
    maze->size = size;
    maze->startX = sX;
    maze->startY = sY;
    maze->endX = eX;
    maze->endY = eY;

    // Allocate for 2D Array
    maze->array = (Cell***)malloc(sizeof(Cell**) * size);
    for(int i = 0; i < size; i++){
        maze->array[i] = (Cell**)malloc(sizeof(Cell*) * size);
        for(int j = 0; j < size; j++){
            if(i == sX && j == sY){
                maze->array[i][j] = initCell(i, j, 'S');
            } else if (i == eX && j == eY) {
                maze->array[i][j] = initCell(i, j, 'E');
            } else {
                maze->array[i][j] = initCell(i, j, '#');
            }
        }
    }

    return maze;
}

Stack* initStack(unsigned capacity){
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = -1;
    stack->capacity = capacity;
    stack->data = (Cell**)malloc(sizeof(Cell*) * capacity);
    return stack;
}

// Rendering
void displayMaze(Maze* maze){
    system("clear");
    for(int row = 0; row < maze->size; row++){
        for(int col = 0; col < maze->size; col++){
            printf("%c ", maze->array[row][col]->data);
        }
        puts("");
    }
    usleep(50000);
}

// Operations
void generateMaze(Maze* maze, Stack* stack){
    // Make the neighbors
    int neighbors[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Up, Right, Down, Left

    Cell* current = maze->array[maze->startX][maze->startY]; // Set the current cell as the start
    current->visited = true; // Mark cell as visited
    stackPush(stack, current); // Push it onto the stack

    while (!isEmpty(stack)){
        current = stackPop(stack);

        if(current->x == maze->endX && current->y + 1 == maze->endY){
            break;
        }

        Cell* unvisitedNeighbors[4]; 
        int unvistedNeighborCount = 0;

        // Check if their are unvisited neighbors
        for(int i = 0; i < 4; i++){
            int neighborX = current->x + neighbors[i][0];
            int neighborY = current->y + neighbors[i][1];
            if(isValidMove(neighborX, neighborY, maze->size)){
                Cell* neighbor = maze->array[neighborX][neighborY];
                if(!neighbor->visited){
                    unvisitedNeighbors[unvistedNeighborCount++] = neighbor;
                }
            }
        }

        // Choose a random unvisited neighbor
        if(unvistedNeighborCount > 0){
            // Choose a random Neighbor
            int randomIndex = rand() % unvistedNeighborCount;
            Cell* chosenNeighbor = unvisitedNeighbors[randomIndex];

            // Change the data and visited values
            chosenNeighbor->data = '.';
            chosenNeighbor->visited = true;

            // Print array
            displayMaze(maze);

            // Push both cells into the stack
            stackPush(stack, current);
            stackPush(stack, chosenNeighbor);
        }
    }
}

void stackPush(Stack* stack, Cell* value){
    if(isFull(stack)){
        printf("Stack is Full\n");
        return;
    }
    stack->data[++stack->top] = value;
}

Cell* stackPop(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty\n");
        return NULL;
    }
    return stack->data[stack->top--];
}

Cell* stackPeek(Stack* stack){
    if(isEmpty(stack)){
        printf("Stack is Empty\n");
        return NULL;
    }
    return stack->data[stack->top];
}


// Checks
bool isValidMove(int x, int y, int size){
    return (x > 0 && x < size - 1 && y > 0 && y < size - 1);
}

bool isEmpty(Stack* stack){
    return stack->top == -1 ? true : false;
}

bool isFull(Stack* stack){
    return stack->top == stack->capacity - 1 ? true : false;
}