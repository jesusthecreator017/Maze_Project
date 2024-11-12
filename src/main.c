#include "dfs.h"
#include "bfs.h"
#include <time.h>

#define SIZE 15

int main(void){
    // Seed random number gen
    srand((unsigned)time(NULL));

    // Initialization
    Maze* maze = initMaze(SIZE, 0, 0, SIZE - 1, SIZE - 1);
    Stack* stack = initStack(SIZE * SIZE);
    Queue* queue = initQueue(SIZE * SIZE);

    // Generate Maze
    generateMazeDFS(maze, stack);

    // Reset visited states and Calculate the distances of each cell form the ending
    resetVisited(maze);
    calculateDistance(maze, queue);

    // Print the maze again with updated distances
    displayMazeDistances(maze);

    // Free Everything
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            free(maze->map[row][col]);
        }
        free(maze->map[row]);
    }
    free(maze);
    free(stack->data);
    free(stack);
    free(queue->data);
    free(queue);

    return 0;
}