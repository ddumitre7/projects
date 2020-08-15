#include "dlinked_list.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  void *elem;
  struct node *next, *prev;
} node_s;

typedef struct dlinked_list {
  node_s *head; /* Head of the list */
  node_s *tail; /* Tail of the lits
                 * Note: Head and Tail are the same when the size of the list
                 * equals 1.
                 */
  node_s *iter; /* Use it to iterate through the list
                 * This field is initialized by calling dlinked_list_get_first
                 * or dlinked_list_get_last.
                 */
} dlinked_list_s;

// Declaration of local functions
static node_s *make_node(void *val);

// Implementation of the local functions
static node_s *make_node(void *val) {
  node_s *n = malloc(sizeof(node_s));

  if (!n) {
    return NULL;
  }

  n->elem = val;
  n->next = NULL;
  n->prev = NULL;

  return n;
}

// Function to create a linked list and return an opaque handle to it
dlinked_list_t dlinked_list_create() {
  dlinked_list_t ll = malloc(sizeof(dlinked_list_s));

  if (!ll) {
    return NULL;
  }

  ll->head = NULL;
  ll->tail = NULL;
  ll->iter = NULL;

  return ll;
}

// Function to destroy a linked list
// If fn is not NULL then it will call fn for each item in the list
void dlinked_list_destroy(dlinked_list_t list, destroy_function_f fn) {}

// Function to check if a list is empty
// returns  0  - False, there are items in the list
//          !0 - True
bool dlinked_list_is_empty(const dlinked_list_t list) {
  // If the beginning of the list in NULL, then we know that the list
  // is empty.
  return !list->head;
}

// Append an item to the list.  This will add the item to the end of the list
// Item must be non-null
//
// Returns:  0 - Success
//          !0 - Failed
int dlinked_list_append(dlinked_list_t list, void *item) {
  assert(item);

  node_s *new_node = make_node(item);
  if (!new_node) {
    return -1;
  }

  if (!list->head) { /* This means we have an empty list */

    list->head = list->tail = new_node;
  } else if (list->head == list->tail) {
    /* This is a special case: the list has just one node */

    list->tail = new_node;
    list->head->next = new_node;
    new_node->prev = list->head;
  } else {
    list->tail->next = new_node;
    new_node->prev = list->tail;
    list->tail = new_node;
  }

  return 0;
}

// Insert an item into the list.  This will insert the item in front of the
// Current item in the list.  Item must be non-null
// Returns:  0 - Success
//          !0 - Failed
int dlinked_list_insert(dlinked_list_t list, void *item) {
  assert(item);

  node_s *new_node = make_node(item);
  if (!new_node) {
    return -1;
  }

  if (!list->head) { /* This means we have an empty list */

    list->head = list->tail = new_node;
  } else if (list->head == list->tail) {
    /* This is a special case: the list has just one node */

    list->head = new_node;
    list->head->next = list->tail;
    list->tail->prev = new_node;
  } else {
    new_node->next = list->head;
    list->head->prev = new_node;
    list->head = new_node;
  }

  return 0;
}

// Remove the current item from the list
// Returns:
//          NULL - the list is empty
//          item - The removed item
void dlinked_list_remove(dlinked_list_t list) {
  assert(list->iter && list->head && list->tail);

  if ((list->iter == list->head) && (list->iter == list->tail)) {
    list->head = list->tail = NULL;
  } else if (list->iter == list->head) {
    list->head = list->head->next;
    list->head->prev = NULL;
  } else if (list->iter == list->tail) {
    list->tail = list->tail->prev;
    list->tail->next = NULL;
  } else {
    list->iter->prev->next = list->iter->next;
    list->iter->next->prev = list->iter->prev;
  }

  free(list->iter);
  list->iter = NULL;

  return;
}

// Get the current item in the list
// Returns:
//          NULL - The list is empty
//          item - The current item
void *dlinked_list_current(dlinked_list_t list) {
  assert(list->iter);

  return list->iter->elem;
}

// Get the first/last item from the list and set as current
//
void *dlinked_list_get_first(dlinked_list_t list) {
  if (!list->head) {
    return NULL;
  }

  // We initialize the list iterator
  list->iter = list->head;

  return list->iter->elem;
}

void *dlinked_list_get_last(dlinked_list_t list) {
  if (!list->tail) {
    return NULL;
  }

  // We initialize the list iterator
  list->iter = list->tail;

  return list->iter->elem;
}

// Get the next / previous item from the list and set as
// current
void *dlinked_list_get_next(dlinked_list_t list) {
  assert(list->iter);

  if (!list->iter->next) {
    return NULL;
  }

  list->iter = list->iter->next;

  return list->iter->elem;
}

void *dlinked_list_get_prev(dlinked_list_t list) {
  assert(list->iter);

  if (!list->iter->prev) {
    return NULL;
  }

  list->iter = list->iter->prev;

  return list->iter->elem;
}

// Sort the linked list
// fn is a function used to compare two list items
// usr_info is a value passed to every call of fn
bool dlinked_list_sort(dlinked_list_t list, compare_function_f fn,
                       void *usr_info) {
  return -1;
}
