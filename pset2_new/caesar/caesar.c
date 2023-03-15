#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define SIZE 1000

char *strings(char *text, int BUFFER_SIZE);
char rotate(char c, int k);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (48 > argv[1][i] || argv[1][i] > 57)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    int key = atoi(argv[1]);

    char *text = strings("Plaintext: ", SIZE);
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        text[i] = rotate(text[i], key);
    }

    printf("Ciphertext: %s\n", text);

    free(text);
    return 0;
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

char rotate(char c, int k)
{
    if (97 <= c && c <= 122)
    {
        c = (c - 97 + k) % 26 + 97;
    }
    else if (65 <= c && c <= 90)
    {
        c = (c - 65 + k) % 26 + 65;
    }
    return c;
}