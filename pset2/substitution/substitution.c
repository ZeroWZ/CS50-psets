#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int Validating_the_Key(int argc, string argv[]);
int main(int argc, string argv[])
{
    int r = Validating_the_Key(argc, argv);
    if (r == 0)
    {
        // Get a plaintext
        string PT = get_string("plaintext: ");
        int n = strlen(PT);
        int nk = strlen(argv[1]);

        // Plaintext encryption
        printf("ciphertext: ");
        for (int i = 0; n > i; i++)
        {
            if (islower(PT[i]))
            {
                int x = PT[i] - 97;
                if (isupper(argv[1][x]))
                {
                    argv[1][x] = argv[1][x] + 32;
                    printf("%c", argv[1][x]);
                }
                else
                {
                    printf("%c", argv[1][x]);
                }

            }
            else if (isupper(PT[i]))
            {
                int y = PT[i] - 65;
                if (islower(argv[1][y]))
                {
                    argv[1][y] = argv[1][y] - 32;
                    printf("%c", argv[1][y]);
                }
                else
                {
                    printf("%c", argv[1][y]);
                }

            }
            else
            {
                printf("%c", PT[i]);

            }
        }
        printf("\n");

    }
    else if (r == 1)
    {
        return 1;
    }
}

// Check if the key is valid
int Validating_the_Key(int argc, string argv[])
{
    if (argc == 2)
    {
        int n = strlen(argv[1]);
        if (n == 26)
        {
            int k = 0, l = 0;
            for (int i = 0; n > i; i++)
            {
                l++;
                if (isalpha(argv[1][i]))
                {
                    k++;
                }
            }
            if (k == 26)
            {
                int m = 0, u = 1;
                int r = 25;
                for (int c = 0; 25 > c; c++)
                {
                    int t = 0;
                    for (int i = 0; r > i; i++)
                    {
                        if (argv[1][c] != argv[1][i + u])
                        {
                            t++;
                        }

                        if (islower(argv[1][c]) && isupper(argv[1][i + u]))
                        {
                            if (argv[1][c] - 32 == argv[1][i + u])
                            {
                                t--;
                            }
                        }
                        if (isupper(argv[1][c]) && islower(argv[1][i + u]))
                        {
                            if (argv[1][c] + 32 == argv[1][i + u])
                            {
                                t--;
                            }
                        }

                        if (t == r)
                        {
                            m++;
                        }
                    }
                    u++;
                    r--;
                }
                if (m == 25)
                {
                    return 0;
                }
                else
                {
                    printf("key must not contain repeated characters.\n");
                    return 1;
                }

            }
            else if (k != 26 && l == 26)
            {
                printf("Key must only contain alphabetic characters.\n");
                return 1;
            }
            else
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
}