/***************************************************************************
 * Stack Header File
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 *  
 * Author : nlantau
 * Date   : 2020-11-16
 * Changed: 2020-11-17
 **************************************************************************/

#ifndef STACK_H_
#define STACK_H_

/***** INCLUDES ***********************************************************/

#include <stdlib.h>
#include <stdio.h>

/***** PROTOTYPES *********************************************************/

typedef struct
{
    int left;
    int right;
} StackData;

typedef struct node
{
    StackData data;
    struct node *next;
} Node, *NodePtr;

typedef struct stackType
{
    NodePtr top;
} StackType, *Stack;

Stack initStack();
int empty(Stack S);
void push(Stack S, StackData d);
StackData pop(Stack S);
/***** END ****************************************************************/

#endif /* STACK_H_ */