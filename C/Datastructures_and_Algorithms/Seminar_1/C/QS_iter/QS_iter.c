/***************************************************************************
 * Quick Sort Iterative in C - Source File
 *  
 * Algorithm heavily inspired by
 * 'Advanced Topics in C' by Noel Kalicharan
 *
 * Author : nlantau
 * Date   : 2020-11-16
 * Changed: 2020-11-15
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "QS_iter.h"

/***** ALGORITHM **********************************************************/

void swap(int *arr, int i, int j)
{
    int hold = arr[i];
    arr[i] = arr[j];
    arr[j] = hold;

} /* End swap() */

int med_of_three(int *arr, int l, int h)
{
    int m = (int)((l + h) / 2);

    if (arr[l] <= arr[m]) // L < M
    {
        if (arr[m] <= arr[h]) // L < M < H
        {
            return m;
        }
        else if (arr[h] <= arr[m]) // L < H < M
        {
            return h;
        }
    }
    else if (arr[m] <= arr[h]) // M < H
    {
        if (arr[h] <= arr[l]) // M < H < L
        {
            return h;
        }
        else if (arr[l] <= arr[h]) // M < L < H
        {
            return l;
        }
    }
    else if (arr[h] <= arr[l]) // H < L
    {
        if (arr[l] <= arr[m]) // H < L < M
        {
            return l;
        }
        else if (arr[m] <= arr[l]) // H < M < L
        {
            return m;
        }
    }

    fprintf(stderr, "> I should not be displayed\n");

} /* End med_of_three() */

int random1(int m, int n)
{
    int offset = rand() / (RAND_MAX + 1.0) * (n - m + 1);
    return m + offset;
} /* End random() */

StackData newStackData(int a, int b)
{
    StackData temp;
    temp.left = a;
    temp.right = b;
    return temp;

} /* End new_stack_data() */

void quick_sort_mot(int *arr, int low, int high)
{
    Stack S = initStack();
    push(S, newStackData(low, high));
    int stackItems = 1, maxStackItems = 1;

    while (!empty(S))
    {
        --stackItems;
        StackData d = pop(S);
        if (d.left < d.right) // if the sublist is > 1 element
        {
            int dp = partition2(arr, d.left, d.right); // dp = division point
            if (dp - d.left + 1 < d.right - dp)        // compare lengths of sublists
            {
                push(S, newStackData(dp + 1, d.right));
                push(S, newStackData(d.left, dp)); // Will pop next iteration and split into sublists
            }
            else
            {
                push(S, newStackData(d.left, dp));
                push(S, newStackData(dp + 1, d.right));
            }
            stackItems += 2; // two items added to stack
        }                    // end if
        if (stackItems > maxStackItems)
        {
            maxStackItems = stackItems;
        }
    } // end while

} /* End quick_sort_mot() */

int partition2(int *arr, int low, int high)
{
#if RANDOM
    swap(arr, low, random1(low, high));
#endif
#if !MED_OF_THREE
    swap(arr, low, med_of_three(arr, low, high)); // Set medof3 at arr[low]
#endif
#if 0
Using arr[low] as pivot:

Sublist example
___________________________________________________
| 53 | 12 | 98 | 63 | 18 | 32 | 80 | 46 | 72 | 21 |
--1----2----3----4----5----6----7----8----9----10--
pivot = 53
___________________________________________________
| 21 | 12 | 98 | 63 | 18 | 32 | 80 | 46 | 72 | 53 |
--1----2----3----4----5----6----7----8----9----10--
___________________________________________________
| 21 | 12 | 46 | 63 | 18 | 32 | 80 | 98 | 72 | 53 |
--1----2----3----4----5----6----7----8----9----10--

#endif

    int pivot = arr[low];
    --low;
    ++high;
    while (low < high)
    {
        do
        {
            --high;
        } while (arr[high] > pivot);
        do
        {
            ++low;
        } while (arr[low] < pivot);
        if (low < high)
        {
            swap(arr, low, high);
        }
    }
    return high;
} /* End partition2() */

/***** END ****************************************************************/