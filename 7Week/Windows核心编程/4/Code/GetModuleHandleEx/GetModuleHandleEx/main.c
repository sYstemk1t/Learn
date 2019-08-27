#include <tchar.h>
#include <windows.h>

extern "C" const IMAGE_DOS_HEADER	__ImageBase;


void DumpModule() {
	// Get the base address of the running application.
	// Can be different from the running module if this code is in a DLL.
	HMODULE hModule = GetModuleHandle(NULL);
	_tprintf(TEXT("with GetModuleHandle(NULL) = 0x%x\r\n"), hModule);

	// Use the pseudo-variable __ImageBase to get
	// the address of the current module hModule/hInstance.
	_tprintf(TEXT("with __ImageBase = 0x%x\r\n"), (HINSTANCE)&__ImageBase);

	// Pass the address of the current method DumpModule
	// as parameter to GetModuleHandleEx to get the address
	// of the current module hModule/hInstance.
	hModule = NULL;
	GetModuleHandleEx(
		GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
		(PCTSTR)DumpModule,
		&hModule);
	_tprintf(TEXT("with GetModuleHandleEx = 0x%x\r\n"), hModule);
}

int main(int argc, char* argv[], char * env[])
{
	DumpModule();
	return 0;
}