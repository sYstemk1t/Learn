#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *f = fopen("test.dat", "wb");
	if (f == NULL)
	{
		return -1;
	}
	fwrite("321",3,1,f);
	fclose(f);
	return 0;
}