/***************************************************************************
 * Stack Source file
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * Author : nlantau
 * Date   : 2020-11-16
 * Changed: 2020-12-01
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "stack.h"

/***** ALGORITHM **********************************************************/

StackData put_me_in_source_file(char c)
{
    /* And change me depending on implementation */

    StackData temp;
    temp.symbol = c;
    return temp;

} /* End newStackData() */

Stack initStack()
{
    Stack sp = (Stack)malloc(sizeof(StackType));
    sp->top = NULL;
    return sp;

} /* End initStack() */

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