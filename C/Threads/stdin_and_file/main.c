/***************************************************************************
 * Playground - pthreads, syscall, FILE
 *
 * Created: 2022-03-03
 * Updated: 2022-03-16
 * Author : nlantau
 **************************************************************************/

/***** Include guard ******************************************************/

/***** Include section ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdatomic.h>
#include <sys/syscall.h>
#include <errno.h>

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
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

/***** Variables **********************************************************/
uint8_t counter = 20;
struct data
{
    int iret1;
    int iret2;
} ret_val;

struct user_data
{
    char *name;
    uint8_t counter;
};


/***** MAIN ***************************************************************/
int main(int argc, char *argv[])
{

    /* CPUs */
    int procs = 0;
    procs = (int)sysconf(_SC_NPROCESSORS_ONLN);
    if (procs < 0) {
        perror("sysconf");
        return -1;
    }
    printf("> procs: [%d]\n", procs);

    /* Dynamic memory allocation */
    struct user_data *user = malloc(sizeof(struct user_data));
    user->name = malloc(sizeof(char) * 100);
    strcpy(user->name, "unnamed");

    /* Threads */
    pthread_t thread1, thread2;
    ret_val.iret1 = pthread_create(&thread1, NULL, (void *)write_time_file, (void *)user);
    ret_val.iret2 = pthread_create(&thread2, NULL, (void *)loopback_stdin, (void *)user);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    /* Result */
    fprintf(stdout,
            "> iret1: %d, iret2: %d, counter: %d\n",
            ret_val.iret1, ret_val.iret2, counter);


    /* No memory leaks... */
    free(user->name); user->name = NULL;
    free(user); user = NULL;

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

        /* STDIN */
        if (!fgets(buf, sizeof(buf), stdin))
            return RET_ERROR;

        len = strlen(buf);

        /* STDIN buffer fix */
        if (buf[len - 1] == '\n') {
            buf[--len] = '\0';
        } else {
            scanf("%*[^\n]");
            getchar();
        }

        /* Loopback STDIN -> STDOUT */
        fprintf(stdout, ">> %s\n", buf);

        /* Mutex: counter */
        pthread_mutex_lock(&mutex1);
        cont = counter;
        fprintf(stdout, ">> Counter: %d\n", counter);
        pthread_mutex_unlock(&mutex1);

        /* Mutex: user_data structure */
        pthread_mutex_lock(&mutex2);
        strcpy(((struct user_data*)arg)->name, buf);
        fprintf(stdout, ">> %s\n", ((struct user_data*)arg)->name);
        ((struct user_data*)arg)->counter = counter;
        pthread_mutex_unlock(&mutex2);
    }

    return RET_OK;

} /* end loopback_stdin() */

e_return write_time_file(void *arg)
{
    int8_t cont = 1;
    while (cont >= 0) {

        /* Mutex: counter */
        pthread_mutex_lock(&mutex1);
        cont = counter--;
        pthread_mutex_unlock(&mutex1);

        /* File handle */
        FILE *fp;

        if (!(fp = fopen("output.txt", "a"))) {
            fprintf(stderr, "> Could not open file\n");
            fclose(fp);
            return RET_ERROR;
        }

        /* Current date & time */
        time_t t = time(NULL);
        struct tm *tm = localtime(&t);
        char s[64];

        strftime(s, sizeof(s), "%c", tm);

        /* Store current date & time in file */
        fprintf(fp, "%s,", s);

        /* Mutex: user_data structure */
        pthread_mutex_lock(&mutex2);
        fprintf(fp, "%s, %d\n",
                ((struct user_data*)arg)->name,
                ((struct user_data*)arg)->counter);

        /* Reset struct fields*/
        strcpy(((struct user_data*)arg)->name, "-");
        ((struct user_data*)arg)->counter = counter;
        pthread_mutex_unlock(&mutex2);

        /* Close file handle and sleep a bit... */
        fclose(fp);
        sleep(1);
    }

    return RET_OK;
} /* end write_time_file() */


/* End main.c */

