# WNDCLASS 结构

**WNDCLASS 结构**
Windows 的窗口总是基于窗口类来创建的，窗口类同时确定了处理窗口消息的窗口过程（回调函数）。
在创建应用程序窗口之前，必须调用 RegisterClass 函数来注册窗口类。该函数只需要一个参数，即指向 WNDCLASS 窗口类的指针。因为 WNDCLASS 类包含了窗口所拥有的基本属性。
**结构原型：**

```c
typedef struct tagWNDCLASSW {
    UINT        style;
    WNDPROC     lpfnWndProc;
    int         cbClsExtra;
    int         cbWndExtra;
    HINSTANCE   hInstance;
    HICON       hIcon;
    HCURSOR     hCursor;
    HBRUSH      hbrBackground;
    LPCWSTR     lpszMenuName;
    LPCWSTR     lpszClassName;
} WNDCLASSW, *PWNDCLASSW, NEAR *NPWNDCLASSW, FAR *LPWNDCLASSW;
```

**成员解析：**

| **成员**      | **含义**                                                     |
| ------------- | ------------------------------------------------------------ |
| style         | 指定窗口类型，各种“类风格”（详见下方↓）可以使用按位或操作符组合起来 |
| lpfnWndProc   | 指定窗口过程（必须是回调函数）                               |
| cbClsExtra    | 预留的额外空间，一般为 0                                     |
| cbWndExtra    | 预留的额外空间，一般为 0                                     |
| hInstance     | 应用程序的实例句柄                                           |
| hIcon         | 为所有基于该窗口类的窗口设定一个图标                         |
| hCursor       | 为所有基于该窗口类的窗口设定一个鼠标指针                     |
| hbrBackground | 指定窗口背景色                                               |
| lpszMenuName  | 指定窗口菜单                                                 |
| lpszClassName | 指定窗口类名                                                 |

style 类风格解析

| **类风格**         | **含义**                                                     |
| ------------------ | ------------------------------------------------------------ |
| CS_VREDRAW         | 移动或者调整窗口的高度（垂直方向）时，重绘整个窗口           |
| CS_HREDRAW         | 移动或者调整窗口的宽度（水平方向）时，重绘整个窗口           |
| CS_DBLCLKS         | 当用户光标在窗口内双击时，允许发送双击消息给窗口过程         |
| CS_OWNDC           | 给予每个窗口实例分配一个唯一的 DC（注意，尽管这样是很方便，但它必须慎重使用，因为每个 DC 大约要占 800 个字节的内存） |
| CS_CLASSDC         | 该窗口类的所有窗口实例都共享一个窗口类 DC                    |
| CS_PARENTDC        | 1. 将子窗口的裁剪区域设置到父窗口的 DC 中去，这样子窗口便可以在父窗口上绘制自身。（注意，这是子窗口从系统缓存中获取 DC，而不是使用父窗口的 DC。） 2. 指定该风格可以提高系统性能 |
| CS_NOCLOSE         | 禁止系统菜单的关闭选项                                       |
| CS_SAVEBITS        | 1. 以位图形式保存被该窗口遮挡的屏幕部分，当给窗口移动以后，系统便可以用该保存的位图恢复屏幕移动的相应部分，从而系统不用向被该窗口遮挡的窗口发送 WM_PAINT 消息 2. 该特性对于菜单类型的窗口比较合适，因为它通常是简短的显示一下之后便消失 3. 设置该特性将增加显示该窗口的时间，因为它通常要先分配保存位图的内存 |
| CS_BYTEALIGNCLIENT | 在字节边界上（在 x 方向上）定位窗口的用户区域的位置          |
| CS_BYTEALIGNWINDOW | 在字节边界上（在 x 方向上）定位窗口的位置                    |
| CS_GLOBALCLASS     | 1. 当调用 CreateWindow 或 CreateWindowEx 函数来创建窗口时允许它的 hInstance 参数和注册窗口类时传递给 RegisterClass 的 hInstance 参数不同 2. 如果不指定该风格，则这两个 hInstance 必须相同 |