#include <stdio.h>
#include <windows.h>

int main(int argc,TCHAR* argv[],TCHAR * env[])
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	TCHAR szCommandLine[] = TEXT("NOTEPAD");
	CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	return 0;
}