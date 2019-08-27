#include <stdio.h>
#include <windows.h>

WINBASEAPI
_When_(lpModuleName == NULL, _Ret_notnull_)
_When_(lpModuleName != NULL, _Ret_maybenull_)
HMODULE
WINAPI
GetModuleHandleW(
_In_opt_ LPCWSTR lpModuleName
);

int main()
{
	HANDLE hInstExe = GetModuleHandle(NULL);
	return 0;
}