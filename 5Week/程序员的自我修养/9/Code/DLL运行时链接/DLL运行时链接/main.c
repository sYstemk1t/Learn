#include <Windows.h>
#include <stdio.h>

typedef double(*func) (double, double);


int main(int argc,char **argv)
{
	func function;
	double result;

	HINSTANCE hinstLib = LoadLibrary("math.dll");

	if (hinstLib == NULL)
	{
		printf("ERROR : unable ti load DLL\r\n");
		return 1;
	}

	function = (func)GetProcAddress(hinstLib, "Add");

	if (function == NULL)
	{
		printf("ERROR: ubale to find DLL dunction\r\n");
		FreeLibrary(hinstLib);
		return 1;
	}


	result = function(1.0, 2.0);


	FreeLibrary(hinstLib);


	printf("Result = %f\r\n", result);

	system("pause");
	return 0;
}