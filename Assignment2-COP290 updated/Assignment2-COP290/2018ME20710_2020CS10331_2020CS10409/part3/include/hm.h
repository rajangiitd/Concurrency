/**

@file hm.h
@brief This header file contains the declarations of functions and structures related to hashmap.
*/
#include "mythread.h"
#include "list.h"
#define SZ 4096
#include <string.h>
/**

@struct hashmap_element_s
@brief This structure contains the key and value pair of hashmap.
*/

struct hashmap_element_s {
  char *key;
  void *data;
};
/**

@struct hashmap_s
@brief This structure defines the hashmap.
*/
struct hashmap_s {
  struct list* table[SZ];
  struct lock* lk[SZ];
};
/**

@brief Initializes the given hashmap with SZ number of linked lists and locks.
@param out_hashmap its the pointer to hashmap, which is to be initialized.
@return int 0 on successful initialization, -1 on failure.
*/

int hashmap_create(struct hashmap_s *const out_hashmap);   // Initialize a hashmap
/**

@brief Puts the given key-value pair in the hashmap.
@param hashmap The hashmap in which the key-value pair is to be inserted.
@param key The key of the pair.
@param data The value of the pair.
@return int 0 on successful insertion, -1 on failure.
*/

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data);   // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function
/**

@brief Fetches the value of the given key from the hashmap.
@param hashmap Pointer to hashmap from which the value is to be fetched.
@param key The key whose value is to be fetched.
@return void* The value of the key-value pair. Returns NULL if the key is not found in the hashmap.
*/
void* hashmap_get(struct hashmap_s *const hashmap, const char* key);    // Fetch value of a key from hashmap
/**

@brief Iterates over each key-value pair in the hashmap and applies the given function on them.
@param hashmap The hashmap over which the iteration is to be done.
@param f The function to be applied on each key-value pair.
*/
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const));  // Execute argument function on each key-value pair in hashmap
/**

@brief Acquires lock on the list-slot corresponding to the given key in the hashmap.
@param hashmap The hashmap containing the list of locks.
@param key The key whose lock we want to store.
@return int 0 on successful locking, -1 on failure.
*/
int acquire_bucket(struct hashmap_s *const hashmap, const char* key);   // Acquire lock on a hashmap slot
/**

@brief Releases the lock acquired on the linked list corresponding to the given key in the hashmap.
@param hashmap The hashmap containing the linked list.
@param key The key whose linked list lock is to be released.
@return int 0
*/
int release_bucket(struct hashmap_s *const hashmap, const char* key);   // Release acquired lock