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

int mazeInit(maze_t* m, size_t width, size_t height) {
    if (!m || width <= 0 || height <= 0) {
        return (-EINVAL);
    }
    int i, j, k, a, b, ret = EOK;
    llist_t list = { 0 };   /* For storing "neighbours" during generation */
    bool bErr = false;
    int iVisited = 0;
    coords_t cur;

    /* Initialize and dynamically allocate memory as needed */
    if (stackInit(&m->stack) != EOK) {
        bErr = true;
    }
    /* Store dimensions */
    m->xMax = width;
    m->yMax = height;
    m->totalCells = m->xMax * m->yMax;
    if (!bErr) {
        if ((m->maze = (cell_t**)calloc(m->xMax, sizeof(cell_t*))) == NULL) {
            bErr = true;
        }
        for (i = 0; i < m->xMax; i++) {
            if ((m->maze[i] = (cell_t*)calloc(m->yMax, sizeof(cell_t))) == NULL) {
                bErr = true;
                break;
            }
        }
    }

    /* Populate cells with coordinates, walls */
    for (i = 0; i < m->xMax; i++) {
        for (j = 0; j < m->yMax; j++) {
            m->maze[i][j].x = j;
            m->maze[i][j].y = i;
            m->maze[i][j].bVisited = false;
            /* Build all walls */
            m->maze[i][j].status.wall = NORTH | SOUTH | EAST | WEST;
        }
    }
    /* Populate borders */
    for (i = 0; i < m->xMax; i++) {
        a = i;
        b = 0;
        m->maze[a][b].status.border |= NORTH;
    }
    for (i = 0; i < m->xMax; i++) {
        a = i;
        b = m->yMax - 1;
        m->maze[a][b].status.border |= SOUTH;
    }
    for (i = 0; i < m->yMax; i++) {
        a = 0;
        b = i;
        m->maze[a][b].status.border |= WEST;
    }
    for (i = 0; i < m->yMax; i++) {
        a = m->xMax - 1;
        b = i;
        m->maze[a][b].status.border |= EAST;
    }

    /* Start depth-first-search generation of maze */
    cur.x = 0;
    cur.y = 0;
    iVisited = 1;

    /* Evaluate all cells in maze to make this a "perfect" maze with a unique
     * path between any two arbitrary points in the maze.
     */
    while (iVisited < m->totalCells) {
        (void)llistInit(&list);
        for (i = -1; i <= 1; i++) {
            for (j = -1; j <= 1; j++) {
                /* Scan all valid neighboring cells */
                if ((i == 0) && (j == 0)) {
                    continue;
                }
                /* Make sure we don't try to address out-of-bounds memory via
                 * sloppy indexing.
                 */
                if (inRange(cur.x + i, cur.y + j, m->xMax, m->yMax)) {
                    /* Are the two cells 4-neighbours */
                    if (isConnected4(cur.x, cur.y, cur.x + i, cur.y + j)) {
                        /* Are all 4 walls for the cell intact */
                        if (m->maze[cur.x + i][cur.y + j].status.wall == (NORTH | SOUTH | WEST | EAST)) {
                            /* All walls are intact; Add cell coordinates to list */
                            lnode_t tmp;
                            coords_t coords;
                            coords.x = cur.x + i;
                            coords.y = cur.y + j;
                            tmp.width = sizeof(coords_t);
                            tmp.data = &coords;
                            if (EOK != llistInsert(&list, &tmp)) {
                                printf("INSERT ERROR\n");
                            }
                        }
                    }
                }
            }
        }
        /* Show maze being generated */
#ifdef ANIMATED_ON_SCREEN
        mazeRender(m);
#endif


