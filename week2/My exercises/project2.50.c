/* Project 2.50 */

#include<stdio.h>

int main(void){
	
	int itemNumber;
	float unitPrice;
	int mm,dd,yyyy;
	
	printf("Enter item number: ");
	scanf("%d", &itemNumber);
	
	printf("\nEnter unit price: ");
	scanf("%f",&unitPrice);
	
	printf("\nEnter purchase date (mm/dd/yyyy): ");
	scanf("%d/%d/%d", &mm,&dd,&yyyy);
	printf("\n\n");	
	printf("Item\t\tUnit\t\tPurchase\n");
	printf("\t\tPrice\t\tDate\n");
	printf("%d\t\t$%7.2f\t%d/%d/%d",itemNumber,unitPrice,mm,dd,yyyy);
	
		
}
