/***************************************************************************
 * Merge Sort Iterative Median of Three in C - Header File
 * 
 *  
 * Author : nlantau
 * Date   : 2020-11-16
 * Changed: 2020-11-19
 **************************************************************************/

#ifndef MS_ITER_H_
#define MS_ITER_H_

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

/***** INCLUDES - ALGO & READ *********************************************/

/***** PROTOTYPES *********************************************************/

void merge(int arr[], int l, int m, int r);
int min(int x, int y);
void merge_sort(int arr[], int n);

/***** END ****************************************************************/

#endif /* MS_ITER_H_ */