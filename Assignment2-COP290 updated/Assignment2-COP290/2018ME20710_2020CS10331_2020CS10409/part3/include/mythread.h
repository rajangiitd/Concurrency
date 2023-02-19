/**

@file mythread.h
@brief Contains function prototypes and struct definitions for implementing user-level thread library in C.
*/
#ifndef THREAD_H
#define THREAD_H

#include<stdio.h>
#include<stdlib.h>
#include<ucontext.h>
#include<signal.h>
#include<sys/time.h>
#include<unistd.h>

/**

@brief Initialize the thread list.
*/
void mythread_init();
/**

@brief Create a new context but doesn't start executing it
@param func Pointer to the function that the new thread will execute
@param arg Pointer to the arguments that will be passed to the function during execution
@return A pointer to the context of the new thread created
*/
void* mythread_create(void func(void*), void* arg);
/**

@brief Start the execution of the all contexts in the thread list
*/
void mythread_join();
/**
 @brief Swap the context of the current thread with the next thread in the list.
 */
void mythread_yield();

/**
 @struct lock
 @brief Define a lock.
 */
struct lock {
	void* c;
};
/**
 @brief Create a new lock.
 @return A pointer to the newly created lock.
 */
struct lock* lock_new();
/**
 @brief Acquire a lock.
 @param lk Pointer to the lock.
 */
void lock_acquire(struct lock* lk);
/**
 @brief Release a lock.
 @param lk Pointer to the lock.
 */
int lock_release(struct lock* lk);

#endif