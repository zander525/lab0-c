#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if (!head) {
        return NULL;
    }
    INIT_LIST_HEAD(head);
    return head;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    if (list_empty(head)) {
        free(head);
        return;
    }
    struct list_head *node, *safe;
    list_for_each_safe(node, safe, head) {
        element_t *current = list_entry(node, element_t, list);
        q_release_element(current);
    }
    free(head);
}

/* Insert an element at head of queue */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *new_node = malloc(sizeof(element_t));
    if (!new_node)
        return false;
    size_t len = strlen(s) + 1;
    new_node->value = malloc(len * sizeof(char));
    if (!new_node->value) {
        q_release_element(new_node);
        return false;
    }
    strncpy(new_node->value, s, len - 1);
    new_node->value[len - 1] = '\0';
    INIT_LIST_HEAD(&(new_node->list));
    list_add(&(new_node->list), head);
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head || !s)
        return false;
    element_t *new_node = malloc(sizeof(element_t));
    if (!new_node)
        return false;
    size_t len = strlen(s) + 1;
    new_node->value = malloc(len * sizeof(char));
    if (!new_node->value) {
        q_release_element(new_node);
        return false;
    }
    strncpy(new_node->value, s, len - 1);
    new_node->value[len - 1] = '\0';
    INIT_LIST_HEAD(&(new_node->list));
    list_add_tail(&(new_node->list), head);
    return true;
}

/* Remove an element from head of queue */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *remove_node = list_first_entry(head, element_t, list);
    if (bufsize > 0 && sp && remove_node->value) {
        strncpy(sp, remove_node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_del_init(&(remove_node->list));
    return remove_node;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    element_t *remove_node = list_last_entry(head, element_t, list);
    if (bufsize > 0 && sp && remove_node->value) {
        strncpy(sp, remove_node->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    list_del_init(&(remove_node->list));
    return remove_node;
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head || list_empty(head))
        return 0;

    int len = 0;
    struct list_head *li;

    list_for_each(li, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head)) {
        return false;
    }
    struct list_head *slow = head;
    struct list_head *fast = head->next;
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct list_head *del_list = slow->next;
    slow->next = del_list->next;
    del_list->next->prev = slow;
    element_t *del_node = list_entry(del_list, element_t, list);
    q_release_element(del_node);
    return true;
    /*
    slow = head->next;
    fast = head->next->next;
    while (fast != head && fast->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    list_del(slow);
    element_t *element = list_entry(slow, element_t, list);
    q_release_element(element);
    */
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    // https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    if (!head || list_empty(head))
        return;

    struct list_head *first = head->next;
    while (first != head && first->next != head) {
        list_move(first, first->next);
        first = first->next;
    }
    /*
    struct list_head *slow = head;
    struct list_head *fast = head->next;
    while (fast != head && fast->next != head) {
        struct list_head *tmp = fast->next->next;
        fast->next->next = fast;
        slow->next = fast->next;
        tmp->prev = fast;
        fast->prev = fast->next;
        fast->next->prev = slow;
        fast->next = tmp;
        slow = fast;
        fast = tmp;
    }
    */
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
    struct list_head *cur = head;
    struct list_head *node;
    do {
        node = cur->next;
        cur->next = cur->prev;
        cur->prev = node;
        cur = node;
    } while (cur != head);
}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
