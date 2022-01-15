#ifndef MAZE_H // Prevent multiple inclusions
#define MAZE_H

/*******************************************************************************
 * Preprocessor Directives
 ******************************************************************************/
#include <stdint.h>
#include "stack.h"

 /*******************************************************************************
  * Macros and Constants
  ******************************************************************************/
  /* Directional bit identities */
#define WEST   (0x1<<3)
#define SOUTH  (0x1<<2)
#define EAST   (0x1<<1)
#define NORTH  (0x1<<0)

#define BITMAP_SIZE  (3)

/*******************************************************************************
 * Abstract Data Types
 ******************************************************************************/
typedef struct status_t {
	uint16_t backtrack : 4;
	uint16_t solution : 4;
	uint16_t border : 4;
	uint16_t wall : 4;
} status_t;


typedef struct cell_t {
	status_t status;
	int      x;
	int      y;
	int      bVisited;
	char     bitmap[BITMAP_SIZE][BITMAP_SIZE];
} cell_t;

typedef struct maze_t {
	cell_t** maze;
	stack_t  stack;
	int      xMax;
	int      yMax;
	int      totalCells;
} maze_t;


/*******************************************************************************
 * Public Function Prototypes
 *******************************************************************************/
 /* Handle compiling C code as part of a C++ project */
#ifdef __cplusplus
extern "C" {
#endif

	/* @functionName: stackInit
	 * @brief:        Initializes an empty stack.
	 * @param:        stk: A pointer to the stack.
	 */
	 //int stackInit(stack_t* stk);

	int  mazeInit(maze_t* maze, size_t width, size_t height);
	int  mazeDestroy(maze_t* maze);
	int  mazeSolve(maze_t* maze);
	void mazeRender(maze_t* m);


#ifdef __cplusplus
}
#endif

#endif // MAZE_H