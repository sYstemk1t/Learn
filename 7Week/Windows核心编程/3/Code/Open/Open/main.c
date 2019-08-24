#include <windows.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	//// {89AE97EA-F13D-4104-B042-43C010033B48}
	HANDLE h = CreateMutex(NULL, FALSE,
		TEXT("{89AE97EA-F13D-4104-B042-43C010033B48}"));
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		// there is already an instance of this application running.
		// close the object and immediately return.
		CloseHandle(h);
		return (0);
	}

	system("pause");
	CloseHandle(h);
	return 0;
}