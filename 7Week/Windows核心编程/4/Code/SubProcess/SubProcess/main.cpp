#include <tchar.h>
#include <windows.h>
#include <stdio.h>
int _tmain(int argc, TCHAR* argv[], TCHAR * env[])
{
	_tprintf(TEXT("Print from the Sub Process\n"));
	return 0;
}