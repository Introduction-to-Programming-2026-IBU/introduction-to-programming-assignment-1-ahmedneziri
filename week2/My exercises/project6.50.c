/*Project 6.50*/

#include<stdio.h>

int main(void)
{

	int sum,x1,y1,x,y,numerator1,numerator2,denominator1,denominator2;
	
	printf("Enter two fractions seperated by a plus sign: ");
	scanf("%d/%d+%d/%d",&numerator1,&denominator1,&numerator2,&denominator2);
	
	x1 = (denominator1*denominator2) / denominator1 * numerator1; 
	y1 = (denominator1*denominator2) / denominator2 * numerator2;
	x =	denominator1 * denominator2;
	sum = x1 + y1;	
	
	printf("The sum is: %d/%d\n",sum, x); 

	system("pause");
	return 0;
}

