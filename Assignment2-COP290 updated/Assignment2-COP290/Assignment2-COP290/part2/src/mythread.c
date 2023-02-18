#include "../include/list.h"
#include "../include/hm.h"
#include "../include/mythread.h"

struct hashmap_s myhashmap;
struct list my_list_of_contexts;
static ucontext_t* mymain;
int curr = 0;

void mythread_init(){
    // Initialize threads list
    my_list_of_contexts = *list_new();
    hashmap_create(&myhashmap);
    mymain = (ucontext_t *)malloc(sizeof(ucontext_t));
    list_add(&my_list_of_contexts, mymain);
    ucontext_t *mycontext = (ucontext_t *)malloc(sizeof(ucontext_t));
    list_add(&my_list_of_contexts, mycontext);
}
    
ucontext_t* mythread_create(void func(void*), void* arg){
    struct listentry* my_tail = my_list_of_contexts.tail;
    ucontext_t* last_context = my_tail->data;
    printf("%d\n", getcontext(last_context));
    char* stack = (char*) malloc(2*SZ);  
    last_context->uc_stack.ss_sp = stack;
    last_context->uc_stack.ss_size = sizeof(stack);

    ucontext_t* context = (ucontext_t*) malloc(sizeof(ucontext_t*));  // context pointer
    list_add(&my_list_of_contexts, context);
    last_context->uc_link = context;
    makecontext(last_context, (void (*)()) func, 1, arg);        // Takes 1 argument as arg here

    return last_context;
}

void mythread_join(){
    printf("In join\n");
    struct listentry* my_tail = my_list_of_contexts.tail;
    ucontext_t* last_context = my_tail->data;
    printf("In join 1\n");
    //ucontext_t* my_current = (ucontext_t*) malloc(sizeof(ucontext_t*));  // context pointer
    struct listentry* my_head = my_list_of_contexts.head;
    printf("In join 2\n");
    
    swapcontext(last_context, my_head->data); 
    printf("Came back to end\n");
}

void mythread_yield(){
    // Perform context switching here
    // ucontext_t* current = (ucontext_t*) malloc(sizeof(ucontext_t));
    // getcontext(current);
    // ucontext_t* next = (ucontext_t*) list_remove(&my_list_of_contexts, 0);
    // list_add(&my_list_of_contexts, current);
    // setcontext(next);

}

struct lock* lock_new(){
       // return an initialized lock object
       return NULL;
}

void lock_acquire(struct lock* lk){
    // Set lock. Yield if lock is acquired by some other thread.
    while (lk->ctx !=NULL) mythread_yield();
    ucontext_t* current = (ucontext_t*) malloc(sizeof(ucontext_t));
    getcontext(current);
    lk->ctx = current;
}
int lock_release(struct lock* lk){
    lk->ctx = NULL; // Release lock
    return 0;
} 