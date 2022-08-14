typedef struct anode{
  int val;
  struct anode *next;
} node;

typedef struct{
  int size;
  node *first;
} list;

/* definition of the list API */

/* Create a new node instance */
node *node_new(int, node *);

/* Create a new list instance */
list *list_new();

/* Fill a list with nodes filled with random values */
list *list_new_random(int, int);

/* Inserts a new node at the head of the list */
void list_add_first(int, list *);

/* Inserts a new node at the tail of the list */
void list_add_last(int, list *);

/* Returns the value of the head of a list */
int list_get_first(list *);

/* Returns the value of the tail of a list */
int list_get_last(list *);

/* Removes the head of a list reconnecting to the remaining nodes */
void list_remove_first(list *);

/* Removes the tail of the list */
void list_remove_last(list *);

/* Returns a list's size */
int list_size(list *);

/* Prints a list's content */
void list_print(list *);

