#include <stdio.h>

int main() {
    int change;
    char n;
    
    printf("Change owed: ");
    while (scanf("%i%c", &change, &n) != 2 || n != '\n' || change < 0){
        while ((getchar()) != '\n');
        printf("Change owed: ");
    }
    

    int i = 0;
    while (change >= 25)
    {
        change -= 25;
        i++;
    }
    while (change >= 10)
    {
        change -= 10;
        i++;
    }
    while (change >= 5)
    {
        change -= 5;
        i++;
    }
    while (change >= 1)
    {
        change -= 1;
        i++;
    }
    
    printf("%i\n", i);
    return 0;
}