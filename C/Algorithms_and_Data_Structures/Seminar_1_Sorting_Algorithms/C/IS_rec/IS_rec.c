/***************************************************************************
 * Insertion Sort Recursive C - Source File
 *
 * Stolen from: https://www.geeksforgeeks.org/recursive-insertion-sort/ 
 *  
 * Author : Sahil Chhabra
 * Thief  : nlantau
 * Date   : 2020-11-21
 * Changed: 2020-11-21
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "IS_rec.h"

/***** ALGORITHM **********************************************************/

void insertionSortRecursive(int *arr, int n)
{
    if (n <= 1)
    {
        return;
    }

    insertionSortRecursive(arr, n - 1);

    int last = arr[n - 1];
    int j = n - 2;

    /* Move elements of arr[0..i-1], that are 
	greater than key, to one position ahead 
	of their current position */
    while (j >= 0 && arr[j] > last)
    {
        arr[j + 1] = arr[j];
        j--;
    }
    arr[j + 1] = last;

} /* End insertionSortRecursive() */