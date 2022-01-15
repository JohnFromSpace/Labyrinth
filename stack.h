#ifndef STACK_H // Prevent multiple inclusions
#define STACK_H

/*******************************************************************************
 * Preprocessor Directives
 ******************************************************************************/


 /*******************************************************************************
  * Macros and Constants
  ******************************************************************************/


  /*******************************************************************************
   * Abstract Data Types
   ******************************************************************************/
   /* Generic node in a stack */
typedef struct snode_t {
	struct snode_t* next;
	void* data;
	size_t width;
} snode_t;

/* Generic stack */
typedef struct stack_t {
	snode_t* top;
	size_t length;
} stack_t;

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
	int stackInit(stack_t* stk);

	/* @functionName: stackDestroy
	 * @brief:        Destroys and cleans up an entire stack.
	 * @param:        stk: A pointer to the stack.
	 */
	int stackDestroy(stack_t* stk);

	/* @functionName: stackPop
	 * @brief:        Pop an item from the top of the stack.
	 * @param:        stk:  A pointer to the stack.
	 * @param:        node: A pointer to where to store the contents of the
	 *                      "popped" element.
	 */
	int stackPop(stack_t* stk, snode_t* node);

	/* @functionName: stackPush
	 * @brief:        Push an item on top of the stack.
	 * @param:        stk:  A pointer to the stack.
	 * @param:        node: A pointer to the element to "push".
	 */
	int stackPush(stack_t* stk, snode_t* node);

	/* @functionName: stackPeek
	 * @brief:        Peek at the item on top of the stack without deleting it.
	 * @param:        stk:  A pointer to the stack.
	 * @param:        node: A pointer to where to store a copy of the data
	 *                      (not including stack pointer contents) of the data
	 *                      a the top of the stack.
	 */
	int stackPeek(stack_t* stk, snode_t* node);

#ifdef __cplusplus
}
#endif

#endif // STACK_H