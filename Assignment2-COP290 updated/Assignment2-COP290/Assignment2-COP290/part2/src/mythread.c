#include "../include/list.h"
#include "../include/hm.h"
#include "../include/mythread.h"

struct hashmap_s hashmap;
struct list my_list_of_contexts;

void mythread_init(){
      // Initialize threads list
      my_list_of_contexts = *list_new();
      hashmap_create(&hashmap);
}
    
ucontext_t* mythread_create(void func(void*), void* arg){
    ucontext_t* context = (ucontext_t*) malloc(sizeof(ucontext_t));  // context pointer
    char* stack = (char*) malloc(2*SZ);                              // stack space for it
    getcontext(context);                                                
    context->uc_stack.ss_sp = stack;
    context->uc_stack.ss_size = sizeof(stack);
    context->uc_link = NULL;
    makecontext(context, (void (*)()) func, 1, arg);        // Takes 1 argument as arg here
    list_add(&my_list_of_contexts, context);
    return context;
}

void mythread_join();  // Waits for other thread to complete. It is used in case of dependent threads.

void mythread_yield(){

    // Perform context switching here
}

struct lock {
	ucontext_t* ctx;
};

struct lock* lock_new();   // return an initialized lock object
void lock_acquire(struct lock* lk){
    // Set lock. Yield if lock is acquired by some other thread.
    while (lk->ctx !=NULL) mythread_yield();
    ucontext_t* current = (ucontext_t*) malloc(sizeof(ucontext_t));
    getcontext(current);
    lk->ctx = current;
}
int lock_release(struct lock* lk){
    lk->ctx = NULL; // Release lock
} 