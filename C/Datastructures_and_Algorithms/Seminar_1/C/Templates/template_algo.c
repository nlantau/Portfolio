/***************************************************************************
 * Template for reading text file with numbers in C
 * Data obtained from text file via 'read_file.c'
 * Text file needs to be passed to argv
 * 
 *  
 * Author : nlantau
 * Date   : 2020-11-10
 * Changed: 2020-11-10
 *
 * Time with UNIX and clock_t, redirecting stdout to dev null:
 * time ./executable <textfile> > /dev/null
 * 
 **************************************************************************/

/***** DEFINITIONS ********************************************************/

#define STDOUT 0

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "read_file.h"

/***** PROTOTYPES *********************************************************/

/***** MAIN ***************************************************************/

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        fprintf(stderr, "> Must provide a filename to read\n");
        exit(1);
    }

    int *data = allocate_memory(argv[1]);
    int *pdata_start;

    /* Store original pointer position in pdata_start */
    pdata_start = data;

    /***** Algorithm Goes Here ********************************************/

    // data += 100;
    char *algo_name = "Quick Sort";
    static int nbr_elements = 1000000;

    clock_t algo_start = clock();

    /* Function Call goes here */

    clock_t algo_done = clock();

#if STDOUT
    int i = 0;
    while (i < nbr_elements)
        printf("%d\n", data[i++]);
#endif
    /*********************************************************************/

    double algo_time = (double)(algo_done - algo_start) / CLOCKS_PER_SEC;

    printf("\n> ------------ RESULT ------------------\n");
    printf("> Amount of integers sorted: %d\n", nbr_elements);
    printf("> Time spent for %s: %f seconds\n", algo_name, algo_time);

    data = pdata_start;
    free(data);
    data = NULL;

    return 0;
}

/***** FUNCTIONS **********************************************************/

/***** ALGORITHM **********************************************************/

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;

} /* End swap() */

int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);

} /* End partition() */

void quick_sort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);

        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }

} /* End quick_sort() */

/***** TODO ****************************************************************
 * 
 * Implement some sort of quick_sort_simple()
 * 
 *
 * ************************************************************************/
