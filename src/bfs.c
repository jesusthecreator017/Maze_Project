#include "bfs.h"

void calculateDistance(Maze* maze, Queue* queue){
    int neighborsOffsets[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // Up Right Down Left

    // Start at end of the maze
    Cell* endCell = maze->map[maze->endX][maze->endY];
    endCell->visited = true;
    endCell->distance = 0;
    enqueue(queue, endCell);

    while (!isQueueEmpty(queue)){
        // Get the current cell
        Cell* currentCell = queuePeek(queue);
        dequeue(queue);

        // Check all neighbors
        for(int i = 0; i < 4; i++){
            int neighborX = currentCell->x + neighborsOffsets[i][0];
            int neighborY = currentCell->y + neighborsOffsets[i][1];

            // Make sure its a valid move
            if(!isValidMove(neighborX, neighborY, maze->size)){
                continue;
            }

            Cell* neighborCell = maze->map[neighborX][neighborY];

            // If the cells are connected mark it as visited
            if(isConnectedNeighbor(currentCell, neighborCell) && !neighborCell->visited){
                // Update the data
                neighborCell->visited = true;
                neighborCell->distance = currentCell->distance + 1;

                // Print the maze
                displayMazeDistances(maze);

                // Put it into the queue
                enqueue(queue, neighborCell);
            }
        }
    }
}

bool isConnectedNeighbor(Cell* cellOne, Cell* cellTwo){
    if(cellTwo->x == cellOne->x - 1 && cellTwo->y == cellOne->y){ // Top Neighbors
        return !(cellOne->walls & TOP_WALL) && !(cellTwo->walls & BOTTOM_WALL);
    } else if(cellTwo->x == cellOne->x + 1 && cellTwo->y == cellOne->y){ // Bottom Neighbor
        return !(cellOne->walls & BOTTOM_WALL) && !(cellTwo->walls & TOP_WALL);
    } else if(cellTwo->x == cellOne->x && cellTwo->y == cellOne->y + 1){ // Right Neighbor
        return !(cellOne->walls & RIGHT_WALL) && !(cellTwo->walls & LEFT_WALL);
    } else if(cellTwo->x == cellOne->x && cellTwo->y == cellOne->y - 1){
        return !(cellOne->walls & LEFT_WALL) && !(cellTwo->walls & RIGHT_WALL);
    }
    return 0; // Not Adjacent
}

//void solveMazeBFS(Maze* maze, Queue* queue);