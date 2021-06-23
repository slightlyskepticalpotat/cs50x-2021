#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int current;
    do
    {
        current = get_int("Starting Population: ");
    }
    while (current < 9);

    int end;
    do
    {
        end = get_int("Ending Population: ");
    }
    while (end < current);

    int year = 0;
    while (current < end)
    {
        current += (current / 3) - (current / 4);
        year += 1;
    }
    printf("Years: %i\n", year);
}