/***************************************************************************
 * Linked List test - C
 * 
 * 
 *  
 * Author : nlantau
 * Date   : 2020-11-28
 * Changed: 2020-11-28
 **************************************************************************/

/***** DEFINITIONS ********************************************************/

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** INCLUDES - ALGO & READ *********************************************/

#include "linked_list.h"

/***** PROTOTYPES *********************************************************/

Data newData(char *c);
void insert(NodePtr last, Data d);
void delete (NodePtr *top, Data d);

/***** GLOBALS ************************************************************/

/***** MAIN ***************************************************************/

int main(int argv, char **argc)
{
    NodePtr top;

    top = makeNode(newData("first"));
    top->next = NULL;

    insert(top, newData("Hejsan"));
    insert(top, newData("hoppsan"));
    insert(top, newData("hello"));
    insert(top, newData("123"));

    printf("top: %s\n", top->data.symbol);
    print_list(top);

    printf("-----> Delete top\n");
    delete (&top, newData("NULL"));

    insert(top, newData("Last"));
    printf("top: %s\n", top->data.symbol);
    print_list(top);
    return 0;
}

Data newData(char *c)
{
    Data temp;
    temp.symbol = c;
    return temp;
}

/***** INSERT *************************************************************
 * Insert at the end of linked list
 * 
 * ***********************************************************************/
void insert(NodePtr top, Data d)
{
    NodePtr new = makeNode(d);
    new->next = top->next;
    top->next = new;
}

/***** DELETE *************************************************************
 * Delete head of linked list
 * 
 * ***********************************************************************/
void delete (NodePtr *top, Data d)
{
    NodePtr temp;
    temp = (*top);
    *top = (*top)->next;
    free(temp);
}