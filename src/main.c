#include "dfs.h"
#include <time.h>

#define SIZE 10

int main(void){
    // Seed random number gen
    srand((unsigned)time(NULL));

    // Initialization
    Maze* maze = initMaze(SIZE, 0, 0, SIZE - 1, SIZE - 1);
    Stack* stack = initStack(SIZE * SIZE);

    // Generate Maze
    generateMazeDFS(maze, stack);

    // Free everythinh
    for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++){
            free(maze->map[row][col]);
        }
        free(maze->map[row]);
    }
    free(maze);
    //free(stack);

    return 0;
}