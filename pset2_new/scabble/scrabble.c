#include<stdio.h>

int compute_score(char word[]);

int VALUE[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int main()
{
    char word[2][100];
    printf("Player 1: ");
    fgets(word[0], 100, stdin);

    printf("Player 2: ");
    fgets(word[1], 100, stdin);

    int score_1 = compute_score(word[0]);
    int score_2 = compute_score(word[1]);

    if (score_1 == 0 || score_2 == 0)
    {
        printf("Try again\n");
        return 1;
    }

    if (score_1 > score_2)
        printf("Player 1 wins!\n");
    else if (score_1 < score_2)
        printf("Player 2 wins!\n");
    else
        printf("Tie!\n");
    return 0;
}

int compute_score(char *ptr)
{
    int score = 0;
    while (*ptr != '\n')
    {
        if (65 <= *ptr && *ptr <= 90)
        {
            int i = *ptr - 65;
            score += VALUE[i];
        }
        else if (97 <= *ptr && *ptr <= 122)
        {
            int i = *ptr - 97;
            score += VALUE[i];
        }
        else if (*ptr == 32)
        {
            return 0;
        }

        ptr++;
    }
    return score;
}