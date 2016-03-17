#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *removeZnaki(char wejscie[], int indeks)
{
    int length = strlen(wejscie);
    char *wyjscie = (char*)malloc(sizeof(length));
    for (int i = 0; i <= length - indeks; i++)
    {
        wyjscie[i] = wejscie[i];
    }
    return wyjscie;
}
