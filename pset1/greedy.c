#include <stdio.h>
#include <cs50.h>
#include <math.h>


int main(void)
{
    int GetRightValue();
    int counter=0;
    int change = GetRightValue();
   
    int quarters = change/25;
    counter = counter+quarters;
    change = change-(quarters*25);
    
    int dimes = change/10;
    counter = counter+dimes;
    change = change-(dimes*10);
    
    int nickels = change/5;
    counter = counter+nickels;
    change = change-(nickels*5);
    
    int pennies = change/1;
    counter = counter+pennies;
    change = change-(pennies*1);
    
    printf("%i\n",counter);
}



int GetRightValue(void)
{
    float n;
    do{
        printf("Enter change: ");
        n = roundf(GetFloat()*100);
    }
    while(n < 0);
    
    return n;
}