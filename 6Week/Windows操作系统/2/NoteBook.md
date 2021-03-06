# Windows系统总述

## 现代操作系统基础结构

**操作系统是软件，但是它需要紧密的和硬件交互**

![](F:\Learn\6Week\Windows操作系统\2\Img\0.png)



## Windows系统结构

Windows内核(由于是从Windows NT发展起来的，也成为NT内核)，Windows采用了双模式(dual mode)结构来保护操作系统本身，以避免应用程序的错误所波及。操作系统核心运行在内核模式(kernel mode)下，应用程序的代码运行在用户模式(user mode)下。

![](F:\Learn\6Week\Windows操作系统\2\Img\1.png)



**在Windows中用户代码和内核代码有各自的运行环境，而且它们可以访问内存空间也并不相同。在32位操作系统中，内核代码可以访问当前进程的整个4GB虚拟地址空间，而用户代码只能访问底端的2GB虚拟空间**







### Windows内核结构

Windows内核分三层，与硬件直接打交道的这一层为硬件抽象层（HAL）,这一层的用以是把所有与硬件相关的代码逻辑隔离到一个专门的模块中。

**HAL之上是内核层，也成为微内核，这一层中包含了基本的操作系统原语与功能，如线程调度、进程与线程、终端与异常、同步对象和各种同步机制**

Windows内核的执行体包含一个对象管理器，用于一直地管理执行体中的对象。

**执行体层和内核层位于同一个二进制模块中，即内核基本模块，称为ntoskrnl.exe**

![](F:\Learn\6Week\Windows操作系统\2\Img\2.png)



ntdll.dll是连接用户模式代码和内核模式系统服务的桥梁。对于内核提供的每一个系统服务，该DLL都提供一个相应的存根函数，这些存根函数的名称以"nt"作为前缀，ntdll.dll提供很多系统级的支持函数，**比如影响加载器函数(以"Ldr"为前缀)，Windows子系统进程通信函数(以"Csr为前缀")，调试函数("以Dbg"为前缀)，系统事件函数(以"Etw"为前缀)，以及一般运行支持函数(以"Rtl"为前缀)和字符串支持函数**





### Windows内核中的关键组件







### Windows子系统

从Windows xp以后，只有Windows子系统随Windows系统一起发行。

在Windows平台上，可执行映像文件的格式都为PE文件格式，其头部域指定了该程序将被运行在哪个环境子系统中。



Windows子系统既有用户模式部分，也有内核模式部分。**内核模式部分的核心是win32k.sys，**它向用户提供了大量的系统服务。



用户模式部分包括Windows子系统进程（carss.exe）以及一组动态链接(DLL),**csrss.exe进程主要负责控制台窗口的功能，以及创建或删除进程和线程等**，**子系统DLL则被直接链接到应用程序进程中，负责很多已文档化的Windows Api函数**

![](F:\Learn\6Week\Windows操作系统\2\Img\3.png)







## 关于Windows研究内核

![](F:\Learn\6Week\Windows操作系统\2\Img\4.png)



![](F:\Learn\6Week\Windows操作系统\2\Img\5.png)






## 内核基本概念

### 处理器模式

Intel X86处理器上，段描述符有一个2位长度的特权级：**0代表最高级、3代表最低级，Windows只使用0和3两种特权级，通常特权0代表CPU处于内核模式，3代表用户模式**



### 内存管理

Intel x86体系支持段式内存管理，也支持页式内存管理，Windows并没有使用段式内存管理，而只是简单的将32位虚拟内存空间按照0~4GB的线性空间来看待，**但是2GB~4GB之间的部分是所有进程共享，称为系统地址空间；而0~2GB的空间是私有的，称为进程地址空间；**



Windows使用Intel x86的二级或多级页表机制来访问虚拟内存。处理器在执行内存访问指令时，将虚拟地址翻译成为物理地址，翻译过程涉及查询页目录和页表，**一旦页表项指向一个页面未在物理空间中，则处罚页面错误异常**

在系统地址空间中，不同的区域使用并不同的内存页面管理算法：

- 非换页内存池

- 换页内存池

- 系统PTE区域

  

内存中的虚拟内存管理器则通过平衡二叉搜索树来管理进程地址空间被使用的情况。树中的每个节点为VAD(虚拟地址描述符)，描述了一段连续的地址范围。

