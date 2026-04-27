/* Read inputs in different conversional specification */

#include<stdio.h>

int main(void){
	
	float ex_1 = 2.16,ex_2 = 12.2536278;
	float de_1 = 3.141,de_2 = 2.71828;
	
	printf("Exponential notation, left-justified with 8field, p = 1 for %.2f",ex_1);
	printf(": %-8.1e\n",ex_1);
	printf("Exponential ex_2 with right-justified in 10fields, six digits after decimalpoint of %.7f",ex_2);
	printf("\n%21.6e\n",ex_2);
	printf("Exponential ex_3; left-justified in field of size 8;thre digits after decimal point for %.3f: ",de_1);
	printf("%11.3f\n",de_1);
	printf("\nExponetial ex_4;right-justified in field of size 6; no digits after the decimal point %.5f: ",de_2);
	printf("\n%13.0f\n", de_2); 
	
	
	
	system("pause");
}
