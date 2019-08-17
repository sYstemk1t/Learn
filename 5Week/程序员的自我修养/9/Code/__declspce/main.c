#include <stdio.h>


__declspec(dllexport) double Sub (double a,double b);


int main()
{
	double result = Sub(3.0,2.0);
	printf("result = %f",result);
	return 0;
}