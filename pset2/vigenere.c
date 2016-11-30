/*
 * Compute the vigenere cipher of a user-inputted string text
 */


#include <stdio.h>
#include <ctype.h>
#include <string.h>


int main(int argc,char *argv[]){
    
    if (argc !=2){
        printf("Try again\n");
        return 1;
    }
    else {
        for(int i=0, n=strlen(argv[1]); i<n; i++){
            if (isalpha(argv[1][i])==0){
                    printf("Alphabetical characters only\n");
                    return 1;
                    }
            }
        }
        
    char *key = argv[1];
    char p[300];
    
    fgets(p,100,stdin);
    
    int shift;
    int j=0;
        
    for (int i=0, n=strlen(p), k=strlen(key); i<n; i++){
        
    //keeping track of shift key
        
        //if char is alpha
        if (isalpha(p[i])){ 
            //if char is uppercase
            if (isupper(key[j%k])) {
                shift = key[j%k] - 65;
                }
            //if char is lowercase
            else if (islower(key[j%k])) { 
                shift = key[j%k] - 97;
                }
            j++;
            }    
        
    //print the characters
    
        //if char is uppercase, print with shift key
        if (isupper(p[i])) {
            printf("%c",(((p[i]-65) + shift) % 26) + 65);
            }
        //if char is lowercase, print with shift key
        else if (islower(p[i])) {
            printf("%c",(((p[i]-97) + shift) % 26) + 97); 
            }   
        //for any other chars, don't shift
        else {
            printf("%c",p[i]);
            }
        }
    
    return 0;
    
    }
