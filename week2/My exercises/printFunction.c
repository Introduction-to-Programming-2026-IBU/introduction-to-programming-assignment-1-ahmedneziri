/* Prints int and float values in various formats */

#include<stdio.h>

int main(void)
{
	int x = 40;
	float y = 839.21f;
	
	printf("%d ~ %5d ~ %-5d ~ %5.3d ~\n", x, x, x , x);
	printf("10.3f ~ %10.3e ~ %-10g\n", y, y, y);
	
	
	system("pause");
	return 0;
}
