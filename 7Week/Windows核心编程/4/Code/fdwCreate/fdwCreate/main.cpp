#include <tchar.h>
#include <windows.h>
#include <stdio.h>
int _tmain(int argc, TCHAR* argv[], TCHAR * env[])
{
	TCHAR szPath[MAX_PATH] = TEXT("SubProcess");
	PROCESS_INFORMATION piProcess;
	STARTUPINFO si = { sizeof(si) };
	_tprintf(TEXT("Start to Create Sub Process\n"));
	CreateProcess(NULL, szPath, NULL, NULL,
		TRUE, 0, NULL, NULL, &si, &piProcess);
	return 0;
}