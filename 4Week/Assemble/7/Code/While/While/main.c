#include <stdio.h>
char a[5] = "BaSiC";
char b[5] = "MinIX";
int main()
{
	int i;
	i = 0;
	do{
		a[i] = a[i] & 0xDF;
		b[i] = b[i] | 0x20;
		i++;
	} while (i < 5);
	getchar();
}