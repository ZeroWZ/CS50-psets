#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

#define MAX 9

char *strings(char *text, int BUFFER_SIZE);
int get_int(char *str);
int Vote(char *vote);
void winner();

typedef struct
{
    char* name;
    int votes;
}
candidate;

candidate candidates[MAX];
int candidate_count;

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++){
        candidates[i].name = argv[i+1];
        candidates[i].votes = 0;
    }

    int voters = get_int("Number of voters: ");
    char *vote;
    for (int i = 0; i < voters; i++){
        vote = strings("Vote: ", 20);
        if(Vote(vote) == 1){
            printf("Invalid vote.\n");
        }
    }

    winner();
    free(vote);
    return 0;
}

int Vote(char *vote){
    for (int j = 0;  j < candidate_count; j++){
        if (strcmp(vote, candidates[j].name) == 0){
            candidates[j].votes++;
            return 0;
        }
    }
    return 1;
}

void winner(){
    int tmp[MAX];
    int j = 0;
    tmp[0] = 0;
    for (int i = 1; i < candidate_count; i++){
        if (candidates[tmp[0]].votes < candidates[i].votes){
            tmp[0] = i;
            j = 0;
        }
        else if (candidates[tmp[0]].votes == candidates[i].votes){
            j++;
            tmp[j] = i;
        }
    }
    for (int n = 0; n <= j; n++){
        printf("%s\n", candidates[tmp[n]].name);
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

int get_int(char *str)
{
    int num;
    char term;

    printf("%s", str);
    if (scanf("%i%c", &num, &term) != 2 || term != '\n')
    {
        do
        {
            printf("%s", str);
            while ((getchar()) != '\n');
        } while (scanf("%i%c", &num, &term) != 2 || term != '\n');

    }
    return num;
}
