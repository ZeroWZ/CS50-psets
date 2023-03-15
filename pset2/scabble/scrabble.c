#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word1);
int compute_score2(string word2);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score2(word2);

    //Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word1)
{
    // Compute and return score for string
    char ltr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char ltrUP[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int sum = 0;
    for (int i = 0, n = strlen(word1); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (islower(word1[i]) || isupper(word1[i]))
            {
                if (word1[i] == ltr[j] || word1[i] == ltrUP[j])
                {
                    sum = sum + POINTS[j];
                }
            }
        }
    }
    return sum;
}

int compute_score2(string word2)
{
    //Compute and return score for string
    char ltr[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char ltrUP[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int sum2 = 0;
    for (int i = 0, n = strlen(word2); i < n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            if (islower(word2[i]) || isupper(word2[i]))
            {
                if (word2[i] == ltr[j] || word2[i] == ltrUP[j])
                {
                    sum2 = sum2 + POINTS[j];
                }
            }
        }
    }
    return sum2;
}