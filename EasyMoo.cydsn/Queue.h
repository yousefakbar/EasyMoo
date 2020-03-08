/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue* queue_t;

typedef struct Node
{
    void *data;
    struct Node *next;
}*node_t;

struct queue
{
    node_t first;
    node_t last;
    int size;
};

queue_t queue_create(void)
{
    queue_t queue;

    queue = malloc(sizeof(*queue));
    queue->first = queue->last = NULL;
    queue->size = 0;
    return queue;
}

int queue_destroy(queue_t queue)
{
    if (!queue  || queue->size != 0)
    {
        return -1;
    }
    free(queue);
    return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
    node_t pushed;

    if (!queue  || !data )
    {
        return -1;
    }

    pushed = malloc(sizeof(*pushed));
    if (!pushed )
    {
        return -1;
    }
    pushed->data = data;
    pushed->next = NULL;

    if (queue->last != NULL)
    {
        queue->last->next = pushed;
    }
    else
    {
        queue->first = pushed;
    }

    queue->last = pushed;
    queue->size++;
    return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
    node_t popped, next;

    if (!queue || !data || queue->size == 0)
    {
        return -1;
    }

    popped = queue->first;
    *data = popped->data;
    next = popped->next;
    free(popped);

    queue->first = next;
    queue->size--;
    if (queue->size == 0)
    {
        queue->last = NULL;
    }
    return 0;
}

int queue_delete(queue_t queue, void *data)
{
    node_t current, previous, next;

    if (!queue  || !data  || queue->size == 0)
    {
        return -1;
    }

    for (current = queue->first, previous = NULL;
         current != NULL && current->data != data;
         previous = current, current = current->next)
        ;
    if (!current )
    {
        return -1;
    }
    next = current->next;
    free(current);

    if (!previous )
    {
        queue->first = next;
    }
    else
    {
        previous->next = next;
    }
    queue->size--;
    if (queue->size == 0)
    {
        queue->last = NULL;
    }
    return 0;
}

typedef int (*queue_func_t)(void *data, void *arg);

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
    node_t current;
    if (data != NULL)
    {
        *data = NULL;
    }

    if (!queue  || !func )
    {
        return -1;
    }

    for (current = queue->first;
         current != NULL && func(current->data, arg) != 1;
         current = current->next);    
    if (current != NULL && data != NULL)
    {
        *data = current->data;
    }

    return 0;
}

int queue_length(queue_t queue)
{
    return queue ? queue->size : -1;
}

/* [] END OF FILE */
