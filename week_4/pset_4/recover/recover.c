#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint8_t BYTE;
int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE");
        return 1;
    }

    // Open input file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", argv[1]);
        return 1;
    }

    // Output file
    FILE *img = NULL;
    char filename[8] = {0};

    // Buffer
    BYTE buffer[512];

    // Counter
    int counter = 0;

    // Looping through the memory card
    while (fread(buffer, sizeof(BYTE) * 512, 1, file) == 1)
    {
        // If is the start of a JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG file
            if (img != NULL)
            {
                // Close the file
                fclose(img);
            }

            sprintf(filename, "%03d.jpg", counter++);
            img = fopen(filename, "w");
        }
        if (img != NULL)
        {
            fwrite(buffer, sizeof(BYTE) * 512, 1, img);
        }
    }

    // Close the files
    if (img != NULL)
    {
        fclose(img);
    }

    fclose(file);

    return 0;
}