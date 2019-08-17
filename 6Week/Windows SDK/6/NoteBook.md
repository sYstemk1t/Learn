# 键盘

## 键盘消息

**击键消息：**

- WM_KEYDOWN
- WM_KEYUP
- WM_SYSKEYDOWN
- WM_SYSKEYUP

**字符消息：**

- WM_CHAR
- WM_DEADCHAR
- WM_SYSCHAR
- WM_SYSDEADCHAR

击键消息：当用户按下键盘的一瞬间产生的消息

字符消息：如Alt等键



![](F:\Learn\6Week\Windows SDK\6\Img\1.png)



## 按键消息

当您按下一个键时，Windows把WM_KEYDOWN或者WM_SYSKEYDOWN消息放入有输入焦
点的窗口的消息队列；当您释放一个键时，Windows把WM_KEYUP或者WM_SYSKEYUP消息放入
消息队列中。

​			键按下  				键释放
非系统键 	 WM_KEYDOWN  		WM_KEYUP
系统键		WM_SYSKEYDOWN 	 WM_SYSKEYUP





## 系统按键与非系统按键

WM_SYSKEYDOWN和WM_SYSKEYUP中的「SYS」代表「系统」；



## 重复计数

重复计数是该消息所表示的按键次数，大多数情况下，重复计数设定为1



## OEM扫描码

OEM扫描码是由硬件（键盘）产生的代码。



## 使用按键消息

WM_SYSKEYDOWN和WM_SYSKEYUP消息是由Windows系统函数使用的，Windows程序通常为不产生字符的按键使用WM_KEYDOWN消息；





## 为SYSMETS加上键盘处理功能

发送消息的函数叫做SendMessage，它所用的参数与传递到窗口消息处理程序的参数是相同的：
SendMessage (hwnd, message, wParam, lParam) ;





# 字符消息

TranslateMessage函数，它将按键消息转换为字符消息。如果消息为WM_KEYDOWN或者WM_SYSKEYDOWN，并且按键与位移状态相组合产生一个字符，则TranslateMessage把字符消息放入消息队列中。

TranslateMessage (&msg) ;



## 死字符

WM_DEADCHAR

在大多数情况下，Windows程序会忽略除WM_CHAR之外的任何消息。

在某些非U.S.英语键盘上，有些键用于给字母加上音调。因为它们本身不产生字符，所以称之为「死键」。





## 消息参数

- wParam

  WM_KETDOWN : 虚拟键代码

  WM_CHAR : ANSI或Unicode字符码

- lParam





### 消息排序

这个方法是不按键盘上的大小写锁定键：

![](F:\Learn\6Week\Windows SDK\6\Img\2.png)



**虚拟键代码为Unicode编码下的16进制字符**



如果是按住Shift然后并且敲击a的情况下，会多两层虚拟键代码,按住Shift的流程和弹起





# 插入符号

Windows中的插入符号函数：

- CreateCaret 建立与窗口有关的插入符号
- SetCaretPos 在窗口中设定插入符号的位置
- ShowCaret 显示插入符号
- HideCaret 隐藏插入符号
- DestroyCaret 撤消插入符号

**一个消息队列只允许有一个插入符号**

**通过相应WM_SETFOCUS消息和WM_KILLFOCUS消息来判断窗口是否具备输入焦点**；

窗口消息处理程序在有输入焦点的时候接收到WM_SETFOCUS消息，失去输入焦点的时候接收到WM_KILLFOCUS消息。





在WM_SIZE消息处理期间，TYPER计算窗口的字符宽度和高度并把值保存在cxBuffer和cyBuffer变量中，然后使用malloc分配缓冲区以保存在窗口内输入的所有字符。注意，缓冲区的字节大小取决于cxBuffer、cyBuffer和sizeof（TCHAR），它可以是1或2，这依赖于程序是以8位的字符处理还是以Unicode方式编译的。

xCaret和yCaret变量保存插入符号位置。在WM_SETFOCUS消息处理期间，TYPER呼叫CreateCaret来建立与字符有相同宽度和高度的插入符号，呼叫SetCaretPos来设定插入符号的位置，呼叫ShowCaret使插入符号可见。在WM_KILLFOCUS消息处理期间，TYPER呼叫HideCaret和DestroyCaret。

对WM_KEYDOWN的处理大多要涉及光标移动键。Home和End把插入符号送至一行的开始和末尾处，Page Up和Page Down把插入符号送至窗口的顶端和底部，箭头的用法不变。对Delete键，TYPER将缓冲区中从插入符号之后的那个位置开始到行尾的所有内容向前移动，并在行尾显示空格。

WM_CHAR处理Backspace、Tab、Linefeed（Ctrl-Enter）、Enter、Escape和字符键。注意，在处理WM_CHAR消息时（假设使用者输入的每个字符都非常重要），我使用了lParam中的重复计数；而在处理WM_KEYDOWN消息时却不这么作（避免有害的重复卷动）。对Backspace和Tab的处理由于使用了SendMessage函数而得到简化，Backspace与Delete做法相仿，而Tab则如同输入了若干个空格。

在非WM_PAINT消息处理期间，如果要在窗口中绘制内容，则应该隐蔽光标。TYPER为Delete键处理WM_KEYDOWN消息和为字符键处理WM_CHAR消息时即是如此。在这两种情况下，TYPER改变缓冲区中的内容，然后在窗口中绘制一个或者多个新字符。虽然TYPER使用了与KEYVIEW2相同的做法以在字符集之间切换（就像使用者切换键盘布局一样），但对于远东版的Windows，它还是不能正常工作。TYPER不允许使用两倍宽度的字符





