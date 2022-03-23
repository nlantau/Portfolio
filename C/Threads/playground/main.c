/***************************************************************************
 * Playground - Readlines and what not...
 *
 * Created: 2022-03-23
 * Updated: 2022-03-23
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

/***** Include section ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***** Macro Definitions **************************************************/

/***** Typedefs ***********************************************************/

/***** Function prototypes ************************************************/
static void print_compiler_version(void);
static char **readlines(char *path);

/***** Constants **********************************************************/

/***** Variables **********************************************************/

/***** MAIN ***************************************************************/
int main(int argc, char *argv[])
{
    const char a = 'A';
    char const *const pa = &a;

    fprintf(stdout, "%c\n", *pa);

    print_compiler_version();

    fprintf(stdout, "> Reading file...\n\n");
    char **lines = readlines("text.txt");

    printf("\n\n> Readlines:\n");

    for (int i = 0; lines[i] != NULL; ++i, printf("\n")) {
        for (int j = 0; lines[i][j] != '\0'; ++j)
            printf("%c", lines[i][j]);
        free(lines[i]); lines[i] = NULL;
    }

    free(lines); lines = NULL;


    return 0;

} /* End main() */


static char **readlines(char *path)
{
    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "> Could not find: %s. Exiting.\n", path);
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
    return rows;;
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

