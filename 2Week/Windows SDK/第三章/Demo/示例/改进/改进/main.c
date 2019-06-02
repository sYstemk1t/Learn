#include <windows.h>
//LRESULT��WIN32������Windows���̻��߻ص������ķ���ֵ 
//CALLBACK���������λص�����
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//hInstance�ǵ�ǰʵ����hPrevInstance��ǰһ��ʵ�����������ͬʱ�򿪶����ʱ��һ����˵��NULL����
//szCmdLine�Ǵ������Ĳ�����iCmdShow����ʾ��ʽ����󻯣���С�������صȣ�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyWindows");   //��һ�����֣����ڳ�ʼ���˵�������������
	HWND hwnd;	//���ھ��
	MSG msg;	//��Ϣ����
	WNDCLASS wndclass;	//������ṹ�����ڲ�ʵ����һ���ṹ��
	wndclass.style = CS_VREDRAW | CS_HREDRAW;	//�϶�����ʱ�����»�����������
	wndclass.lpfnWndProc = WndProc;	//ʹ�ú������ƶ����ڽ��̣������ǻص�������
	wndclass.cbClsExtra = 0;	//Ԥ���Ķ���ռ䣬һ��Ϊ 0
	wndclass.cbWndExtra = 0;	//Ԥ���Ķ���ռ䣬һ��Ϊ 0
	wndclass.hInstance = hInstance;	//���ó����ʵ�����WinMain��������д
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//�����޸ĳ����ͼ��
	wndclass.hCursor = wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //Ϊ���л��ڸô�����Ĵ����趨һ�����ָ��
	//wndclass.hbrBackground = (HBRUSH)GetStockObject(0);   //���������������ɫ�����˰�ɫ�������ɫ...
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //��ɫ
	wndclass.lpszMenuName = NULL;	//�ƶ��˵���
	wndclass.lpszClassName = szAppName;		//ָ����������,Ҳ������ʾ��
	if (!RegisterClass(&wndclass))	//�������һ��ָ��	//RegisterClass������������֪ͨϵͳ����Ҫ����һ���µĴ������ͣ���������Ǵ�����������˳�
	{
		MessageBox(NULL, TEXT("���������Ҫ��Windows NT����ϵͳ������"), szAppName, 0);    //0Ӧ���Ǵ���ϵͳ����
		return 0;
	}
	hwnd = CreateWindow
		(
		szAppName,  //����������
		TEXT("���Ǵ��ڱ���"),	//���ڱ���
		WS_OVERLAPPEDWINDOW,	//WS_OVERLAPPEDWINDOW�Ƕ��ִ������͵����
		CW_USEDEFAULT,	//��ʼ��x����
		CW_USEDEFAULT,	//��ʼ��y����
		CW_USEDEFAULT,	//��ʼ��x����ߴ�
		CW_USEDEFAULT,	//��ʼ��y����ߴ�
		NULL,	//��ָ�򱻴������ڵĸ����ڻ������ߴ��ڵľ��
		NULL,	//ָ�򴰿ڲ˵�����������ݴ��ڷ��ָ��һ���Ӵ��ڱ�ʶ
		hInstance,	//�봰���������ģ��ʵ���ľ��
		NULL	//ָ��һ��ֵ��ָ�룬��ֵ���ݸ����� WM_CREATE ��Ϣ��
		);
	ShowWindow(hwnd, iCmdShow);	// CreateWindowEx ���������Ժ���ʱ�򣬴������ѽ���������û������Ļ����ʾ����,ShowWindows��������ָ�����ڵ���ʾ״̬
	UpdateWindow(hwnd);	//UpdateWindow �����ƹ�Ӧ�ó������Ϣ���У�ֱ�ӷ��� WM_PAINT ��Ϣ��ָ�����ڵĴ��ڹ��̡�
	while (GetMessage(&msg, NULL, 0, 0))	//GetMessage���õ�����Ϣ������䡣
	{
		TranslateMessage(&msg);	//��һЩ�����߼���ʱ����з��룬�����Ϊ���Ӧ���ַ�
		DispatchMessage(&msg);	//�������Ϣ���з���
	}
	return msg.wParam;


}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   //����ʵ��

{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (message)
	{
	case WM_PAINT:    //WM_PAINT�������ƴ���
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("��������"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
		/*
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("�ɹ��������"),TEXT("�������¼�"),0);
		return 0;
		*/
	case WM_LBUTTONUP:
		MessageBox(hwnd, TEXT("����������"), TEXT("�������¼�"), 0);
		return 0;
	case WM_NCLBUTTONDOWN:
	{
		MessageBox(hwnd, TEXT("�ڷǿͻ�����"), TEXT("�������¼�"), 0);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}