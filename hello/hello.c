#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name = get_string("Hi, what's your name?\n");
    printf("Hello, %s\n", name);
}