# 鼠标

## 鼠标基础



GetSystemMetrics函数来确认鼠标是否存在：

**fMouse = GetSystemMetrics (SM_MOUSEPRESENT) ;**

如果已经安装了鼠标，fMouse将传回TRUE（非0）；如果没有安装，则传回0。然而，在Windows98中，不论鼠标是否安装，此函数都将传回TRUE 。在Microsoft Windows NT中，它可以正常工作。

要确定所安装鼠标其上按键的个数，可使用：

**cButtons = GetSystemMetrics (SM_CMOUSEBUTTONS) ;**

如果没有安装鼠标，那么函数将传回0。然而，在Windows 98下，如果没有安装鼠标，此函数
将传回2。



### 鼠标热点

Windows在显示器上移动一个称为「鼠标光标」的小位图。鼠标光标有一个指向显示器上精确位置的单像素「热点」。

**wndclass.hCursor = LoadCursor (NULL, IDC_ARROW) ;**

Clicking按下并放开一个鼠标按键。
Double-clicking快速按下并放开鼠标按键两次。
Dragging按住鼠标按键并移动鼠标。



### 鼠标击键

LBUTTON：单击

MBUTTON: 双击

RBUTTON：拖动



## 客户区的鼠标消息

**键盘：Windows只把键盘消息发送给拥有输入焦点的窗口。**

**鼠标：只要鼠标跨越窗口或者在某窗口中按下鼠标按键，那么窗口消息处理程序就会收到WM_MOUSEMOVE消息。**



键  	按下  				释放  			按下( 双键)
左  	WM_LBUTTONDOWN  WM_LBUTTONUP  WM_LBUTTONDBLCLK
中  	WM_MBUTTONDOWN  WM_MBUTTONUP  WM_MBUTTONDBLCLK
右  	WM_RBUTTONDOWN  WM_RBUTTONUP  WM_RBUTTONDBLCLK



### lParam参数

如果收到DBLCLK消息，其lParam值含有鼠标的位置：低字组为x坐标，高字组为y坐标，这两个坐标是相对于窗口显示区域左上角的位置

**x = LOWORD (lParam) ;**
**y = HIWORD (lParam) ;**



看过小甲鱼的视频发现，上面的方法已经不适用了，在多显示器的情况下会报错，微软更推荐使用GET_X_LPARAM和GET_Y_LPARAM宏

**GET_X_LPARAM(lParam)	>	x坐标**

**GET_Y_LPARAM(lParam)	>	y坐标**





### wParam参数

**wParam的值指示鼠标按键以及Shift和Ctrl键的状态**

**MK前缀代表[鼠标按键]**

**WM前缀代表[键盘按键]**

MK_LBUTTON  	按下左键
MK_MBUTTON  	按下中键
MK_RBUTTON  	按下右键
MK_SHIFT  		按下Shift键
MK_CONTROL  	按下Ctrl键

比如当收到鼠标消息时，wParam & WM_MK_LBUTTON的值为TRUN，则表示此鼠标坐标是被按下的状态





CONNECT处理三个鼠标消息：
WM_LBUTTONDOWNCONNECT 清除显示区域。
WM_MOUSEMOVE如果按下左键，那么CONNECT就在显示区域中的鼠标位置处绘制一个黑点，并保存该坐标。
WM_LBUTTONUP CONNECT把显示区域中绘制的点与其它每个点连接起来。





## 处理SHIFT键位

当CONNECT接收到一个WM_MOUSEMOVE消息时，它把wParam和MK_LBUTTON进行位与（AND）运算，来确定是否按下了左键。

```c
	case WM_LBUTTONDOWN:
	{
		if (wParam & MK_SHIFT)
		{
			if (wParam & MK_CONTROL)
			{
				MessageBox(hwnd, TEXT("同时按下了CTRL和SHIFT键位"), TEXT("提醒"), 0);
			}
			else
			{
				MessageBox(hwnd, TEXT("同时按下了SHIFT键位"), TEXT("提醒"), 0);
			}
		}
		else
		{
			if (wParam & MK_CONTROL)
			{
				MessageBox(hwnd, TEXT("同时按下了CTRL键位"), TEXT("提醒"), 0);
			}
			else
			{
				MessageBox(hwnd, TEXT("没有同时按下了CTRL和SHIFT键位"), TEXT("提醒"), 0);
			}
		}
	}
```



## 鼠标双击

双击鼠标按键是指在短时间内单击两次。

如果希望您的窗口消息处理程序能够收到双按键的鼠标消息，那么在呼叫RegisterClass初始化窗口类别结构时，必须在窗口风格中包含CS_DBLCLKS标识符：
wndclass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;

如果在窗口风格中未包含CS_DBLCLKS，而使用者在短时间内双击了鼠标按键，那么窗口消息处理程序会接收到下面这些消息：

WM_LBUTTONDOWN
WM_LBUTTONUP
WM_LBUTTONDOWN
WM_LBUTTONUP

如果您的窗口类别风格中包含了CS_DBLCLKS，那么双击时窗口消息处理程序将收到如下消息：
WM_LBUTTONDOWN
WM_LBUTTONUP
WM_LBUTTONDBLCLK
WM_LBUTTONUP

WM_LBUTTONDBLCLK消息简单地替换了第二个WM_LBUTTONDOWN消息。第二次按键（WM_LBUTTONDBLCLK消息）则完成第一次按键以外的事情。





## 非客户区鼠标消息

**只要鼠标在窗口的非客户区移动，窗口过程会收到WM_NCMOUSEMOVE消息**

**NC表示非客户区域消息**

**在非客户区内按下或释放鼠标按钮时，窗口过程也会收到相对应的消息：**

键  按下  					释放  				按下（双击）
左  WM_NCLBUTTONDOWN  WM_NCLBUTTONUP  WM_NCLBUTTONDBLCLK
中  WM_NCMBUTTONDOWN  WM_NCMBUTTONUP  WM_NCMBUTTONDBLCLK
右  WM_NCRBUTTONDOWN  WM_NCRBUTTONUP  WM_NCRBUTTONDBLCLK



**非客户区使用屏幕坐标，客户区使用客户区坐标**

Windows函数将屏幕坐标转换为显示区域坐标或者反之：
ScreenToClient (hwnd, &pt) ;
ClientToScreen (hwnd, &pt) ;





Windows 应 用 程 序 通 常 把 这 个 消 息 传 送 给 DefWindowProc ， 然 后 Windows 用
WM_NCHITTEST消息产生与鼠标位置相关的所有其它鼠标消息。对于非显示区域鼠标消息，在处理WM_NCHITTEST时，从DefWindowProc传回的值将成为鼠标消息中的wParam参数这个值可以是任意非显示区域鼠标消息的wParam值再加上以下内容：

![](F:\Learn\6Week\Windows SDK\7\Img\1.png)



**非客户区鼠标消息的wParam消息的值被设定成一个以“HT”为首的标识符，用于表示非客户区**





