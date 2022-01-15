#ifndef LINKED_LIST_H // Prevent multiple inclusions
#define LINKED_LIST_H

/*******************************************************************************
 * Preprocessor Directives
 ******************************************************************************/


 /*******************************************************************************
  * Macros and Constants
  ******************************************************************************/


  /*******************************************************************************
   * Abstract Data Types
   ******************************************************************************/
   /* Generic node in a linked list */
typedef struct lnode_t {
	struct lnode_t* next;
	void* data;
	size_t   width;
} lnode_t;

/* Generic list */
typedef struct llist_t {
	lnode_t* head;
	size_t   length;
} llist_t;

/*******************************************************************************
 * Public Function Prototypes
 *******************************************************************************/
 /* Handle compiling C code as part of a C++ project */
#ifdef __cplusplus
extern "C" {
#endif

	/* @functionName: llistInit
	 * @brief:        Initializes an empty linked list.
	 * @param:        list: A pointer to the list.
	 */
	int llistInit(llist_t* list);

	/* @functionName: llistDestroy
	 * @brief:        Destroys and cleans up an entire list.
	 * @param:        list: A pointer to the list.
	 */
	int llistDestroy(llist_t* list);

	/* @functionName: llistInsert
	 * @brief:        Inserts a new node at the beginning of a linked list.
	 * @param:        list: A pointer to the list.
	 * @param:        ins:  A pointer to the node to insert.
	 */
	int llistInsert(llist_t* list, lnode_t* ins);

	/* @functionName: llistDelete
	 * @brief:        Delete an item at a specific position in a list.
	 * @param:        list: A pointer to the list.
	 * @param:        idx:  The index of the item to delete.
	 */
	int llistDelete(llist_t* list, int idx);

	/* @functionName: llistAppend
	 * @brief:        Appends an item to the end of a list.
	 * @param:        list: A pointer to the list.
	 * @param:        append:  A pointer to the node to add to the list.
	 */
	int llistAppend(llist_t* list, lnode_t* append);

	/* @functionName: llistInsertAfter
	 * @brief:        Adds an item to a linked list at a specific index.
	 * @param:        list: A pointer to the list.
	 * @param:        add:       A pointer to the node to add to the list.
	 * @param:        position:  The index at which to add the new node.
	 */
	int llistInsertAfter(llist_t* list, lnode_t* add, int position);

#ifdef __cplusplus
}
#endif

#endif // LINKED_LIST_H
