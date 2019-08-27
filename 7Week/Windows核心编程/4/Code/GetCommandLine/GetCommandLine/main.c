#include <stdio.h>
#include <windows.h>
SHSTDAPI_(LPWSTR *)  CommandLineToArgvW(_In_ LPCWSTR lpCmdLine, _Out_ int* pNumArgs);

int main(int argc, char* argv[], char * env[])
{
	int nNumArgs;
	PWSTR *ppArgv = CommandLineToArgvW(GetCommandLineW(), &nNumArgs);

	// Use the arguments...

	// Free the memory block
	HeapFree(GetProcessHeap(), 0, ppArgv);
	return 0;
}