#include <stdio.h>
#include<string.h>

int main(void)
{
    char name[20];
    printf("What is your name?\n");

    if(fgets(name, sizeof name, stdin) == NULL)
        return 1;
    name[strcspn(name, "\n")] = '\0';
    
    printf("Hello, %s!\n", name);

    return 0;
}