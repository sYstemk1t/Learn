#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	HANDLE hMutex = CreateMutex(&sa, FALSE, TEXT("JeffMutex"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		//Opened a handle to an existing object.
		//sa.lpSecurityDescriptor and the second parameter
		// are ignored.
		printf("Opened a handle to an existing object.\n");
	}
	else
	{
		//Created a brand new object.
		//sa.lpSecurityDescriptor and the second parameter
		//FALSE are used to construct the object.
		printf("Created a brand new object.\n");
	}
	system("pause");
	return 0;
}