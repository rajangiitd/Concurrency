#include "../include/list.h"
#include "../include/hm.h"
#include "../include/mythread.h"

int hashmap_create(struct hashmap_s *const out_hashmap){
    // Initialize a hashmap
    for(int i=0;i<SZ;i++){
        out_hashmap->table[i] = list_new(); 
        out_hashmap->lk[i] = lock_new();
    }
    return 0;
}   

int hashmap_put(struct hashmap_s *const hashmap, const char* key, void* data){
    // Set value of the key as data in hashmap. You can use any method to resolve conflicts. Also write your own hashing function

    // Getting hash_value
    int my_hash_value = 0;
    int prime = 31;
    int temp_prime = 1;
    for(int i=0; key[i] != '\0';i++){
        my_hash_value += ((int) key[i])*temp_prime;
        my_hash_value = my_hash_value%SZ;
        temp_prime = (temp_prime*prime)%SZ; 
    }

    // Create element for hashmap
    struct hashmap_element_s *element = (struct hashmap_element_s *) malloc(sizeof(struct hashmap_element_s));     
    char* mykey = (char*) malloc(sizeof(char)*strlen(key));
    strcpy(mykey,key);
    element->key = mykey;       // copying key in hashmap hashmap
    element->data = data;       // saving pointer to data in hashmap

    // Search if there is a data in linkedlist whose key is same as above key
    struct list* target_list = hashmap->table[my_hash_value];
    struct listentry* my_head = target_list->head;
    while(my_head != NULL){
        struct hashmap_element_s *myele = my_head->data;
        if( strcmp(myele->key,key)==0){
            myele->data = data;             // Update data if key is same
            return 0;
        }else{
            my_head = (my_head->next);
        }
    }

    // No key was not over-written, hence add a new node in linked list 
    list_add(target_list, element);
    return 0;
}   

void* hashmap_get(struct hashmap_s *const hashmap, const char* key){
    // Fetch value of a key from hashmap

    // Getting hash_value
    int my_hash_value = 0;
    int prime = 31;
    int temp_prime = 1;
    for(int i=0; key[i] != '\0';i++){
        my_hash_value += ((int) key[i] )*temp_prime;
        my_hash_value = my_hash_value%SZ;
        temp_prime = (temp_prime*prime)%SZ; 
    }

    // Search if there is a data in linkedlist whose key is same as above key
    struct list* target_list = hashmap->table[my_hash_value];
    struct listentry* my_head = target_list->head;
    while(my_head != NULL){
        struct hashmap_element_s *myele = my_head->data;
        if( strcmp(myele->key,key)==0){
            return myele->data;
        }else{
            my_head = (my_head->next);
        }
    }
    // key is not found, hence return NULL
    return NULL;
}
void hashmap_iterator(struct hashmap_s* const hashmap, int (*f)(struct hashmap_element_s *const)){
    // Execute argument function on each key-value pair in hashmap
    for(int i=0;i<SZ;i++){
        struct list* target_list = hashmap->table[i];
        struct listentry* my_head = target_list->head;
        while (my_head != NULL){
            f(my_head->data);
            my_head = (my_head->next);          // Travel each linked list and call function on each node
        }
    }
}

int acquire_bucket(struct hashmap_s *const hashmap, const char* key){
    // Acquire lock on a hashmap slot

    // Getting hash_value
    int my_hash_value = 0;
    int prime = 31;
    int temp_prime = 1;
    for(int i=0; key[i] != '\0';i++){
        my_hash_value += ((int) key[i] )*temp_prime;
        my_hash_value = my_hash_value%SZ;
        temp_prime = (temp_prime*prime)%SZ; 
    }

    lock_acquire(hashmap->lk[my_hash_value]);   // Acquire the lock
    return 0;
}
int release_bucket(struct hashmap_s *const hashmap, const char* key){
       // Release acquired lock

    // Getting hash_value
    int my_hash_value = 0;
    int prime = 31;
    int temp_prime = 1;
    for(int i=0; key[i] != '\0';i++){
        my_hash_value += ((int) key[i] )*temp_prime;
        my_hash_value = my_hash_value%SZ;
        temp_prime = (temp_prime*prime)%SZ; 
    }

    lock_release(hashmap->lk[my_hash_value]);   // Release the lock
    return 0;
}
