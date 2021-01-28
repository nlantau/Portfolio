/***************************************************************************
 *  ManipulateArray Header
 *
 *
 *	Created: 2020-09-18
 *  Updated: 2020-10-06
 *  Author: nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

#ifndef MANIPULATE_ARRAY_H_
#define MANIPULATE_ARRAY_H_
#ifndef F_CPU
#define F_CPU 16000000UL
#endif

/***** Include section ****************************************************/

#include <math.h>
#include <stdio.h>

/***** Function prototypes ************************************************/

void manipulateArray_replaceTrailingIndexesWithSpace(uint8_t bufSize, char *buf);
void manipulateArray_digitsToStringFillEmptyWithSpace(uint8_t bufSize, char *buf);
void manipulateArray_parsePositiveFloatToString(char *_buf, float val);
void manipulateArray_parseDoubleToString(char *_buf, double val);

#endif /* MANIPULATE_ARRAY_H */