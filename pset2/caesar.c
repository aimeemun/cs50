#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    
    int k;
    
    if (argc==2){
        k = atoi(argv[1]);
        
        if (k<0){
           printf("This is a negative number\n");
           return 1;
            }
            
        }
    
    else{
        printf("Add a key\n");
        return 1;
    }

    string Text = GetString();
    
    for (int i=0, n=strlen(Text); i<n ;i++) {
        if (isupper(Text[i])){
            printf("%c",((Text[i]-65) + k) % 26 + 65);
        }
        else if (islower(Text[i])){
            printf("%c",((Text[i]-97) + k) % 26 + 97);
        }
        else {
            printf("%c",Text[i]);
        }
        
    }
    
    printf("\n");

    return 0;
}