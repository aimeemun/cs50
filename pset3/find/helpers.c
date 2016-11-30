/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"
#include <string.h>
#include <stdio.h>

bool binary(int low,int high,int values[], int value);



/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0) {
        return false;
    }
    
    //implement a binary search algorithm
    return binary(0, n-1, values, value);
}


bool binary(int low,int high,int values[],int value){
    
    //base case
    if (high < low){
        return false;
    }
    
    int mid = (low+high)/2;
    
    // printf("low: %i high: %i mid: %i needle: %i\n",low,high,mid,values[mid]);

    if (values[mid] == value){
        return true;
    }
    else if (values[mid] > value){
        return binary(low,mid-1,values,value);
    }
    else{
        return binary(mid+1,high,values,value);
    }
        
}



/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{

    // implement bubble sorting algorithm
    
    int swaps;
    
    do {    
        swaps=0;
    
        for (int i=0; i < n-1; i++){
        
            if (values[i] > values[i+1]){
                int temp = values[i];
                values[i] = values[i+1];
                values[i+1] = temp;
                swaps++;
            }
    }
    
    } while(swaps !=0);

    
}