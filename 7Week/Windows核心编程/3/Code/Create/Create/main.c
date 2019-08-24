#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateMutexW(
_In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
_In_ BOOL bInitialOwner,
_In_opt_ LPCWSTR lpName
);

WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateEventW(
_In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
_In_ BOOL bManualReset,
_In_ BOOL bInitialState,
_In_opt_ LPCWSTR lpName
);

WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateSemaphoreW(
_In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
_In_     LONG lInitialCount,
_In_     LONG lMaximumCount,
_In_opt_ LPCWSTR lpName
);

WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateWaitableTimerW(
_In_opt_ LPSECURITY_ATTRIBUTES lpTimerAttributes,
_In_     BOOL bManualReset,
_In_opt_ LPCWSTR lpTimerName
);

WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateFileMappingW(
_In_ HANDLE hFile,
_In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
_In_ DWORD flProtect,
_In_ DWORD dwMaximumSizeHigh,
_In_ DWORD dwMaximumSizeLow,
_In_opt_ LPCWSTR lpName
);

WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateJobObjectW(
_In_opt_ LPSECURITY_ATTRIBUTES lpJobAttributes,
_In_opt_ LPCWSTR lpName
);

int main()
{
	HANDLE hMutex = CreateMutexW(NULL, FALSE, TEXT("sYstemk1t"));
	HANDLE hSem = CreateSemaphoreW(NULL, 1, 1, TEXT("sYstemk1t"));
	DWORD dwErrorCode = GetLastError();
	return 0;
}