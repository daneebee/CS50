#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // check for only one arg being passed
    if (argc != 2)
    {
        fprintf(stderr, "usage: ./recover image\n");
        return 1;
    }

    int c;
    int buffer[512];
    int fileCounter = 0;
    FILE *outptr;
    long fileLen = 0;

    // open raw file
    FILE *inptr = fopen(argv[1], "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s\n", argv[1]);
        return 2;
    }

    fseek(inptr, 0, SEEK_END);
    fileLen = ftell(inptr);
    fseek(inptr, 0, SEEK_SET);

    //find first non-zero byte of file
    for (int t = 0; t < fileLen - 1; t++)
    {
        fread(&c, 1, 1, inptr);
        if (c == 0xff)
        {
            fseek(inptr, -1, SEEK_CUR);
            break;
        }
    }

    for (int i = 0; i < fileLen - 1; i++)
    {
        int header[4];

        // loop through first 4 elements of block to get header bytes
        for (int j = 0; j < 4; j++)
        {
            fread(&header[j], 1, 1, inptr);
        }

        fseek(inptr, -4, SEEK_CUR);

        // read infile in 512 byte blocks
        fread(&buffer, 1, 512, inptr);

        // create new file if correct byte combo is found
        if (header[0] == 0xff &&
            header[1] == 0xd8 &&
            header[2] == 0xff &&
            (header[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            // set filename
            char filename[7];
            sprintf(filename, "%03i.jpg", fileCounter++);

            // open new file and check for existence
            outptr = fopen(filename, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Error creating new file.");
                return 3;
            }
            fwrite(&buffer, 1, 512, outptr);
        }
        else
            fwrite(&buffer, 1, 512, outptr);

        if (ftell(inptr) == fileLen)
            break;
    }

    // clean up
    fclose(inptr);
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    return 0;
}
