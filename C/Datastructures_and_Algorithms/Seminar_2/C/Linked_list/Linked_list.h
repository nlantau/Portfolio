/***************************************************************************
 * Linked List Header File
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * Author : nlantau
 * Date   : 2020-12-02
 * Changed: 2020-12-02
 **************************************************************************/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

/***** INCLUDES ***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/***** PROTOTYPES *********************************************************/
typedef struct
{
    char name[20];
    char address[20];
} LinkData;

typedef struct node
{
    LinkData data;
    struct node *next;
} Node, *NodePtr;

typedef struct linked_type
{
    NodePtr top;
} LinkedType, *LinkedList;

LinkedList init_linked_list(void);
int empty(LinkedList L);
void insert_node(LinkedList L, LinkData d);
void remove_node(LinkedList L, char *name);
void print_list(LinkedList np);
int length(NodePtr top);
NodePtr get_node(LinkedList L, int index);

/***** END ****************************************************************/

#endif /* LINKED_LIST_H_ */