/***************************************************************************
 * Linked List Source file
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * Author : nlantau
 * Date   : 2020-11-28
 * Changed: 2020-11-28
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "linked_list.h"

/***** ALGORITHM **********************************************************/

void print_list(NodePtr np)
{
    while (np != NULL)
    {
        printf("%s\n", np->data.symbol);
        np = np->next;
    }
}

int length(NodePtr top)
{
    int n = 0;
    NodePtr curr = top;
    while (curr != NULL)
    {
        n++;
        curr = curr->next;
    }
    return n;
} /* End length() */

NodePtr makeNode(Data d)
{
    NodePtr np = (NodePtr)malloc(sizeof(Node));
    np->data = d;
    np->next = NULL;
    return np;
}
NodePtr search(NodePtr top, Data key)
{
    while (top != NULL && key.symbol != top->data.symbol)
    {
        top = top->next;
    }
    return top;
} /* End search() */