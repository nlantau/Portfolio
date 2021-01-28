/***************************************************************************
 * Quick Sort Iterative Median of Three in C - Header File
 * 
 *  
 * Author : nlantau
 * Date   : 2020-11-16
 * Changed: 2020-11-21
 **************************************************************************/

#ifndef QS_ITER_H_
#define QS_ITER_H_

#define RANDOM 0
#define MED_OF_THREE 1

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/***** INCLUDES - ALGO & READ *********************************************/

#include "../Templates/stack.h"

/***** PROTOTYPES *********************************************************/

extern StackData newStackData(int, int);
void swap(int *, int, int);
void quick_sort_mot(int *, int, int);
int partition1(int *, int, int);
int partition2(int *arr, int low, int high);
int random1(int, int);
int med_of_three(int *arr, int l, int h);

/***** END ****************************************************************/

#endif /* QS_ITER_H_ */