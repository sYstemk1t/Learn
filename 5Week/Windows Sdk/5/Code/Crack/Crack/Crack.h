#pragma once

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ�ļ����ų�����ʹ�õ�����
#define _CRT_SECURE_NO_WARNINGS

// Windows ͷ�ļ�
#include <windows.h>
#include <stdio.h>


__declspec(selectany) HHOOK g_hHook = NULL;

//��װ����
extern "C" __declspec(dllexport) BOOL InstallHook();

//ж�ع���
extern "C" __declspec(dllexport) BOOL UninstallHook();

//���Ӵ�����
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);