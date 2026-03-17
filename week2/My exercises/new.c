/* This is new project in new IDE  */
    
#include<stdio.h>

#define PI 3.141519f

int main(void){
    
    float height, width, renctangle_area, radius, circleArea;
    
          printf(" *** CALCULATING AREA OF RENTANGLE AND CIRCLE ***\n");
    
    printf("Enter value for height of rectangle: ");
    scanf("%f",&height);
    printf("Enter value for width: ");
    scanf("%f",&width);
    renctangle_area = height * width;
    printf("Area of renctangle is: %.1f",renctangle_area);
    printf("\n");
    
    printf("Enter value of circle radius: ");
    scanf("%f", &radius);
    circleArea = PI * radius * radius;
   
    printf("Area of circle is: %.1f",circleArea);
    printf("\n");
    system("pause");
    
    return 0;
}
