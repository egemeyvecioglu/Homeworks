#include "the3.h"

#include<iostream>
#define start(x) (x)[0]
#define end(x) (x)[1]
using namespace std;
int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
        
    number_of_calls+=1;
    int N = i,M;
    if(i == 0){
        return len[0];
    }

    if(number_of_calls==1)
    {
        int a=0;
        bool matches;
        for(int n=0;n<N;n++)
        {
            int mk=recursive_sln(n,arr,len,number_of_calls);
            matches =(start(arr[N]) =='S' && end(arr[n]) == 'S')||(start(arr[N]) =='O' && end(arr[n]) == 'I')||(start(arr[N]) =='I' && end(arr[n]) == 'O');
            if(matches)mk+=len[N];
            if(mk>a)a=mk;
        }    

        return a;
    }

    else
    {
        //cout<<"ME\n";
        int a=0,b=0;
        int j;
        bool matches=false;
        bool equals=false;
        int c=-1,u=-1;
        for(j=N-1;j>=0;j--)
        {
            equals = (end(arr[N])==end(arr[j]));
            if(equals && j>c)c=j;

            matches =(start(arr[N]) =='S' && end(arr[j]) == 'S')||(start(arr[N]) =='O' && end(arr[j]) == 'I')||(start(arr[N]) =='I' && end(arr[j]) == 'O');
            if(matches && j>u)u=j;
        }
        cout<<"ME\n";
        a=recursive_sln(c,arr,len,number_of_calls);
        b=recursive_sln(u,arr,len,number_of_calls)+len[N];
        return a>b?a:b;
    }

}



int memoization_sln(int i, char**& arr, int*& len, int**& mem) { //memoization

    /*if(i==0)return len[i];
    
    if(end(arr[i])=='O')
    {
        
    }

    if(start(arr[i]))


    /*
        if (m == 0 || n == 0)
        return 0;
 
    // if the same state has already been
    // computed
    if (dp[m - 1][n - 1] != -1)
        return dp[m - 1][n - 1];
 
    // if equal, then we store the value of the
    // function call
    if (X[m - 1] == Y[n - 1]) {
 
        // store it in arr to avoid further repetitive
        // work in future function calls
        dp[m - 1][n - 1] = 1 + lcs(X, Y, m - 1, n - 1, dp);
 
        return dp[m - 1][n - 1];
    }
    else {
 
        // store it in arr to avoid further repetitive
        // work in future function calls
        dp[m - 1][n - 1] = max(lcs(X, Y, m, n - 1, dp),
                               lcs(X, Y, m - 1, n, dp));
 
        return dp[m - 1][n - 1];
    }
}*/

    return 0; // this is a dummy return value. YOU SHOULD CHANGE THIS!
}



int dp_sln(int size, char**& arr, int*& len, int**& mem) { //dynamic programming
    
    for(int i=0;i<3;i++)
    {
        mem[0][i]=0;
    }
    if(end(arr[0])=='I')mem[0][0]+=len[0];
    else if(end(arr[0])=='O')mem[0][1]+=len[0];
    else if(end(arr[0])=='S')mem[0][2]+=len[0];

    int kkk;
    for(int i=1;i<size;i++)
    {
        if(start(arr[i])=='I')
        {
            kkk=len[i] + mem[i-1][1];
            if(end(arr[i])=='I')
            {
                mem[i][0]=kkk>mem[i-1][0]?kkk:mem[i-1][0];
                mem[i][1]=mem[i-1][1];
                mem[i][2]=mem[i-1][2];
            }
            else if(end(arr[i])=='O')
            {

                mem[i][1]=kkk>mem[i-1][1]?kkk:mem[i-1][1];
                mem[i][0]=mem[i-1][0];
                mem[i][2]=mem[i-1][2];
            }    
            else if(end(arr[i])=='S')
            {
                mem[i][2]=kkk>mem[i-1][2]?kkk:mem[i-1][2];
                mem[i][1]=mem[i-1][1];
                mem[i][0]=mem[i-1][0];
            }
        }
        
        else if(start(arr[i])=='O')
        {
            kkk=len[i] + mem[i-1][0];
            if(end(arr[i])=='I')
            {
                mem[i][0]=kkk>mem[i-1][0]?kkk:mem[i-1][0];
                mem[i][1]=mem[i-1][1];
                mem[i][2]=mem[i-1][2];
            }
            
            else if(end(arr[i])=='O')
            {
                mem[i][1]=kkk>mem[i-1][1]?kkk:mem[i-1][1];
                mem[i][0]=mem[i-1][0];
                mem[i][2]=mem[i-1][2];
            } 
            else if(end(arr[i])=='S')
            {
                mem[i][2]=kkk>mem[i-1][2]?kkk:mem[i-1][2];
                mem[i][1]=mem[i-1][1];
                mem[i][0]=mem[i-1][0];
            }     
        }
        else if(start(arr[i])=='S')
        {
            kkk=len[i] + mem[i-1][2];
            if(end(arr[i])=='I')
            {
                mem[i][0]=kkk>mem[i-1][0]?kkk:mem[i-1][0];  
                mem[i][1]=mem[i-1][1];
                mem[i][2]=mem[i-1][2];
            } 
            else if(end(arr[i])=='O')
            {
                mem[i][1]=kkk>mem[i-1][1]?kkk:mem[i-1][1];
                mem[i][0]=mem[i-1][0];
                mem[i][2]=mem[i-1][2];
            } 
            else if(end(arr[i])=='S')
            {
                mem[i][2]=kkk>mem[i-1][2]?kkk:mem[i-1][2];  
                mem[i][1]=mem[i-1][1];
                mem[i][0]=mem[i-1][0];
            }          
        }
   
    }
    int max=0;
    for(int j=0;j<3;j++)
    {
        if(mem[size-1][j]>max)max=mem[size-1][j];
    }
    return max; 
}

