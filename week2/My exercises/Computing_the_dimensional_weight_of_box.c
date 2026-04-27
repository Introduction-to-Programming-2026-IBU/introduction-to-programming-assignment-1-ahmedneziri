#include<stdio.h>

    /*  Computes the dimensional weight of a 
        box from input provided by the use  */ 
    

int main(void){

    int height, length, width, volume, weight;
    
    printf("Enter height of the box: ");
    scanf("%d", &height);
    printf("Enter length of the box: ");
    scanf("%d",&length);
    printf("Enter width of the box: ");
    scanf("%d",&width);

    
    volume = height * width * length;
    weight = (volume + 165) / 166;
    
    printf("Volume is: %d\n",volume);
    printf("Dimensional weight is: %d",weight);


    return 0;
}