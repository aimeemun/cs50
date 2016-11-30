#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Number of minutes you take a shower: ");
    int min = GetInt();
    printf("minutes: %d\n", min);
    printf("bottles: %d\n", min*12);
}