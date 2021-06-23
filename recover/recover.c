#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check number of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Check if file valid
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        fprintf(stderr, "Invalid file %s.\n", argv[1]);
        return 1;
    }

    // Actually look for the photos
    BYTE buffer[512];
    FILE *current;
    char filename[8];
    int name = 0;

    while (fread(&buffer, sizeof(BYTE), 512, input))
    {
        // 224 == 0xe0, 239 == 0xef
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 224 && buffer[3] <= 239)
        {
            // Printf to an empty string
            sprintf(filename, "%03i.jpg", name);
            current = fopen(filename, "w");
            name += 1;
        }
        if (name)
        {
            fwrite(&buffer, sizeof(BYTE), 512, current);
        }
    }

    // Close file pointers
    fclose(current);
    fclose(input);
}