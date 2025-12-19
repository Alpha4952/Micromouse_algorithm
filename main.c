#include "map_track_alg.h"

int main(void)
{
    // Variables declaration
    mouse_type mouse;
    cell_type maze[MAZE_SIZE][MAZE_SIZE];

    initMouseMaze(&mouse, maze);

    // Single call: explore() now contains the full exploration loop
    explore(maze, &mouse);

    // Make the mouse go back to the start
    returnToStart(maze, &mouse);

    return 0;
}