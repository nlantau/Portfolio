/***************************************************************************
 * Read file in C - Header
 * Data obtained from text file
 * Returns dynamically allocated pointer
 *  
 * Author : nlantau
 * Date   : 2020-11-10
 * Changed: 2020-11-10
 *
 **************************************************************************/

/***** INCLUDES ***********************************************************/
#ifndef READ_FILE_H
#define READ_FILE_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/***** PROTOTYPES *********************************************************/

int get_nr_lines(char *filename, int *len);
int *allocate_memory(char *argv_filename, int *len);

#endif /* READ_FILE_H */