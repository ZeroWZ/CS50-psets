#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int Validating_the_Key(int argc, string argv[]);
int main(int argc, string argv[])
{
    int r = Validating_the_Key(argc, argv);
    if (r == 0)
    {
        int key = atoi(argv[1]);
        string pt = get_string("plaintext: ");
        int n = strlen(pt);
        char c;
        printf("ciphertext: ");
        for (int i = 0 ; n > i; i++)
        {
            if (isupper(pt[i]))
            {
                pt[i] = pt[i] - 65;
                c = (pt[i] + key) % 26;
                c = c + 65;
                printf("%c", c);
            }
            else if (islower(pt[i]))
            {
                pt[i] = pt[i] - 97;
                c = (pt[i] + key) % 26;
                c = c + 97;
                printf("%c", c);
            }
            else
            {
                printf("%c", pt[i]);

            }
        }

        printf("\n");


    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
}



int Validating_the_Key(int argc, string argv[])
{
    int k = 0;
    if (argc == 2)
    {
        int n = strlen(argv[1]);
        for (int i = 0 ; n > i; i++)
        {
            if (isdigit(argv[1][i]))
            {
                k++;
            }
        }
        if (k == n)
        {
            return 0;
        }
        else
        {
            return 1;
        }

    }
    else
    {
        return 1;
    }

}