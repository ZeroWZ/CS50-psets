#include <stdio.h>
#include <stdint.h>

int64_t get_int(char *str);
int lnf(int64_t number);
int is_valid(int64_t card);
int what_it (int num, int ln);

int main(){
    int64_t card_number = get_int("Card Number: ");

    int ln = lnf(card_number);

    int vld = is_valid(card_number);

    int num;
    if (vld == 0)
    {
        num = card_number / 1000000000000;
        what_it (num, ln);
    }
    else
    {
        printf("INVALID\n");
        return 0;
    }
}


int64_t get_int(char *str){
    int64_t num;
    char term;

    printf("%s", str);
    if (scanf("%li%c", &num, &term) != 2 || term != '\n')
    {
        do
        {
            printf("%s", str);
            while ((getchar()) != '\n');
            // fflush(stdin);
        } while (scanf("%li%c", &num, &term) != 2 || term != '\n');

    }
    return num;
}

int lnf(int64_t number)
{
    int i = 0;
    while (number > 0 )
    {
        number = number / 10;
        i++;
    }
    return i;
}

int is_valid(int64_t card)
{
    int num[] = {0, 0, 0, 0};
    while (card > 0)
    {
        num[2] += card % 10;
        card /= 10;
        num[0] = (card % 10) * 2;
        num[1] += (num[0] > 9) ? num[0] = (num[0] % 10 + num[0] / 10) : num[0];
        card /= 10;
    }
    num[3] = (num[1] + num[2]) % 10 == 0 ? 0 : 1;
    return num[3];
}

int what_it (int num, int ln)
{
    do
    {
        if ((num == 4 && ln == 16) || ln == 13)
        {
            printf("VISA\n");
            return 0;
        }
        if (num == 34 || (num == 37 && ln == 15))
        {
            printf("AMEX\n");
            return 0;
        }
        if (num == 51 || num == 52 || num == 53 || num == 54 || (num == 55 && ln == 16))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        num = num / 10;

    } while (num > 0);

    printf("INVALID\n");
    return 1;
}