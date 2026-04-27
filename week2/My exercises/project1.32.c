/* Project - 1 */

#include <stdio.h>

int main (void)
{
	
	int day,month,year;
	
	printf("Enter a date (mm/dd/yyyy) :");
	scanf("%d/%d/%d", &day,&month,&year);
	
	printf("\nYou entered: %d%.2d%d\n",year,day,month);
	
	system("pause");
	exit(0);
	 
		
}
