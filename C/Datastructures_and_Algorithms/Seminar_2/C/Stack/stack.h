/***************************************************************************
 * Stack Header File
 * 
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 *  
 * Author : nlantau
 * Date   : 2020-11-16
 * Changed: 2020-12-01
 **************************************************************************/

#ifndef STACK_H_
#define STACK_H_

/***** INCLUDES ***********************************************************/

#include <stdlib.h>
#include <stdio.h>

/***** PROTOTYPES *********************************************************/

typedef struct
{
    char symbol;
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
StackData put_me_in_source_file(char c);

/***** END ****************************************************************/

#endif /* STACK_H_ */