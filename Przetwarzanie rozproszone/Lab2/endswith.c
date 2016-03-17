#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void endswith(char *tmp1, char *tmp2)
{
    int length1 = strlen(tmp1);
    int length2 = strlen(tmp2);
    int endwith = 0;
    int j = 0;
    for ( int i = length1 - length2; i < length1; i++, j++)
    {
        if (tmp1[i] == tmp2[j])
            endwith = 1;
        else
        {
            endwith = 0;
            break;
        }
    }
    if (endwith == 1)
        printf("Tak\n");
    else
        printf("Nie\n");
}
