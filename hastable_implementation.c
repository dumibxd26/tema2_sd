#include <stdio.h>
#include "hashtable_implementation.h"

ds_hashtable *
create_hashtable(unsigned int size, unsigned int (*hash_function)(void *), 
                 int (*compare_function)(void *, void *), int data_size)
{
    ds_hashtable *hashtable = malloc(sizeof(ds_hashtable));
    hashtable->resize_list = malloc(sizeof(ds_list));
    hashtable->bucket = malloc(sizeof(ds_list *) * size);
    hashtable->size = size;
    hashtable->compare_function = compare_function;
    hashtable->hash_function = hash_function;

    for (unsigned int i = 0; i < size; i++) 
        hashtable->bucket[i] = create_list(data_size);

    return hashtable;
}

ds_list *
get_bucket(ds_hashtable *hashtable, void *data)
{
    unsigned int index = hashtable->hash_function(data) % hashtable->size;
    return hashtable->bucket[index];
}

int
has_key(ds_hashtable *hashtable, void *key)
{
    ds_list *bucket = get_bucket(hashtable, key);
    ds_node *current = bucket->head;

    while (current != NULL) 
    {
        ds_info *info = current->data;
        if (hashtable->compare_function(info->key, key) == 0)
            return 1;
        
        current = current->next;
    }

    return 0;
}

void *
get_key(ds_hashtable *hashtable, void *key)
{
    ds_list *bucket = get_bucket(hashtable, key);
    ds_node *current = bucket->head;

    while (current != NULL)
    {
        ds_info *info = current->data;
        if (hashtable->compare_function(info->key, key) == 0)
            return current->data;
        
        current = current->next;
    }

    return NULL;
}

void *
put_key(ds_hashtable *hashtable, void *key, void *value)
{
    ds_list *bucket = get_bucket(hashtable, key);
    ds_node *current = bucket->head;

    ds_info *new_info = malloc(sizeof(ds_info));
    new_info->key = key;
    new_info->value = value;

    while (current != NULL)
    {
        ds_info *data_info = current->data;
        if (hashtable->compare_function(data_info->key, key) == 0)
        {
            void *old_value = data_info;
            current->data = new_info;
            return old_value;
        }
        
        current = current->next;
    }

    add_last(hashtable->resize_list, new_info);
    add_last(bucket, new_info);

    return NULL;
}

void *
remove_key(ds_hashtable *hashtable, void *key)
{
    ds_list *bucket = get_bucket(hashtable, key);
    ds_node *current = bucket->head;

    while (current != NULL)
    {
        ds_info *data_info = current->data;
        if (hashtable->compare_function(data_info->key, key) == 0)
        {
            void *old_value = data_info;
            remove_node(bucket, current);
            return old_value;
        }
        
        current = current->next;
    }

    return NULL;
}

void hashtable_resize(ds_hashtable *hashtable, unsigned int new_size)
{
    
    for(unsigned int i = 0; i < hashtable->size; i++)
    {
        ds_list *bucket = hashtable->bucket[i];
        ds_node *node = bucket->head;
        ds_node *next_node;

        while (node != NULL)
        {
            next_node = node->next;
            free(node);

            node = node->next;
        }

        free(hashtable->bucket[i]);
    }

    hashtable->size = new_size;

///////    

}