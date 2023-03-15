#include <stdio.h>

int main(void)
{
    int start, end;
    int n = 0;
    do
    {
        printf("Start size: \n");
        scanf("%i", &start);
    }
    while (start < 9);

    do
    {
        printf("End size: \n");
        scanf("%i", &end);
    }
    while (end < start);

    if (start < end)
    {
        do
        {
            start += start/3 - start/4;
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

