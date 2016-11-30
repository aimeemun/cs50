/**
 * generate.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Generates pseudorandom numbers in [0,LIMIT), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// constant
#define LIMIT 65536

int main(int argc, string argv[])
{
    // if argc is anything but 2 or 3, print this statement
    if (argc != 2 && argc != 3)
    {
        printf("Usage: generate n [s]\n");
        return 1;
    }

    // create an integer variable called n and assign it the converted integer string value in argv[1]
    int n = atoi(argv[1]);

    // if argc equals 3, 
    if (argc == 3)
    {
        srand48((long int) atoi(argv[2])); //initialization function
    }
    else
    {
        srand48((long int) time(NULL)); //initialization function
    }

    //initialize integer variable i to 0, loop while i less than n, increase i after every iteration
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT)); //generates a semirandom nonnegative double precision floating point
    }

    // success
    return 0;
}