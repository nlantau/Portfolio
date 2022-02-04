/***************************************************************************
 * Binary Search Recursive in C - Source File
 * 
 * Algorithm inspired by the description given in
 * 'Advanced Topics in C' by Noel Kalicharan
 * 
 * 
 * Author : nlantau
 * Date   : 2020-11-09
 * Changed: 2020-11-21
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "BS_rec.h"

/***** ALGORITHM **********************************************************/

int binary_search(int *arr, int start, int end, int target_value)
{
    int m;
    if (start > end)
    {
        return -1;
    }

    m = (start + end) / 2;

    if (target_value == arr[m])
    {
        return m;
    }
    else if (target_value > arr[m])
    {
        return binary_search(arr, m + 1, end, target_value);
    }
    else if (target_value < arr[m])
    {
        return binary_search(arr, start, m - 1, target_value);
    }
    return -2;
}