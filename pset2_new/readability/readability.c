#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>

#define SIZE 10000

char *strings(char *text, int BUFFER_SIZE);
int count_letters(char *text);
int count_words(char *text);
int count_sentences(char *text);

int main()
{
    char *text = strings("Text: ", SIZE);

    float letters = count_letters(text);
    float words = count_words(text);
    float sentences = count_sentences(text);

    float L = letters / words * 100;
    float S = sentences / words * 100;

    float index = 0.0588 * L - 0.296 * S - 15.8;
    int index_r = (int)(index < 0 ? (index - 0.5) : (index + 0.5));
    if (index_r >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (index_r < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", index_r);
    }
    return 0;

    free(text);
}

int count_letters(char *text)
{
    int j = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if ((65 <= text[i] || text[i] >= 90) || (97 <= text[i] || text[i] >= 122))
        {
            j++;
        }
    }
    return j;
}

int count_words(char *text)
{
    int j = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (text[i] == ' ')
        {
            j++;
        }
    }
    return j;
}

int count_sentences(char *text)
{
    int j = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        char c = text[i];
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            j++;
        }
    }
    return j;
}


char *strings(char *text, int BUFFER_SIZE)
{
    printf("%s", text);

    char *inputBuffer = malloc(sizeof(char) * BUFFER_SIZE);
    if(inputBuffer == NULL){
		fprintf(stderr, "malloc: %s\n", strerror(errno));
		return NULL;
	}

    memset(inputBuffer, 0, BUFFER_SIZE);
    char *result = NULL;

    while (result == NULL)
    {
        result = fgets(inputBuffer, BUFFER_SIZE, stdin);

        if (inputBuffer[strlen(inputBuffer) - 1] != '\n')
        {
            fprintf(stderr, "[ERROR]: The input was too long, please try again.\n");

            char c;
            while ((c = getchar()) != '\n' && c != EOF) {}

            result = NULL;
        }
    }
    inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

    return inputBuffer;
}
