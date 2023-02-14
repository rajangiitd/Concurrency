#include "../include/list.h"
#include "../include/hm.h"
#include "../include/mythread.h"

int hashmap_create(struct hashmap_s *const out_hashmap){
    // Initialize a hashmap
    for(int i=0;i<SZ;i++){
        out_hashmap->table[i] = list_new(); 
    }
    return 0;
}   

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data){
    // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function
    return -1;
}   

void* hashmap_get(struct hashmap_s *const hashmap, const char* key){
        // Fetch value of a key from hashmap
}
void hashmap_iterator(struct hashmap_s* const hashmap, 
                        int (*f)(struct hashmap_element_s *const)){
                              // Execute argument function on each key-value pair in hashmap
                        }
int acquire_bucket(struct hashmap_s *const hashmap, const char* key){
       // Acquire lock on a hashmap slot
       return -1;
}
int release_bucket(struct hashmap_s *const hashmap, const char* key){
       // Release acquired lock
       return -1;
}