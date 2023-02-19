/**

@file list.h
@brief Defines a linked list and its operations.
*/
#ifndef LIST_H
#define LIST_H
#include <stdlib.h>
/**

@struct list
@brief A linked list.
*/
struct list {
	struct listentry* head;
	struct listentry* tail;
};
/**

@struct listentry
@brief An element in a linked list.
*/
struct listentry {
	void *data;
	struct listentry *prev;
	struct listentry *next;
};
/**

@brief Remove an item from the list.
@param l Pointer to the list.
@param e Pointer to the element to be removed from the list.
*/
void list_rm(struct list* l, struct listentry* e);    // Remove an item from the list
/**

@brief Add an item to the list.
@param l Pointer to the list.
@param data Pointer to the data to be stored in the new list element.
@return Pointer to the newly created list element.
*/
struct listentry* list_add(struct list* l, void* data);  // Add an item to the list
/**

@brief Return an initialized list.
@return Pointer to the initialized list.
*/
struct list* list_new();  // Return an initialized list
/**

@brief Check if list is empty or not.
@param l Pointer to the list.
@return 1 if the list is empty, 0 otherwise.
*/
int is_empty(struct list* l);  // Check if list is empty or not
#endif
