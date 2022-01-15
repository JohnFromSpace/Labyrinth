/*******************************************************************************
 * Preprocessor Directives
 ******************************************************************************/
 
 /* System Includes */
#include <stdio.h>
#include <fstream>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <io.h> // For VC with Windows
//#include "unistd.h" //For linux
#include "limits.h"//Linux

/* Header Files */
#include "linked_list.h"
#include "maze.h"
#include "stack.h"


/*******************************************************************************
 * Macros and Constants
 ******************************************************************************/
#define EOK (0)
#define ANIMATION_DELAY_US (50000)

 //#define RENDER_GIF
 //#define ANIMATED_ON_SCREEN

static int outCount = 0;

/*******************************************************************************
 * Abstract Data Types
 ******************************************************************************/
typedef struct coords_t {
    int x;
    int y;
} coords_t;

typedef uint8_t direction_t;


/*******************************************************************************
 * Private Function Prototypes
 ******************************************************************************/
 /* Tells us if two cells are within the extremities of an array ie: [0, dimMax]
  * so a future operation does trigger a segfault due to addressing invalid
  * memory.
  */
bool inRange(int x, int y, int xMax, int yMax);

/* Tells us if two cells are in range of each other (ie: 4-connected
 * neighbours.
 */
bool isConnected4(int x1, int y1, int x2, int y2);

/* Takes a pair of coordinates, and if they are 4-neighbours, converts the
 * coordinates into a constants representing one of 4 cartesian unit vectors.
 */
direction_t direction(int x1, int y1, int x2, int y2);

/* Provides the inverse of the the direction() function.
 */
direction_t reverseDirection(int dir);

/* Tells us if it is possible to travel from one location to another, taking
 * into account whether there is a wall between the two coordinates.
 */
bool isAccessible(int x1, int y1, status_t status1, int x2, int y2, status_t status2);


/*******************************************************************************
 * Function Definitions
 ******************************************************************************/
 /*----------------------------------------------------------------------------*/
int main(void) {
    maze_t maze = { 0 };

    /* Initialize random seed */
    srand(time(NULL));

    setbuf(stdout, NULL);

    /* Determine size of map to generate */
    const int x = 16;
    const int y = 9;

    /* Generate random maze */
    if (mazeInit(&maze, x, y) != EOK) {
        printf("Failed to generate maze.\n");
        return (-EIO);
    }
    else {
        system("clear");
    }

    /* Solve the maze */
    mazeSolve(&maze);

    /* Print maze to screen */
    mazeRender(&maze);

    /* Clean up */
    mazeDestroy(&maze);

#ifdef RENDER_GIF
    system("convert *.png -set delay 10 output.gif");
#endif

    return EOK;
}

