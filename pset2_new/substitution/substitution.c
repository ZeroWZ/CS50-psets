#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define SIZE 10000

char *strings(char *text, int BUFFER_SIZE);
int is_key_valid(char key[]);
void crypt(char *text, char *key);

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // Check if the key is valid
    if (is_key_valid(argv[1]) == 1)
        return 1;

    // Get plaintext
    char *text = strings("Plaintext: ", SIZE);

    // Plaintext encryption
    crypt(text, argv[1]);
    printf("ciphertext: %s\n", text);

    free(text);
    return 0;
}

int is_key_valid(char key[])
{
    int n = strlen(key);

    if (n != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        if (65 > key[i] || (key[i] > 90 && 97 > key[i]) || key[i] > 122)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
        for (int j = i + 1; j < n; j++)
        {
            if (key[i] == key[j])
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    return 0;
}

void crypt(char *text, char *key)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (97 <= text[i] && text[i] <= 122)
        {
            text[i] = (97 <= key[text[i]-97] && key[text[i]-97] <= 122) ? key[text[i]-97] : key[text[i]-97] + 32;
        }
        else if (65 <= text[i] && text[i] <= 90)
        {
            text[i] = (97 <= key[text[i]-65] && key[text[i]-65] <= 122) ? key[text[i]-65] - 32 : key[text[i]-65];
        }
    }
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
