// This file contains Execises from 2.1 to 2.8 section on C programing by K.N king
#include <stdio.h>

#define PI 3.14159
#define VOLUME_FRACTION (4.0f/3.0f)

int main(void)
{
 /*    printf("Hello, world\n");
    
    system("pause");
    exit(0);
*/
/*
  int height = 12,length = 10,width = 8,volume;
  volume = height * length * width;
  printf("Dimensions of the box with Height: %d",height);
  printf(", Length: %d",length);
  printf(", Width: %d\n",width);
  
  
  printf("Weight is: %d\n", (volume + 165) / 166);
*/
/*
  printf("        *\n");
  printf("       *\n");  
  printf("      *\n");
  printf("*    *\n");
  printf(" *  *\n");  
  printf("   *\n");  
*/
/*  
    //   float radius  = , sphereVolume;
   //sphereVolume = VOLUME_FRACTION * PI * radius * radius * radius;
   
                  // printf("Volume of sphere with 8 meter radius is: %.1f\n",sphereVolume);      
   printf("Enter radius of sphere: ");
   scanf("%f",&radius);
   sphereVolume = VOLUME_FRACTION * PI * radius * radius * radius;
   printf("Volume of sphere with radius %.1f",radius);
   printf(" has volume: %.1f", sphereVolume);
   printf(" cubic meter\n");
*/
/*  
  float dollarAndCents,tax = 5.00f;
  printf("Enter Dollar and cents amount: ");
  scanf("%f",&dollarAndCents);
  printf("\nWith tax added: %.2f\n", (dollarAndCents + tax));
*/  
/*  
  int x,polynomial;
  printf("Enter value of x: ");
  scanf("%d", &x);
  //polynomial = ( (3*(x*x*x*x*x)) + (2*(x*x*x*x)) - (5*(x*x*x)) + (7*x) - 6);
  //polynomial = (((((((((((((3*x)+2)*x)+2)*x)-5)*x)-1)*x)-1)*x)+7)*x)-6;
  polynomial = ((((3 * x + 2) * x - 5) * x - 1) * x + 7) * x - 6;
  
  printf("Value of x: %d",x);
  printf(" give result of: %d\n",polynomial); 
  */
/*
	int dollarAmount,twenties,tens,fives,ones;
	printf("Enter your Dollar amount: ");
	scanf(" %d",&dollarAmount);
	
	twenties = dollarAmount / 20;
	dollarAmount = dollarAmount %20;
	
	tens = dollarAmount / 10;
	dollarAmount = dollarAmount % 10;
	
	fives = dollarAmount / 5;
	dollarAmount = dollarAmount % 5;
	
	ones = dollarAmount;
	
	printf("\nTwenties: %d", twenties);
	printf("\nFives: %d",fives);
	printf("\nTens: %d", tens);
	printf("\nOnes: %d\n", ones);	
*/

	float loan,interest_rate,monthly_payment,first_month,second_month,third_month,interest_increased;
	
	printf("Enter amount of loan: ");
	scanf("%f",&loan);
	printf("Enter interest rate: ");
	scanf("%f",&interest_rate);
	printf("Enter monthly payment: ");
	scanf("%f",&monthly_payment);
	
	interest_rate = ( interest_rate / 100 ) / 12;
	interest_increased = ( loan * interest_rate);
	
	
	first_month = (loan - monthly_payment) + interest_increased;
	printf("\nBalance remaining  after first payment: %.2f",first_month);
	second_month = (first_month - monthly_payment) + interest_increased;
	printf("\nBalance remaining after second month: %.2f",second_month);
	third_month = (second_month - monthly_payment) + interest_increased;
	printf("\nBalance remaining after third month: %.2f", third_month);






  system("pause");
  return 0;
}
