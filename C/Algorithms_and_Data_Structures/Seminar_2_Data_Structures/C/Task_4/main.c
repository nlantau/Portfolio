/***************************************************************************
 * Address Book using a Linked List - C
 * 
 * Task 4 of Seminar 2 in DT256C
 * 
 * Author : nlantau
 * Date   : 2020-12-02
 * Changed: 2020-12-02
 **************************************************************************/

/***** DEFINITIONS ********************************************************/

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** INCLUDES - ALGO & READ *********************************************/

#include "../Linked_list/Linked_list.h"

/***** PROTOTYPES *********************************************************/

LinkData new_LL_data(char *name, char *address);
int display_menu(void);
char *get_input(char *n, char *msg);
void get_index(LinkedList L);

/***** GLOBALS ************************************************************/

/***** MAIN ***************************************************************/

int main(int argv, char **argc)
{
    LinkedList LL = init_linked_list();
    int choice;
    char name[20];
    char address[20];

    printf("---> Welcome to Address Book <---\n");

    while (1)
    {
        choice = display_menu();
        switch (choice)
        {
        case 1:
            print_list(LL);
            break;
        case 2:
            insert_node(LL, new_LL_data(get_input(name, "name"), get_input(address, "address")));
            break;
        case 3:
            remove_node(LL, get_input(name, "name"));
            break;
        case 4:
            get_index(LL);
            break;
        case 0:
            exit(0);
            break;
        }
    }

    free(LL);
    return 0;

} /* End main() */

void get_index(LinkedList L)
{
    NodePtr temp;
    int i;
    printf("> Enter index: ");
    scanf("%d", &i);
    getchar();
    if ((temp = get_node(L, i)) == NULL)
    {
        fprintf(stderr, "> Error, index\n");
        return;
    }
    printf("> Name: %s\n> Address: %s\n", temp->data.name, temp->data.address);
}

char *get_input(char *n, char *msg)
{
    /* Clear previous usage of char * */
    memset(n, 0, 20);

    printf("> Enter %s: ", msg);
    if (fgets(n, 20, stdin) == NULL)
    {
        fprintf(stderr, "Error reading %s \n", msg);
    }
    /* Replace devoured newline */
    n[strcspn(n, "\n")] = '\0';
    return n;

} /* End get_input() */

int display_menu(void)
{
    int choice;
    printf("===========================\n");
    printf("> (1). View Address Book\n");
    printf("> (2). Add contact\n");
    printf("> (3). Remove contact\n");
    printf("> (4). Get contact by index\n");
    printf("> (0). Exit\n");
    printf("===========================\n");

    printf(">> Enter choice: \n");

    /* This bastard needs getchar() to clear the buffer */
    scanf("%d", &choice);
    getchar();
    return choice;

} /* End display_menu() */

LinkData new_LL_data(char *name, char *address)
{
    LinkData temp;
    strcpy(temp.name, name);
    strcpy(temp.address, address);
    return temp;

} /* End new_LL_data() */