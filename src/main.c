#include <time.h>
#include "maze.h"

int main(void){
    // Seed random number generatos
    srand((unsigned)time(NULL));

    // Create the maze
    Maze* maze = initMaze(10, 1, 0, 8, 9);

    // Create a stack
    Stack* stack = initStack(10 * 10);
    
    // Generate Maze
    generateMaze(maze, stack);

    // Display the maze
    //displayMaze(maze);

    free(maze);
    return 0;
}