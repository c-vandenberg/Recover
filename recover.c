#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>

typedef uint8_t BYTE;

bool is_jpeg_header(BYTE buffer[]);

int main(int argc, char *argv[])
{
    // Check if command line argument is valid
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s image\n", argv[0]);
        return 1;
    }
    // Open memory card files
    char *mem_card = argv[1];
    FILE *infile = fopen(mem_card, "r");
    if (infile == NULL)
    {
        printf("File not found/n");
        return 2;
    }
    BYTE buffer[512];
    int image_count = 0;
    char filename[9];
    FILE *outfile = NULL;


    // Repeat until end of memory card
    while (fread(buffer, sizeof(buffer), 1, infile) == 1)
    {
        // Check if we have found a JPEG
        if (is_jpeg_header(buffer))
        {
            // If we're already writing a JPEG, close it
            if (outfile)
            {
                fclose(outfile);
            }
            // Create filename for new JPEG (e.g. if second JPEG found, filename would be 002.jpg)
            sprintf(filename, "%03i.jpg", image_count);
            // Create a file with that filename so that we can begin to write new JPEG to file
            outfile = fopen(filename, "w");
            // Check that outfile != NULL
            if (outfile == NULL)
            {
                printf("File not found/n");
                return 3;
            }
            // Keep track of how many JPEG images found
            image_count++;
        }
        // Else if no new JPEG found, continue to write current JPEG to file
        if (outfile)
        {
            fwrite(buffer, sizeof(buffer), 1, outfile);
        }
    }
    fclose(infile);
    fclose(outfile);
    return 0;
}

bool is_jpeg_header(BYTE buffer[])
{
    if (((buffer[0] == 0xff) && (buffer [1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0)))
    {
        return true;
    }
    return false;
}






