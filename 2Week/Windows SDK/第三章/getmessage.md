# GetMessage

  **函数功能：**

GetMessage 函数的作用是从当前线程的消息队列里获取一个消息并填入 [MSG 结构](http://bbs.fishc.com/thread-47240-1-1.html) 中。

该函数只能获取调用线程的消息，不能获得其他线程的消息。成功获取消息后，线程将从消息队列中删除该消息。

使用 GetMessage 函数，如果消息队列为空，函数会一直等待直到有消息到来才有返回值。

**API 函数原型：**

```c
BOOL WINAPI GetMessage(
  _Out_     LPMSG lpMsg,
  _In_opt_  HWND hWnd,
  _In_      UINT wMsgFilterMin,
  _In_      UINT wMsgFilterMax
);
```

参数解析：

| **参数**      | **含义**                                                     |
| ------------- | ------------------------------------------------------------ |
| lpMsg         | 指向 [MSG 结构](http://bbs.fishc.com/thread-47240-1-1.html)的指针，用于存放获取到的消息 |
| hWnd          | 1. 需要获取消息的窗口的句柄，该窗口必须属于当前线程 2. 当其值是 NULL 时，将获取所有的当前线程的窗口消息和线程消息 3. 当其值是 -1 时，只获取当前线程消息 |
| wMsgFilterMin | 指定被可以被获取的消息值的最小整数（消息其实就是一个被定义的整数） |
| wMsgFilterMax | 指定被可以被获取的消息值的最小整数                           |

返回值：

1. 如果函数取得 WM_QUIT 之外的其他消息，返回值是非 0；

2. 如果函数取得 WM_QUIT 消息，返回值是 0；

3. 如果出现了错误，返回值是 -1。

备注：

1. 应用程序通常根据 GetMessage 函数的返回值决定是否结束消息循环并退出程序；

2. 如果 hWnd 参数不为零，则 GetMessage 函数只获取属于 hWnd 窗口的消息，以及被 IsChild函数确定为 hWnd 的子窗口的消息；

3. wMsgFilterMin 和 wMsgFilterMax 参数限定消息获取的范围，如果二者都为 0，则消息获取的范围为所有消息；

4. 注意，即便你通过 wMsgFilterMin 和 wMsgFilterMax 参数限定消息获取的范围，但 WM_QUIT 不受此范围影响（无法阻止此消息被 PeekMessage 函数获取）；

5. 调用此函数的过程中，如果接收到非排队消息 —— 也就是由该线程调用 SendMessage, SendMessageCallback, SendMessageTimeout, 或 SendNotifyMessage发送给所属窗口的消息 —— 系统先暂时挂起等待，然后再获取过滤器匹配的第一个队列消息。如果不指定过滤器，那么按照以下顺序获取消息：

- Sent messages
- Posted messages
- Input (hardware) messages and system internal events
- Sent messages (again)
- WM_PAINT messages
- WM_TIMER messages

6. PeekMessage 函数通常不会从消息队列中删除 WM_PAINT 消息，WM_PAINT 会持续保留在消息队列中直到它们被处理，除非一个 WM_PAINT 消息指定的区域为 NULL。



7. 如果一个顶层窗口停止响应的消息超过几秒钟，系统认为窗口没有响应，并使用一个备用窗口替代，该窗口具有相同的 Z 序列、位置、尺寸和视觉属性。这使得用户可以移动、调整大小，甚至关闭该应用程序。然而，这些仅仅是动作，现有的程序事实上仍然没有响应（为了提高用户体验而制作的假象）。当一个程序被调试时，系统并不会为其生成备用窗口。