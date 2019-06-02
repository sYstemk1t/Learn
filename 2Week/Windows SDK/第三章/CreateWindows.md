# **CreateWindow**

**函数功能：**

**函数功能：**
CreateWindow 函数创建一个重叠式窗口、弹出式窗口或子窗口。它指定窗口类，窗口标题，窗口风格，以及窗口的初始位置及大小（可选的）。函数也指该窗口的父窗口或所属窗口（如果存在的话），及窗口的菜单。
若要使用除 CreateWindow 函数支持的风格外的扩展风格，则使用 CreateWindowEx 函数代替 CreateWindow 函数。

**API 函数原型：**

注释：_In_ 说明该参数是输入的，_opt_ 说明该参数是可选参数。

```c
HWND WINAPI CreateWindow(
  _In_opt_  LPCTSTR lpClassName,    // 窗口类名称
  _In_opt_  LPCTSTR lpWindowName,   // 窗口标题
  _In_      DWORD dwStyle,          // 窗口风格，或称窗口格式
  _In_      int x,                  // 初始 x 坐标
  _In_      int y,                  // 初始 y 坐标
  _In_      int nWidth,             // 初始 x 方向尺寸
  _In_      int nHeight,            // 初始 y 方向尺寸
  _In_opt_  HWND hWndParent,        // 父窗口句柄
  _In_opt_  HMENU hMenu,            // 窗口菜单句柄
  _In_opt_  HINSTANCE hInstance,    // 程序实例句柄
  _In_opt_  LPVOID lpParam          // 创建参数
);

```

**参数解析：**

| **参数**     | **含义**                                                     |
| ------------ | ------------------------------------------------------------ |
| lpClassName  | 1. 窗口类名称，可以是一个指向 NULL 结束的字符串或一个整型数值 2. 如果是字符串，它指定了窗口的类名。这个类名可以是任何用函数 RegisterClass 注册的类名，或是任何预定义的控制类名 3. 如是一个整型量，它是由此前调用 theGlobalAddAtom 函数产生的全局量。这个小于 0xC000 的 16 位数必须是 lpClassName 参数字的低 16 位，该参数的高位必须是 0 |
| lpWindowName | 1. 窗口标题，一个指向 NULL 结束的字符串指针 2. 如果窗口风格指定了标题条，由 lpWindowName 指向的窗口标题将显示在标题条上 3. 当使用 Createwindow 函数来创建控制例如按钮，选择框和静态控制时，可使用 lpWindowName 来指定控制文本 |
| dwStyle      | 指定创建窗口的风格（详见下方↓）                              |
| x            | 1. 指定窗口的初始水平位置（x 坐标） 2. 对一个层叠或弹出式窗口，x 参数是屏幕坐标系的窗口的左上角的初始 x 坐标 3. 对于子窗口，x 是子窗口左上角相对父窗口客户区左上角的初始 x 坐标 4. 如果该参数被设为 CW_USEDEFAULT 则系统为窗口选择缺省的左上角坐标并忽略 y 参数，CW_USEDEFAULT 只对层叠窗口有效，如果为弹出式窗口或子窗口设定，则 x 和 y 参数被设为零。 |
| y            | 1. 指定窗口的初始垂直位置（y 坐标） 2. 对一个层叠或弹出式窗口，y 参数是屏幕坐标系的窗口的左上角的初始 y 坐标 3. 对于子窗口，y 是子窗口左上角相对父窗口客户区左上角的初始 y 坐标 4. 对于列表框，y 是列表框客户区左上角相对父窗口客户区左上角的初始 y 坐标 5. 如果层叠窗口是使用 WS_VISIBLE 风格位创建的并且 x 参数被设为 CW_USEDEFAULT，则系统将忽略 y 参数 |
| nWidth       | 1. 以设备单元指明窗口的宽度 2. 对于层叠窗口，nWidth 的值或是屏幕坐标的窗口宽度或是 CW_USEDEFAULT 3. 若 nWidth 是 CW_USEDEFAULT，则系统为窗口选择一个默认的高度和宽度（默认宽度为从初始 x 坐标开始到屏幕的右边界，缺省高度为从初始 y 坐标开始到目标区域的顶部。)，CW_USEDEFAULT 只对层叠窗口有效，如果为弹出式窗口和子窗口设定 CW_USEDEFAULT 标志则 nWidth 和 nHeight 被设为零 |
| nHeight      | 1. 以设备单元指明窗口的高度 2. 对于层叠窗口，nHeight 是屏幕坐标的窗口宽度 3. 若 nWidth 被设为 CW_USEDEFAULT，则系统忽略 nHeight 参数，自动为 nWidth 和 nHeight 设置默认参数 |
| hWndParent   | 1. 指向被创建窗口的父窗口或所有者窗口的句柄 2. 若要创建一个子窗口或一个从属窗口，需提供一个有效的窗口句柄 3. 创建一个单纯的消息窗口，可以提供 HWND_MESSAGE 或提供一个己存在的消息窗口的句柄 |
| hMenu        | 1. 指向窗口菜单句柄，或依据窗口风格指明一个子窗口标识 2. 对于层叠或弹出式窗口，hMenu 指定窗口使用的菜单：如果使用了菜单类，则 hMenu 可以为 NULL 3. 对于子窗口，hMenu 指定了该子窗口标识（一个整型量），一个对话框使用这个整型值将事件通知父类。应用程序确定子窗口标识，这个值对于相同父窗口的所有子窗口必须是唯一的 |
| hInstance    | 与窗口相关联的模块实例的句柄                                 |
| lpParam      | 1. 指向一个值的指针，该值传递给窗口 WM_CREATE 消息。该值通过在 IParam 参数中的 CREATESTRUCT 结构传递 2. 如果应用程序调用 CreateWindow 创建一个 MDI 客户窗口，则 lpParam 必须指向一个 CLIENTCREATESTRUCT 结构 |

dwStyle 窗口风格解析

| **窗口风格**        | **含义**                                                     |
| ------------------- | ------------------------------------------------------------ |
| WS_BORDER           | 创建一个带边框的窗口                                         |
| WS_CAPTION          | 创建一个有标题框的窗口（包含了 WS_BODER 风格）               |
| WS_CHILD            | 创建一个子窗口，这个风格的窗口不能拥有菜单也不能与 WS_POPUP 风格合用 |
| WS_CHILDWINDOW      | 与 WS_CHILD 相同                                             |
| WS_CLIPCHILDREN     | 当在父窗口内绘图时，排除子窗口区域，在创建父窗口时使用这个风格 |
| WS_CLIPSIBLINGS     | 1. 排除子窗口之间的相对区域，也就是，当一个特定的窗口接收到 WM_PAINT 消息时，WS_CLIPSIBLINGS 风格将所有层叠窗口排除在绘图之外，只重绘指定的子窗口 2. 如果未指定该风格，并且子窗口是层叠的，则在重绘子窗口的客户区时，就会重绘邻近的子窗口 |
| WS_DISABLED         | 1. 创建一个初始状态为禁止的子窗口，一个禁止状态的窗口不能接受来自用户的输入信息 2. 在窗口创建之后，可以调用 EnableWindow 函数来启用该窗口 |
| WS_DLGFRAME         | 创建一个带对话框边框风格的窗口，这种风格的窗口不能带标题条   |
| WS_GROUP            | 1. 指定一组“控制窗口”的第一个“控制窗口” 2. 这个“控制窗口”组由第一个“控制窗口”和随后定义的“控制窗口”组成，自第二个“控制窗口”开始每个“控制窗口”具有 WS_GROUP 风格 3. 每个组的第一个“控制窗口”带有 WS_TABSTOP 风格，从而使用户可以在组间移动 4. 用户随后可以使用光标在组内的控制间改变键盘焦点 |
| WS_HSCROLL          | 创建一个有水平滚动条的窗口                                   |
| WS_ICONIC           | 创建一个初始状态为最小化状态的窗口，与 WS_MINIMIZE 风格相同  |
| WS_MAXIMIZE         | 创建一个初始状态为最大化状态的窗口                           |
| WS_MAXIMIZEBOX      | 创建一个具有最大化按钮的窗口，该风格不能与 WS_EX_CONTEXTHELP 风格同时出现，同时必须指定 WS_SYSMENU 风格 |
| WS_MINIMIZE         | 创建一个初始状态为最小化状态的窗口，与 WS_ICONIC 风格相同    |
| WS_MINIMIZEBOX      | 创建一个具有最小化按钮的窗口，该风格不能与 WS_EX_CONTEXTHELP 风格同时出现，同时必须指定 WS_SYSMENU 风格 |
| WS_OVERLAPPED       | 产生一个层叠的窗口，一个层叠的窗口有一个标题条和一个边框，与 WS_TILED 风格相同 |
| WS_OVERLAPPEDWINDOW | 相当于（WS_OVERLAPPED \| WS_CAPTION \| WS_SYSMENU \| WS_THICKFRAME \| WS_MINIMIZEBOX \| WS_MAXIMIZEBOX），与 WS_TILEDWINDOW 风格相同 |
| WS_POPUP            | 创建一个弹出式窗口，该风格不能与 WS_CHILD 风格同时使用。     |
| WS_POPUPWINDOW      | 相当于（WS_POPUP \| WS_BORDER \| WS_SYSMENU），但 WS_CAPTION 和 WS_POPUPWINDOW 必须同时设定才能使窗口某单可见 |
| WS_SIZEBOX          | 创建一个可调边框的窗口，与 WS_THICKFRAME 风格相同            |
| WS_SYSMENU          | 创建一个在标题条上带有窗口菜单的窗口，必须同时设定 WS_CAPTION 风格 |
| WS_TABSTOP          | 1. 创建一个“控制窗口”，在用户按下 Tab 键时可以获得键盘焦点。 2. 按下 Tab 键后使键盘焦点转移到下一具有 WS_TABSTOP 风格的“控制窗口” |
| WS_THICKFRAME       | 创建一个具有可调边框的窗口，与 WS_SIZEBOX 风格相同           |
| WS_TILED            | 产生一个层叠的窗口，一个层叠的窗口有一个标题和一个边框，与 WS_OVERLAPPED 风格相同 |
| WS_TILEDWINDOW      | 相当于（WS_OVERLAPPED \| WS_CAPTION \| WS_SYSMENU \| WS_THICKFRAME \| WS_MINIMIZEBOX \| WS_MAXIMIZEBOX），与 WS_OVERLAPPEDWINDOW 风格相同 |
| WS_VISIBLE          | 创建一个初始状态为可见的窗口                                 |
| WS_VSCROLL          | 创建一个有垂直滚动条的窗口                                   |

**返回值：**

\1. 如果函数成功，返回值为新窗口的句柄；

\2. 如果函数失败，返回值为 NULL。