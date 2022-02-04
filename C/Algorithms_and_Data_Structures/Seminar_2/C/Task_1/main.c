/***************************************************************************
 * Balancing Symbols - C
 * 
 * Task 1 of Seminar 2 in DT256C
 * 
 * Author : nlantau
 * Date   : 2020-11-26
 * Changed: 2020-12-02
 **************************************************************************/

/***** DEFINITIONS ********************************************************/

#define PRINT_FS 0

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** INCLUDES - ALGO & READ *********************************************/

#include "../Stack/stack.h"
#include "../Read_file/read_text_file.h"

/***** PROTOTYPES *********************************************************/

int balance_symbols(char *s);
StackData newStackData(char c);

/***** GLOBALS ************************************************************/

/***** MAIN ***************************************************************/

int main(int argv, char **argc)
{
    char *fs;
    if (argv == 1)
    {
        fprintf(stderr, "> Could not open file\n");
        return -1;
    }
    if ((fs = read_file(argc[1])) == NULL)
    {
        fprintf(stderr, "> char *fs error\n");
        return -1;
    }

#if PRINT_FS
    printf("%s", fs);
#endif

    int bs = balance_symbols(fs);
    (bs == 1) ? printf("\nSuccess\n") : printf("\nError\n");

    free(fs);
    return 0;

} /* End main() */

int balance_symbols(char *s)
{
    Stack S = initStack();
    int balance = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        if (s[i] == '/' && s[i + 1] == '*')
        {
            push(S, newStackData(s[i]));
            push(S, newStackData(s[i + 1]));
            balance += 2;
            while (s[i++] != '*' && s[i + 1] != '/')
            {
                ;
            }
        }
        else if (s[i] == '*' && s[i + 1] == '/')
        {
            StackData first = pop(S);
            StackData second = pop(S);
            if (first.symbol == '*' && second.symbol == '/')
            {
                balance -= 2;
            }
        }
        else if (s[i] == '/' && s[i + 1] == '/')
        {
            push(S, newStackData(s[i]));
            push(S, newStackData(s[i + 1]));
            balance += 2;
            StackData first = pop(S);
            StackData second = pop(S);
            balance -= 2;
            while (s[i++] != '\n')
            {
                ;
            }
        }
        else if (s[i] == '[' || s[i] == '{' || s[i] == '(')
        {
            push(S, newStackData(s[i]));
            balance += 1;
        }
        else if (s[i] == ']' || s[i] == '}' || s[i] == ')')
        {
            StackData bracket = pop(S);
            if (bracket.symbol == '[' || bracket.symbol == '{' || bracket.symbol == '(')
            {
                balance -= 1;
            }
        }
        else
        {
            /* Nothing */
        }
    }
    printf("\nBalance: %d\n", balance);
    while (!(empty(S)))
    {
        printf("> Left in stack: %c\n", pop(S).symbol);
    }
    return (balance == 0);

} /* End balance_symbols() */

StackData newStackData(char c)
{
    StackData temp;
    temp.symbol = c;
    return temp;

} /* End newStackData() */