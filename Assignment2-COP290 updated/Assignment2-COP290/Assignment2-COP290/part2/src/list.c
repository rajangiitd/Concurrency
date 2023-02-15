
#include "../include/list.h"

struct list* list_new(){
	struct list* mylist = (struct list*) malloc(sizeof(struct list));
	mylist->head = NULL; mylist->tail = NULL;
	return mylist;
}

int is_empty(struct list* l){
	if(l->head == NULL ) return 1;
	else return 0;
}

struct listentry* list_add(struct list* l, void* data){
	struct listentry* node = (struct listentry*) malloc(sizeof(struct listentry));
	node->data = data; node->prev = l->tail; node->next = NULL;

   if (l->tail != NULL)  l->tail->next = node;
   if (l->head == NULL)  l->head = node;
   l->tail = node;

   return node;
}

void list_rm(struct list* l, struct listentry* e){
	if(e == NULL) return;

	if (e->prev != NULL) e->prev->next = e->next;
    if (e->next != NULL) e->next->prev = e->prev;
	if (e == l->head) l->head = e->next;
    if (e == l->tail) l->tail = e->prev;
   	
	free(e);
	return;
}

