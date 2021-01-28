/***************************************************************************
 * Queue Source file
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * Author : nlantau
 * Date   : 2020-12-02
 * Changed: 2020-12-02
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "queue.h"

/***** ALGORITHM **********************************************************/

void enqueue(Queue Q, char *s)
{
    NodePtr np = make_node(s);
    if (empty(Q))
    {
        Q->head = np;
        Q->tail = np;
    }
    else
    {
        Q->tail->next = np;
        Q->tail = np;
    }

} /* End enqueue() */

QueueData dequeue(Queue Q)
{
    if (empty(Q))
    {
        fprintf("Attempt to remove from empty queue\n");
        exit(1);
    }
    QueueData hold = Q->head->data;
    NodePtr temp = Q->head;

    Q->head = Q->head->next;
    if (Q->head == NULL)
    {
        Q->tail = NULL;
    }
    free(temp);
    return hold;

} /* End dequeue() */

int empty(Queue Q)
{
    return (Q->head == NULL);

} /* End empty() */

Queue init_queue(void)
{
    Queue qp = (Queue)malloc(sizeof(QueueType));
    qp->head = NULL;
    qp->tail = NULL;
    return qp;

} /* End init_queue() */

NodePtr make_node(char *s)
{
    NodePtr np = (NodePtr)malloc(sizeof(Node));
    strcpy(np->data, s);
    np->next = NULL;
    return np;

} /* End make_node() */

void print_list(Queue np)
{
    NodePtr temp = (NodePtr)malloc(sizeof(Node));
    temp = np->head;

    while (temp != NULL)
    {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
    free(temp);

} /* End print_list() */