/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q != NULL) {
        q->head = NULL;
        q->tail = q->head;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL)
        return;

    /* How about freeing the list elements and the strings? */
    if (q->head != NULL) {
        list_ele_t *p = q->head;
        list_ele_t *n = q->head->next;
        while (p != NULL) {
            free(p->value);
            free(p);
            p = n;
            if (n != NULL)
                n = n->next;
        }
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    /* Don't forget to allocate space for the string and copy it */
    newh->value = (char *) malloc((strlen(s) + 1) * sizeof(char));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s) + 1);
    /* What if either call to malloc returns NULL? */
    newh->next = q->head;
    q->head = newh;
    q->size += 1;
    if (q->tail == NULL)
        q->tail = newh;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;

    newh->value = (char *) malloc((strlen(s) + 1) * sizeof(char));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strncpy(newh->value, s, strlen(s) + 1);
    newh->next = NULL;
    if (q->tail != NULL)
        q->tail->next = newh;
    q->tail = newh;
    if (q->head == NULL)
        q->head = newh;
    q->size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL)
        return false;
    if (q->head == NULL)
        return false;

    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    if (sp != NULL) {
        strncpy(sp, tmp->value, bufsize - 1);
        sp[bufsize - 1] = 0;
    }
    free(tmp->value);
    free(tmp);
    q->size -= 1;
    if (q->size == 0)
        q->tail = NULL;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    if (q != NULL)
        return q->size;
    return 0;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if (q == NULL)
        return;
    if (q->head == NULL)
        return;

    list_ele_t *p = NULL;
    list_ele_t *t = q->head;
    list_ele_t *r = q->head->next;
    while (t != NULL) {
        t->next = p;
        p = t;
        t = r;
        if (r != NULL)
            r = r->next;
    }
    q->tail = q->head;
    q->head = p;
}
