#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<errno.h>

#define MAX_CANDIDATES 9
#define MAX_VOTERS 5
int preferences[MAX_VOTERS][MAX_CANDIDATES];

typedef struct
{
    char* name;
    int votes;
    bool eliminated;
}
candidate;

candidate candidates[MAX_CANDIDATES];
int candidate_count;
int voters;

bool vote(int voter, int rank, char* name);
void tabulate();
bool print_winner();
int find_min();
bool is_tie(int min);
void eliminate(int min);
char *strings(char *text, int BUFFER_SIZE);
int get_int(char *str);

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }

    for (int i = 0; i < candidate_count; i++){
        candidates[i].name = argv[i+1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voters = get_int("Number of voters: ");
    if (voters > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    char *name;
    for (int i = 0; i < voters; i++){
        for (int j = 0; j < candidate_count; j++){
            printf("Rank %i", j+1);
            name = strings(":", 20);
            bool True = vote(i, j, name);
            if (!True){
                printf("Invalid vote\n");
            }
        }
        printf("\n");
    }

    while (true)
    {
        tabulate();

        if (print_winner()){
            break;;
        }

        int min = find_min();
        bool tie = is_tie(min);

        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min);

        for (int i = 0; i<candidate_count; i++){
            if (candidates[i].eliminated == false){
                printf("%s: %i\n", candidates[i].name, candidates[i].votes);
            } 
        }
    }
    free(name);
    return 0;
}

bool vote(int voter, int rank, char* name){
    for (int i = 0;  i < candidate_count; i++){
        if (strcmp(name, candidates[i].name) == 0){
            preferences[voter][rank] = i;
            return true;
        }
    }
    preferences[voter][rank] = -1;
    return false;
}

void tabulate(){
    for (int i = 0; i < voters; i++){
        for (int j = 0; j < candidate_count; j++){
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }    
    }
}

bool print_winner(){
    for (int j = 0; j < candidate_count; j++){
        if (candidates[j].votes > (voters / 2)){
            printf("The winner: %s\n", candidates[j].name);
            return true;
        }
    }
    return false;
}

int find_min(){
    int tmp;
    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].eliminated == false){
            tmp = i;
            break;
        }
    }

    for (int j = 0; j < candidate_count; j++){
        if (candidates[j].eliminated == false && candidates[tmp].votes > candidates[j].votes){
            tmp = j;
        }
    }
    return candidates[tmp].votes;
}

bool is_tie(int min){
    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].eliminated == false && min != candidates[i].votes){
            return false;
        }
    }
    return true;
}

void eliminate(int min){
    for (int i = 0; i < candidate_count; i++){
        if (candidates[i].votes == min){
            candidates[i].eliminated = true;
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