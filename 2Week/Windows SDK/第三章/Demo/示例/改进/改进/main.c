#include <windows.h>
//LRESULT是WIN32环境下Windows进程或者回调函数的返回值 
//CALLBACK仅用于修饰回调函数
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//hInstance是当前实例，hPrevInstance是前一个实例（这个程序同时打开多个的时候，一般来说是NULL），
//szCmdLine是传进来的参数，iCmdShow是显示方式（最大化，最小化，隐藏等）
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("MyWindows");   //起一个名字，用于初始化菜单名，窗口类名
	HWND hwnd;	//窗口句柄
	MSG msg;	//消息机制
	WNDCLASS wndclass;	//窗口类结构，看内部实现是一个结构体
	wndclass.style = CS_VREDRAW | CS_HREDRAW;	//拖动窗口时，重新绘制整个窗口
	wndclass.lpfnWndProc = WndProc;	//使用函数来制定窗口进程（必须是回调函数）
	wndclass.cbClsExtra = 0;	//预留的额外空间，一般为 0
	wndclass.cbWndExtra = 0;	//预留的额外空间，一般为 0
	wndclass.hInstance = hInstance;	//引用程序的实例句柄WinMain函数后有写
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);	//用于修改程序的图标
	wndclass.hCursor = wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);  //为所有基于该窗口类的窗口设定一个鼠标指针
	//wndclass.hbrBackground = (HBRUSH)GetStockObject(0);   //这个内置有六个颜色，除了白色，五个灰色...
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);   //白色
	wndclass.lpszMenuName = NULL;	//制定菜单名
	wndclass.lpszClassName = szAppName;		//指定窗口类名,也就是显示名
	if (!RegisterClass(&wndclass))	//传入的是一个指针	//RegisterClass函数的作用是通知系统，你要定义一个新的窗体类型，如果它不是窗口类程序，则退出
	{
		MessageBox(NULL, TEXT("这个程序需要在Windows NT操作系统上运行"), szAppName, 0);    //0应该是代表系统弹出
		return 0;
	}
	hwnd = CreateWindow
		(
		szAppName,  //窗口类名称
		TEXT("我是窗口标题"),	//窗口标题
		WS_OVERLAPPEDWINDOW,	//WS_OVERLAPPEDWINDOW是多种窗口类型的组合
		CW_USEDEFAULT,	//初始化x坐标
		CW_USEDEFAULT,	//初始化y坐标
		CW_USEDEFAULT,	//初始化x方向尺寸
		CW_USEDEFAULT,	//初始化y方向尺寸
		NULL,	//初指向被创建窗口的父窗口或所有者窗口的句柄
		NULL,	//指向窗口菜单句柄，或依据窗口风格指明一个子窗口标识
		hInstance,	//与窗口相关联的模块实例的句柄
		NULL	//指向一个值的指针，该值传递给窗口 WM_CREATE 消息。
		);
	ShowWindow(hwnd, iCmdShow);	// CreateWindowEx 建立窗口以后，这时候，窗口虽已建立，但还没有在屏幕上显示出来,ShowWindows函数设置指定窗口的显示状态
	UpdateWindow(hwnd);	//UpdateWindow 函数绕过应用程序的消息队列，直接发送 WM_PAINT 消息给指定窗口的窗口过程。
	while (GetMessage(&msg, NULL, 0, 0))	//GetMessage把拿到的消息进行填充。
	{
		TranslateMessage(&msg);	//将一些鼠标或者键盘时间进行翻译，翻译称为相对应的字符
		DispatchMessage(&msg);	//对这个消息进行分派
	}
	return msg.wParam;


}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)   //函数实现

{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	switch (message)
	{
	case WM_PAINT:    //WM_PAINT函数绘制窗口
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("我是正文"), -1, &rect,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		return 0;
		/*
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("成功按下左键"),TEXT("鼠标左键事件"),0);
		return 0;
		*/
	case WM_LBUTTONUP:
		MessageBox(hwnd, TEXT("鼠标左键弹起"), TEXT("鼠标左键事件"), 0);
		return 0;
	case WM_NCLBUTTONDOWN:
	{
		MessageBox(hwnd, TEXT("在非客户区啊"), TEXT("鼠标左键事件"), 0);
		return 0;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hwnd, message, wParam, lParam);
}