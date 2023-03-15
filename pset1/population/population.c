#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start, end;
    int n = 0;
    do
    {
        start = get_int("Start size: \n");
    }
    while (start < 9);

    do
    {
        end = get_int("End size: \n");
    }
    while (end < start);

    if (start < end)
    {
        do
        {
            start = start + start / 3 - start / 4;
            n++;
        }
        while (start < end);
        printf("Years: %i\n", n);
    }
    else
    {
        printf("Years: 0 \n");
    }

}