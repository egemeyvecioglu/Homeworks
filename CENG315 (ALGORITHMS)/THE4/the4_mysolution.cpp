#include "the4.h"

int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //dynamic programming

    for(int box1=0;box1<=ncol1;box1++)
    {
        for(int box2=0;box2<=ncol2;box2++)
        {
            if(box2 == 0 and box1 == 0) mem[box1][box2] = 0;
            else if(box2==0)
            {
                mem[box1][box2] = mem[box1-1][box2];
                for(int k=0;k<nrow;k++)if(arr1[k][box1-1] != '-')mem[box1][box2] += 1;
            }
            else if(box1==0)
            {
                mem[box1][box2] = mem[box1][box2-1];
                for(int k = 0;k<nrow;k++)if(arr2[k][box2-1] != '-')mem[box1][box2] += 1;
            }
            else
            {
                 int total_cost = mem[box1][box2-1]-mem[0][box2-1] + mem[0][box2];
                 for(int j=0;j<=box1-1;j++)
                 {
                     char b1[nrow] ,b2[nrow];
                     int replacement_cost = 0;
                     for(int i=0;i<nrow;i++)
                     {
                         b1[i] = arr1[i][j];
                         b2[i] = arr2[i][box2-1];
                         if(arr1[i][j] != arr2[i][box2-1])
                         {
                             if(arr1[i][j]=='-' or arr2[i][box2-1]=='-')replacement_cost+=2;
                             else replacement_cost+=1;
                         }
                     }
                     
                    int immediate_cost = replacement_cost + mem[j][box2-1] + mem[box1][0]-mem[j+1][0];;
                    if(immediate_cost<total_cost)total_cost=immediate_cost;

                    for (int mk=0; mk<nrow-1; mk++)
                    {
                        for (int km=0; km<nrow-1-mk; km++)
                        {
                            if (b1[km] > b1[km+1])
                            {
                                char temp=b1[km];
                                b1[km] =  b1[km+1];
                                b1[km+1] = temp;
                            }
                           if (b2[km] > b2[km+1])
                            {
                                char temp=b2[km];
                                b2[km] =  b2[km+1];
                                b2[km+1] = temp;
                            }
                        }
                    }
                    

                    for(int messi =0;b1[messi]==b2[messi];messi++)
                    if(messi == nrow)
                    {
                        int reorder_cost=0;
                        for(int uwu =0;uwu<nrow;uwu++)
                        {
                            if(arr1[uwu][box1-1] != arr2[uwu][box2-1])reorder_cost+=1;   
                        }
                        int immediate_cost = reorder_cost + mem[j][box2-1] + mem[box1][0]-mem[j+1][0];;
                        if(immediate_cost<total_cost)total_cost=immediate_cost;
                    }
                    
                 }
                 
                 mem[box1][box2] = total_cost;
            }
        }
    }

    return mem[ncol1][ncol2];
}