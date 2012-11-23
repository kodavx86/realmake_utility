

/* Custom String Tokenizer - by mind@metalshell.com
 *
 * This example is more of an example on predetermined strings such as
 * reading in a configuration file and splitting the variable from the value
 * in or around quotation marks or equal signs.
 *
 * See below for porting this to read a configuration file or similar
 *
 * http://www.metalshell.com
 */
#include <stdio.h>
#include <string.h>

#include "runexample.h"
#include "extract.h"

int main()
{
    int    x, i;
    char    tmp[]="writing:your:own:string!tokenizer:yay";
    char    tnp[strlen(tmp)];
 
    /* See below
     *
     * int    z;
     * char    exempt[]="!@:$.,";
     * char    tmp[]="writing,your!own@str.ingto$kenize:ryay";
     *
     */
 
    /* Uncomment the next two lines to run the second example */
 
    // RunExample();
    // return 1;
 
    /* zero out our temp string */
    bzero(tnp, sizeof(tnp));
 
    for (x = 0, i = 0; x < strlen(tmp); x++)
    {
        /* Use this if you want to parse segments from
         * numerous splitters.
         *
         * for (z = 0; z < strlen(exempt); z++)
         * {
         *        if (tmp[x] == exempt[z])
         *        {
         *            .....
         *        }
         * }
         *
         */
 
        /* check for end of segment */
        if (tmp[x] == ':' || tmp[x] == '!')
        {
            printf("Extracted segment: %s\n", tnp);
 
            /* zero out our temp string */
            bzero(tnp, sizeof(tnp));
 
            /* reset our writing point back to the beginning */
            i = 0;
 
            /* start from the beginning of our loop
             * this is needed so the loop wont finish
             * and write : or ! to tnp[0] */
            continue;
        }
 
        /* write our character at position tnp[i] from tmp[x] */
        tnp[i] = tmp[x];
 
        /* increase our temp string's position */
        i++;
    }
    return 175;
}
 

 


