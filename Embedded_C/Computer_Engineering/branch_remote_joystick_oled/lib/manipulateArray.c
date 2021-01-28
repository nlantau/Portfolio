/*
* array_algos.c
*
* Created: 2020-09-18 14:07:48
*  Author: nlantau
*/
#include "manipulateArray.h"

void manipulateArray_replaceTrailingIndexesWithSpace(uint8_t bufSize, char *buf)
{
	uint8_t i = 0;
	while (i < bufSize)
	{
		(i < 5) ? (buf[i] = buf[i]) : (buf[i] = ' ');
		i++;
	}
	buf[bufSize - 1] = '\0';

} /* End manipulate_buff_adjust_decimal() */

/**************************************************************************
 *	manipulateBufferFillEmptyWithSpace()
 *	params: 
 *************************************************************************/
void manipulateArray_digitsToStringFillEmptyWithSpace(uint8_t bufSize, char *buf)
{

	for (uint8_t i = 0; i < bufSize; i++)
	{
		if ((buf[i] > 44) && (buf[i] < 58) || (buf[i] == 'X' || buf[i] == 'Y')) // Allows ASCII value 44 < x < 58; All digits and [-./]
		{
			buf[i] = buf[i];
		}
		else
		{
			buf[i] = ' ';
		}
	}
	buf[bufSize - 1] = 0;

} /* End manipulate_buff_loop_rx() */

void manipulateArray_parsePositiveFloatToString(char *_buf, float val)
{
	int16_t tmp_int = (int16_t)val;
	float tmp_frac = val - tmp_int;
	int16_t tmp_int2 = trunc(tmp_frac * 1000);

	if (tmp_int < 2)
	{
		tmp_int = 0;
		tmp_int2 = 0;
		sprintf(_buf, "%d.%d  ", tmp_int, tmp_int2);
	}
	else
	{
		sprintf(_buf, "%d.%1d", tmp_int, tmp_int2);
	}
} /* End manipulate_buff_float() */

void manipulateArray_parseDoubleToString(char *_buf, double val)
{

	/*********************************
	 * 
	 *	TODO: Sort this mess... 
	 * 
	 * 
	 * *******************************/
	int16_t tmp_int = (int16_t)val;
	double tmp_frac; // = val - tmp_int;
	(val <= 0) ? (tmp_frac = (val + tmp_int) / -1) : (tmp_frac = val - tmp_int);
	int16_t tmp_int2 = trunc(tmp_frac * 1000);

	if (tmp_int != tmp_int)
	{
		tmp_int = 0;
		tmp_int2 = 0;
		sprintf(_buf, "%d.%d  ", tmp_int, tmp_int2);
	}
	else
	{
		sprintf(_buf, "%d.%1d", tmp_int, tmp_int2);
	}
} /* End manipulate_buff_float() */