#include <stdlib.h>
#include "linked_list_implementation.h"

ds_list *
create_list(unsigned int data_size)
{
    ds_list *list = malloc(sizeof(ds_list));
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->data_size = data_size;
    return list;
}

ds_node *
create_node(void *data)
{
    ds_node *node = malloc(sizeof(ds_node));
    node->data = data;
    node->next = NULL;
    return node;
}

void
add_last(ds_list *list, void *data)
{
    ds_node *node = create_node(data);
    if (list->size == 0) {
        list->head = node;
        list->tail = node;
    } else {
        list->tail->next = node;
        list->tail = node;
    }
    list->size++;
}

void *
remove_nth_node(ds_list *list, unsigned int position)
{
    if (position >= list->size) {
        return NULL;
    }
    ds_node *current = list->head;
    ds_node *delete_node = current;

    if (position == 0) {
        list->head = current->next;
        if (list->head == NULL) 
            list->tail = NULL;

    } else {
        for (unsigned int i = 0; i < position - 1; i++)
            current = current->next;
        
        delete_node = current->next;
        current->next = current->next->next;
        if (current->next == NULL) {
            list->tail = current;
        }
    }
    list->size--;

    return delete_node;
}
