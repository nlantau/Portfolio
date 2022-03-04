/***************************************************************************
 * Playground - pthreads
 *
 * Created: 2022-03-03
 * Updated: 2022-03-04
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

/***** Include section ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

/***** Macro Definitions **************************************************/

/***** Typedefs ***********************************************************/
typedef enum _e_return {
    RET_OK = 1,
    RET_ERROR = 0,
} e_return;

/***** Function prototypes ************************************************/
e_return loopback_stdin(void *arg);
e_return write_time_file(void *arg);

/***** Constants **********************************************************/
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

/***** Variables **********************************************************/
uint8_t counter = 20;

/***** MAIN ***************************************************************/

int main(int argc, char *argv[])
{
    pthread_t thread1, thread2;
    uint8_t iret1, iret2;

    iret1 = pthread_create(&thread1, NULL, (void *)write_time_file, NULL);
    iret2 = pthread_create(&thread2, NULL, (void *)loopback_stdin, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    fprintf(stdout,
            "> iret1: %d, iret2: %d, counter: %d\n",
            iret1, iret2, counter);

    return 0;

} /* End main() */

e_return loopback_stdin(void *arg)
{
    int8_t cont = 1;
    while (cont >= 0) {
        char buf[100];
        uint8_t len;
        fprintf(stdout, "> Enter name: ");
        fflush(stdout);

        if (!fgets(buf, sizeof(buf), stdin)) return RET_ERROR;

        len = strlen(buf);

        if (buf[len - 1] == '\n') {
            buf[--len] = '\0';
        } else {
            scanf("%*[^\n]");
            getchar();
        }

        fprintf(stdout, ">> %s\n", buf);

        pthread_mutex_lock(&mutex1);
        cont = counter;

        fprintf(stdout, ">> Counter: %d\n", counter);

        pthread_mutex_unlock(&mutex1);

    }

    return RET_OK;

} /* end loopback_stdin() */

e_return write_time_file(void *arg)
{
    int8_t cont = 1;
    while (cont >= 0) {

        pthread_mutex_lock(&mutex1);
        cont = counter--;
        pthread_mutex_unlock(&mutex1);

        FILE *out;

        if (!(out = fopen("output.txt", "a"))) {
            fprintf(stderr, "> Could not open file\n");
            fclose(out);
            return RET_ERROR;
        }

        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[64];

        strftime(s, sizeof(s), "%c", tm);

        fprintf(out, "%s\n", s);
        fclose(out);

        sleep(1);
    }

    return RET_OK;
} /* end write_time_file() */


/* End main.c */

