#include <cs50.h>
#include <stdio.h>

bool luhn(long to_check);

int main(void)
{
    long number = get_long("Number: ");

    if (!luhn(number))
    {
        printf("INVALID\n");
    }
    else
    {
        // First two digits to check
        long first_two = number;

        while (first_two >= 100)
        {
            first_two = first_two / 10;
        }

        // Check first two digits and number of digits
        if ((first_two == 34 || first_two == 37) && (number >= 1e14 && number < 1e15))
        {
            printf("AMEX\n");
        }
        else if ((first_two > 50 && first_two < 56) && (number >= 1e15 && number < 1e16))
        {
            printf("MASTERCARD\n");
        }
        else if ((first_two / 10 == 4) && ((number >= 1e12 && number < 1e13) || (number >= 1e15 && number < 1e16)))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
}

bool luhn(long to_check)
{
    int times_two = 0;
    int times_one = 0;
    int product = 0;

    while (to_check)
    {
        times_one += to_check % 10;
        to_check /= 10;

        // Check at least one digit left
        if (to_check)
        {
            product = (to_check % 10) * 2;

            while (product)
            {
                times_two += product % 10;
                product /= 10;
            }

            to_check /= 10;
        }
    }



    return (times_two + times_one) % 10 == 0;
}