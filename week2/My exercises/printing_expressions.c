#include<stdio.h>

int main(void){

    int volume, a , b , c;
    
    printf("Enter values for a,b,c: ");
    scanf("%d",&a);
    scanf("%d",&b);
    scanf("%d",&c);
    volume = a*b*c;
    printf("Volume is: %d",volume);
    printf("\nVolume is as well: %d", a*b*c);


    return 0;
}