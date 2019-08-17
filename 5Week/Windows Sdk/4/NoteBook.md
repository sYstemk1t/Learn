# 输出文字

## 绘制和更新

Windows是一个消息驱动程序。它通过把消息投入应用程序消息队列中或者把消息发送给合适的窗口消息处理程序，将发生的各种事情通知给应用程序



### WM_PAINT消息

大多数Windows程序在WinMain中进入消息循环之前的初始化期间都需要呼叫函数UpdateWindow。Windows利用这个机会给消息处理程序发送第一个WM_PAINT消息。这个消息通知窗口消息程序，绘制显示区域。



**程序使用ScrollWindow或ScrollDC函数滚动显示区域的一部分**

**程序使用InvalidateRect或IncalidateRgn函数刻意产生WM_PAINT消息**





### 有效矩形和无效举行

Windows内部为每个窗口保存一个[绘图消息结构]，这个结构包含了包围无效区域的最小矩形的坐标以及信息。

**窗口消息处理程序可以通过呼叫InvalidateRect使显示区域内的矩形无效**

**窗口消息处理程序在呼叫了BeginPaint之后，整个显示区域有效**







## GDI简介

Windows提供给了**DrawText函数和TextOut函数**



**TextOut(hdc,x,y,psText,iLength);**

psText参数是指向字符串的指针，Ilength是字符串长度，x和y参数定义了字符串在显示区域的开始位置，hdc参数是[设备内容句柄]，它是GDI的重要部分。**每个GDI函数都需要将这个句柄作为函数的第一个参数**





#### 设备内容

句柄只不过是一个对象，Windows以它在内部使用对象。



设备内容（简称DC）实际上是GDI内部保存的数据结构。设备内容与特定的显示内容有关。



在处理WM_PAINT消息时，使用这种方法。它涉及BeginPaint和EndPaint两个函数，这两个
函数需要窗口句柄（作为参数传给窗口消息处理程序）和PAINTSTRUCT结构的变量（在WINUSER.H
表头文件中定义）的地址为参数。Windows程序写作者通常把这一结构变量命名为ps并且在窗口
消息处理程序中定义它：
PAINTSTRUCT ps ;
在处理WM_PAINT消息时，窗口消息处理程序首先呼叫BeginPaint。BeginPaint函数一般在
准备绘制时导致无效区域的背景被擦除。该函数也填入ps结构的字段。BeginPaint传回的值是设备
内容句柄，这一传回值通常被保存在叫做hdc的变量中。它在窗口消息处理程序中的定义如下：

```c
case WM_PAINT:
hdc = BeginPaint (hwnd, &ps) ;
//使用GDI函数
EndPaint (hwnd, &ps) ;
return 0 ;
```





###  绘图信息结构

TextOut (hdc, x, y, psText, iLength) ;

要得到窗口显示区域的设备内容句柄，可以呼叫GetDC来取得句柄，在使用完后呼叫

```c
ReleaseDC：
hdc = GetDC (hwnd) ;
//使用GDI函数
ReleaseDC (hwnd, hdc) ;
```



与BeginPaint和EndPaint一样，GetDC和ReleaseDC函数必须成对地使用。如果在处理某消
息时呼叫GetDC，则必须在退出窗口消息处理程序之前呼叫ReleaseDC。不要在一个消息中呼叫
GetDC却在另一个消息呼叫ReleaseDC。







### 系统字体

要使用GetTextMetrics函数，需要先定义一个结构变量（通常称为tm）：TEXTMETRIC tm ;
在需要确定文字大小时，先取得设备内容句柄，再呼叫GetTextMetrics：

```c
hdc = GetDC (hwnd) ;
GetTextMetrics (hdc, &tm) ;
ReleaseDC (hwnd, hdc) ;
```





## 滚动条

在内定情况下，滚动条的范围是从0（顶部或左部）至100（底部或右部），但将范围改变为更
方便于程序的数值也是很容易的：

```c
SetScrollRange (hwnd, iBar, iMin, iMax, bRedraw) ;
```

参数iBar为SB_VERT或者SB_HORZ，iMin和iMax分别是范围的最小值和最大值。如果想要Windows根据新范围重画滚动条，则设置bRedraw为TRUE（如果在呼叫SetScrollRange后，呼叫
了影响滚动条位置的其它函数，则应该将bRedraw设定为FALSE以避免过多的重画）。

WndProc窗口消息处理程序在处理WM_CREATE消息时增加了两条叙述，以设置垂直滚动条
的范围和初始位置：

```c
SetScrollRange (hwnd, SB_VERT, 0, NUMLINES - 1, FALSE) ;
SetScrollPos (hwnd, SB_VERT, iVscrollPos, TRUE) ;
```





## 建立更好的滚动

