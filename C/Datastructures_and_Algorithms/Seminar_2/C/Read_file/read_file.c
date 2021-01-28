/***************************************************************************
 * Read file in C - Source File
 * Data obtained from text file
 * Returns dynamically allocated pointer
 *  
 * Author : nlantau
 * Date   : 2020-11-10
 * Changed: 2020-11-10
 *
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "read_file.h"

/***** FUNCTIONS **********************************************************/

/*
1. Open file and count number of lines
2. Allocate memory for all the numbers (calculate size with number of lines)
3. Return int * 
*/

int *allocate_memory(char *argv_filename, int *len)
{
    
    int *data = (int *)malloc(sizeof(int) * get_nr_lines(argv_filename, len));
    int i = 0;

    FILE *fp = fopen(argv_filename, "r");

    if (!fp)
    {
        fprintf(stderr, "> Could not open file: %s\n", argv_filename);
        exit(1);
    }

    while (!feof(fp))
    {
        fscanf(fp, "%d", &data[i++]);
    }

    fclose(fp);

    return data;

} /* End allocate_memory() */

int get_nr_lines(char *filename, int *len)
{
    int count = 1;
    char c;

    FILE *fp = fopen(filename, "r");
    if (!fp)
    {
        fprintf(stderr, "> Could nto open file: %s\n", filename);
        exit(1);
    }

    for (c = getc(fp); c != EOF; c = getc(fp))
    {
        if (c == '\n')
        {
            count++;
        }
    }
    *len = count;
    fclose(fp);
    return count;

} /* End get_nr_lines() */