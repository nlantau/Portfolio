/***************************************************************************
 * Stack Source file
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * Author : nlantau
 * Date   : 2020-11-16
 * Changed: 2020-11-17
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "stack.h"

/***** ALGORITHM **********************************************************/

Stack initStack()
{
    Stack sp = (Stack)malloc(sizeof(StackType));
    sp->top = NULL;
    return sp;
}

int empty(Stack S)
{
    return (S->top == NULL);

} /* End empty()*/

void push(Stack S, StackData d)
{
    NodePtr np = (NodePtr)malloc(sizeof(Node));
    np->data = d;
    np->next = S->top;
    S->top = np;

} /* End push() */

StackData pop(Stack S)
{
    if (empty(S))
    {
        fprintf(stderr, "> Attemp to pop an empty stack\n");
        exit(1);
    }
    StackData hold = S->top->data;
    NodePtr temp = S->top;
    S->top = S->top->next;
    free(temp);
    return hold;

} /* End pop() */