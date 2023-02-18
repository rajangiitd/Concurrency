#include "../include/list.h"
#include "../include/hm.h"
#include "../include/mythread.h"

struct list my_list_of_contexts;
static ucontext_t mymain;
static struct listentry* my_head_for_join;
static struct listentry* my_head_for_yield;

void mythread_init(){
    my_list_of_contexts = *list_new();  // Initialize threads list
}
    
ucontext_t* mythread_create(void func(void*), void* arg){
    ucontext_t* context = (ucontext_t*) malloc(sizeof(ucontext_t));  // context pointer
    getcontext(context);
    char* stack = (char*) malloc(4*SZ);  
    context->uc_stack.ss_sp = stack;
    context->uc_stack.ss_size = sizeof(stack);
    context->uc_link = &mymain;
    makecontext(context, (void (*)()) func, 1, arg);        // Takes 1 argument as arg here
    list_add(&my_list_of_contexts, context);
    return context;
}

void mythread_join(){
    my_head_for_join = my_list_of_contexts.head;

    while( my_list_of_contexts.head != NULL){   
        my_head_for_join = my_list_of_contexts.head;
        my_head_for_yield = my_head_for_join;                    // track node we are in
        swapcontext(&mymain, my_head_for_join->data);
        list_rm(&my_list_of_contexts, my_head_for_join);
    }
}

void mythread_yield(){
    // Perform context switching here      // Lets Assume that the current context was always the head of list
    if(my_list_of_contexts.head == my_list_of_contexts.tail) return;
    if(my_head_for_yield == my_list_of_contexts.tail){
        ucontext_t *curr_context = my_head_for_yield->data;
        my_head_for_yield = my_head_for_join;
        swapcontext(curr_context, my_head_for_yield->data);
    }else{
        ucontext_t *curr_context = my_head_for_yield->data;
        my_head_for_yield = my_head_for_yield->next;
        swapcontext(curr_context, my_head_for_yield->data);
    }
}

struct lock* lock_new(){
       // return an initialized lock object
       struct lock* mylock = (struct lock*) malloc(sizeof(struct lock));
       mylock->ctx = NULL;
       return mylock;
}

void lock_acquire(struct lock* lk){
    // Set lock. Yield if lock is acquired by some other thread.
    while (lk->ctx !=NULL) mythread_yield();
    lk->ctx = my_head_for_yield->data;
}
int lock_release(struct lock* lk){
    lk->ctx = NULL; // Release lock
    return 0;
} 