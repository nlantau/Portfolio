/***************************************************************************
 * Read Text File Source File
 * 
 * 
 * Author : nlantau
 * Date   : 2020-12-01
 * Changed: 2020-12-02
 **************************************************************************/

/***** INCLUDES ***********************************************************/

#include "read_text_file.h"

/***** ALGORITHM **********************************************************/

/***************************************************************************
 * read_file()
 * 
 * param        : char *path: self-explained
 * functionality:
 *       Opens 'path' in read binary mode
 *       Uses fseek() to find the EOF (binary files recommended)
 *       Stores the size of file pointer
 *       Rewinds file pointer to start of file
 *       Mallocs char *fs with size of char* * ftell(fp)
 * return       : Malloced char *
 **************************************************************************/
char *read_file(char *path)
{
    FILE *fp;
    long fp_size;

    if ((fp = fopen(path, "rb")) == NULL)
    {
        fprintf(stderr, "> Something went wrong when opening the file\n");
        return NULL;
    }
    /* Find length of file for dynamic allocation */
    fseek(fp, 0L, SEEK_END);
    fp_size = ftell(fp);
    rewind(fp);

    char *fs = malloc(sizeof(char) * fp_size);

    if (fread(fs, fp_size, 1, fp) != 1)
    {
        fclose(fp);
        free(fs);
        fprintf(stderr, "Error while reading\n");
        return NULL;
    }
    fclose(fp);
    return fs;

} /* End read_file() */