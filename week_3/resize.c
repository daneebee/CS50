#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

// STEPS
// Update Header file -> fileSize (bfSize), imageSize (biSizeImage), height (biHeight), width (biWidth)
// Resize Horizontally
// Add padding if width not multiple of 4
// Resize Vertically

int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        printf("usage: ./resize n infile outfile\n");
        return 1;
    }

    // remember filenames
    char *scaleFactor = argv[1];
    char *infile = argv[2];
    char *outfile = argv[3];
    int n = atoi(scaleFactor);

    // simple copy file if n = 1
    /*
    if (n == 1) {
        printf("Please select a scale greater than 1. Exiting...\n");
        return 0;
    }
    */

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

    // determine padding for enlarged file
    int inPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // update header info
    bi.biHeight *= n;
    bi.biWidth *= n;

    // determine padding for enlarged file
    int outPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + outPadding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);


    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight) / n; i < biHeight; i++)
    {
        long currentPos = ftell(inptr);
        printf("current pos: %li\n", currentPos);

        for (int rowNum = 1; rowNum <= n; rowNum++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth / n; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0, factor = n; k < factor; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }

            }

            // add the padding in if required
            for (int t = 0; t < outPadding; t++)
            {
                fputc(0x00, outptr);
            }

            if (rowNum < n)
            {
                int offset = (bi.biWidth / n) * sizeof(RGBTRIPLE);
                fseek(inptr, -offset, SEEK_CUR);
            }
            else
            {
                // skip over padding, if any
                fseek(inptr, inPadding, SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}