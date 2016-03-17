#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char** argv) {

    
    //Zad1
    char test[] = "Ala ma kota";
    char *test2 = removeZnaki(test, 7);
    printf("%s\n", test2);
    
    //Zad2
    endswith("ellopo", "opo");
    endswith("ellopo", "pop");  
    
    //Zad3
    printf("%-40s%5i%5i\n", "strcmp(cat, dog)", strcmp("cat", "dog"), my_strcmp("cat", "dog", 0));
    printf("%-40s%5i%5i\n", "strcmp(cat, cats)", strcmp("cat", "cats"), my_strcmp("cat", "cats",0));
    printf("%-40s%5i%5i\n", "strcmp(dog, Dog,1)", strcmp("cat", "Dog"), my_strcmp("dog", "Dog",1));
    printf("%-40s%5i%5i\n", "strcmp(dog, Dog,0)", strcmp("cat", "Dog"), my_strcmp("dog", "Dog",0));
 
    return (EXIT_SUCCESS);
}

