/**
 * Resizes bmp file.
 */

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // create a variable for a factor
    int n = atoi(argv[1]);

    // ensure proper usage
    if (argc != 4 || n <= 0 || n > 100)
    {
        fprintf(stderr, "Usage: ./resize infile outfile\n");
        return 1;
    }

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // change width and height
    int oldwidth = bi.biWidth;
    int oldheight = bi.biHeight;
    bi.biWidth = oldwidth * n;
    bi.biHeight = oldheight * n;

    // determine padding for infile's and outfile's scanlines
    int padding = (4 - (oldwidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // change biSizeImage and bfSize
    bi.biSizeImage = (bi.biWidth * sizeof(RGBTRIPLE) + out_padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // change height into a positive integer
    int abs_oldheight = abs(oldheight);

    // iterate over infile's scanlines
    for (int i = 0; i < abs_oldheight; i++)
    {
        // print a row into an outfile n - 1 times
        for (int k = 0; k < n - 1; k++)
        {
            // iterate over infile's pixels
            for (int j = 0; j < oldwidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write RGB triple to outfile n times
                for (int t = 0; t < n; t++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }

            // write outfile's padding
            for (int d = 0; d < out_padding; d++)
            {
                fputc(0x00, outptr);
            }

            // send infile cursor back
            int width = oldwidth * sizeof(RGBTRIPLE);
            fseek(inptr, -width, SEEK_CUR);
        }

        // print a row into outfile
        for (int j = 0; j < oldwidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile n times
            for (int t = 0; t < n; t++)
            {
                fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            }
        }

        // write outfile's padding
        for (int d = 0; d < out_padding; d++)
        {
            fputc(0x00, outptr);
        }

        // skip over infile's padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
