#include<stdio.h>

/*  Reading imputs provided by use for int and float variables  */

int main(void)
{
    int im1;
    float im2;

    printf("Enter value as integer: ");
    scanf("%d",&im1);
    printf("Enter value number with decimal point: ");
    scanf("%f",&im2);

    printf("Integer value is: %d",im1);
    printf("\nFloat number is: %.1f", im2);

}