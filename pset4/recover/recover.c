/**
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // remember file's name
    char *infile = argv[1];


    // open file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    BYTE buffer[512];
    char filename[10];
    FILE *img = NULL;
    int i = 0;

    // iterate over blocks till the end of file
    while (!feof(inptr))
    {
        fread (buffer, 512, 1, inptr);

        // check if it has JPEG signature
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // check if the outfile is not open
            if (img == NULL)
            {
                // give name for outfile
                sprintf(filename, "%03i.jpg", i);
                // open outfile
                img = fopen(filename, "w");

            }
            // if outfile is open
            else
            {
                // close current outfile
                fclose(img);
                i++;
                // give name for new outfile
                sprintf(filename, "%03i.jpg", i);
                // open outfile
                img = fopen(filename, "w");
            }
        }

        // check if outfile is open
        if (img !=NULL)
        {
            fwrite (buffer, 512, 1, img);
        }
    }

    // success
    fclose(inptr);
    fclose(img);
    return 0;
}

















