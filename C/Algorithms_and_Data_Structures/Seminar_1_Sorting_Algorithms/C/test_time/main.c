/***************************************************************************
 * Test file for sleep duration in C
 * 
 *  
 * Author : nlantau
 * Date   : 2020-11-20
 * Changed: 2020-11-20
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

/***** PROTOTYPES *********************************************************/

void *func(void *arg);

/***** MAIN ***************************************************************/

int main(void)
{
    int i = 0;
    int msec = 0;
    pthread_t freddy;

    while (i < 10)
    {
        clock_t tic = clock();

        pthread_create(&freddy, NULL, func, (void *)&freddy);
        pthread_join(freddy, NULL);

        clock_t toc = clock() - tic;
        double res = (double)(toc)*1000 / CLOCKS_PER_SEC;

        printf("> Sleep: 1000 ms.\n> Actual: %f ms\n", res);

        i++;
    }
    i = 0;
    while (i < 10)
    {
        clock_t tic = clock();
        sleep(1);
        clock_t toc = clock() - tic;
        double res = ((double)(toc)*1000) / CLOCKS_PER_SEC;
        printf("> Sleep: 1000 ms.\n> Actual: %f ms\n", res);
        i++;
    }
}

void *func(void *arg)
{
    sleep(1);
    return NULL;
}