#include "hashTable.h"
#include "objects.h"
#include <stdio.h>
#include <stdlib.h>

#define HASH 

/**
 * Hash
 */
 typedef struct hash_map_s {
   profile *profiles;
   unsigned long length;
   unsigned long loadFactor;
 } hash_map;

typedef struct hash_node_s {
  profile prof;

} hash_node;

/**
 * Given a hash map, returns the constant value incrementened
 * every added hash_node
 */
unsigned long hash_length(hash_map hash){
  return hash.length;
}

/**
 * Runs the input through the hash function to find the value
 * in the hashmap (passing over sentinel values). Find method is
 * run via quadratic probing.
 *
 * If the value is not found, NULL is returned.
 */
hash_node *hash_find(hash_map hash, profile value){

}


/**
 * Conducts the same process as the find method and then
 * replaces the node with a sentinel (where profile = NULL)
 *
 * Sentinel values count torwards the length of the hash_map
 */
hash_node *hash_remove(hash_map hash, profile value);

/**
 * Using the hash function and quadratic probing,
 * the profile value is inserted into the hashmap.
 *
 * If the number of nodes in the map overcomes the load factor,
 * the hash map will be resized
 */
void *ll_insert(hash_map hash, profile value);

/**
 * Resizing the hashmap involves reinserting every value into a new hash_map
 * excluding sentinel values
 */
hash_map resize(hash_map hash);


#endif /* ifdef __LINKEDLIST_H */
