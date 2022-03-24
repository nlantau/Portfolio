/***************************************************************************
 * Playground - Readlines and threads. Returning char ** via some
 *              typecasting and what not...
 *
 * Created: 2022-03-23
 * Updated: 2022-03-24
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

/***** Include section ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/***** Macro Definitions **************************************************/

/***** Typedefs ***********************************************************/

/***** Function prototypes ************************************************/
static void print_compiler_version(void);
void *readlines(void *path);

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(int argc, char *argv[])
{
    int pret, i = 0, j;
    char **lines = NULL;
    void *vptr_return;
    pthread_t thread1;

    print_compiler_version();

    fprintf(stdout, "> Reading file...\n\n");

    pret = pthread_create(&thread1, NULL, readlines, "text.txt");
    
    if (!!pret) {
        fprintf(stderr, "> Thread error. Exiting.\n");
        exit(1);
    }

    pthread_join(thread1, &vptr_return);
    lines = (char**)vptr_return;

    printf("\n\n> Readlines:\n");

    for ( ; lines[i] != NULL; printf("\n"), free(lines[i]), lines[i++] = NULL)
        for (j = 0; lines[i][j] != '\0'; ++j)
            printf("%c", lines[i][j]);

    free(lines); lines = NULL;


    return 0;

} /* End main() */


void *readlines(void *path)
{
    char *p = (char*)path;
    FILE *fp = fopen(p, "r");
    if (!fp) {
        fprintf(stderr, "> Could not find: %s. Exiting.\n", p);
        exit(1);
    }

    int rows_index = 0, buffer_index = 0, lines = 1, cpl = 100;
    char **rows = calloc(lines, sizeof(char*)), *buffer = calloc(cpl, sizeof(char*));
    
    for (char c = getc(fp); c != EOF; c = getc(fp))
        if (c != '\n') {
            /* TODO: realloc buffer if buffer_index - 1 > cpl */
            buffer[buffer_index++] = c;
        } else {
            rows = realloc(rows, ++lines * sizeof(char*));
            rows[rows_index] = calloc(cpl, sizeof(char*));
            strcpy(rows[rows_index++], buffer);
            memset(buffer, 0, cpl);
            buffer_index = 0;
        }

    fclose(fp);
    pthread_exit((void*)rows);
}


static void print_compiler_version(void)
{
#ifdef __GNUC__
    printf ("gcc detected version %d.%d\n", __GNUC__, __GNUC_MINOR__);
#endif

#if __STDC_VERSION__ >=  201710L
  printf("We are using C18!\n");
#elif __STDC_VERSION__ >= 201112L
  printf("We are using C11!\n");
#elif __STDC_VERSION__ >= 199901L
  printf("We are using C99!\n");
#else
  printf("We are using C89/C90!\n");
#endif
}


/* End main.c */

