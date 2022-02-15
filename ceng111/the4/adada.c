#include<stdio.h>

int factorial(int a){
    if(a==0 || a== 1) return a;
    return a*factorial(a-1);
}
int main(){

    printf("%d",factorial(31));
    return 31;
}