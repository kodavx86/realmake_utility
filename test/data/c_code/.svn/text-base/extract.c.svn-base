#include <string.h>

/* Extraction method; */
void Extract(char *str)
{
    int        x, i, y;
    char    tmp[strlen(str)];
 
    /* zero out our temp string */
    bzero(tmp, sizeof(tmp));
 
    for (x = 0, i = 0, y = 0; x < strlen(str); x++)
    {
        /* check to see if the last loop reached the end of
         * our first segment. */
        if (!y)
        {
            /* nope.. check to see if this loop does */
            if (str[x] == '=')
            {
                y = 1;
 
                /* First segment passed; continue back to a new loop
                 * and search for the next segment */
                continue;
            }
 
            /* keep looping back until we've gone through the
             * first segment (skipping) */
            continue;
        }
 
        /* check to see if we have passed the first segment */
        if (y == 1)
        {
            /* check if we are at the start of our valued segment */
            if (str[x] == 34)
            {
                /* we are.. setup y so we can start writing our value */
                y = 2;
 
                /* continue back to the beginning so we dont write '"' */
                continue;
            }
 
            /* '"' hasn't been reached yet continue looping.. */
            continue;
        }
 
        /* check to see if our value is done with an ending '"' */
        if (y == 2 && str[x] == 34)
        {
            /* Everything looks good; zero out our string and
             * start writing our temp string to our real string */
            bzero(str, strlen(tmp) + 1);
            for (x = 0; x < strlen(tmp); x++)
                str[x] = tmp[x];
 
            /* end loop */
            break;
        }
 
        /* write to our temp string */
        tmp[i] = str[x];
        i++;
    }
}