#include "the2.h"
#include <cmath>

int pow(int a, int b)
{
    int n=1;
    for(int i=0;i<b;i++)
    {
        n*=a;
    }
    return n;
}


long counting_sort(int* arr, int arraySize, long k, int groupSize,int digit,bool ascending)
{
    long numberOfIterations=0;
    int B[arraySize],C[k]={0};


    for(int i=0;i<arraySize;i++)
    {
        C[(arr[i]/digit) % pow(10,groupSize)]++;
        numberOfIterations++;
    }

    for(long i=1;i<k;i++)
    {
        C[i] += C[i-1];
        numberOfIterations++;
    }
    
    for (int i = arraySize - 1; i >= 0; i--)
    {
        B[C[(arr[i]/digit) % pow(10,groupSize)] - 1] = arr[i];
        C[(arr[i]/digit) % pow(10,groupSize)]--;
        
        numberOfIterations++;
    }

    
    
    for (unsigned i = 0; i < arraySize; i++) 
    {
    arr[i] = B[i];
    numberOfIterations ++;
    }

    return numberOfIterations;
}

long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength)
{
    long numberOfIterations = 0;
    int digit,j = maxDigitLength;
    digit = 1;
    for (j = maxDigitLength; j>=groupSize; j-=groupSize)
    {
                int max_num = pow(10,groupSize);

        numberOfIterations += counting_sort(arr,arraySize, max_num, groupSize,digit,ascending);
        digit*=pow(10,groupSize);        
    }
    if(j>0)
    {
    int max_num = pow(10,j);
    numberOfIterations += counting_sort(arr,arraySize, max_num, j,digit,ascending);        
    }

    
    if(!ascending)
    {
        for (int i = 0, j = arraySize - 1; i < arraySize/2; i++, j--)  
        {     
            int temp = arr[i];  
            arr[i] = arr[j];  
            arr[j] = temp;  
        }  
    }
    
    return numberOfIterations;
}