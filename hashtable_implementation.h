#include "linked_list_implementation.h"

typedef struct ds_info {
    int *key;
    int *value;
} ds_info;

typedef struct ds_hashtable {
        ds_list **bucket;
        ds_list *resize_list;
        unsigned int size;
        unsigned int (*hash_function)(void *);
        int (*compare_function)(void*, void*);
} ds_hashtable;

ds_hashtable *
create_hashtable(unsigned int size, unsigned int (*hash_function)(void *), 
                 int (*compare_function)(void *, void *), int data_size);

ds_list *
get_bucket(ds_hashtable *hashtable, void *data);

int
has_key(ds_hashtable *hashtable, void *key);

void *
get_key(ds_hashtable *hashtable, void *key);

void *
put_key(ds_hashtable *hashtable, void *key, void *value);