#include <stdio.h>
#include <stdlib.h>
int a = 3;
int main1(int argc,char *argv[])
{
	int *p = (int *)malloc(sizeof(int));
	scanf("%d", p);
	printf("%d\r\n", a + *p);
	free(p);
	return 0;
}