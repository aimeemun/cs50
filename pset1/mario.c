#include <stdio.h>
#include <cs50.h>

int GetPositiveInt();

int main(void)
{
    int Height = GetPositiveInt();
    
    for (int row = 0; row < Height; row++)
    {
        for (int space = Height-row-1; space != 0; space--)
        {
            printf(" ");
        }
        
        for (int hash = Height-row; hash < Height+2; hash++)
        {
            printf("#");
        }
        printf("\n");
        
    }
    
}    

/* Example (height=3):
 *
 *     ## spaces: 3-0-1 = 2, hashes: 3-0 < 5
 *    ### spaces: 3-1-1 = 1, hashes: 3-1 < 5
 *   #### spaces: 3-2-1 = 0, hashes: 3-2 < 5*/


int GetPositiveInt(void)
{
    int n;
    do
    {
        printf("Height: ");
        n = GetInt();
    }
    while (n < 0 || n > 23);
    
    return n;
}



