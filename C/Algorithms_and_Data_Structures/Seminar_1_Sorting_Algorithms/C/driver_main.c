/***************************************************************************
 * Driver Code for running various algorithms in C
 * 
 * Data obtained from text file via 'read_file.c'
 * Text file needs to be passed to argv
 * 
 *  
 * Author : nlantau
 * Date   : 2020-11-09
 * Changed: 2020-11-22
 *
 * 
 * Information:
 * CSV                surrounds STDERR which is used for printing
 *                    the amount of numbers being sorted and
 *                    the amount of time it took to sort them
 *                    (recommended for testing)
 * PREV_INCLUDES      surrounds not current includes and functions
 *                    (a bit unnecessary perhaps, but why not)
 * STOUT              surrounds output to STDOUT
 *                    (not recommended for actual tests)
 * STDOUT_ALL_NUMBERS surrounds loop that prints ALL sorted numbers
 *                    (definately not recommended for actual tests)
 **************************************************************************/

/***** DEFINITIONS ********************************************************/

#define PREV_INCLUDES 0
#define STDOUT 0
#define STDOUT_ALL_NUMBERS 1
#define CSV 1
#define STDOUT_BIN_SEARCH 0

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

/***** INCLUDES - ALGO & READ *********************************************/

#include "Templates/read_file.h"
#include "Templates/stack.h"
#include "QS_iter/QS_iter.h"

/***** INCLUDES - OLDIES **************************************************/

#if PREV_INCLUDES
#include "BS_rec/BS_rec.h"
#include "IS_rec/IS_rec.h"
#include "MS_iter/MS_iter.h"
#endif

/***** CONSTANTS **********************************************************/

const int binary_number = 12345678;

/***** MAIN ***************************************************************/

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "> Must provide a filename to read\n");
        exit(1);
    }
    int len = 0;
    int *data = allocate_memory(argv[1], &len);
    int *pdata_start;

    /* Store original pointer position in pdata_start */
    pdata_start = data;

    /***** Algorithm Goes Here ********************************************/

#if PREV_INCLUDES
    char *algo_name = "Quick Sort Recursive";
    char *algo_name = "Insertion Sort Recursive";
    insertionSortRecursive(data, len);
    merge_sort(data, len);
    int result = binary_search(data, 0, len - 1, binary_number);
#endif
    struct timespec start, end;

    char *algo_name = "Quick Sort - Iterative";
    clock_gettime(CLOCK_MONOTONIC, &start);

    quick_sort_mot(data, 0, len - 1);

    clock_gettime(CLOCK_MONOTONIC, &end);

#if STDOUT_BIN_SEARCH
    fprintf(stdout, "> %d found at %d\n", binary_number, result);
#endif

#if STDOUT_ALL_NUMBERS
    int i = 0;
    while (i < len - 1)
    {
        printf("%d, ", data[i++]);
    }
    printf("%d\n", data[i++]);
#endif

    /*********************************************************************/

    data = pdata_start;

    free(data);
    data = NULL;

    double time_taken;
    time_taken = (end.tv_sec - start.tv_sec) * 1e9;
    time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;

#if STDOUT
    printf("\n> ------------ RESULT ------------------\n");
    printf("> Amount of integers sorted: %d\n", len);
    printf("> Time spent for %s: %f seconds\n", algo_name, algo_time);
#endif

#if CSV
    fprintf(stderr, "%d,", len);
    fprintf(stderr, "%f\n", time_taken);
#endif

    return 0;

} /* End main() */
