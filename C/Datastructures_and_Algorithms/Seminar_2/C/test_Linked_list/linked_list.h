/***************************************************************************
 * Linked List Header File
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 *  
 * Author : nlantau
 * Date   : 2020-11-28
 * Changed: 2020-11-28
 **************************************************************************/

#ifndef LINKED_LIST_H_
#define LINKED_LIST_H_

/***** INCLUDES ***********************************************************/

#include <stdlib.h>
#include <stdio.h>

/***** PROTOTYPES *********************************************************/

typedef struct
{
    char *symbol;
} Data;

typedef struct node
{
    Data data;
    struct node *next;
} Node, *NodePtr;

int length(NodePtr top);
NodePtr search(NodePtr top, Data key);
NodePtr makeNode(Data d);
void print_list(NodePtr np);
/***** END ****************************************************************/

#endif /* LINKED_LIST_H_ */