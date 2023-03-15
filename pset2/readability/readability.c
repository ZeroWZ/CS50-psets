#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int main(void)
{
    //Get a text
    string text = get_string("Text: ");

    float nl = count_letters(text);
    float nw = count_words(text);
    float ns = count_sentences(text);
    //Calculation of the Coleman-Liau Index
    float L = 100 * nl / nw;
    float S = 100 * ns / nw;
    int index = round(0.0588 * L - 0.296 * S - 15.8);
    //print the results
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", index);
    }

}

//count the number of letters
int count_letters(string text)
{
    int k = 0;
    for (int i = 0, n = strlen(text); n > i ; i++)
    {
        if ((text[i] >= 'a' && text[i] <= 'z') || (text[i] >= 'A' && text[i] <= 'Z'))
        {
            k++;
        }
    }
    return k;
}
//count the number of words
int count_words(string text)
{
    int w = 0;
    for (int i = 0, n = strlen(text); n > i ; i++)
    {
        if (text[i] == ' ')
        {
            w++;
        }
    }
    return w + 1;
}
//count the number of sentences
int count_sentences(string text)
{
    int s = 0;
    for (int i = 0, n = strlen(text); n > i ; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            s++;
        }
    }
    return s;
}