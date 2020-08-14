/* Double linked list header file.
 *
 * This is a linked list implementation. The user does not require
 * any knowledge of the internal structure and implementation of the list.
 *
 * Items in the linked list are passed through as void pointers and cannot
 * be NULL as NULL is used as a return value in the functions which iterate
 * through the list.
 */

#include <stdbool.h>

/* The linked list handle */
typedef struct dlinked_list *dlinked_list_t;

/* User destruction function */
typedef void (*destroy_function_f)(void *ptr);

// User compare function
// Returns -ve ptr1 <  ptr2
//          0  ptr1 == ptr2
//         +ve ptr1 >  ptr2
typedef int (*compare_function_f)(const void *ptr1, const void *ptr2);

// Function to create a linked list and return an opaque handle to it
dlinked_list_t dlinked_list_create();

// Function to destroy a linked list
// If fn is not NULL then it will call fn for each item in the list
void dlinked_list_destroy(dlinked_list_t list, destroy_function_f fn);

// Function to check if a list is empty
// returns  0  - False, there are items in the list
//          !0 - True
bool dlinked_list_is_empty(dlinked_list_t list);

// Append an item to the list.  This will add the item to the end of the list
// Item must be non-null
//
// Returns:  0 - Success
//          !0 - Failed
int dlinked_list_append(dlinked_list_t list, void *item);

// Insert an item into the list.  This will insert the item in front of the
// Current item in the list.  Item must be non-null
// Returns:  0 - Success
//          !0 - Failed
int dlinked_list_insert(dlinked_list_t list, void *item);

// Remove the current item from the list
// Returns:
//          NULL - the list is empty
//          item - The removed item
void dlinked_list_remove(dlinked_list_t list);

// Get the current item in the list
// Returns:
//          NULL - The list is empty
//          item - The current item
void *dlinked_list_current(dlinked_list_t list);

// Get the first/last item from the list and set as current
//
void *dlinked_list_get_first(dlinked_list_t list);
void *dlinked_list_get_last(dlinked_list_t list);

// Get the next / previous item from the list and set as
// current
void *dlinked_list_get_next(dlinked_list_t list);
void *dlinked_list_get_prev(dlinked_list_t list);

// Sort the linked list
// fn is a function used to compare two list items
// usr_info is a value passed to every call of fn
bool dlinked_list_sort(dlinked_list_t list, compare_function_f fn, void *usr_info);
