
typedef struct ds_node {
    void *data;      
    struct ds_node *next;
} ds_node;

typedef struct ds_list {
        ds_node *head;
        ds_node *tail;
        unsigned int size;  
        unsigned int data_size;
} ds_list;

ds_list
*create_list(unsigned int data_size);

ds_node 
*create_node(void *data);

void 
remove_front(ds_list *list);

void
add_front(ds_list *list, void *data);

void
add_last(ds_list *list, void *data);

void *
remove_nth_node(ds_list *list, unsigned int position);
