#include "dlinked_list.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  void *elem;
  struct node *next, *prev;
} node_s;

typedef struct dlinked_list {
  node_s *head; /* Th head of the list */
  node_s *tail; /* The tail of the lits
                 * Note: Head and tail are the same when the size of the list
                 * equals 1. When the list is empty, then both head and tail
                 * are NULL.
                 */
  node_s *iter; /* Use it to iterate through the list
                 * This field is initialized by calling dlinked_list_get_first
                 * or dlinked_list_get_last.
                 */
} dlinked_list_s;

/* Declaration of local functions */
static node_s *make_node(void *val);

/* Implementation of the local functions */
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

dlinked_list_t dlinked_list_create() {
  dlinked_list_t list = malloc(sizeof(dlinked_list_s));

  if (!list) {
    return NULL;
  }

  list->head = NULL;
  list->tail = NULL;
  list->iter = NULL;

  return list;
}

void dlinked_list_destroy(dlinked_list_t list, destroy_function_f fn) {
  while (list->head) {
    node_s *next_head = list->head->next;

    if (fn) {
      fn(list->head->elem);
    }

    free(list->head);

    list->head = next_head;
  }

  free(list);
}

bool dlinked_list_is_empty(const dlinked_list_t list) {
  /* If the beginning of the list in NULL, then we know that the list
   * is empty.
   */
  return !list->head;
}

bool dlinked_list_append(dlinked_list_t list, void *item) {
  assert(item);

  node_s *new_node = make_node(item);
  if (!new_node) {
    return false;
  }

  if (!list->head) { 
    /* This is the case when we have an empty list */

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

  return true;
}

bool dlinked_list_insert(dlinked_list_t list, void *item) {
  assert(item);

  node_s *new_node = make_node(item);
  if (!new_node) {
    return false;
  }

  if (!list->head) { 
    /* In this case we have an empty list */
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

  return true;
}

void dlinked_list_store(dlinked_list_t list, void *item) {
  assert(list->iter);

  list->iter->elem = item;
}

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

void *dlinked_list_current(dlinked_list_t list) {
  assert(list->iter);

  return list->iter->elem;
}

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

/* Internally this function uses an array of pointers to do the sorting. */
bool dlinked_list_sort(dlinked_list_t list, compare_function_f fn) {
  node_s *cursor = list->head;
  int size = 0;

  while (cursor) {
    ++size;
    cursor = cursor->next;
  }

  if (size == 0) return true; /* Nothing to sort */

  void **array = malloc(size * sizeof(void *));
  if (array == NULL) return false;

  /* We copy the pointers from the list to the array */
  void *item = dlinked_list_get_first(list);
  int i = 0;
  while (item) {
    array[i++] = item;
    item = dlinked_list_get_next(list);
  }

  qsort(array, size, sizeof(void *), fn);

  /* We re-write the ponter values  the pointers from the list to the array */
  item = dlinked_list_get_first(list);
  i = 0;
  while (item) {
    dlinked_list_store(list, array[i++]);
    item = dlinked_list_get_next(list);
  }

  free(array);

  return true;
}
