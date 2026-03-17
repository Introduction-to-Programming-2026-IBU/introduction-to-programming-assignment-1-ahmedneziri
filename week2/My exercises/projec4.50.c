/* Project 4.50 */

#include<stdio.h>

int main(void)
{

	int phoneNumber1,ph_2,ph3;
	printf("Enter phone number [ (xxx) xxx-xxxx]: ");
	scanf("(%d) %d-%d",&phoneNumber1,&ph_2,&ph3);
	
	printf("\nYou entered %d.%d.%d\n",phoneNumber1,ph_2,ph3);
	
	system("pause");
	return 0;
		
	
}
