/* Project 3.50 */

#include<stdio.h>

int main(void)
{
	
	int gs1_prefix,groupIdentifier,publisher_code,itemNumber,checkDigit;
	
	printf("Enter ISBN: ");
	scanf("%d-%d-%d-%d-%d",&gs1_prefix,&groupIdentifier,&publisher_code,&itemNumber,&checkDigit);
	
	printf("\nGS1 prefix: %d",gs1_prefix);
	printf("\nGroup Identifier: %d",groupIdentifier);
	printf("\nPublisher code: %d",publisher_code);
	printf("\nItem Number: %d",itemNumber);
	printf("\nCheck digit: %d",checkDigit);
	printf("\n");
	
	
	system("pause");
	return 0;	
}
