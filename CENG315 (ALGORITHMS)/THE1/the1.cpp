#include "the1.h"
#include <climits>

void insertionSort(int* arr, long &comparison, long &swap, int size) 
{
    int i = 1,x,j;
    while(i<size)
    {
        x = arr[i];
        j = i-1;
        int s = 0;
        while(j>=0 && arr[j]>x)
        {
            arr[j+1] = arr[j];
            j--;
            s++;
        }
        arr[j+1] =x;
        i++;
        swap += s;
        comparison+=(j>=0?s+1:s);
    }
}

void heapify(int* arr[], int size,long& swap,long& comparison,int i=0)
{
	int minimum = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	if(left<size)
	{   
        if(*(arr[left])!=INT_MAX)comparison++;
        if(*(arr[left])<*(arr[minimum]))minimum = left;
		
	}
	if(right<size)
	{  
        if(*(arr[right])!=INT_MAX)comparison++;
		if(*(arr[right])<*(arr[minimum]))minimum = right;	
	}

	if(minimum!=i ) 
	{
		int *temp = arr[i];
		arr[i] = arr[minimum];
		arr[minimum] = temp;
		swap++;
		heapify(arr, size, swap, comparison, minimum);
	}
}

void construct_heap(int *arr[], int size, long& swap, long& comparison)
{
    for (int i = (size / 2) - 1; i >= 0; i--)heapify(arr, size, swap, comparison,i);
}

int kWayMergeSortWithHeap(int* arr, int K, int size, long& comparison, long& swap){
    int number_of_calls = 1;
	int sortedArray[size],ind=0;
    if(K>size) insertionSort(arr, comparison, swap, size);
	else
	{
		int n = size / K;
		int* partitions[K];
		int* heapArr[K];
		for(int i = 0; i<K;i++)
		{	
			number_of_calls+=kWayMergeSortWithHeap(arr+i*n, K, n, comparison, swap);
			partitions[i] = arr+i*n;
			heapArr[i] = partitions[i];
		}
		construct_heap(heapArr,K,swap,comparison);
		while(ind<size)
		{
			sortedArray[ind++]=*(heapArr[0]);

			for(int i=0; i<K;i++)
			{
				if(heapArr[0] == partitions[i])
				{	*(partitions[i])=INT_MAX;
					if(partitions[i]-(arr+i*n) < n-1)partitions[i] = partitions[i]+1;
					heapArr[0] = partitions[i];
				} 
			}			

			heapify(heapArr, K, swap, comparison,0);
		}
		for(int k=0; k<size;k++)arr[k] = sortedArray[k];
	}
	return number_of_calls;
}