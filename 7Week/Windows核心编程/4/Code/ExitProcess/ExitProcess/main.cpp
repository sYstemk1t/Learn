#include <tchar.h>
#include <windows.h>
#include <stdio.h>

class CSomeObj{
public:
	CSomeObj() { printf("Constructor \n"); }
	~CSomeObj() { printf("Destructor \n"); }
};

CSomeObj g_GlobalObj;

int _tmain(int argc, TCHAR* argv[], TCHAR * env[])
{
	CSomeObj LocalObj;
	ExitProcess(0);

	return 0;
}