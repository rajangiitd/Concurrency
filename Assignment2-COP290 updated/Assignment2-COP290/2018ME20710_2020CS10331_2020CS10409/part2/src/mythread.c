#include "../include/list.h"
#include "../include/hm.h"
#include "../include/mythread.h"

struct list my_list_of_contexts;                // Linked list for storing contexts
static struct listentry* my_head_for_join;      // Pointer to track the linked list of contexts
static struct listentry* my_head_for_yield;     // Pointer to track the context that is running
static ucontext_t mymain;                       // Pointer for the main context of file

void mythread_init(){
    my_list_of_contexts = *list_new();  // Initialize threads list
    // (Left)  Head--->node--->node--->Tail (Right)
}
    
ucontext_t* mythread_create(void func(void*), void* arg){
    ucontext_t* context = (ucontext_t*) malloc(sizeof(ucontext_t));  // Allocating heap memory to context
    getcontext(context);                                        // Prepares context
    char* stack = (char*) malloc(4*SZ);                         // Setup stack
    context->uc_stack.ss_sp = stack;
    context->uc_stack.ss_size = sizeof(stack);                  // Allocated 4*4 = 16kB memory
    context->uc_link = &mymain;
    makecontext(context, (void (*)()) func, 1, arg);        // Takes 1 argument as arg here
    list_add(&my_list_of_contexts, context);                // Adding context to list
    return context;
}

void mythread_join(){
    my_head_for_join = my_list_of_contexts.head;            // Start from head of context's linked list

    while( my_list_of_contexts.head != NULL){
        my_head_for_join = my_list_of_contexts.head;    // Assume that we begin from running head node's context
        my_head_for_yield = my_head_for_join;           // Track-node to track context we are in 
        swapcontext(&mymain, my_head_for_join->data);       // Switch from main of file to context
        list_rm(&my_list_of_contexts, my_head_for_yield);   // Remove the completed context from list
    }
}

void mythread_yield(){
    // Perform context switching here
    if(my_list_of_contexts.head == my_list_of_contexts.tail) 
        return;                 // If there is only 1 thread left, there is no place to switch 
    if(my_head_for_yield == my_list_of_contexts.tail){
        ucontext_t *curr_context = my_head_for_yield->data; // Case when we have reached the context at tail
        my_head_for_yield = my_head_for_join;               // And there is no more context on right
        swapcontext(curr_context, my_head_for_yield->data);
    }else{
        ucontext_t *curr_context = my_head_for_yield->data; // Case when we are in middle of list of context
        my_head_for_yield = my_head_for_yield->next;        // And there is a context available on right of list
        swapcontext(curr_context, my_head_for_yield->data);
    }
}

struct lock* lock_new(){
    // return an initialized lock object
    struct lock* mylock = (struct lock*) malloc(sizeof(struct lock));   // Allocate heap memory to lock
    mylock->ctx = NULL;                                 // Initialize context pointer with NULL
    return mylock;
}

void lock_acquire(struct lock* lk){
    // Set lock. Yield if lock is acquired by some other thread.
    while (lk->ctx !=NULL) mythread_yield();
    lk->ctx = my_head_for_yield->data;      // Acquiring the lock by current context
}

int lock_release(struct lock* lk){
    lk->ctx = NULL; // Release lock
    return 0;
} 
