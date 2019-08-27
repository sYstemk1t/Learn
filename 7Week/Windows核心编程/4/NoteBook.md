# 进程

**进程通常被定义为一个正在运行的程序实例，它由两部分组成**

- 一个是操作系统用来管理进程的内核对象。内核对象也是系统用来存放关于进程的统计信息的地方
- 另一个是地址空间，它包含所有可执行模块或DLL模块的代码和数据。它还包含动态内存分配的空间



进程是拥有“惰性”的。若要使进程完成某项操作，它必须拥有一个在它环境中运行的线程，该线程负责执行包含在进行的地址空间中的代码。

实际上，单个进程可能包含若干个线程，所有这些线程“同时”执行进程地址空间中的代码。为此，**每个线程都有它自己的一组CPU寄存器和自己的堆栈**

**每个进程至少拥有一个线程，来执行进程的地址空间中的代码**

如果没有线程要继续执行的代码，进程就失去了存在的理由。系统回自动销毁进程和其地址空间。



**若要使得这些线程都能运行，操作系统就要为每个线程安排一定的CPU时间。它是以一种循环的方式对线程提供时间片(简称量程)，造成一种假象，彷佛所有的线程都是同时运行的**



如果计算机装载多cpu或者（多核cpu），操作系统会采用更复杂的算法为线程分配cpu时间。

![](Windows-Kernel-4\1.png)

以上图片为在单CPU的计算机上，操作系统以轮询方式为每个单独的线程分配时间量



## 编程第一个Windows应用程序

Windows支持两种类型的应用程序：

- 基于图形用户界面(GUI)的应用程序
- 基于控制台用户(CUI)的应用程序



用于 C U I应用程序的链接程序开关是 / S U B S Y S T E M : C O N D O L E，而用于 G U I应用程序的链接程序开关是S U B S Y S T E M : W I N D O W S。当用户运行一个应用程序时，操作系统的加载程序就会查看可执行图形程序的标题，并抓取该子系统的值。如果该值指明一个 C U I应用程序，那么加载程序就会自动保证为该应用程序创建文本控制台窗口。



**用户运行应用程序时，操作系统加载程序（loader）会检查可执行文件映像的文件头，并获取这个子系统值。然后进行相应的加载（开启一个命令行窗口或者是创建一个主窗口）**



等程序加载以后，操作系统就不会关心当前运行的是CUI和GUI了



Windows应用程序的入口函数：

```c
INT WINAPI _tWinMain(
	_In_ HINSTANCE hInstance,				//窗口句柄
	_In_opt_ HINSTANCE hPrevInstance,		//实例句柄
	_In_ LPSTR lpCmdLine,					
	_In_ int nShowCmd);						//显示方式
 
int _tmain(
	_In_ int _Argc,
	_In_reads_(_Argc) _Pre_z_ wchar_t ** _Argv,
	_In_z_ wchar_t ** _Env);

```



操作系统本身并不会调用入口函数main或是WinMain，而是调用C/C++运行实现的函数库，并在链接时使用-ENTRY：命令选项来设置的一个C/C++运行时的启动函数

该函数初始化C/C++运行库，使我们可以调用malloc free之类的函数。 还确保在代码执行前任何全局和静态的C++对象都被正确构造。





![](Windows-Kernel-4\2.png)



连接器选择正确的C/C++运行库启动函数。如果指定SUBSYSTEM：WINDOWS 连接器就会寻找WinMain

如果没有找到WinMain则返回“unresolved external symbol”

如果选择/SUBSYSTEM:CONSOLE 连接器默认会寻找main或者wmain 如果找不到则返回"unresolved external symbol"

可以自行关闭SUBSYSTEM连接器开关，让连接器自动判断（入口是main 还是winmain）。


当创建应用程序时，编程员会看到一个链接程序错误消息，因为 w i n 3 2应用程序项目设置了/ S U B S Y S T E M : W I N D O W S链接程序开关，但是不存在Wi n M a i n或w Wi n M a i n函数。这时，编程员可以有4个选择：

- 将m a i n函数改为Wi n M a i n。通常这不是最佳的选择，因为编程员可能想要创建一个控制台应用程序。
- 用Visual C++创建一个新的Win32 控制台应用程序，并将现有的源代码添加给新应用程序项目。这个选项冗长而乏味，因为它好像是从头开始创建应用程序，而且必须删除原始的应用程序文件。
- 单击Project Settings对话框的 L i n k选项卡，将 / S U B S Y S T E M : W I N D O W S开关改为/ S U B S Y S T E M : C O N S O L E。这是解决问题的一种比较容易的方法，很少有人知道他们只需要进行这项操作就行了。
- 单击Project Settings对话框的L i n k选项卡，然后全部删除/ S U B S Y S T E M : W I N D O W S开关。这是我喜欢选择的方法，因为它提供了最大的灵活性。现在，连接程序将根据源代码中实现的函数进行正确的操作。当用Visual C++的Developer Studio创建新Wi n 3 2应用程序或Wi n 3 2控制台应用程序项目时，我不知道为什么这没有成为默认设置。





Visual C++配有C运行期库的源代码。可以在CR t0.c文件中找到这4个启动函数的代码:

- 检索指向新进程的完整命令行的指针。
- 检索指向新进程的环境变量的指针
- 对C/C++运行期的全局变量进行初始化。如果包含了这个StdLib.h文件，代码就能访问这些变量。
- 对C运行期内存单元分配函数（malloc和calloc）和其他低层输入/输出例程使用的内存栈进行初始化。
- 为所有全局和静态C++类对象调用构造函数。



![](Windows-Kernel-4\3.png)





完成以上所有初始化以后，C/C++启动函数就会调用应用程序的入口函数。

如果我们定义了Unicode C/C++标准库将执行以下代码



```c
STARTUPINFO StartupInfo;
	GetStartupInfo(&StartupInfo);
	int nMainRetVal = wWinMain((HINSTANCE)&__ImageBase, NULL, pszCommandLineUnicode,
		(STARTUPINFO.dwFlags & STARTF_USESHOWWINDOW)
		? STARTUPINFO.wShowWindow : SW_SHOWDEFAULT);
```

如果我们没有定义Unicode C/C++标准库将执行以下代码



```c
	STARTUPINFO StartupInfo;
	GetStartupInfo(&StartupInfo);
	int nMainRetVal = WinMain((HINSTANCE)&__ImageBase, NULL, pszCommandLineAnsi,
		(STARTUPINFO.dwFlags & STARTF_USESHOWWINDOW)
		? STARTUPINFO.wShowWindow : SW_SHOWDEFAULT);

```





如果编写了一个w m a i n函数，它将以下面的形式被调用：

```c
int nMainRetVal = wmain(__agrc,__wargv,_webviron);
```

如果编写了一个m a i n函数，它将以下面的形式被调用：

```c
int nMainRetVal = main(__argc,__argv,_environ);
```

当进入点函数返回时，启动函数便调用 C运行期的e x i t函数，将返回值（n M a i n R e t Va l）传递给它。E x i t函数负责下面的操作：

- 调用由_onexit函数的调用而注册的任何函数
- 为所有全局和静态的C++类对象调用析构函数
- 调用操作系统的ExitProcess函数，将nMainRetVal传递给它。





### 进程的实例句柄

加载到进程地址空间的每个可执行文件或DLL文件均被赋予一个独一无二的实例句柄。可执行文件的实例作为(w)WinMain的第一个参数hinstExe来传递。对于加载资源的函数调用来说，通常都需要该剧并的值：

```c
WINUSERAPI
HICON
HICON LoadIcon{
    HINSTANCE hinst,			//指明哪个文件(可执行文件或DLL)包含逆向加载的资源
    PCTSTR pszIcon				//
};
```

有的函数需要一个HMODULE类型的参数和HINSTANCE一致

```c
WINBASEAPI
_Success_(return != 0)
_Ret_range_(1, nSize)
DWORD
WINAPI
GetModuleFileNameW(
    _In_opt_ HMODULE hModule,
    _Out_writes_to_(nSize, ((return < nSize) ? (return + 1) : nSize)) LPWSTR lpFilename,
    _In_ DWORD nSize
    );
```

WinMain的HinstExe参数实际的值是系统将可执行文件的映象到进程的地址空间时使用的基本地址空间。

如果系统打开了可执行文件并且将它的内容加载到地址0x00400000中，那么WinMain的hinstExe参数的值就说0x00400000。



**可执行程序的映像加载到的基地址是由链接程序决定的。不同的链接程序可以使用不同的默认基地址。**



**VC++链接程序使用的默认基地址是0x00400000，因为这是在运行Windows98时可执行文件的映象可以加载到的最低地址。修改方法在微软的链接程序中的/BASE:address链接程序开关。**



**如果你想在Windows上加载的可执行文件的基地址小于0x00400000，那么Windows98加载程序必须将可执行文件重新加载到另一个地址。**



下面的G e t M o d u l e H a n d l e函数返回可执行文件或D L L文件加载到进程的地址空间时所用的句柄/基地址：

```c
HMODULE GetModuleHandle(PCTSTR pszMoudle);
```



可以传入NULL 就会获得主调进程可执行文件的地址。

```c
#include <stdio.h>
#include <windows.h>

WINBASEAPI
_When_(lpModuleName == NULL, _Ret_notnull_)
_When_(lpModuleName != NULL, _Ret_maybenull_)
HMODULE
WINAPI
GetModuleHandleW(
_In_opt_ LPCWSTR lpModuleName
);

int main()
{
	HANDLE hInstExe = GetModuleHandle(NULL);
	return 0;
}
```



![](Windows-Kernel-4\4.png)





### 进程的前一个实例句柄

C / C + +运行期启动代码总是将N U L L传递给( w ) WinMain的hinstExePrev参数。该参数用在1 6位Window s中，并且保留了WinMain的一个参数，目的仅仅是为了能够容易地转用1 6位Windows应用程序。



hPrevInstance 参数用于16位windows系统，在32位系统中不要使用此参数。


 可以不在参数列表中写参数变量，也可以通过宏

UNREFERENCED_PARAMETER(hPrevInstance);  来让编译器不发出警告







### 进程的命令行

**当一个新的进程创建时，它需要传递一个命令行。该命令行几乎永远不是空的，至少创建新进程的可执行文件的名字是命令行上的第一个标记。**



**当C运行期的启动代码开始运行的时候，它需要检索进程的命令行，跳过可执行文件的名字，并且指向命令行其余部分的指针传递给WinMain的pszCmdLine参数**



pszCmdLine参数总是指向一个ANSI字符串。但是如果将WinMain改为wWinMain，就能够访问进程的Unicode版本命令行

也可以获得一个指向进程的完整命令行的指针，方法是调用GetCommandLine函数：

```c
PTSTR GetCommandLine();
```

该函数返回一个指向包含完整命令行的缓存的指针，该命令行包括执行文件的完整路径名。



许多应用程序常常拥有转换成它的各个标记的命令行。使用全局性 _ _ a rg c（或_ _ w a rg v）变量，应用程序就能访问命令行的各个组成部分。下面这个函数 C o m m a n d L i n e To A rg v W将U n i c o d e字符串分割成它的各个标记：

```c
SHSTDAPI_(LPWSTR *)  CommandLineToArgvW(_In_ LPCWSTR lpCmdLine, _Out_ int* pNumArgs);
```



**CommaneLineToArgvW负责在内部分配内存。大多数应用程序不释放该内存，它们在进程运行终止时依靠操作系统来释放内存。**



例子：

```c
#include <stdio.h>
#include <windows.h>
SHSTDAPI_(LPWSTR *)  CommandLineToArgvW(_In_ LPCWSTR lpCmdLine, _Out_ int* pNumArgs);

int main(int argc, char* argv[], char * env[])
{
	int nNumArgs;
	PWSTR *ppArgv = CommandLineToArgvW(GetCommandLineW(), &nNumArgs);
	HeapFree(GetProcessHeap(), 0, ppArgv);
	return 0;
}
```







### 进程的环境变量

**每个进程都有一个与它相关的环境快。环境快是进程的地址空间中分配的一个内存块。每个环境块都包含一组字符串**

![](Windows-Kernel-4\6.png)

每个字符串的第一部分是环境变量的名字，后跟一个等号，等号后面是要赋予变量的值。环境块中的所有字符串都必须按环境变量名的字母顺序进行排序。



**通常，子进程可以继承一组与父进程相同的环境变量。但是，父进程能够控制子进程继承什么环境变量。**

**所谓继承，指的是子进程获得它自己的父进程的环境块拷贝，子进程与父进程并不共享相同的环境块。这意味着子进程能够添加、删除或修改它的环境块中的变量，而这个变化在父进程的环境块中却得不到反映。**







### 线程的亲缘性

一般来说，进程中的线程可以在主计算机中的任何一个 CPU上执行。但是一个进程的线程可能被强制在可用C P U的子集上运行。







### 进程的错误模式

每个进程相关联的是一组标志，用于告诉系统，进程对严重的错误应该做出如何反映，包括磁盘介质错误，未处理的异常，文件查找错误以及数据对齐错误。

方法是调用SetErrorMode函数：



```c
UINT SetErrorMode(UINT fuErrorMode);
```

fuErroMode参数是表4 - 3的任何标志按位用OR连接在一起的组合。

![](Windows-Kernel-4\7.png)

错误模式会被子进程继承，除非在CreatePcocess中设置CREATE_DEFAULT_ERROR_MODE









### 进程当前的驱动器和目录

当不提供全路径名时，Wi n d o w s的各个函数就会在当前驱动器的当前目录中查找文件和目录。



系统将在内部保持对进程的当前驱动器和目录的追踪。由于该信息是按每个进程来维护的，因此改变当前驱动器或目录的进程中的线程，就可以为该进程中的所有线程改变这些信息。



```c
WINBASEAPI
_Success_(return != 0 && return < nBufferLength)
DWORD
WINAPI
GetCurrentDirectoryW(
    _In_ DWORD nBufferLength,
    _Out_writes_to_opt_(nBufferLength, return + 1) LPWSTR lpBuffer
    );
 
WINBASEAPI
BOOL
WINAPI
SetCurrentDirectoryW(
    _In_ LPCWSTR lpPathName
    );
```



如果进程中的某一线程调用了SetCurrentDirectory修改了默认的进程目录，则所有使用相对路径处理的可能会导致意外的错误。
GetCurrentDirectory可以传入  （0， NULL） 会返回需要字符的个数包括末尾的'\0'

或者直接传入MAX_PATH 尺寸的buffer





### 进程中的当前目录

系统将对进程的当前驱动器和目录保持跟踪，但是它不跟踪每个驱动器的当前目录。**系统跟着记录这进程的当前驱动器和目录，但没有记录每个驱动器的当前目录。可以通过环境变量来支持**



![](Windows-Kernel-4\8.png)

例如假定当前进程的目录是C:\Utility\Bin ,而我们调用CreateFile来打开D:ReadMe.Txt 那么系统会查找环境变量=D:

由于=D:是存在的，系统将尝试从D:\Program Files目录打开ReadMe.txt文件，如果=D:不存在，系统会尝试从D盘根目录打开ReadMe.txt文件

Windows的文件函数从来不会添加或更改驱动器号。他们只是读取这种变量。

_chdir也可以更改当前目录其内部调用SetCurrentDirectory, _chdir还会调用SetEnvironmentVariable来添加或修改环境变量，从而使不同驱动器的当前目录得以保留。




**如果父进程创建了一个它想传递给子进程的环境块，子进程的环境块不会自动继承父进程的当前目录。相反，子进程的当前目录将默认为每个驱动器的根目录。如果想要让子进程继承父进程的当前目录，该父进程必须创建这些驱动器名的环境变量。**



获取每个驱动器的当前目录:

```c
	TCHAR szCurDir[MAX_PATH] = { 0 };
	DWORD cchLength = GetFullPathName(TEXT("D:"), MAX_PATH, szCurDir, NULL);
	_tprintf(TEXT("%s\n"), szCurDir);
```



驱动器号环境变量通常必须放在环境块的开始处。



以下例子修改D盘的当前目录并调用GetFullPathName获取



```c

	SetCurrentDirectory(TEXT("D:\\Program Files (x86)"));
	TCHAR szCurDir[MAX_PATH] = { 0 };
	DWORD cchLength = GetFullPathName(TEXT("d:"), MAX_PATH, szCurDir, NULL);
	_tprintf(TEXT("%s\n"), szCurDir);
```





如果希望子进程继承父进程的当前目录，父进程就必须在生成子进程之前，创建这些驱动器号的环境变量，并把它添加到环境块中。



GetCurrentDirectory

SetCurrentDirectory

GetFullPathName 在多线程应用中应该特别小心，因为他们的值是进程相关的。在获取过程中可能被其他线程所修改了。而且也应该避免使用相对路径








### 系统版本

应用程序常常需要确定用户运行的是哪个 Windows版本。

Windows API拥有下面的GetVersion函数：

```c
DWORD GetVersion();			////主版本号在低字节，次版本号在高字节
```





```c
typedef struct _OSVERSIONINFOEXW {
    DWORD dwOSVersionInfoSize;
    DWORD dwMajorVersion;
    DWORD dwMinorVersion;
    DWORD dwBuildNumber;
    DWORD dwPlatformId;
    WCHAR  szCSDVersion[ 128 ];     // Maintenance string for PSS usage
    WORD   wServicePackMajor;
    WORD   wServicePackMinor;
    WORD   wSuiteMask;
    BYTE  wProductType;
    BYTE  wReserved;
} OSVERSIONINFOEXW, *POSVERSIONINFOEXW, *LPOSVERSIONINFOEXW, RTL_OSVERSIONINFOEXW, *PRTL_OSVERSIONINFOEXW;
```



![](Windows-Kernel-4\9.png)

![](Windows-Kernel-4\10.png)







## CreatProcess函数



CreatProcess函数：

```c
BOOL CreateProcess
(
LPCTSTR lpApplicationName,
LPTSTR lpCommandLine,
LPSECURITY_ATTRIBUTES lpProcessAttributes,
LPSECURITY_ATTRIBUTES lpThreadAttributes,
BOOL bInheritHandles,
DWORD dwCreationFlags,
LPVOID lpEnvironment,
LPCTSTR lpCurrentDirectory,
LPSTARTUPINFO lpStartupInfo,
LPPROCESS_INFORMATION lpProcessInformation
);
```



- 系统将创建一个进程内核对象，其初始引用计数器为1，进程内核对象并不是进程本身，而是操作系统用来管理该进程用的一个小型数据结构
- 系统为进程创建一个虚拟地址空间，并将可执行文件（DLL）的代码以及数据加载到进程的地址空间
- 系统为新进程的主线程创建一个线程内核对象（其引用计数为1）。与进程内核对象一样，线程内核对象也是操作系统用来管理线程的小型数据结构。通过C/C++运行期启动代码，该主线程便开始运行，它最终调用WinMain、wWinMain、main、或者wmain函数。**如果系统成功创建了新线程和主线程，CreateProcess便返回TRUE**

在进程被完全初始化之前，CreateProcess返回TRUE。这意味着操作系统加载程序尚未找出所需要的DLL。如果一个DLL无法找到，或者未能正确初始化，那么该进程就终止运行。由于CreateProcess返回TRUE，因此父进程不知道出现的任何初始化问题。



### pszApplicationName和pszCommandLine

前者是新进程可执行文件的名字

后者是要传递给新进程的命令行参数。CreateProcess实际会修改我们传给它的命令行字符。但在CreateProcess返回之前，它会将此字符还原成原来的形式。



这是很重要的，不能传递只读内存区。否则可能会报错



```c
#include <stdio.h>
#include <windows.h>

int main(int argc,TCHAR* argv[],TCHAR * env[])
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	CreateProcess(NULL, TEXT("NOTEPAD"), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	return 0;
}
```

在调用之前将字符串常量复制到一个临时变量则不会报错。



```c
#include <stdio.h>
#include <windows.h>

int main(int argc,TCHAR* argv[],TCHAR * env[])
{
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	TCHAR szCommandLine[] = TEXT("NOTEPAD");
	CreateProcess(NULL, szCommandLine, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
	return 0;
}
```

如果调用Windows 2000上CreateProcess的ANSI版本，就不会违规访问，因为系统已经制作了一个命令行字符串的临时拷贝。





可以使用pszApplicationName参数设定一个完整的命令行，以便于CreateProcess用来创建新的进程。当CreateProcess分析pszCommandLine字符串的时候，它将查看字符串中的第一个标记，并假设该标记是想运行的可执行文件的名字。如果可执行文件没有扩展名，那么假设它为.exe，CreateProcess也按照下面的顺序搜索可执行文件：

- 包含调用进程的.exe文件的目录
- 调用进程的当前目录
- Windows的系统目录
- Windows目录
- PATH环境变量中列出的目录

当然如果包含了绝对路径，则会直接使用绝对路径来查找可执行文件。



只要pszApplicationName设置为NULL，就会发生上述情况。





也可以在pszApplicationName只指定应用程序的名字，但是必须指定扩展名。CreateProcess假定当前目录，除非文件名之前有指定目录。并且CreateProcess不会在其他路径查找文件。







### psaProcess、psaThread和binheritHandles

**若要创建一个新进程，系统必须创建一个进程内核对象和一个线程内核对象（用于进程的主线程），由于这些都是内核对象，因此父进程可以得到机会将安全属性与这两个对象关联起来。**

**可以使用pasProcess和pasThread参数分别设定进程对象和线程对象需要的安全性，可以为NULL，在这种情况下，系统为这些对象赋予默认安全性描述符**



为psaProcess和psaThread参数使用SECURITY_ATTRIBUTES结构可以使其支持继承（继承父进程的句柄表）



一个继承的例子：

- 进程A创建了进程B并且设置进程B的进程内核对象可继承、主线程内核对象不可继承。（两个对象在进程B创建以后会更新A的句柄表，并且可以看到两个内核对象的继承标志）
- 由于创建进程B的时候CreateProcess的binheritHandles设置为FALSE，所以进程B不会继承进程A中的任何“可继承”的内核对象。
- 接着进程A又创建了进程C，并设置CreateProcess的两个SECURITY_ATTRIBUTES为NULL，表明进程C的进程对象和线程对象在进程A的句柄表中是不可被继承的。
- 创建进程C的时候CreateProcess设置binheritHandles为TRUE，此时进程C将继承进程A中的所有继承内核对象。这里有之前创建的进程B的内核对象，但不包含进程B的主线程和内核对象。



```c
	// Prepare a STARTUPINFO structure for spawning process.
	STARTUPINFO si = { sizeof(si) };
	SECURITY_ATTRIBUTES saProcess, saThread;
	PROCESS_INFORMATION piProcessB, piProcessC;
	TCHAR szPath[MAX_PATH];
 
	// Prepare to spawn Process B from Process A.
	// The handle identifying the new process
	// object should be inheritable.
	saProcess.nLength = sizeof(saProcess);
	saProcess.lpSecurityDescriptor = NULL;
	saProcess.bInheritHandle = TRUE;
 
	// The handle identifying the new thread
	// object should NOT be inheritable.
	saThread.nLength = sizeof(saThread);
	saThread.lpSecurityDescriptor = NULL;
	saThread.bInheritHandle = FALSE;
 
	// Spawn Process B.
	_tcscpy_s(szPath, _countof(szPath), TEXT("ProcessB"));
	CreateProcess(NULL, szPath, &saProcess, &saThread,
		FALSE, 0, NULL, NULL, &si, &piProcessB);
 
	// The pi structure contains two handles
	// relative to Process A:
	// hProcess, which identifies Process B's process
	// object and is inheritable, and hTrhead, which identifies
	// Process B's primary thread object and is NOT inheritable.
	// Prepare to spawn Process C from Process A.
	// Since NULL is passed for the psaProcess and psaThread
	// parameters, the handle to Process's process and
	// primary thread objects default to "noninheritable."
	// If Process A were to spawn another process, this new
	// process would NOT inherit handles to Process's process
	// and thread object.
	// Because TRUE is passed for the bInheritHandles parameter,
	// Process C will inherit the handle that identifies Process
	// B's process object but will not inherit a handle to
	// Process B's primary thread object.
	_tcscpy_s(szPath, _countof(szPath), TEXT("ProcessC"));
	CreateProcess(NULL, szPath, NULL, NULL,
		TRUE, 0, NULL, NULL, &si, &piProcessC);
```





### fdwCreate

fdwCreate参数影响了创建新进程创建方式的flag



DEBUG_PROCESS 标志父进程希望调试子进程以及子进程将来创建的所有进程。（父进程现在的身份是调试器）



DEBUG_ONLY_THIS_PROCESS 最近创建的一个进程会通知父进程。而其创建的子进程将不会通知父进程。

CREATE_SUSPENDED 让系统创建新进程的同时挂起子进程的主线程。这样父进程就可以修改子进程地址空间中的内存，更改子进程主线程的优先级，或者在进程执行任何代码以前将次进程添加到一个作业中。父进程修改好子进程，可以调用ResumeThread函数来允许子进程执行代码。



DETACHED_PROCESS 标志阻止一个基于CUI的子进程访问其父进程的控制台窗口，并告诉系统它的输出发送到一个新的控制台窗口。

通常一个一个CUI进程创建了一个新的CUI子进程，那么默认情况下新进程也会使用父进程的控制台。如果指定了此标志那么子进程必须调用AllocConsole来创建自己的控制台。



**CREATE_NEW_CONSOLE**,会自动为子进程创建自己的CONSOLE不能和DETACHED_PROCESS一起使用。

CREATE_NO_WINDOW  标志应用程序不要为子进程创建任何控制台，用于执行没有用户界面的程序。



CREATE_NEW_PROCESS_GROUP 对CUI程序而言的。用于创建新进程组。在同一组中的所有进程，当按下Ctrl+C中断当前操作时，系统会向这个组的进程发出通知。



CREATE_DEFAULT_ERROR_MODE 新进程不会继承父进程的错误模式



CREATE_SEPARATE_WOW_VDM 表明创建一个16位windows程序（Virtual DOS Machine） 默认创建的16位进程会共享一个VDM（因为创建一个会消耗较多的资源）



CREATE_SHARED_WOW_VDM 在运行16位应用程序才有用， 可以修改注册表 HKEY_LOCAL_MACHINE\System\CurrentControlSet\Control\WOW\

DefaultSeparateVDM 设置为yes

可以调用IsWow64Process 来判断检测进程句柄是不是32位进程（在64bit系统下）



CREATE_UNICODE_ENVIRONMENT 告诉系统子进程的环境块包含UNICODE字符，进程环境块默认包含ANSI字符



CREATE_FORCEDOS 强制系统运行嵌入一个在16位OS中的MS-DOS程序



CREATE_BREAKAWAY_FROM_JOB 允许一个作业中的进程生成一个和作业无关的进程



EXTENDED_STARTUPINFO_PRESENT  告知操作系统传给psiStartInfo参数的是STARTUPINFOEX结构



fdwCreate还运行给进程分配优先级。但是大部分应用没这个必要。

低IDLE_PRIORITY_CLASS

低于标准BELOW_NORMAL_PRIORITY_CLASS

标准NORMAL_PRIORITY_CLASS

高于标准ABOVE_NORMAL_PRIORITY_CLASS

高HIGH_PRIORITY_CLASS

实时REALTIME_PRIORITY_CLASS





### pvEnvironment

pvEnvironment参数指向一块内存，其中包含新进程要使用的环境字符串。大多数时候这个参数传入NULL，

子进程会继承其父进程使用的一组环境字符串。

还可以通过GetEnvironmentString函数获得父进程的环境块的串地址，传递给CreateProcess用于创建子进程。 该功能和传入NULL的行为一致。

不使用环境字符串的时候调用FreeEnvironmentStrings释放其空间。







### **pszCurDir**

允许父进程设置当前进程的当前驱动器和目录。如果为NULL则默认和主进程一致。如果非NULL

pszCurDir必须执行一个以'\0'结尾的字符串，其中包含了工作驱动器和目录。







### psiStartInfo参数

指向一个**STARTUPINFO** 或者 **STARTUPINFOEX**的结构体

```c
typedef struct _STARTUPINFOW {
    DWORD   cb;
    LPWSTR  lpReserved;
    LPWSTR  lpDesktop;
    LPWSTR  lpTitle;
    DWORD   dwX;
    DWORD   dwY;
    DWORD   dwXSize;
    DWORD   dwYSize;
    DWORD   dwXCountChars;
    DWORD   dwYCountChars;
    DWORD   dwFillAttribute;
    DWORD   dwFlags;
    WORD    wShowWindow;
    WORD    cbReserved2;
    LPBYTE  lpReserved2;
    HANDLE  hStdInput;
    HANDLE  hStdOutput;
    HANDLE  hStdError;
} STARTUPINFOW, *LPSTARTUPINFOW;
```





```c
typedef struct _STARTUPINFOEXW {
    STARTUPINFOW StartupInfo;
    LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList;
} STARTUPINFOEXW, *LPSTARTUPINFOEXW;
```

默认值只要生成次结构

STARTUPINFO si = {sizeof(si)};

CreateProcess(..., &si, ...);

如果没有把结构内容清0，则成员将包含线程栈上的垃圾数据。会造成CreateProcess 未知运行结果。



![](Windows-Kernel-4\11.png)

![](Windows-Kernel-4\12.png)



关于dwFlags成员，包含一组标志用于修改子进程的创建方式。

![](Windows-Kernel-4\13.png)



另外还有两个标志

STARTF_FORCEONFEEDBACKCreateProcess会监控进程的初始化过程，并根据结果更改光标的形状。一旦子进程调用了GetMessage（表明初始化完毕）CreateProcess则停止监控。

START_FORCEOFFFEEDBACK 改为等待图标

在启动进程时候控制鼠标指针。CreateProcess临时将系统的护镖指针改为 加载等待 图片



wShowWindow会作为参数传递给子进程WinMain函数中的nCmdShow参数。  可能值是SW_SHOWNORMAL, SW_SHOWMINNOACTIVE 和 SW_SHOWDEFAULT

也可以在应用程序的快捷方式中修改此值。



![](Windows-Kernel-4\14.png)

Microsoft为了避免创建多个CreateProcess版本，仅仅是通过扩展STARTUPINFOEX结果来升级新的feature。

STARTUPIINFOEX保护一个字段 lpAttributeList用于传递额外属性。

PROC_THREAD_ATTRIBUTE_HANDLE_LIST 该属性告知CreateProcess进程究竟应该继承哪一些内核对象的句柄。这些对象句柄必须在创建时指定可继承（SECURIT_ATTRIBUTES结构中保护设置为TRUE的bInheritHandle字段）。

使用这个属性，子进程只能继承一组选定的句柄，而不是继承所有可继承的句柄。



PROC_THREAD_ATTRIBUTE_PARENT_PROCESS  自行指定进程成为当前要创建的进程的父进程。 但是不改变调试关系。调用CreateProcess的进程仍然能收到调试通知。

调用以下函数两次，才能创建一个空白的属性列表。










lpAttributeList是之前初始化的attribute列表， 他接受PROC_THREAD_ATTRIBUTE_PARENT_PROCESS  或者  PROC_THREAD_ATTRIBUTE_HANDLE_LIST的值。
如果是前者pValue 必须执行一个变量的地址，包含了新的父进程句柄，而cbSize应该使用sizeof(HANDLE)作为其值。

如果是后者pValue必须执行一个数组的起始地址，包含了运行进程访问的，可继承的内核对象句柄， cbSize = sizeof(HANDLE)*句柄数。

dwFlags, PreviousValue和pReturnSize是保留参数，必须设定为0，NULL和NULL

一个初始化Attributelist 并使用STARTUPINFOEX创建进程的例子

创建了一个mutex 并设定AttributeList让子进程继承此Mutex








最后应用程序可以调用以下函数获得STARTUPINFO结构的一个副本。此结构是由父进程初始化的。子进程可以检查这个结构并根据成员值来修改其行为。
VOID GetStartupInfo(LPSTARTUPINFO pStartupInfo);

StartupInfo中的一些句柄值在父进程中创建的，其地址是父进程的地址空间。








### ppiProcInfo

指向一个**PROCESS_INFORMATION**的结构

```c
typedef struct _PROCESS_INFORMATION {
    HANDLE hProcess;
    HANDLE hThread;
    DWORD dwProcessId;
    DWORD dwThreadId;
} PROCESS_INFORMATION, *PPROCESS_INFORMATION, *LPPROCESS_INFORMATION;
```

CreateProcess返回的与当前进程相关的 进程内核对象句柄 和 线程内核对象句柄。引用计数器为1. 而CreateProcess内部打开这些对象引用计数器又会加1
因此若要让子进程和子进程的主线程在父进程退出之前关闭，子进程必须先终止（引用计数器-1）必须在父进程中调用CloseHandle将其引用计数器再-1. 

释放子进程的主线程内核对象同理。

注意：关闭句柄并不会真正关闭子进程和子线程（只改变其引用计数器）！



进程会被操作系统分配一个独一无二的ProcessID， PID=0 是System Idle Process 其线程数等于CPU数量



![](Windows-Kernel-4\15.png)

PID主要供一些系统工具辨识进程使用。

PID由操作系统管理会被回收分配和重用。所以要特备注意。

GetCurrentProcessId获得PID

GetCurrentThreadId 获得当前正在运行线程的ID

根据指定句柄获得PID  GetProcessId

根据指定句柄获得线程ID  GetThreadId

获得当前线程所在进程的PID GetProcessIdOfThread



ToolHelp函数允许进程通过PROCESSENTRY32 结构查询其父进程的PID。

但是由于PID具有实效性，可能不准确。最好使用内核对象，窗口句柄等来定位一个进程的父进程。

如果一定要使用PID，唯一的办法就是保证进程或线程的内核对象不被销毁。（例如将父进程的内核对象继承给子进程） 在不需要使用以后调用CloseHandle







## 终止进程

4种方式可以终止进程：

- 主线程的入口点函数返回
- 进程中有一个ExitProcess函数
- 另一个进程中的线程调用TeaminateProcess函数
- 进程中的线程全部“自然死亡”





### 主线程的入口点函数返回

应该确保只有在主线程的入口点函数返回之后，这个应用程序才终止。这样主线程的所以资源才能被正确清理。确保以下操作会被执行

- 该线程创建的任何C++对象都将由这些对象的析构函数正确销毁
- 操作系统将正确释放线程栈使用的内存
- 系统将进程的退出代码（在进程的内核对象中维护）设为入口点函数的返回值
- 系统递减内核对象使用计数器







### ExitProcess

**当进程中的一个线程调用ExitProcess函数时，进程便结束运行：**

```c
void ExitProcess(UNIT fuExitCode);
```

该函数用于终止进程的运行，并将进程的退出代码设置为fuExitCode。ExitProcess函数并不返回任何值，因为进程已经终止运行。如果在调用ExitProcess之后又增加了代码，那么这段代码是永远不会被运行的。



**Windows SDk文档声明，进程要等到所有线程终止运行以后才终止运行。如果在入口点调用的ExitThread，而不是调用ExitProcess或者仅仅是返回，那么应用程序的主线程将停止运行，但是如果进程中至少还有一个线程在运行，该进程不会终止运行。**



```c
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
 
class CSomeObj{
public:
	CSomeObj() { printf("Constructor \n"); }
	~CSomeObj() { printf("Destructor \n"); }
};
 
CSomeObj g_GlobalObj;
 
int _tmain(int argc, TCHAR* argv[], TCHAR * env[])
{
	CSomeObj LocalObj;
	ExitProcess(0);
 
	return 0;
}
```



全局对象和局部对象都没有调用析构函数，C++对象没有被正确析构，因为ExitProcess造成进程当场终止运行。C/C++运行库没有机会执行清理工作。

只需要主线程的入口函数返回，C/C++运行库就能执行其清理工作。

所以不要显示调用ExitProcess和ExitThread


  



### TerminateProcess

调用TerminateProcess也可以终止一个进程

```c
WINBASEAPI
BOOL
WINAPI
TerminateProcess(
    _In_ HANDLE hProcess,
    _In_ UINT uExitCode
    );
```

任何线程都可以调用TerminateProcess来终止另一个进程或者自己的进程。 hProcess指定了要终止的进程的句柄。其退出代码的值就是传给uExitCode的值。
被终止的进程得不到自己要被终止的通知--应用程序不能正确清理，也不能阻止它自己被强行终止。例如这种情况下进程不能将它在内存中的信息flush到磁盘上。

操作系统在进程终止以后会进行彻底清理，保证不会泄露任何操作系统资源。在进程终止后绝对不会泄漏任何东西。

TerminateProcess函数是异步的，并不等到进程完全终止了才返回。为了确定进程是否终止需要使用WaitForSingleObject





### 当进程中的所有线程终止时

当进程的所有线程终止时，操作系统认为没有任何理由再保持进程的地址空间。并会终止这个进程。进程的退出代码会被设置为最后一个终止的哪个线程的退出代码。





### 当进程终止运行时

一个进程终止时，系统回依次执行以下操作。

- 终止进程中驻留的任何线程
- 释放进程分配的所有用户对象和GDI对象，关闭所有内核对象（如果没有其他进程打开这些内核对象的句柄，那么他们会被销毁。否则引用计数器-1）
- 进程的退出代码从**STILL_ACTIVE**变为传给ExitProcess或TerminateProcess函数的代码
- 进程内核对象状态变为已触发状态
- 进程内核对象引用计数器-1



当父进程忘记关闭子进程句柄时候，子进程即使结束。其进程内核对象句柄仍然不会被销毁。此时可以获得一些统计信息，例如GetExitCodeProcess来获得一个已经终止的进程的退出代码。

```c
WINBASEAPI
BOOL
WINAPI
GetExitCodeProcess(
    _In_ HANDLE hProcess,
    _Out_ LPDWORD lpExitCode
    );
```

如果被调用的进程未终止，lpExitCode会返回 STILL_ACTIVE(0x103)





重点，如果对进程的统计数据不再感兴趣应该调用CloseHandle来递减内核对象的使用计数器，并释放它。





## 子进程

为了执行复杂的任务而不让当前线程一直等待，可以创建一个新的进程来完成工作。父进程和子进程之间可以进行一些数据共享。

（DDE dynamic Data Exchange） OLE， 管道， 邮件槽等。共享数据最方便的方式就是使用内存映像文件（CreateFileMapping）



以阻塞方式运行子进程

以下代码创建了一个子进程，并等待子进程完成相应的工作正常结束以后，再继续当前线程的执行。


```c
	PROCESS_INFORMATION pi;
	DWORD dwExitCode;
 
	//Spawn the child process.
	BOOL fSuccess = CreateProcess(..., &pi);
	if (fSuccess) {
		// Close the thread handle as soon as it is no longer needed!
		CloseHandle(pi.hThread);
 
		// Suspend our execution until the child has terminated.
		WaitForSingleObject(pi.hProcess, INFINITE);
 
		// The child process terminated; get its exit code.
		GetExitCodeProcess(pi.hProcess, &dwExitCode);
 
		// Close the process handle as soon as it is no longer needed.
		CloseHandle(pi.hProcess);
	}
```

上面的例子使用了WaitForSingleObject函数，该函数会一直等待直到hObject参数所表示的对象变为已触发。 进程对象在终止的时候会变为已触发。



**WaitForSingleObject**将会挂起当前线程，直到子进程终止。


  一个良好的编程习惯：在不需要使用子进程的相关内核对象应该立即CloseHandle。 否则假定子进程生成了另外一个新的子进程，而自己的主线程已经退出。由于调用CreateProcess的当前进程未释放子进程的进程对象，因此自进程的内核对象不会被操作系统释放。


  

**运行独立的子进程**

大多数时候应用程序将另一个进程作为独立的进程（detached process）来启动。这就意味着一旦子进程创建，父进程就不再与其通信，或者不必等他它完成工作之后再继续自己的工作（当前进程不必挂起等待）。这时候只需要调用CloseHandle关闭子进程的进程句柄和主线程句柄。



```c
	PROCESS_INFORMATION pi;
 
	//Spawn the child process.
	BOOL fSuccess = CreateProcess(..., &pi);
	if (fSuccess) {
		// Allow the system to destroy the process & thread kernel
		// objects as soon as the child process terminates.
		// Close the thread handle as soon as it is no longer needed!
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
	}
```







## 管理员以标准用户权限运行时

每个用户登录windows以后会有一个安全令牌（Security token）其后该用户启动的进程都拥有此令牌的权限。

由于许多windows用户使用Administrator登录，此用户的权限太高（可以修改系统文件）可能导致操作系统以高权限执行而已软件而破坏操作系统。



在Vista以上用户以Administrator登录出来具有高特权的安全令牌，还会具有一个筛选过的令牌（filtered token） 只有普通的标准用户权限（standard user）。

之后从第一个进程开始所有启动的进程都和筛选过的令牌相关联。因此默认运行的应用程序将无法访问受限资源。



可以在进程启动之前（进程边界， 进程已经启动以后会与筛选过的令牌相关联并且运行时不可修改）让操作系统提示用户取得提升权限的同意。也可以在快捷菜单中选择以管理员身份运行。



可以在自己的应用程序上显示一个盾牌图，会弹出一个权限提升对话框。



Windows只允许进程边界上进行权限提升（未启动以前）。 可以用一个未提升权限的进程来生成另一个提升了权限的进程，后者将包含一个com服务器，这个新进程将保持活动状态。这样未提升权限的进程就可以向已经提升权限的进程发出IPC调用，而不必启动一个新的实例再终止它自身。






### 自动提升进程的权限

windows每次启动应用程序都将自动弹框询问并提升应用程序的权限（比如安装程序）

在可执行文件中嵌入资源(RT_MANIFEST) 系统会检查<trustInfo>段



```c
<trustInfo xmlns="urn:schemas-microsoft-com:asm.v2">  
    <security>  
        <requestedPrivileges>  
            <requestedExecutionLevel level="requireAdministrator"/>  
        </requestedPrivileges>  
    </security>  
</trustInfo> 
```





也可以保存成一个  应用程序.exe.manifest的文件的外部清单

如果exe本身内嵌了一个清单，则外部清单会被忽略。

也可以自行设定应用程序默认以管理员权限运行







##  枚举系统正在运行的进程

Windows在注册表中维护一个性能数据库，包含海量信息。例如RegQueryValueEx把注册表的根目录设为KEY_PERFORMANCE_DATA

但是该数据库在Win95和98上不可用， 

没有自己的函数，使用注册表函数

数据库信息布局非常复杂



为了更方便访问此数据库借助Performance Data Helper（PDH.dll）

在（Win9X中 使用ToolHelp API的Process32First 和Process32Next函数）

在WinNT中使用EnumProcess函数。

在Win2000开始Tool Help函数支持2K以上的NT内核系统。


