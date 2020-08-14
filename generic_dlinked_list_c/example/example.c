#include <stdio.h>
#include <stdlib.h>

#include "dlinked_list.h"

const int NBR_PTRS = 10;

static void print_list(const dlinked_list_t list);
static bool delete_value_from_list(dlinked_list_t list, int value);

int main() {

    int *ptrs[NBR_PTRS];  /* A table of pointers that we are going to
                           * store in our list.
                           */
    int *ptrsx[NBR_PTRS]; /* Another table of pointers that we are going to
                           * store in our list.
                           */


    for (int i = 0; i < NBR_PTRS; ++i) {

        if (!(ptrs[i] = malloc(sizeof(ptrs[i])))) {

            fprintf(stderr, "Couldn't create a pointer at index %d.\n", i);
            exit(EXIT_FAILURE);
        }

        if (!(ptrsx[i] = malloc(sizeof(ptrsx[i])))) {

            fprintf(stderr, "Couldn't create a pointer at index %d.\n", i);
            exit(EXIT_FAILURE);
        }

        *ptrs[i] = *ptrsx[i] = 10 * i;
 
    } 

    dlinked_list_t dl_list = dlinked_list_create();

    if (!dl_list) {

        fprintf(stderr, "Couldn't create a list structure.\n");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "The list is empty: %s.\n",
        dlinked_list_is_empty(dl_list) ? "true" : "false.");

    /* Appending the pointers to the list. */
    for (int i = 0; i < NBR_PTRS; ++i) {

        if (dlinked_list_append(dl_list, ptrs[i]) < 0) {

            fprintf(stderr, "Couldn't append a pointer at index %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    /* It should print: 0 10 20 30 40 50 60 70 80 90 */
    print_list(dl_list);

    /* Inserting this set of pointers to the list. */
    for (int i = 0; i < NBR_PTRS; ++i) {

        if (dlinked_list_insert(dl_list, ptrsx[i]) < 0) {

            fprintf(stderr, "Couldn't append a pointer at index %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    /* It should print: 90 80 70 60 50 40 30 20 10 0 0 10 20 30 40 50 60 70 80 90 */
    print_list(dl_list);

    int value = 50;

    fprintf(stdout, "Deleted <%d> from the list: %s.\n",
        value, delete_value_from_list(dl_list, value) ? "true" : "false");

    /* It should print: 90 80 70 60 40 30 20 10 0 0 10 20 30 40 50 60 70 80 90 */
    print_list(dl_list);

    fprintf(stdout, "Deleted <%d> from the list: %s.\n",
        value, delete_value_from_list(dl_list, value) ? "true" : "false");

    /* It should print: 90 80 70 60 40 30 20 10 0 0 10 20 30 40 60 70 80 90 */
    print_list(dl_list);

    fprintf(stdout, "Deleted <%d> from the list: %s.\n",
        value, delete_value_from_list(dl_list, value) ? "true" : "false");

    print_list(dl_list);

    /* Removing the elements from the head and then from the tail of the list */
    int *int_p;
    if ((int_p = dlinked_list_get_first(dl_list))) {
        /* Note that the caller decides what to do with the pointer stored in
         * the list before removing the node from the list.
         */
        free(int_p);
        dlinked_list_remove(dl_list);
    }

    if ((int_p = dlinked_list_get_last(dl_list))) {
        /* Note again that the caller decides what to do with the pointer stored
         * in the list before removing the node from the list.
         */
        free(int_p);
        dlinked_list_remove(dl_list);
    }

    /* It should print: 80 70 60 40 30 20 10 0 0 10 20 30 40 60 70 80 */
    print_list(dl_list);

    return 0;
}

static void print_list(const dlinked_list_t list) {

    if (dlinked_list_is_empty(list)) {
        fprintf(stdout, "The list is empty.\n");
        return;
    }

    fprintf(stdout, "The list has the following elements: ");

    int *p = dlinked_list_get_first(list);

    while (p) {

        fprintf(stdout, "%d ", *p);
        p = dlinked_list_get_next(list);
    }

    fprintf(stdout, "\n");

}

static bool delete_value_from_list(dlinked_list_t list, int value) {

    bool return_flag = false;

    if (dlinked_list_is_empty(list)) {
        return return_flag;
    }

    int *p = dlinked_list_get_first(list);

    while (p) {

        if (*p == value) {

           return_flag = true;
           dlinked_list_remove(list);
           break; 
        }

        p = dlinked_list_get_next(list);
    }

    return return_flag;
}