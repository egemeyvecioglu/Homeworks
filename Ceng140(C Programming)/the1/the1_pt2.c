#include <stdio.h>

void possibilities(int cost[],int gain[], int index, int size, int sum,int sum2,int subset[],int subset2[],int budget,int counter)
{   
    
    if (index > size) {
        printf("%d ",counter);
        if(sum < budget){
            subset[counter] = sum; 
            subset2[counter] = sum2;
            
        }
        else{
            subset[counter] = 0; 
            subset2[counter] = 0;
            
        }
        printf("%d\n",counter);
        return ;
    }
 
    
    possibilities(cost,gain, index + 1, size, sum + cost[index],sum2+gain[index],subset,subset2,budget, 2*counter  );
    
    
    possibilities(cost,gain, index + 1, size, sum, sum2,subset,subset2,budget,  2*counter + 1 ); 
}

int optimal(int A[], int n)
{
    int a;
    if (n == 1 ) return A[0];
    
    a = optimal(A,n-1);

    if(A[n-1] >= a) return A[n-1];
    else return a;
}

int main()
{
    int i,costs[6] , costssubsets[64];
    int gains[6] , gainssubsets[64], budget;
    scanf("%d",&budget);
    for(i=0;i<6;i++){
        scanf("%d %d",&costs[i],&gains[i]);
    }
     
    possibilities(costs,gains, 0, 5, 0, 0, costssubsets,gainssubsets,budget,0);
    for(i=0;i<64;i++)printf("%d-%d\n",costssubsets[i],gainssubsets[i]);
    printf("%d\n",optimal(gainssubsets,64));

    return 0;

}

