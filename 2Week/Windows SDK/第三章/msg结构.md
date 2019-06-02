# msg结构

在 Windows 程序中，消息是由 MSG 结构体来表示的。

**结构原型：**

```c
typedef struct tagMSG {
  HWND   hwnd;
  UINT   message;
  WPARAM wParam;
  LPARAM lParam;
  DWORD  time;
  POINT  pt;
} MSG, *PMSG, *LPMSG;
```

**成员解析：**

| **成员** | **含义**                                                     |
| -------- | ------------------------------------------------------------ |
| hwnd     | 指定接收消息的窗口句柄 如果是线程消息，该值是 NULL           |
| message  | 1. 消息的标识符，由于数值不便于记忆，所以 Windows 将消息对应的数值定义为 WM_XXX 宏的形式 2. 应用程序消息只能使用低 16 位，高 16 位被系统保留 3. 传送门：[Windows 常用消息及含义](http://bbs.fishc.com/thread-47244-1-1.html) |
| wParam   | 指定消息的附加消息，确切的含义取决于消息成员的值             |
| lParam   | 指定消息的附加消息，确切的含义取决于消息成员的值             |
| time     | 该消息被投放到消息队列的时间                                 |
| pt       | 当消息被投放到消息队列的时，鼠标位于屏幕中的位置             |

