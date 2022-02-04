/***************************************************************************
 * Linked List Source file
 * 
 * Algorithm somewhat inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * Author : nlantau
 * Date   : 2020-12-02
 * Changed: 2020-12-02
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "Linked_list.h"

/***** ALGORITHM **********************************************************/

LinkedList init_linked_list(void)
{
    LinkedList LL = (LinkedList)malloc(sizeof(LinkedType));
    LL->top = NULL;
    return LL;

} /* End init() */

int empty(LinkedList L)
{
    return (L->top == NULL);

} /* End empty() */

void insert_node(LinkedList L, LinkData d)
{
    // printf("> Adding contact \"%s\"\n", d.name);
    NodePtr np = (NodePtr)malloc(sizeof(Node));
    np->data = d;
    np->next = L->top;
    L->top = np;

} /* End insert() */

void remove_node(LinkedList L, char *name)
{
    if (length(L->top) <= 1)
    {
        L->top = NULL;
        return;
    }
    NodePtr temp = L->top;
    NodePtr prev;
    // printf("> Removing contact: \"%s\"\n", name);

    temp = L->top;

    do
    {
        prev = temp;
        temp = temp->next;
    } while ((strcmp(temp->data.name, name)) != 0 && temp->next != NULL);

    if ((strcmp(temp->data.name, name)) == 0)
    {
        if (temp->next == NULL)
        {
            prev->next = NULL;
        }
        else
        {
            prev->next = temp->next;
        }
    }
    else if ((strcmp(L->top->data.name, name)) == 0)
    {
        L->top = L->top->next;
    }

} /* End remove() */


NodePtr get_node(LinkedList L, int index)
{
    NodePtr temp = (NodePtr)malloc(sizeof(Node));
    temp = L->top;

    int counter = 1;
    while (counter != index && counter <= length(L->top))
    {
        temp = temp->next;
        counter++;
    }
    if (counter > length(L->top))
    {
        return NULL;
    }

    return temp;

} /* End get_node() */

void print_list(LinkedList np)
{
    NodePtr temp = (NodePtr)malloc(sizeof(Node));
    temp = np->top;
    int index = 1;
    while (temp != NULL)
    {
        printf("%d. %s\t\t%s\n", index, temp->data.name, temp->data.address);
        temp = temp->next;
        index++;
    }
    printf("\n");
    free(temp);

} /* End print_list() */

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
}