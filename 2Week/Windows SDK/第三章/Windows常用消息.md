# Windows 常用消息大全

表A-1  Windows消息分布

| 消息范围              | 说 明                |
| --------------------- | -------------------- |
| 0 ～ **WM_USER** – 1  | 系统消息             |
| **WM_USER** ～ 0x7FFF | 自定义窗口类整数消息 |
| **WM_APP** ～ 0xBFFF  | 应用程序自定义消息   |
| 0xC000 ～ 0xFFFF      | 应用程序字符串消息   |
| > 0xFFFF              | 为以后系统应用保留   |

表A-2  常用Windows消息

| 消息名称                  | 值     | 说  明                                                       |
| ------------------------- | ------ | ------------------------------------------------------------ |
| WM_NULL                   | 0x0000 | 空消息，此消息将被接收窗口忽略                               |
| WM_CREATE                 | 0x0001 | 应用程序创建一个窗口                                         |
| WM_DESTROY                | 0x0002 | 一个窗口被销毁                                               |
| WM_MOVE                   | 0x0003 | 移动一个窗口                                                 |
| WM_SIZE                   | 0x0005 | 改变一个窗口的大小                                           |
| WM_ACTIVATE               | 0x0006 | 一个窗口被激活或失去激活状态                                 |
| WM_SETFOCUS               | 0x0007 | 获得焦点后                                                   |
| WM_KILLFOCUS              | 0x0008 | 失去焦点                                                     |
| WM_ENABLE                 | 0x000A | 应用程序Enable状态改变时产生                                 |
| WM_SETREDRAW              | 0x000B | 设置窗口是否能重画                                           |
| WM_SETTEXT                | 0x000C | 应用程序发送此消息来设置一个窗口的文本                       |
| WM_GETTEXT                | 0x000D | 应用程序发送此消息来复制对应窗口的文本到缓冲区               |
| WM_GETTEXTLENGTH          | 0x000E | 得到与一个窗口有关的文本的长度（不包含空字符）               |
| WM_PAINT                  | 0x000F | 要求一个窗口重绘自己                                         |
| WM_CLOSE                  | 0x0010 | 当一个窗口或应用程序要关闭时发送一个信号                     |
| WM_QUERYENDSESSION        | 0x0011 | 用户选择结束对话框或应用程序自己调用ExitWindows()函数        |
| WM_QUIT                   | 0x0012 | 用来结束程序运行或应用程序调用Postquitmessage()函数来产生此消息 |
| WM_QUERYOPEN              | 0x0013 | 当用户窗口恢复以前的大小位置时，把此消息发送给某个图标       |
| WM_ERASEBKGND             | 0x0014 | 当窗口背景必须被擦除时（例如在窗口改变大小时）               |
| WM_SYSCOLORCHANGE         | 0x0015 | 当系统颜色改变时，发送此消息给所有顶级窗口                   |
| WM_ENDSESSION             | 0x0016 | 当系统进程发出WM_QUERYENDSESSION消息后，此消息发送给应用程序 |
| WM_SHOWWINDOW             | 0x0018 | 当隐藏或显示窗口是发送此消息给这个窗口                       |
| WM_ACTIVATEAPP            | 0x001C | 当某个窗口将被激活时，将被激活窗口和当前活动（即将失去激活）窗口会收到此消息，发此消息给应用程序哪个窗口是激活的，哪个是非激活的 |
| WM_FONTCHANGE             | 0x001D | 当系统的字体资源库变化时发送此消息给所有顶级窗口             |
| WM_TIMECHANGE             | 0x001E | 当系统的时间变化时发送此消息给所有顶级窗口                   |
| WM_CANCELMODE             | 0x001F | 发送此消息来取消某种正在进行的操作                           |
| WM_SETCURSOR              | 0x0020 | 如果鼠标引起光标在某个窗口中移动且鼠标输入没有被捕获时，发消息给该窗口 |
| WM_MOUSEACTIVATE          | 0x0021 | 当光标在某个非激活的窗口中而用户正按着鼠标的某个键发送此消息给当前窗口 |
| WM_CHILDACTIVATE          | 0x0022 | 发送此消息给MDI子窗口当用户点击此窗口的标题栏，或当窗口被激活、移动、改变大小 |
| WM_QUEUESYNC              | 0x0023 | 此消息由基于计算机的训练程序发送，通过WH_JOURNALPALYBACK的Hook程序分离出用户输入消息 |
| WM_GETMINMAXINFO          | 0x0024 | 当窗口要将要改变大小或位置时，发送此消息给该窗口             |
| WM_PAINTICON              | 0x0026 | 当窗口图标将要被重绘时，发送此消息给该窗口                   |
| WM_ICONERASEBKGND         | 0x0027 | 在一个最小化窗口的图标在重绘前，当图标背景必须被重绘时，发送此消息给该窗口 |
| WM_NEXTDLGCTL             | 0x0028 | 发送此消息给一个对话框程序以更改焦点位置                     |
| WM_SPOOLERSTATUS          | 0x002A | 当打印管理列队增加或减少一条作业时发出此消息                 |
| WM_DRAWITEM               | 0x002B | 当Button，ComboBox，Listbox，Menu控件的外观改变时，发送此消息给这些控件的所有者 |
| WM_MEASUREITEM            | 0x002C | 当Button，ComboBox，list box，ListView，Menu 项被创建时，发送此消息给控件的所有者 |
| WM_DELETEITEM             | 0x002D | 当ListBox 或 ComboBox 被销毁或当某些项通过发送LB_DELETESTRING、LB_RESETCONTENT、 CB_DELETESTRING、CB_RESETCONTENT 消息被删除时，发送此消息给控件的所有者 |
| WM_VKEYTOITEM             | 0x002E | 一个具有LBS_WANTKEYBOARDINPUT风格的ListBox控件发送此消息给它的所有者，以此来响应WM_KEYDOWN消息 |
| WM_CHARTOITEM             | 0x002F | 一个具有LBS_WANTKEYBOARDINPUT风格的ListBox控件发送此消息给它的所有者，以此来响应WM_CHAR消息 |
| WM_SETFONT                | 0x0030 | 应用程序绘制控件时，发送此消息得到以何种字体绘制控件中的文本 |
| WM_GETFONT                | 0x0031 | 应用程序发送此消息得到当前控件绘制文本的字体                 |
| WM_SETHOTKEY              | 0x0032 | 应用程序发送此消息让一个窗口与一个热键相关联                 |
| WM_GETHOTKEY              | 0x0033 | 应用程序发送此消息来判断热键与某个窗口是否有关联             |
| WM_QUERYDRAGICON          | 0x0037 | 此消息发送给最小化窗口，当此窗口将要被拖放而它的类中没有定义图标，应用程序就返回一个图标或光标的句柄，当用户拖放图标时系统显示这个图标或光标 |
| WM_COMPAREITEM            | 0x0039 | 发送此消息来判定ComboBox或ListBox新增加的项的相对位置        |
| WM_COMPACTING             | 0x0041 | 显示内存已经很少了                                           |
| WM_WINDOWPOSCHANGING      | 0x0046 | 当调用SetWindowPos()函数改变窗口的大小和位置后，发送此消息给该窗口 |
| WM_POWER                  | 0x0048 | 当系统将进入挂起状态时发送此消息给所有进程                   |
| WM_COPYDATA               | 0x004A | 当一个应用程序传递数据给另一个应用程序时发送此消息           |
| WM_CANCELJOURNAL          | 0x004B | 当某个用户取消程序日志激活状态，发送此消息给应用程序         |
| WM_NOTIFY                 | 0x004E | 当某个控件的某个事件已经发生或这个控件需要得到一些信息时，发送此消息给它的父窗口 |
| WM_INPUTLANGCHANGEREQUEST | 0x0050 | 当用户选择某种输入语言，或输入语言的热键改变                 |
| WM_INPUTLANGCHANGE        | 0x0051 | 当应用程序输入语言改变后发送此消息给受影响的最顶级窗口       |
| WM_TCARD                  | 0x0052 | 当应用程序已经初始化Windows帮助例程时发送此消息给应用程序    |
| WM_HELP                   | 0x0053 | 当用户按下了F1，如果某个菜单是激活的，就发送此消息给此窗口关联的菜单，否则就发送给有焦点的窗口，如果当前都没有焦点，就把此消息发送给当前激活的窗口 |
| WM_USERCHANGED            | 0x0054 | 当用户已经登录或退出后发送此消息给所有的窗口，当用户登录或退出时系统更新用户的具体设置信息，在用户更新设置时系统马上发送此消息 |
| WM_NOTIFYFORMAT           | 0x0055 | 公用控件和它们的父窗口通过此消息来判断在WM_NOTIFY消息中是使用ANSI还是UNICODE形式的结构，使用此控件能使某个控件与它的父控件进行相互通信 |
| WM_CONTEXTMENU            | 0x007B | 当用户在某个窗口中点击右键，则发送此消息给该窗口             |
| WM_STYLECHANGING          | 0x007C | 当将要调用SetWindowLong()函数窗口的一个或多个风格时，发送此消息给该窗口 |
| WM_STYLECHANGED           | 0x007D | 当调用SetWindowLong()函数改变了窗口的一个或多个风格后，发送此消息给该窗口 |
| WM_DISPLAYCHANGE          | 0x007E | 当显示器的分辨率改变后发送此消息给所有的窗口                 |
| WM_GETICON                | 0x007F | 发送此消息给某个窗口，返回与某个窗口有关联的大图标或小图标的句柄 |
| WM_SETICON                | 0x0080 | 应用程序发送此消息让一个新的大图标或小图标与某个窗口关联     |
| WM_NCCREATE               | 0x0081 | 当某个窗口第一次被创建时，此消息在WM_CREATE消息被发送前发送  |
| WM_NCDESTROY              | 0x0082 | 此消息通知某个窗口，正在销毁非客户区                         |
| WM_NCCALCSIZE             | 0x0083 | 当计算某个窗口的客户区大小和位置时发送此消息                 |
| WM_NCHITTEST              | 0x0084 | 移动鼠标，按住或释放鼠标时产生此消息                         |
| WM_NCPAINT                | 0x0085 | 当某个窗口的框架必须被绘制时，应用程序发送此消息给该窗口     |
| WM_NCACTIVATE             | 0x0086 | 通过改变某个窗口的非客户区来表示窗口是处于激活还是非激活状态时，此消息被发送给该窗口 |
| WM_NCMOUSEMOVE            | 0x00A0 | 当光标在窗口的非客户区（窗口标题栏及边框）内移动时发送此消息给该窗口 |
| WM_NCLBUTTONDOWN          | 0x00A1 | 当光标在窗口的非客户区并按下鼠标左键时发送此消息             |
| WM_NCLBUTTONUP            | 0x00A2 | 当光标在窗口的非客户区并释放鼠标左键时发送此消息             |
| WM_NCLBUTTONDBLCLK        | 0x00A3 | 当光标在窗口的非客户区并双击鼠标左键时发送此消息             |
| WM_NCRBUTTONDOWN          | 0x00A4 | 当光标在窗口的非客户区并按下鼠标右键时发送此消息             |
| WM_NCRBUTTONUP            | 0x00A5 | 当光标在窗口的非客户区并释放鼠标右键时发送此消息             |
| WM_NCRBUTTONDBLCLK        | 0x00A6 | 当光标在窗口的非客户区并双击鼠标右键时发送此消息             |
| WM_NCMBUTTONDOWN          | 0x00A7 | 当光标在窗口的非客户区并按下鼠标中键时发送此消息             |
| WM_NCMBUTTONUP            | 0x00A8 | 当光标在窗口的非客户区并释放鼠标中键时发送此消息             |
| WM_NCMBUTTONDBLCL         | 0x00A9 | 当光标在窗口的非客户区并双击鼠标中键时发送此消息             |
| WM_KEYDOWN                | 0x0100 | 按下一个非系统键（按下键时未按下“ALT”键）                    |
| WM_KEYUP                  | 0x0101 | 释放一个非系统键                                             |
| WM_CHAR                   | 0x0102 | 按下某键，当TranslateMessage()转发WM_KEYDOWN后发送本消息     |
| WM_DEADCHAR               | 0x0103 | 释放某键，当TranslateMessage()转发WM_KEYUP后发送本消息       |
| WM_SYSKEYDOWN             | 0x0104 | 当按住ALT键同时按下其他键时发送此消息给拥有键盘焦点的窗口    |
| WM_SYSKEYUP               | 0x0105 | 当释放一个键同时按住ALT键时发送此消息给拥有键盘焦点的窗口    |
| WM_SYSCHAR                | 0x0106 | 当TranslateMessage()转发WM_SYSKEYDOWN后发送此消息给拥有键盘焦点的窗口 |
| WM_SYSDEADCHAR            | 0x0107 | 当TranslateMessage()转发WM_SYSKEYUP后发送此消息给拥有键盘焦点的窗口 |
| WM_INITDIALOG             | 0x0110 | 在被显示前发送此消息对话框，通常用此消息初始化控件和执行其他任务 |
| WM_COMMAND                | 0x0111 | 选择窗口菜单项或某个控件发送一条消息给它的父窗口或按下一个快捷键时产生此消息 |
| WM_SYSCOMMAND             | 0x0112 | 选择窗口菜单项或选择最大化或最小化时，发送此消息给该窗口     |
| WM_TIMER                  | 0x0113 | 发生了定时器事件                                             |
| WM_HSCROLL                | 0x0114 | 当窗口水平滚动条产生一个滚动事件时发送此消息给该窗口和滚动条的所有者 |
| WM_VSCROLL                | 0x0115 | 当窗口垂直滚动条产生一个滚动事件时发送此消息给该窗口和滚动条的所有者 |
| WM_INITMENU               | 0x0116 | 当一个菜单将要被激活时发送此消息，它发生在按下菜单项或按下菜单快捷键时，它允许程序在显示前更改菜单 |
| WM_INITMENUPOPUP          | 0x0117 | 当一个下拉菜单或子菜单将要被激活时发送此消息，它允许显示前在修改菜单而不必更改整个菜单 |
| WM_MENUSELECT             | 0x011F | 选择一条菜单项时发送此消息给菜单的所有者（一般是窗口）       |
| WM_MENUCHAR               | 0x0120 | 当菜单已被激活且用户按下了某个键（非快捷键），发送此消息给菜单的所有者 |
| WM_ENTERIDLE              | 0x0121 | 当一个有模式对话框或菜单进入空闲状态时发送此消息给它的所有者，空闲状态指在处理完一条或几条先前的消息后，消息列队为空 |
| WM_MENURBUTTONUP          | 0x0122 | 当光标位于菜单项上时，释放鼠标右键产生此消息                 |
| WM_MENUDRAG               | 0x0123 | 当拖动菜单项时，发送此消息给拖放菜单的所有者                 |
| WM_MENUGETOBJECT          | 0x0124 | 当光标移入菜单项或者从菜单项中心移到菜单项顶部或底部时，发送此消息给拖放菜单的所有者 |
| WM_UNINITMENUPOPUP        | 0x0125 | 当下拉菜单或者子菜单被销毁时产生此消息                       |
| WM_MENUCOMMAND            | 0x0126 | 当用户选择菜单项时产生此消息                                 |
| WM_CHANGEUISTATE          | 0x0127 | 应用程序发送此消息表明用户界面（UI）状态应当被改变           |
| WM_UPDATEUISTATE          | 0x0128 | 应用程序发送此消息改变指定窗口及其子窗口的用户界面（UI）状态 |
| WM_QUERYUISTATE           | 0x0129 | 应用程序发送此消息得到某个窗口的用户界面（UI）状态           |
| WM_CTLCOLORMSGBOX         | 0x0132 | 绘制消息框前发送此消息给它的父窗口，通过响应这条消息，父窗口可以通过使用给定的相关显示设备的句柄来设置消息框的文本和背景颜色 |
| WM_CTLCOLOREDIT           | 0x0133 | 绘制编辑型控件前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色 |
| WM_CTLCOLORLISTBOX        | 0x0134 | 绘制列表框控件前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色 |
| WM_CTLCOLORBTN            | 0x0135 | 绘制按钮控件前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色 |
| WM_CTLCOLORDLG            | 0x0136 | 绘制对话框前发送此消息给它的父窗口，可用来设置编辑框的文本和背景颜色 |
| WM_CTLCOLORSCROLLBAR      | 0x0137 | 绘制滚动条控件前发送此消息给它的父窗口，可用来设置滚动条控件的文本和背景颜色 |
| WM_CTLCOLORSTATIC         | 0x0138 | 绘制静态控件前发送此消息给它的父窗口，可用来设置静态控件的文本和背景颜色 |
| WM_MOUSEMOVE              | 0x0200 | 鼠标移动                                                     |
| WM_LBUTTONDOWN            | 0x0201 | 按下鼠标左键                                                 |
| WM_LBUTTONUP              | 0x0202 | 释放鼠标左键                                                 |
| WM_LBUTTONDBLCLK          | 0x0203 | 双击鼠标左键                                                 |
| WM_RBUTTONDOWN            | 0x0204 | 按下鼠标右键                                                 |
| WM_RBUTTONUP              | 0x0205 | 释放鼠标右键                                                 |
| WM_RBUTTONDBLCLK          | 0x0206 | 双击鼠标右键                                                 |
| WM_MBUTTONDOWN            | 0x0207 | 按下鼠标中键                                                 |
| WM_MBUTTONUP              | 0x0208 | 释放鼠标中键                                                 |
| WM_MBUTTONDBLCLK          | 0x0209 | 双击鼠标中键                                                 |
| WM_MOUSEWHEEL             | 0x020A | 当鼠标滚轮转动时发送此消息给当前获得焦点的窗口               |
| WM_PARENTNOTIFY           | 0x0210 | 当MDI子窗口被创建或被销毁，或当光标位于子窗口上且用户按了一下鼠标键时，发送此消息给它的父窗口 |
| WM_ENTERMENULOOP          | 0x0211 | 发送此消息通知应用程序的主窗口进程已经进入了菜单模式循环     |
| WM_EXITMENULOOP           | 0x0212 | 发送此消息通知应用程序的主窗口进程已经退出了菜单模式循环     |
| WM_SIZING                 | 0x0214 | 调整窗口大小时发送此消息给窗口，通过此消息应用程序可以监视或修改窗口大小和位置 |
| WM_CAPTURECHANGED         | 0x0215 | 当窗口设定为不捕获鼠标事件时，发送此消息给该窗口             |
| WM_MOVING                 | 0x0216 | 移动窗口时发送此消息给窗口，通过此消息应用程序可以监视或修改窗口大小和位置 |
| WM_POWERBROADCAST         | 0x0218 | 发送此消息给应用程序通知它有关电源管理事件                   |
| WM_DEVICECHANGE           | 0x0219 | 当设备的硬件配置改变时发送此消息给应用程序或设备驱动程序     |
| WM_MDICREATE              | 0x0220 | 应用程序发送此消息给多文档的客户窗口来创建一个MDI 子窗口     |
| WM_MDIDESTROY             | 0x0221 | 应用程序发送此消息给多文档的客户窗口来关闭一个MDI 子窗口     |
| WM_MDIACTIVATE            | 0x0222 | 应用程序发送此消息给多文档的客户窗口通知客户窗口激活另一个MDI子窗口，当客户窗口收到此消息后，它发出WM_MDIACTIVE消息给MDI子窗口（未激活）来激活它 |
| WM_MDIRESTORE             | 0x0223 | 应用程序发送此消息给MDI客户窗口通知子窗口恢复到原来大小      |
| WM_MDINEXT                | 0x0224 | 应用程序发送此消息给MDI客户窗口激活下一个或前一个窗口        |
| WM_MDIMAXIMIZE            | 0x0225 | 应用程序发送此消息给MDI客户窗口以最大化一个MDI子窗口         |
| WM_MDITILE                | 0x0226 | 应用程序发送此消息给MDI客户窗口以平铺方式重新排列所有MDI子窗口 |
| WM_MDICASCADE             | 0x0227 | 应用程序发送此消息给MDI客户窗口以层叠方式重新排列所有MDI子窗口 |
| WM_MDIICONARRANGE         | 0x0228 | 应用程序发送此消息给MDI客户窗口重新排列所有最小化的MDI子窗口 |
| WM_MDIGETACTIVE           | 0x0229 | 应用程序发送此消息给MDI客户窗口以找到激活的子窗口的句柄      |
| WM_MDISETMENU             | 0x0230 | 应用程序发送此消息给MDI客户窗口用MDI菜单代替子窗口的菜单     |
| WM_ENTERSIZEMOVE          | 0x0231 | 当窗口进入移动或改变大小模式循环时，发送此消息给该窗口       |
| WM_EXITSIZEMOVE           | 0x0232 | 当窗口退出移动或改变大小模式循环时，发送此消息给该窗口       |
| WM_DROPFILES              | 0x0233 | 当用户在应用程序窗口中拖动某个文件时，产生此消息             |
| WM_MDIREFRESHMENU         | 0x0234 | 应用程序发送此消息给MDI客户窗口以刷新窗口菜单                |
| WM_MOUSEHOVER             | 0x02A1 | 当光标在窗口客户区悬停超过TrackMouseEvent()指定的时间时，发送此消息给该窗口 |
| WM_MOUSELEAVE             | 0x02A3 | 当光标离开窗口客户区超过TrackMouseEvent()指定的时间时，发送此消息给该窗口 |
| WM_CUT                    | 0x0300 | 应用程序发送此消息给一个编辑框或ComboBox以删除当前选择的文本 |
| WM_COPY                   | 0x0301 | 应用程序发送此消息给一个编辑框或ComboBox以复制当前选择的文本到剪贴板 |
| WM_PASTE                  | 0x0302 | 应用程序发送此消息给一个编辑框或ComboBox以从剪贴板中得到数据 |
| WM_CLEAR                  | 0x0303 | 应用程序发送此消息给一个编辑框或ComboBox以清除当前选择的内容 |
| WM_UNDO                   | 0x0304 | 应用程序发送此消息给一个编辑框或ComboBox以撤消最后一次操作   |
| WM_DESTROYCLIPBOARD       | 0x0307 | 当调用EmptyClipboard()清空剪贴板时，发送此消息给剪贴板所有者 |
| WM_DRAWCLIPBOARD          | 0x0308 | 当剪贴板的内容变化时发送此消息给剪贴板观察链中的第一个窗口，它允许用剪贴板观察窗口来显示剪贴板的新内容 |
| WM_PAINTCLIPBOARD         | 0x0309 | 当剪贴板包含CF_OWNERDIPLAY格式的数据且剪贴板观察窗口的客户区需要重绘时，发送此消息给剪贴板所有者 |
| WM_VSCROLLCLIPBOARD       | 0x030A | 当剪贴板包含CF_OWNERDIPLAY格式的数据且剪贴板观察窗口发生垂直滚动条事件时，剪贴板观察窗口发送此消息给剪贴板所有者 |
| WM_SIZECLIPBOARD          | 0x030B | 当剪贴板包含CF_OWNERDIPLAY格式的数据且剪贴板观察窗口的客户区域的大小已经改变时，剪贴板观察窗口发送此消息给剪贴板的所有者 |
| WM_ASKCBFORMATNAME        | 0x030C | 剪贴板观察窗口发送此消息给剪贴板所有者以获得CF_OWNERDISPLAY剪贴板格式的名字 |
| WM_CHANGECBCHAIN          | 0x030D | 当一个窗口从剪贴板观察链中移去时发送此消息给剪贴板观察链中的第一个窗口 |
| WM_HSCROLLCLIPBOARD       | 0x030E | 当剪贴板包含CF_OWNERDIPLAY格式的数据且剪贴板观察窗口发生水平滚动条事件时，剪贴板观察窗口发送此消息给剪贴板所有者 |
| WM_QUERYNEWPALETTE        | 0x030F | 发送此消息给将要获得键盘焦点的窗口，此消息使窗口在获得焦点时同时有机会实现它的逻辑调色板 |
| WM_PALETTEISCHANGING      | 0x0310 | 应用程序将要实现它的逻辑调色板时发送此消息通知所有应用程序   |
| WM_PALETTECHANGED         | 0x0311 | 获得焦点的窗口实现它的逻辑调色板后发送此消息给所有顶级并重叠的窗口，以此来改变系统调色板 |
| WM_HOTKEY                 | 0x0312 | 当用户按下由RegisterHotKey()注册的热键时产生此消息           |
| WM_PRINT                  | 0x0317 | 应用程序发送此消息给窗口，要求窗口在指定设备环境中绘制自己，一般情况下是打印机设备环境 |
| WM_PRINTCLIENT            | 0x0318 | 应用程序发送此消息给窗口，要求窗口在指定设备环境中绘制窗口客户区，一般情况下是打印机设备环境 |
| WM_APP                    | 0x8000 | 帮助用户自定义消息，自定义消息可以为WM_APP+X，X为正整数      |
| WM_USER                   | 0x0400 | 帮助用户自定义消息，自定义消息可以为WM_USER+X，X为正整数     |

  表A-3  通知消息－按钮

| 消息名称         | 说 明        |
| ---------------- | ------------ |
| BN_CLICKED       | 单击按钮     |
| BN_DISABLE       | 按钮被禁止   |
| BN_DOUBLECLICKED | 双击按钮     |
| BN_HILITE        | 加亮按钮     |
| BN_PAINT         | 按钮应当重画 |
| BN_UNHILITE      | 加亮应当去掉 |

表A-4  通知消息－组合框

| 消息名称         | 说 明                    |
| ---------------- | ------------------------ |
| CBN_CLOSEUP      | 组合框的列表框被关闭     |
| CBN_DBLCLK       | 用户双击了一个字符串     |
| CBN_DROPDOWN     | 组合框的列表框被拉下     |
| CBN_EDITCHANGE   | 用户修改了组合框中的文本 |
| CBN_EDITUPDATE   | 组合框内的文本即将更新   |
| CBN_ERRSPACE     | 组合框内存不足           |
| CBN_KILLFOCUS    | 组合框失去输入焦点       |
| CBN_SELCHANGE    | 在组合框中选择了一项     |
| CBN_SELENDCANCEL | 用户的选择将被忽略       |
| CBN_SELENDOK     | 用户的选择将被执行       |
| CBN_SETFOCUS     | 组合框获得输入焦点       |

表A-5  通知消息－编辑框

| 消息名称     | 说 明                  |
| ------------ | ---------------------- |
| EN_CHANGE    | 编辑框中的文本己更新   |
| EN_ERRSPACE  | 编辑框内存不足         |
| EN_HSCROLL   | 用户点击了水平滚动条   |
| EN_KILLFOCUS | 编辑框失去输入焦点     |
| EN_MAXTEXT   | 插入的内容被截断       |
| EN_SETFOCUS  | 编辑框获得输入焦点     |
| EN_UPDATE    | 编辑框中的文本将要更新 |
| EN_VSCROLL   | 用户点击了垂直滚动条   |

表A-6  通知消息－列表框

| 消息名称      | 说 明                  |
| ------------- | ---------------------- |
| LBN_DBLCLK    | 用户双击了一项         |
| LBN_ERRSPACE  | 列表框内存不足         |
| LBN_KILLFOCUS | 列表框正在失去输入焦点 |
| LBN_SELCANCEL | 用户选择被取消         |
| LBN_SELCHANGE | 用户选择将改变         |
| LBN_SETFOCUS  | 列表框获得输入焦点     |