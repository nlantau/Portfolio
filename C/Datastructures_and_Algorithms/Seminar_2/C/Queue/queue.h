/***************************************************************************
 * Queue Header File
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * Author : nlantau
 * Date   : 2020-12-02
 * Changed: 2020-12-02
 **************************************************************************/

#ifndef QUEUE_H_
#define QUEUE_H_

/***** INCLUDES ***********************************************************/

#include <stdlib.h>
#include <stdio.h>

/***** PROTOTYPES *********************************************************/

typedef struct
{
    int num;
} QueueData;

typedef struct node
{
    QueueData data;
    struct node *next;
} Node, *NodePtr;

typedef struct
{
    NodePtr head, tail;
} QueueType, *Queue;

NodePtr make_node(char *s);
Queue init_queue(void);
QueueData dequeue(Queue Q);
int empty(Queue q);
void print_list(Queue np);
void enqueue(Queue Q, char *s);

/***** END ****************************************************************/

#endif /* QUEUE_H_ */