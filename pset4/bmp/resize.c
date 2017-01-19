/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a bitmap by a factor of n using the recopy method
 * 
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile\n");
        return 1;
    }


    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    if ( n > 100 || n < 1){
        printf("n must be between 1 and 100, inclusive\n");
        return 1;
    } 

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER. Reading in small.bmp's info header into &bi
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    // determine padding for scanlines
    int padding =  (4 - ((bi.biWidth) * sizeof(RGBTRIPLE)) % 4) % 4;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // determine new padding for output file
    int padding_o =  (4 - ((bi.biWidth*n) * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // write outfile's BITMAPFILEHEADER & BITMAPINFOHEADER
    BITMAPFILEHEADER bf_new = bf;
    BITMAPINFOHEADER bi_new = bi;
    
    bf_new.bfSize = sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER) + bi_new.biSizeImage;
    
    fwrite(&bf_new, sizeof(BITMAPFILEHEADER), 1, outptr);

    bi_new.biWidth = bi.biWidth*n;
    bi_new.biHeight = bi.biHeight * n;
    bi_new.biSizeImage = (bi_new.biWidth*sizeof(RGBTRIPLE) + padding_o) * abs(bi_new.biHeight);
    
    fwrite(&bi_new, sizeof(BITMAPINFOHEADER), 1, outptr);

    
    // iterate over infile's scanlines
    for (int i = 0, biHeightr = abs(bi.biHeight); i < biHeightr; i++)
    {
        // write this row n-1 times
        for (int f = 0; f < n-1; f++)
        
            {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // write RGB triple n times to the output file
                for (int h = 0; h < n; h++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                    }
            }
                    
                // skip over padding in the input file, if any, before moving to the next line
                fseek(inptr, padding, SEEK_CUR);
                    
                // add the necessary padding for the new file
                for (int k = 0; k < padding_o; k++)
                    {
                    fputc(0x00, outptr);
                    }
                
            
            // return cursor back to beginning of the row
            fseek(inptr, -(long int) ((bi.biWidth * sizeof(RGBTRIPLE)) + padding), SEEK_CUR);
            
            }
            
        // iterate over pixels in scanline one last time
        for (int e = 0; e < bi.biWidth; e++)
            {
           
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
            // write one last time to the output file
            for (int r = 0; r < n; r++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);    
                }
                
            }
            
            // add the necessary padding for the new file
            for (int u = 0; u < padding_o; u++)
                {
                fputc(0x00, outptr);
                }
        
            // skip over padding in the input file, if any, before moving to the next row of pixels
            fseek(inptr, padding, SEEK_CUR);
    }
                    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
