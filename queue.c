#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

#ifndef strlcpy
#define strlcpy(dst, src, sz) snprintf((dst), (sz), "%s", (src))
#endif
/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    while (q && q->head) {
        list_ele_t *tmp;
        tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* TODO: What should you do if the q is NULL? */
    if (!q || !s)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    newh->value = NULL;
    newh->next = NULL;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    char *tmp = malloc(sizeof(char) * (strlen(s) + 1));
    if (!tmp) {
        free(newh);
        return false;
    }
    newh->value = tmp;
    strlcpy((newh->value), s, strlen(s) + 1);

    newh->next = q->head;
    (q->size)++;
    q->head = (q->size == 1 ? (q->tail = newh) : newh);
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !s)
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    char *tmp = malloc(sizeof(char) * (strlen(s) + 1));
    if (!tmp) {
        free(newh);
        return false;
    }
    newh->value = tmp;
    strlcpy(newh->value, s, strlen(s) + 1);
    newh->next = NULL;
    (q->size)++;
    q->tail = (q->size == 1 ? (q->head = newh) : (q->tail->next = newh));
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !(q->head) || !sp)
        return false;
    //  if (!sp)
    //     sp = malloc(sizeof(char) * bufsize);
    strlcpy(sp, q->head->value, bufsize);
    *(sp + bufsize - 1) = '\0';
    list_ele_t *tmp;
    tmp = q->head;
    q->head = q->size == 1 ? q->tail = q->tail->next : q->head->next;
    free(tmp->value);
    free(tmp);
    (q->size)--;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !(q->head))
        return 0;
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !(q->head))
        return;
    if (q->size == 1) {
        return;
    } else {
        list_ele_t *lhead;
        list_ele_t *rhead;
        lhead = NULL;
        rhead = q->head->next;
        q->tail = q->head;
        while (rhead != NULL) {
            q->head->next = lhead;
            lhead = q->head;
            q->head = rhead;
            rhead = rhead->next;
        }
        q->head->next = lhead;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !(q->head) || q->size == 1)
        return;


    q->head = split_list(q->head);

    q->tail = q->head;
    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}

list_ele_t *split_list(list_ele_t *head)
{
    if (!(head->next))
        return head;

    list_ele_t *right = head->next;
    list_ele_t *left = head;

    // split list
    while (right && right->next) {
        left = left->next;
        right = right->next->next;
    }
    right = left->next;
    left->next = NULL;

    // sort each list
    list_ele_t *l1 = split_list(head);
    list_ele_t *l2 = split_list(right);


    // merge sorted l1 and sorted l2
    return merge_sort(l1, l2);
}

list_ele_t *merge_sort(list_ele_t *l1, list_ele_t *l2)
{
    //"merge" actually is changing the address in 'next' field.
    //'head' is no different with the 'next' field in  list_ele_t.
    list_ele_t *head = NULL;
    list_ele_t **tmp = &head;

    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) < 0) {
            (*tmp) = l1;
            l1 = l1->next;
        } else {
            (*tmp) = l2;
            l2 = l2->next;
        }
        tmp = &((*tmp)->next);
    }

    if (l1) {
        (*tmp) = l1;
    } else {
        (*tmp) = l2;
    }
    return head;
}
