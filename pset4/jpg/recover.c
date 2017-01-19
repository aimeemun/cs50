/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 * 
 * Remaining questions: fprintf? uint8_t?
 * 
 */

#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE; // defining 8-bit unsigned integer type called BYTE

BYTE byte_reader[512];
char outname[50];
int num = 0;

int main(int argc, char* argv[])
{
    
    // create warning if image file is not provided
    if (argc != 2){
        fprintf(stderr, "Usage: ./recover image\n");
    }
    
    // put name of image file into an array via pointer into var named infile
    char *infile = argv[1];
    
    FILE *fp = fopen(infile, "r"); /** FILE is an opaque data type **/
    
    // create warning in case file is missing
    if (fp == NULL){
        return 1;
        printf("Could not open file");
    }

    // initially set outptr to NULL
    FILE *outptr = NULL;

    do { 
        // read in 1 block of 512 bytes
        //fread(&byte_reader, 512, 1, fp);
        
        /** STEPS
            a. If there is an outfile open, check to see if the current block of bytes is the start of a new JPEG image
                i. If start of a new JPEG, close current outfile, open a new one, and write to new outfile
               ii. If not the start of a new JPEG, write to current outfile
            b. If there is no outfile open, check to see if the current block of bytes is the start of a new JPEG
                i. If start of a new JPEG, close the current outfile, open a new one, and write to new outfile
               ii. If not the start of a new JPEG, continue to next loop
        **/
        
        // IF the outfile is already open...
        if (outptr != NULL) {
            
            // Check to see if we have the start of a new JPEG. If so, close the current outfile and open a new one 
            if ( byte_reader[0] == 0xff && byte_reader[1] == 0xd8 && byte_reader[2] == 0xff && 
                (byte_reader[3] == 0xe0 || byte_reader[3] <= 0xe1) ){ // am I reading this correctly?
            
                fclose(outptr);
            
                /** sprintf() works like printf() 
                  * The only difference is that the composed string is not output to the standard output, 
                  * but is placed in array of characters passed as the first parameter.
                  * Source: http://mcs.uwsuper.edu/sb/202/Intro/printf **/
                
                sprintf(outname, "%03d.jpg", num);  
                num = num + 1;
                
                outptr = fopen(outname, "w");
                fwrite(&byte_reader, 512, 1, outptr);
            }
            
            // If it's not the start of a new JPEG, write the bytes to the current outfile
            else{
                fwrite(&byte_reader, 512, 1, outptr);
            }
            
        }
        
        // ELSE if the file is not open...
        else {
            
            // Check to see if we are at the start of a JPEG
            if ( byte_reader[0] == 0xff && byte_reader[1] == 0xd8 && byte_reader[2] == 0xff && 
                (byte_reader[3] == 0xe0 || byte_reader[3] <= 0xe1) ){
        
                sprintf(outname, "%03d.jpg", num);  
                num = num + 1;
                        
                outptr = fopen(outname, "w");
                fwrite(&byte_reader, 512, 1, outptr);

            }
            
            // If we are not at the start of a new JPEG and the outfile is not open, continue to the next iteration of the loop
            else{
                continue;
            }
            
        }

        
    } while (fread(&byte_reader, 512, 1, fp) == 1); // repeat until you reach EOF
    

    return 0;
    
}
