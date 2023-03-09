#include <stdio.h>
#define CARD_COUNT 100

void sort(int arr[],int length){
    int i,k;
    for(i=0;i<length;i++){
        for(k=1;k<length;k++){
            if(arr[k-1]<arr[k]){
                int temp;
                temp=arr[k-1];
                arr[k-1]=arr[k];
                arr[k]=temp;
            }
        }

    }
}

int is_in(int arr[],int length,int num){
    int i,val = 0;
    for(i=0;i<length;i++){
        if(num==arr[i]) val += 1;
    }
    return val;
}

int main(){

    int g[3]={0,0,0},n[2]={0,0},i,lastg[1],j;   
    int gurbuz_score = 0,nazli_score = 0;
    scanf("%d %d %d %d %d",&g[0],&g[1],&g[2],&n[0],&n[1]);
    sort(n,2);sort(g,3);

    /*if(g[0]>n[0]){
        int newg[2],newn[1];

        gurbuz_score += 1;
        
        for(i=0;i<2;i++) newg[i] = g[i+1];
        
        newn[0] = n[1];
        
        if(newg[0]>newn[0]){
            gurbuz_score += 1;
            lastg[0]=newg[1];
        }
        else{
            nazli_score += 1;
            lastg[0]=newg[0];

        }

    }
    else{
        int newg[2],newn[1];
        nazli_score += 1;
        for(i=0;i<2;i++) newg[i] = g[i];
        newn[0] = n[1];

        if(newg[0]>newn[0]){
            gurbuz_score += 1;
            if(newg[1]>newn[0]) lastg[0]=newg[0];
            else lastg[0]=newg[1];
            
        }
        else{
            nazli_score += 1;
            lastg[0]=newg[0];

        }

    }*/
    for(j=2;j>0;j--){
    	int i=0;
    	if(g[i]>n[i]){

        	gurbuz_score += 1;
        
        	g[i] = g[i+1];
        	n[i] = n[i+1];
        }
        else{
        	nazli_score += 1;
        	n[i] = n[i+1];
        	g[i] = g[i+1];
		}
    }
    if(gurbuz_score == 2) printf("WITHDRAW\n");
    else{
        for(i=1;i<=CARD_COUNT;i++){
        if((i>g[0]) && (is_in(g,3,i)) == 0 && (is_in(n,2,i)) == 0){
            printf("%d\n",i);
            break;
        }
    }
    }
    
    
    return 0;
}