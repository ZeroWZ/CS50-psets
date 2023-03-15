#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long n = get_long("Number: ");
    long a, b, c = 0, k, j, m = 0, p, h, z = n, x = n;
    // multiply each of the numbers starting with the number’s second-to-last digit then  add those products’ digits together
    while (n > 0)
    {
        n = n / 10;
        b = n % 10;
        a = b * 2 % 10;
        k = b * 2 / 10;
        j = a + k;
        n = n / 10;
        c += j;
    }
    // add the digits that weren’t multiplied starting from the end
    while (z > 0)
    {
        p = z % 10;
        z = z / 100;
        m += p;
    }
    h = m + c;
    // check for card length and starting digit
    if (h % 10 == 0)
    {

        if (x / 10000000000000 == 34 || x / 10000000000000 == 37)
        {
            printf("AMEX\n");
        }
        else if (x / 100000000000000 == 51 || x / 100000000000000 == 52 || x / 100000000000000 == 53 || x / 100000000000000 == 54
                 || x / 100000000000000 == 55)
        {
            printf("MASTERCARD\n");
        }
        else if (x / 1000000000000000 == 4 || x / 1000000000000 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }

}