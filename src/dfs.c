#include "dfs.h"

// Operations
void generateMazeDFS(Maze* maze, Stack* stack){
    // Neighbors offsets
    int neighborsOffsets[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Up Right Left Down

    // Get current cell
    Cell* current = maze->map[maze->startX][maze->startY]; // Starting Cell
    current->data = 'S'; // Mark as path
    current->visited = true;

    // Push onto the stack
    stackPush(stack, current);
    
    // Loop while the stack is NOT empty
    while (!isEmpty(stack)){
        // Pop off the stack
        current = stackPop(stack);  
        
        // Make a list of neighbors
        Cell* unvisitedNeighborsList[4];
        int unvisitedNeighborCount = 0;

        // Check for any unvisited neighbors
        for(int i = 0; i < 4; i++){
            int neighborX = current->x + neighborsOffsets[i][0];
            int neighborY = current->y + neighborsOffsets[i][1];
            if(isValidMove(neighborX, neighborY, maze->size)){
                Cell* neighbor = maze->map[neighborX][neighborY];
                if(!neighbor->visited){
                    unvisitedNeighborsList[unvisitedNeighborCount++] = neighbor;
                }
            }
        }

        // Choose a random unvisited neighbor
        if(unvisitedNeighborCount > 0){
            // Choose a random integer
            int randomIndex = rand() % unvisitedNeighborCount;
            Cell* chosenNeighbor = unvisitedNeighborsList[randomIndex];

            // Change the data to visited and remove corresponding wall
            removeWall(current, chosenNeighbor);
            if(chosenNeighbor->x == maze->endX && chosenNeighbor->y == maze->endY){
                chosenNeighbor->data = 'E';
            } else {
                chosenNeighbor->data = ' ';
            }

            chosenNeighbor->visited = true;

            // Print the maze
            displayMaze(maze);

            // Push to stack
            stackPush(stack, current);
            stackPush(stack, chosenNeighbor);
        }
    }
    
}

void removeWall(Cell* cellOne, Cell* cellTwo){
    // Top Wall
    if(cellTwo->x == cellOne->x - 1 && cellTwo->y == cellOne->y){
        cellOne->walls &= ~TOP_WALL;
        cellTwo->walls &= ~BOTTOM_WALL;
    } else if (cellTwo->x == cellOne->x + 1 && cellTwo->y == cellOne->y){ // Bottom Wall
        cellOne->walls &= ~BOTTOM_WALL;
        cellTwo->walls &= ~TOP_WALL;
    } else if (cellTwo->x == cellOne->x && cellTwo->y == cellOne->y + 1){ // Right Wall
        cellOne->walls &= ~RIGHT_WALL;
        cellTwo->walls &= ~LEFT_WALL;
    } else if (cellTwo->x == cellOne->x && cellTwo->y == cellOne->y - 1){
        cellOne->walls &= ~LEFT_WALL;
        cellTwo->walls &= ~RIGHT_WALL;
    }
}