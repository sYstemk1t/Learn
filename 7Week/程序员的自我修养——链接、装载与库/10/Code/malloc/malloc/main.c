#include <stdio.h>

int main()
{
	char *p = (char *)malloc(1000);
	free(p);
}