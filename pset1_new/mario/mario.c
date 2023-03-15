#include <stdio.h>

int main() {

    int n, type;
    printf("Type 1 for Up or 2 for Down: ");
    scanf("%i", &type);
    if (type != 1 && type != 2)
    {
        printf("Invalid");
        return 1;
    }

    printf("Hight: ");
    scanf("%i", &n);
    if (n > 20)
    {
        printf("Choose hight less then or equal 20");
        return 1;
    }

    if (type == 2)
    {
        for (int i = n; i > 0; i--)
        {
            for(int j = 1; j < i; j++)
            {
                printf(" ");
            }
            for(int j = n; j >= i; j--)
            {
                printf("#");
            }

            // printf(" ");

            for(int j = n; j >= i; j--)
            {
                printf("#");
            }
            printf("\n");
        }
        return 0;
    }
    
    if (type == 1)
    {
        for (int i = n; i > 0; i--)
        {
            for(int j = n; j > i; j--)
            {
                printf(" ");
            }
            for(int j = 0; j < i; j++)
            {
                printf("#");
            }

            // printf(" ");

            for(int j = 0; j < i; j++)
            {
                printf("#");
            }
            printf("\n");
        }
        return 0;
    }
}