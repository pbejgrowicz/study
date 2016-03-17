#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int my_strcmp(char s1[], char s2[], int flag)
{
    int length = strlen(s1);
    char * str = (char*)malloc(sizeof(length));
    strcpy(str,s1);
    int length2 = strlen(s2);
    char * str2 = (char*)malloc(sizeof(length2));
    strcpy(str2,s2);
    if (flag == 1)
    {
        
        for(int i = 0; str[i]; i++){
            str[i] = tolower(str[i]);
           }
        for(int i = 0; str2[i]; i++){
            str2[i] = tolower(str2[i]);
           }
    }

    int i;
    for (i =0; str[i] != '\0' && str2[i]!= '\0'; i++)
    {
        if(str[i] > str2[i])return 1;
        if(str[i] < str2[i])return -1;
    }
    if(str[i] != '\0') return 1;  //s1 is longer than s2
    if(str2[i] != '\0') return -1;  //s2 is longer than s1
}
