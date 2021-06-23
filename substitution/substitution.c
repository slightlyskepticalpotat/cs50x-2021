#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Various checks for valid key
    if (argc != 2)
    {
        printf("Invalid number of arguments.\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Invalid key length.\n");
        return 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Invalid key character.\n");
            return 1;
        }
        argv[1][i] = toupper(argv[1][i]);
    }
    for (int i = 0; i < 26; i++)
    {
        for (int j = i + 1; j < 26; j++)
        {
            if (argv[1][i] == argv[1][j])
            {
                printf("Duplicate key character.\n");
                return 1;
            }
        }
    }

    string plaintext = get_string("plaintext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        if (isupper(plaintext[i]))
        {
            plaintext[i] = argv[1][plaintext[i] - 65];
        }
        else if (islower(plaintext[i]))
        {
            plaintext[i] = tolower(argv[1][plaintext[i] - 97]);
        }
    }

    printf("ciphertext: %s\n", plaintext);
}