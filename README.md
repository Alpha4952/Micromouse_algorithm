# Micromouse Algorithm

Algorithm used for micromouse.

# Structure
map_track_alg.h is the header file for map_track_alg.c

### Constants
| Name      | Type          | Value                                                                | Description                                                                                                                                           |
|-----------|---------------|----------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------|
| MAZE_SIZE | int           | 16                                                                   | Size of the maze (default: 16)                                                                                                                        |
| DELTA_X   | int[]         | {0, 1, 0, -1}                                                        | The directional difference when moving in a direction (0 to 3: NESW)<br/>This is used to quickly calculate the new position of the mouse while moving |
| DELTA_Y   | int[]         | {-1, 0, 1, 0}                                                        | Similar to **DELTA_X**                                                                                                                                |
| REAL_MAZE | cell_type[][] | Each position store a cell_type value, see **cell_type** for details | Only used for testing, each cell has to be manually set with wall directions (not used for real maze solving)                                         |

### Data types
| Name       | Data                                                                            | Description                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         |
|------------|---------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| mouse_type | float direction;<br/>int x, y;                                                  | Used to store the micromouse's data. The direction is determined clockwise, with 0 being looking straight up (to the North)<br/>x and y is the position of the mouse in the maze<br/>The initial direction is 2.0 (looking down or South), position is 0, 0 (see **initMouseMaze**)<br/>This means the expected position and rotation of the mouse in the maze is top left and looking down                                                                                                                                                                                                                                         |
| point_type | int x, y;                                                                       | Used to store a cell's position (see **cell_type**)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 |
| cell_type  | uint8_t wall;<br/>bool known;<br/>uint16_t dist;<br/>point_type previous_point; | Used to store a whole maze cell's data, each unit of cell_type represents a maze's cell<br/>wall is a int value to store walls of the maze. It uses bit shifts to determine the walls. With the last 4 bits being N, E, S and W respectively.<br/>For example:<br/>- cell >> 0 & 1 is the W wall (wall on the left)<br/>- cell >> 3 & 1 is the N wall (wall on the top)<br/>known marks if that cell is discovered or not. "Discovered" means the cell has been gone through by the mouse, the walls are scanned and stored<br/>dist and previous_point are used for the BFS function (see **findPath** and **findNearestUnknown**) |

### Functions
Main functions used for the algorithm.

| Return type | Name           | Parameters                                        | Usage                                                                                                | Logic                                                                                                                                                                                                                                                                                                                                                            |
|-------------|----------------|---------------------------------------------------|------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| void        | initMouseMaze  | mouse_type *mouse<br/>cell_type maze[][MAZE_SIZE] | Calling it will set mouse and maze to be ready for other functions (position, direction, walls, etc) | Literally nothing                                                                                                                                                                                                                                                                                                                                                |
| void        | explore        | cell_type maze[][MAZE_SIZE]<br/>mouse_type *mouse | Calling it will make the mouse explore the maze                                                      | 1.Check if there is an reachable unexplored cell (using **findNearestUnknown**). Exit if there isn't one, otherwise mark the current position for BFS.<br/>2. Check the adjacent cells if it's unexplored and unblocked. If so, move to that cell.<br/>3. If no move was made, the mouse will move to the nearest unexplored and unblocked cell (see **step 1**) |
| void        | returnToStart  | cell_type maze[][MAZE_SIZE]<br/>mouse_type *mouse | Calling it will make the mouse go to the beginning                                                   | Literally uses **goTo**                                                                                                                                                                                                                                                                                                                                          |
| void        | calculateRoute | cell_type maze[][MAZE_SIZE]<br/>mouse_type *mouse | Unimplemented (needs further discussion with the team about the mouse's movement, direction, etc)    |                                                                                                                                                                                                                                                                                                                                                                  |

Other functions

| Return type | Name               | Parameters                                                              | Usage                                                                                                                                      | Logic                                                                                                                        |
|-------------|--------------------|-------------------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------------------------------------------------|
| void        | fetchMouseData     | mouse_type mouse                                                        | Print the mouse's data including position and rotation (might be helpful)                                                                  | What logic?                                                                                                                  |
| int         | readSensor         | mouse_type *mouse                                                       | Used to convert sensor data into memory data used in cell_type.wall (unimplemented)                                                        | Not yet                                                                                                                      |
| void        | forward            | mouse_type *mouse                                                       | Make the mouse move 1 cell a head (already used in functions, just need real motor control)                                                | Not yet                                                                                                                      |
| void        | turnRight          | mouse_type *mouse<br/>float direction                                   | Used to make the mouse turn right a certain direction (already used in functions, just need real motor control)                            | Not yet                                                                                                                      |
| void        | turnLeft           | mouse_type *mouse<br/>float direction                                   | Used to make the mouse turn left a certain direction (already used in functions, just need real motor control)                             | Not yet                                                                                                                      |
| void        | rotateTo           | mouse_type *mouse<br/>float goal_direction                              | Used to make the mouse turn to a certain direction (uses turnRight and turnLeft)                                                           | Maybe?                                                                                                                       |
| bool        | isValid            | int x<br/>int y                                                         | Used to check if a cell position is in the maze (valid)                                                                                    | Nuh uh                                                                                                                       |
| void        | setWall            | cell_type maze[][MAZE_SIZE]<br/>mouse_type *mouse                       | Used to save the walls into memory. Note that this doesn't save the walls according to direction so it has to be rotated in **readSensor** | Uh...                                                                                                                        |
| int         | findPath           | cell_type maze[][MAZE_SIZE]<br/>int sx<br/>int sy<br/>int gx<br/>int gy | Used to find the path between 2 points (sx, sy) and (gx, gy). Returns the length of the path or -1 if there isn't any paths to the goal    | Uses BFS, saves the previous points of each cell and the distance to that cell to memory for easy traversing using **goTo**. |
| void        | goTo               | cell_type maze[][MAZE_SIZE]<br/>mouse_type *mouse<br/>int gx<br/>int gy | Uses **findPath** to find the shortest path between the mouse and the goal, then move there if possible                                    | **findPath**                                                                                                                 |
| point_type  | findNearestUnknown | cell_type maze[][MAZE_SIZE]<br/>int x<br/>int y                         | Used to find the closest unknown and unblocked cell. Returns the position of that cell in point_type if found, otherwise (-1, -1)          | Uses BFS                                                                                                                     |
| void        | renderMaze         | cell_type maze[][MAZE_SIZE]                                             | Used to write the whole maze structure in the terminal, useful for debugging                                                               | Nothing                                                                                                                      |

Note that turnRight and turnLeft use the direction of the mouse, not degree directions.

# Usage

Example program to simulate the mouse exploring the maze then come back to the start.

```c++
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
```

# Important note

This is just the general algorithm; it still needs some method of moving the mouse using motors (e.g. turnRight, turnLeft, forward).
