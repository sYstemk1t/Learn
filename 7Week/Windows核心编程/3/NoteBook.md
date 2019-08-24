# 内核对象

## 什么是内核对象

**每个内核对象只是内核分配的一个内存块，并且只能由该内核访问。该内存块是一种数据结构，它的成员负责维护对象的各种信息。**



### 内核对象的使用计数

内核对象由内核拥有，而不是进程拥有。

**假如你的进程调用了一个创建内核对象的函数，然后你的进程终止运行，那么内核对象不一定会被撤销，在大多数情况下，对象被撤销，但是如果另一个进程正在使用你的进程创建内核对象，那么内核知道，在另一个进程停止使用该对象之前不要撤销该对象，必须记住：内核对象的存在时间可以比创建该对象的进程长**



**内核知道有多少进程正在使用某个内核对象，因为每个对象包含一个使用计数。使用计数是所有内核对象类型常用的数据类型之一。**



**当一个对象被创建的时候，它的计数被置为1，当另外一个进程访问内核对象的时候，使用计数就递增1，当进程终止的时候，内核对象就自动确定该进程打开的所有内核对象的使用计数。当内核对象的使用计数为0，内核就撤销该对象**



使用Winobj查看内核对象

![](images\0.png)



### 安全性

**内核对象能够得到安全描述符的保护。安全描述符用于描述谁创建了对象，谁能够访问或操作该对象。**



用于创建内核对象的函数几乎都有一个指向**SECURITY_ATTRIBUTES**结构的指针作为其参数；

```c
HANDLE CreateFileMapping{
    HANDLE hFile,
    PSECURITY_ATTRIBUTES,
    DWORD flProtect,
    DWORD dwMaximumSizeHigh,
    DWORD dwMaximumSizeLow,
    PCTSTR pszName
};
```

大多数应用程序只是为该函数传递NULL，这样就可以创建带有默认安全性的内核对象；

**默认安全性意味着对象的管理小组的任何成员和对象的创建者都拥有对该对象的全部访问权，而其他所有人均无权访问该对象。**





## 进程的内核对象句柄表

**当一个进程被初始化时，系统要为它分配一个句柄表。该句柄表只用于内核对象不用于用户对象或者GDI对象**

进程句柄表是一个由数据结构组成的数组。每个结构包含一个指向内核对象的指针，一个访问掩码和一些标志。



### 创建内核对象

**当进程初次初始化时，它的句柄表是空的，当进程中的线程调用创建内核对象的函数的时候，内核就为该对象分配一个内存块，并对它初始化。这时候，内核对进程的句柄表进行扫描，找出一个空项。**



```c
HANDLE CreateThread(
    PSECURITY_ATTRIBUTE psa,
    DWORD dwStackSize,
    LPTHREAD_START_ROUTINE pfnStartAddr,
    PVOID pvParam,
    DWORD dwCreationFlags,
    PDWORD pdwThreadId);

HANDLE CreateFile(
    PCTSTR pszFileNAme,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    PSECURITY_ATTRIBUTES psa,
    DWORD dwCreationDistribution,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile);

HANDLE CreateFileMapping(
    HANDLE hFile,
    PSECURITY_ATTRIBUTES psa,
    DWORD flPRotect,
    DWORD dwMaximumSizeHigh,
    DWORD dwMaximumSizeLow,
    PCTSTR pszName);

HANDLE CreateSemaphore(
    PSECURITY_ATTRIBUTES psa,
    LONG lInitialCount,
    LONG lMaximumCount,
    PCTSTR pszName);
```



用于创建内核对象的所有函数均返回与进程相关的句柄，这些句柄可以被在相同的进程中运行的任何或所有线程成功的加以使用。该句柄值实际上是放入进程的句柄表中的索引，它用于标识内核对象的信息存放的位置。

每当调用一个将内核对象句柄接受为参数的函数时，就要传递由一个 C r e a t e * &函数返回的值。从内部来说，该函数要查看进程的句柄表，以获取要生成的内核对象的地址，然后按定义得很好的方式来生成该对象的数据结构。



如果调用一个函数以便创建内核对象，但是调用失败了，那么返回的句柄值通常是0（NULL）。发生这种情况是因为系统的内存非常短缺，或者遇到了安全方面的问题。不过有少数函数在运行失败时返回的句柄值是-1（INVALID_HANDLE_VALUE）。例如，如果CreateFile未能打开指定的文件，那么它将返回INVALID_HANDLE_VALUE，而不是返回NULL。当查看创建内核对象的函数返回值时，必须格外小心。特别要注意的是，只有当调用CreateFile函数时，才能将该值与INVALID_HANDLE_VALUE进行比较。下面的代码是不正确的：



```c
HANDLE hMutex = CreateMutex(...);
if (hMutex == INVALID_HANDLE_VALUE) {
    //这段代码不会执行，因为CreateMutex调用失败的时候返回的是NULL
}
```

同样的，下面的代码也不正确：

```c
HANDLE hFile = CreateFile(...);
if (hFIle == NULL) {
    //这段代码不会执行，因为CreateFile调用失败的时候返回的是INVALID_HANDLE_VALUE(-1)
}
```



### 关闭内核对象

无论怎样创建内核对象，都要向系统指明将通过调用C l o s e H a n d l e来结束对该对象的操作：

```c
BOOL CloseHandle(HANDLE hobj);
```

如果该句柄是有效的，那么系统就可以获得内核对象的数据结构的地址，并可确定该结构中的使用计数的数据成员。如果使用计数是0，该内核便从内存中撤消该内核对象。

如果将一个无效句柄传递给CloseHandle，将会出现两种情况之一。如果进程运行正常，CloseHandle返回FALSE，而GetLastError则返回ERROR_INVALID_HANDLE。如果进程正在排除错误，系统将通知调试程序，以便能排除它的错误。

在CloseHandle返回之前，它会清除进程的句柄表中的项目，该句柄现在对你的进程已经无效，不应该试图使用它。无论内核对象是否已经撤消，都会发生清除操作。当调用CloseHandle函数之后，将不再拥有对内核对象的访问权，不过，如果该对象的使用计数没有递减为0，那么该对象尚未被撤消。这没有问题，它只是意味着一个或多个其他进程正在使用该对象。当其他进程停止使用该对象时（通过调用CloseHandle），该对象将被撤消。

假如忘记调用CloseHandle函数，那么会不会出现内存泄漏呢？答案是可能的，但是也不一定。在进程运行时，进程有可能泄漏资源（如内核对象）。但是，当进程终止运行时，操作系统能够确保该进程使用的任何资源或全部资源均被释放，这是有保证的。对于内核对象来说，系统将执行下列操作：当进程终止运行时，系统会自动扫描进程的句柄表。如果该表拥有任何无效项目（即在终止进程运行前没有关闭的对象），系统将关闭这些对象句柄。如果这些对象中的任何对象的使用计数降为0，那么内核便撤消该对象。

因此，应用程序在运行时有可能泄漏内核对象，但是当进程终止运行时，系统将能确保所有内容均被正确地清除。另外，这个情况适用于所有对象、资源和内存块，也就是说，当进程终止运行时，系统将保证进程不会留下任何对象。







## 跨越进程边界共享内核对象

需要跨进程共享的内核对象

a.利用文件映像对象，可以在同一台机器上运行的两个进程之间共享数据块。

b. 借助邮件槽和命名管道，在网络中的不同计算机上运行的进程可以相互发送数据块。

c. 互斥量，信号量和事件允许不同进程的线程同步执行。例如一个应用程序可能需要完成某一个任务以后向另一个应用程序发出通知。

为了操作系统的安全，OS将内核对象设计成进程相关。

windows中有3中机制允许进程共享内核对象：使用对象句柄继承；为对象命名；复制对象句柄。





### 使用对象句柄继承

只有在进程之间有一个父-子关系的时候，才可以使用对象句柄继承。 父进程有一个或多个内核对象句柄可以使用，而且父进程创建一个子进程，并允许子进程访问父进程的内核对象。


  步骤

- 父进程创建句柄的时候必须向系统指出该对象是可以继承的。（这里指的是对象句柄的继承）

父进程需要初始化**SECURITY_ATTRIBUTES**结构 再将其传递给Create函数。 以下代码创建了一个可继承的互斥量对象。

```c
SECURITY_ATTRIBUTES sa;
sa.nLength = sizeof(sa);
sa.lpSecurityDescriptor = NULL;
sa.bInheritHandle = TRUE; // Make the returned handle inheritable.
 
HANDLE hMutex = CreateMutex(&sa, FALSE, NULL);

```

句柄表中每个记录项都有一个指明句柄是否可以继承的标志位。如果在创建句柄时传入的

SECURITY_ATTRIBUTES

结构参数为NULL返回的句柄是不可继承的，这个标志位为0.



将bInheritHandle成员设置为TRUE，将导致这个标志位被设为1.



![](images\1.png)

以上句柄表中，索引号为3的内核对象可以被继承。索引号为1的内核对象不可继承，索引号为2的内核对象不可用。



- 为了使对象句柄继承，接下来是生成子进程。通过CreateProcess函数完成

```c
WINBASEAPI
BOOL
WINAPI
CreateProcessW(
    _In_opt_ LPCWSTR lpApplicationName,
    _Inout_opt_ LPWSTR lpCommandLine,
    _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes,
    _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes,
    _In_ BOOL bInheritHandles,
    _In_ DWORD dwCreationFlags,
    _In_opt_ LPVOID lpEnvironment,
    _In_opt_ LPCWSTR lpCurrentDirectory,
    _In_ LPSTARTUPINFOW lpStartupInfo,
    _Out_ LPPROCESS_INFORMATION lpProcessInformation
    );

```

bInheritHandles参数，通常情况传递FALSE（不希望子进程继承父进程句柄表中的“可继承句柄”）
如果传递TRUE，子进程就会继承父进程的“可继承的句柄值”。创建进程以后系统先建一张空的句柄表，然后遍历其父进程句柄表并复制所有可继承属性的内核对象。

并且复制项的位置和他在父进程表中的位置是完全一样的。主进程中的Handle值在子进程中仍然可用。

同时会增加被复制的内核对象的引用计数器。



表3是一个子进程的句柄表



![](images\2.png)

1,2 项未初始化不可用

第三项是从父进程复制过来的内核对象，地址完全相同索引号也一致，并且标志是可继承。



内核对象的内容被保存在内核地址空间中--系统上所有运行的进程共享这个空间。（内核模式分区）

在32位系统下 是 0x8000 0000  到  0xFFFF FFFF之间。  对于64位系统，则是  0x0000 0400 0000 0000 到  0xFFFF FFFF FFFF FFFF之间。



子进程同样调用CreateProcess创建自己的孙进程，并将bInheritHandles参数设置为TRUE，孙进程也会继承该内核对象。并且3个进程的内核对象在句柄表中的内容和索引号一致。以此类推



对象继承只发生在创建进程的同时，如果子进程创建以后父进程又创建了新的内核对象则该对象并不被继承。



另外子进程本身并不会被通知从父进程那里继承了哪些内核对象（需要自行写代码通知）

通常用命令行参数传递。子进程的初始化代码将解析命令行并提取值。（因为内核对象具有相同的索引值和指针值）可以直接使用父句柄传递的句柄值



也可以等子进程创建完毕主线程发送一个消息给子进程中的一个线程处理（WaitForInputIdle）



另一种方式是在主进程所在的环境块添加环境变量设置继承句柄值，子进程会继承父进程的环境变量。通过调用GetEnvironmentVariable来获取继承到的内核对象的句柄值。

参考子进程继承父控制台的特例



### 改变句柄的标志

SetHandleInformation可以改变内核对象句柄的继承标志。

```c
WINBASEAPI
BOOL
WINAPI
SetHandleInformation(
    _In_ HANDLE hObject,
    _In_ DWORD dwMask,
    _In_ DWORD dwFlags
    );
```



hObject一个有效的句柄



dwMask更改那些标志

```c
#define HANDLE_FLAG_INHERIT             0x00000001
#define HANDLE_FLAG_PROTECT_FROM_CLOSE  0x00000002
```

dwFlags要设置的值。



例如



```c
// open the inherit flag
SetHandleInformation(hObj, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
 
// clos the inherit flag
SetHandleInformation(hObj, HANDLE_FLAG_INHERIT, 0);

```

HANDLE_FLAG_PROTECT_FROM_CLOSE

告知系统不允许关闭句柄



以下例子会触发一个异常（在调试器下）在运行模式下CloseHandle返回FALSE



```
SetHandleInformation(hObj, HANDLE_FLAG_PROTECT_FROM_CLOSE,HANDLE_FLAG_PROTECT_FROM_CLOSE);
CloseHandle(hObj);
```



关闭保护



```c
SetHandleInformation(hObj, HANDLE_FLAG_PROTECT_FROM_CLOSE, 0);
```



获取内核对象的标志信息

```c
WINBASEAPI
BOOL
WINAPI
GetHandleInformation(
    _In_ HANDLE hObject,
    _Out_ LPDWORD lpdwFlags
    );
```

获取一个内核对象是否允许被继承的例子



```c
DWORD  dwFlags;
GetHandleInformation(hObj, &dwFlags);
BOOL fHandleIsInheritable = (0 != (dwFlags & HANDLE_FLAG_INHERIT));
```





### 为对象命名

垮进程共享内核对象的第二个方法是为对象命名。许多内核对象都可以命名。

```c
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateMutexW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpMutexAttributes,
    _In_ BOOL bInitialOwner,
    _In_opt_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateEventW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpEventAttributes,
    _In_ BOOL bManualReset,
    _In_ BOOL bInitialState,
    _In_opt_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateSemaphoreW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,
    _In_     LONG lInitialCount,
    _In_     LONG lMaximumCount,
    _In_opt_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateWaitableTimerW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpTimerAttributes,
    _In_     BOOL bManualReset,
    _In_opt_ LPCWSTR lpTimerName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateFileMappingW(
    _In_ HANDLE hFile,
    _In_opt_ LPSECURITY_ATTRIBUTES lpFileMappingAttributes,
    _In_ DWORD flProtect,
    _In_ DWORD dwMaximumSizeHigh,
    _In_ DWORD dwMaximumSizeLow,
    _In_opt_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
CreateJobObjectW(
    _In_opt_ LPSECURITY_ATTRIBUTES lpJobAttributes,
    _In_opt_ LPCWSTR lpName
    );
 
```



所有这些Create函数有一个Name参数，传入NULL表示匿名内核对象。可以使用继承技术



或者使用DuplicateHandle来实现进程间的对象共享。

所有的命名内核对象共享一个命名空间。以下例子CreateSemaphore函数会返回NULL 



![](images\3.png)

通过命名对象共享的一个例子

在进程A中创建了一个名字为“JeffMutex”的互斥量对象

HANDLE hMutexProcessA = CreateMutex(NULL, FALSE, TEXT("JeffMutex"));



然后通过某进程生成了进程B（B不是A的子进程）在B进程中调用

HANDLE hMutexProcessB = CreateMutex(NULL, FALSE, TEXT("JeffMutex"));

系统找到内核表中的JeffMutex判断类型，进行安全检查。都通过就会将记录赋值到进程B中的句柄表内，并且引用计数器+1

否则返回NULL

（可以采用CreateMutexEx设置信号量的访问权限。）


通过名称来实现内核对象共享时，进程B调用CreateMutex时，会向安全函数传递安全信息。如果已经存在一个指定名称的对象，这些参数就会被忽略。函数并不知道自己是创建了一个新的内核对象还是打开一个已有的。

可以调用GetLastError判断刚才是创建了一个还是打开了一个现有的。



```c
#include <windows.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.lpSecurityDescriptor = NULL;
	sa.bInheritHandle = TRUE;
	HANDLE hMutex = CreateMutex(&sa, FALSE, TEXT("JeffMutex"));
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		//Opened a handle to an existing object.
		//sa.lpSecurityDescriptor and the second parameter
		// are ignored.
		printf("Opened a handle to an existing object.\n");
	}
	else
	{
		//Created a brand new object.
		//sa.lpSecurityDescriptor and the second parameter
		//FALSE are used to construct the object.
		printf("Created a brand new object.\n");
	}
	system("pause");
	return 0;
}
```



![](images\4.png)





为了实现具名内核对象的共享，还可以使用一系列Open*函数

```c
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
OpenMutexW(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
OpenEventW(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
OpenSemaphoreW(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
OpenWaitableTimerW(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCWSTR lpTimerName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
OpenFileMappingW(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCWSTR lpName
    );
 
WINBASEAPI
_Ret_maybenull_
HANDLE
WINAPI
OpenJobObjectW(
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ LPCWSTR lpName
    );
```



以上函数原型一致，最后一个参数指向内核对象的名称。并且该参数不能为NULL
如果在系统内核表中无法搜索到同名的内核对象则返回NULL  GetLastError返回2 （ERROR_FILE_NOT_FOUND）

如果找到同名的内核对象但类型不同，返回NULL GetLastError返回6（ERROR_INVALID_HANDLE）

如果同名且类型相同，系统会检查访问权限。如果允许访问该内核对象，则会更新主调进程的句柄表，并使对象的使用计数器递增。

如果bInHeritHandle参数传入TRUE，那么返回的句柄就是“可继承”的



Create*如果不存在则创建， Open*如果不存在则返回NULL。

为了避免两个互不相干的程序冲突建议使用GUID来创建具名内核对象。



一个利用具名内核对象来防止应用程序创建多个实例的例子。



```c
#include <windows.h>
#include <stdio.h>
int main(int argc, char* argv[])
{
	//// {89AE97EA-F13D-4104-B042-43C010033B48}
	HANDLE h = CreateMutex(NULL, FALSE,
		TEXT("{89AE97EA-F13D-4104-B042-43C010033B48}"));
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		// there is already an instance of this application running.
		// close the object and immediately return.
		CloseHandle(h);
		return (0);
	}

	system("pause");
	CloseHandle(h);
	return 0;
}
```

该程序只会运行一个实例。



### 终端服务命名空间

终端服务程序（service）除了有一全局的命名空间，所有客户端能访问的内核对象要放在这个命名空间中。

每个客户端会话（Client session）都有自己的命名空间。对于两个会话正在运行同一个程序的时候，这样的安排可以避免彼此之间的干扰--一个会话不会访问另一个会话的对象，即使对象的名称相同。



 因为系统服务默认启动与Session 0 ，而用户的应用会在一个新的Session中启动。如果和系统服务间的通信不在一个命名空间中就会可能出问题。



可以通过ProcessIdToSessonId函数知道我们的应用程序在哪个Terminal Services会话中运行。



```c
#include <stdio.h>
#include <windows.h>
int main(int argc, char* argv[])
{
	DWORD processID = GetCurrentProcessId();
	DWORD sessionID;
	if (ProcessIdToSessionId(processID, &sessionID)){
		printf("Process '%u' runs in Terminal Services session '%u'\n",
			processID, sessionID);
	}
	else{
		// ProcessIdToSessionId might fail if you don't have enough rights
		// to access the process for which you pass the ID as parameter.
		// Notice that it is not the case here because we're using our own process ID.
		printf("Unable to get Terminal Services session ID for process '%u'\n",
			processID);
	}
	system("pause");
	return 0;
}
```





一个服务（system service）的命名内核对象始终位于全局命名空间。默认情况下应用程序的命名内核对象在会话的命名空间内。

可以强制把命名对象放入全局命名空间"Global\"

HANDLE h = CreateEvent(NULL, FALSE, FALSE, TEXT("Global\\MyName"));

也可以显式把内核对象放入当前会话的命名空间 加上"Local\"前缀

HANDLE h = CreateEvent(NULL, FALSE, FALSE, TEXT("Local\\MyName"));



Global 和 Local是命名对象的保留字。除非强制一个特定的命名空间，否则不应在对象名中使用。 Session也是保留字，但是不能在当前Session中创建创建另外一个Session前缀的对象。GetLastError返回ERROR_ACCESS_DENIED

(保留关键字都是区分大小写的)



### 专有命名空间

如果想确保我们的应用程序创建的内核对象名称永远不会和其他应用程序的名称冲突，或者想保护他们免遭劫持，可以定义一个自定义的前缀，并把他作为自己的专有命名空间使用，这和使用Global和Local前缀是相似的。 一个单例进程的例子，以一种更安全的方式来实现前面的例子

研究以下问题

1）如何创建一个边界  

2）如何将对应于本地管理组（Local Administrators）的安全描述符（Security identifier， SID）和边界关联

3）如何创建或打开其名称被用作互斥量内核对象前缀的一个专有命名空间。

边界描述符会获得一个名称， 而且还会与一个特权用户组的SID相关联。 Windows就可以确保在用户隶属于这个权限时（SID），以其身份创建的应用程序才能在此SID对应的边界条件中创建相同的命名空间，从而访问在这个边界中创建的，以专有命名空间的名称作为前缀的内核对象。



如果由于SID泄漏，一个低权限的而已程序试图创建相同的边界描述符，那么当其试图创建或打开一个高权限账户保护的专有命名空间时，调用就会失败GetLastError返回

ERROR_ACCESS_DENIED.



原始代码 Singleton.cpp



```cpp
/*
	Module: Singleton.cpp
	Notices: Copyright (c) 2008 Jeffrey Richter & Christophe Nasarre
*/
 
 
#include "resource.h"
 
#include "..\CommonFiles\CmnHdr.h"	// common header for Windows Via C++ sample
#include <windowsx.h>
#include <Sddl.h>		// for SID management
#include <tchar.h>
#include <strsafe.h>
 
///////////////////////////////////////////////////////////////////////////////
 
// Main dialog
HWND		g_hDlg;
 
// Mutex, boundary and namespace used to detect previous running instance
HANDLE		g_hSingleton = NULL;
HANDLE		g_hBoundary = NULL;
HANDLE		g_hNamespace = NULL;
 
// Keep track whether or not the namespace wa created or open for clean-up
BOOL		g_bNamespaceOpened = FALSE;
 
// Names of boundary and private namespace
PCTSTR		g_szBoundary = TEXT("3-Boundary");
PCTSTR		g_szNamespace = TEXT("3-Namespace");
 
#define DETAILS_CTRL	GetDlgItem(g_hDlg, IDC_EDIT_DETAILS)
 
///////////////////////////////////////////////////////////////////////////////
 
// Adds a string to the "Details" edit control
void AddText(PCTSTR pszFormat, ...) {
 
	va_list argList;
	va_start(argList, pszFormat);
 
	TCHAR sz[20 * 1024] ;
 
	Edit_GetText(DETAILS_CTRL, sz, _countof(sz));
	_vstprintf_s(
		_tcschr(sz, TEXT('\0')), _countof(sz) - _tcslen(sz),
		pszFormat, argList);
	Edit_SetText(DETAILS_CTRL, sz);
	va_end(argList);
}
 
///////////////////////////////////////////////////////////////////////////////
 
void Dlg_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify) {
	switch (id) {
	case IDOK:
	case IDCANCEL:
		// User has clicked on the exit button
		// Or dismissed the dialog with ESCAPE
		EndDialog(hwnd, id);
		break;
	}
}
 
 
///////////////////////////////////////////////////////////////////////////////
 
void CheckInstances() {
 
	// Create the boundary descriptor
	g_hBoundary = CreateBoundaryDescriptor(g_szBoundary, 0);
 
	// Create a SID corresponding to the Local Administrator group
	BYTE localAdminSID[SECURITY_MAX_SID_SIZE];
	PSID pLocalAdminSID = &localAdminSID;
	DWORD cbSID = sizeof(localAdminSID);
 
	if (!CreateWellKnownSid(
		WinBuiltinAdministratorsSid, NULL, pLocalAdminSID, &cbSID)
		) {
		AddText(TEXT("AddSIDToBoundaryDescriptor failed: %u\r\n"),
			GetLastError());
		return;
	}
 
	// Associate the Local Admin SID to the boundary descriptor
	// --> only applications running under an administrator user
	// will be able to access the kernel objects in the same namespace
	if (!AddSIDToBoundaryDescriptor(&g_hBoundary, pLocalAdminSID)) {
		AddText(TEXT("AddSIDToBoundaryDescriptor failed: %u\r\n"),
			GetLastError());
		return;
	}
 
	// Create the namespace for Local Administrators only
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	if (!ConvertStringSecurityDescriptorToSecurityDescriptor(
		TEXT("D:(A;;GA;;;BA)"),
		SDDL_REVISION_1, &sa.lpSecurityDescriptor, NULL)) {
		AddText(TEXT("Security Descriptor creation failed: %u\r\n"),
			GetLastError());
		return;
	}
 
	g_hNamespace =
		CreatePrivateNamespace(&sa, g_hBoundary, g_szNamespace);
 
	// Don't forget to release memory for the security descriptor
	LocalFree(sa.lpSecurityDescriptor);
 
	// Check the private namespace creation result
	DWORD dwLastError = GetLastError();
	if (g_hNamespace == NULL) {
		// Nothing to do if access is denied
		// --> this code must run under a Local Administrator acount
		if (dwLastError == ERROR_ACCESS_DENIED) {
			AddText(TEXT("Access denied when create the namespace.\r\n"));
			AddText(TEXT("	You must be running as Administrator.\r\n\r\n"));
			return;
		}
		else {
			if (dwLastError == ERROR_ALREADY_EXISTS) {
				// if another instance has already created the namespace,
				// we need to open it instead.
				AddText(TEXT("CreatePrivateNamespace failed: %u\r\n"), dwLastError);
				g_hNamespace = OpenPrivateNamespace(g_hBoundary, g_szNamespace);
				if (g_hNamespace == NULL) {
					AddText(TEXT("	and OpenPrivateNamespace failed: %u\r\n"),
						dwLastError);
					return;
				}
				else {
					g_bNamespaceOpened = TRUE;
					AddText(TEXT("	but OpenPrivateNamespace succeeded\r\n\r\n"));
				}
			}
			else {
				AddText(TEXT("Unexpected error occured: %u\r\n\r\n"),
					dwLastError);
				return;
			}
		}
	}
 
 
	// Try to create the mutex object with a name
	// based on the private namespace
	TCHAR szMutexName[64];
	StringCchPrintf(szMutexName, _countof(szMutexName), TEXT("%s\\%s"),
		g_szNamespace, TEXT("Singleton"));
 
	g_hSingleton = CreateMutex(NULL, FALSE, szMutexName);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		// There is already an instance of this Singleton object
		AddText(TEXT("Another instance of Singleton is running:\r\n"));
		AddText(TEXT("--> Impossible to access application features.\r\n"));
	}
	else {
		// First time the Singleton object is created
		AddText(TEXT("First instance of Singleton:\r\n"));
		AddText(TEXT("--> Access application features now.\r\n"));
	}
}
 
///////////////////////////////////////////////////////////////////////////////
 
BOOL Dlg_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) {
 
	chSETDLGICONS(hwnd, IDI_SINGLETON);
 
	// Keep track of the main dialog window handle
	g_hDlg = hwnd;
 
	// Check whether another instance is already running
	CheckInstances();
 
	return TRUE;
}
 
///////////////////////////////////////////////////////////////////////////////
 
INT_PTR WINAPI Dlg_Proc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		chHANDLE_DLGMSG(hwnd, WM_COMMAND, Dlg_OnCommand);
		chHANDLE_DLGMSG(hwnd, WM_INITDIALOG, Dlg_OnInitDialog);
	}
 
	return FALSE;
}
 
 
///////////////////////////////////////////////////////////////////////////////
 
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR	lpCmdLine,
	int		nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
 
	// Show main window
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_SINGLETON), NULL, Dlg_Proc);
 
	// Don't forget to clean up and release kernel resource
	if (g_hSingleton != NULL) {
		CloseHandle(g_hSingleton);
	}
 
	if (g_hNamespace != NULL) {
		if (g_bNamespaceOpened) { // Open namespace
			ClosePrivateNamespace(g_hNamespace, 0);
		}
		else {
			ClosePrivateNamespace(g_hNamespace, PRIVATE_NAMESPACE_FLAG_DESTROY);
		}
	}
 
	if (g_hBoundary != NULL) {
		DeleteBoundaryDescriptor(g_hBoundary);
	}
 
	return 0;
}
```







CheckInstances函数的几个步骤。

- 创建边界描述符

```c
	// Create the boundary descriptor
	g_hBoundary = CreateBoundaryDescriptor(g_szBoundary, 0);
```

注意该函数的返回类型虽然是HANDLE，但是并非是一个内核对象的句柄。而是一个指针，指向了用户模式的结构，结构体中保护了边界的定义。



应该调用DeleteBoundaryDescriptor释放 （CloseHandle会失败）



- 将一个特权用户组的SID与边界描述符关联起来：

```c
	// Associate the Local Admin SID to the boundary descriptor
	// --> only applications running under an administrator user
	// will be able to access the kernel objects in the same namespace
	if (!AddSIDToBoundaryDescriptor(&g_hBoundary, pLocalAdminSID)) {
		AddText(TEXT("AddSIDToBoundaryDescriptor failed: %u\r\n"),
			GetLastError());
		return;
	}
```

在本例中创建了基于Local Administrator组的SID，并使用CreateWellKnownSid创建SID的描述符



- 创建专有命名空间

```c
	// Create the namespace for Local Administrators only
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = FALSE;
	if (!ConvertStringSecurityDescriptorToSecurityDescriptor(
		TEXT("D:(A;;GA;;;BA)"),
		SDDL_REVISION_1, &sa.lpSecurityDescriptor, NULL)) {
		AddText(TEXT("Security Descriptor creation failed: %u\r\n"),
			GetLastError());
		return;
	}
 
	g_hNamespace =
		CreatePrivateNamespace(&sa, g_hBoundary, g_szNamespace);
```

边界描述符添加的SID决定了谁能进入边界并创建命名空间。
是通过ConvertStringSecurityDescriptorToSecurityDescriptor创建的 关于安全描述符的语法接口参考MSDN

(https://msdn.microsoft.com/en-us/library/aa374928.aspx)

如果试图创建一个已有的命名空间，CreatePrivateNamespace将返回NULL, GetLastError将返回ERROR_ALREADY_EXISTS

此时调用OpenPrivateNamespace来打开命名空间

```c
			g_hNamespace = OpenPrivateNamespace(g_hBoundary, g_szNamespace);
```



注意CreatePrivateNamespace和 OpenPrivateNamespace返回的伪HANDLE并非内核句柄， 调用ClosePrivateNamespace来关闭伪句柄。



- 进程终止前调用 DeleteBoundaryDescriptor 关闭边界





### 复制对象句柄

跨进程共享内核对象的最后一招是使用DuplicateHandle函数

```c
WINBASEAPI
BOOL
WINAPI
DuplicateHandle(
    _In_ HANDLE hSourceProcessHandle,
    _In_ HANDLE hSourceHandle,
    _In_ HANDLE hTargetProcessHandle,
    _Outptr_ LPHANDLE lpTargetHandle,
    _In_ DWORD dwDesiredAccess,
    _In_ BOOL bInheritHandle,
    _In_ DWORD dwOptions
    );
```

获得一个进程句柄表中的记录项，在另一个进程的句柄表中创建这个记录项的一个副本。

参数1 和3 是进程内核对象的句柄。并且这两个句柄必须相对于调用DuplicateHandle函数的进程（hSourceProcessHandle 也可以调用DuplicateHandle）。 如果传递非进程句柄则会失败。

第二个参数是指向任何类型的内核对象的句柄。但是他的值一定不能和调用DuplicateHandle函数的那个进程相关。 必须和hSourceProcessHandle的这个进程有关。

函数最终会将源进程中的句柄信息复制到hTargetProcessHandle所表示的进程的句柄表中。

第四个参数是一个HANDLE指针，用于传递复制以后获得的句柄值。

后3个参数指定这个内核对象在目标进程中所对应的句柄表项，应该使用何种访问掩码和继承标志。 dwOptions可以为0 或者  DUPLICATE_SAME_ACCESS(保留同样的掩码)  和 DUPLICATE_CLOSE_SOURCE（关闭源进程中的句柄）



使用DuplicateHandle函数和继承有一个问题，目标进程不知道他现在能访问一个新的内核对象。必须通过某种进程间通信来通知目标进程。

一个DuplicateHandle的例子 两个进程互相拷贝:

```c
	// All of the following code is excuted by process S.
 
	// Create a mutex object accessible by Process S.
	HANDLE hObjInProcessS = CreateMutex(NULL, FALSE, NULL);
 
	// Get a handle to Process T's kernel object.
	HANDLE hProcessT = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwProcessIdT);
 
	HANDLE hObjInProcessT;		// An uninitialized handle relative to Process T.
 
	// Give Process T access to our mutex object.
	DuplicateHandle(GetCurrentProcess(), hObjInProcessS, hProcessT,
		&hObjInProcessT, 0, FALSE, DUPLICATE_SAME_ACCESS);
 
	// Use some IPC mechanism to get the handle value of hObjInProcessS into Process T.
 
	// We no longer need to commicate with Process T.
	CloseHandle(hProcessT);
 
	// When Process S no longer needs to use the mutex, it should close it.
	CloseHandle(hObjInProcessS);
```





在本例中**DuplicateHandle**返回的句柄相对于进程T，因此绝对不要在进程S中释放此句柄 例如 CloseHandle(hObjInProcessT);

另一个例子在同一个进程中执行DuplicateHandle拷贝一个副本内核对象。注意创建和释放的周期



```c
	// Create a file-mapping object; the handle has read/write access.
	HANDLE hFileMapRW = CreateFileMapping(INVALID_HANDLE_VALUE,
		NULL, PAGE_READWRITE, 0, 10240, NULL);
 
	// Create another handle to the file-mapping object;
	// the handle has read-only access.
	HANDLE hFileMapRO;	//uninitialized.
 
	DuplicateHandle(GetCurrentProcess(), hFileMapRW, GetCurrentProcess(),
		&hFileMapRO, FILE_MAP_READ, FALSE, 0);
 
	// call the function that should only read from the file mapping.
	ReadFromTheFileMapping(hFileMapRO);
 
	// Close the read-only file-mapping object.
	CloseHandle(hFileMapRO);
 
	// We can still read/write the file-mapping object using hFileMapRW.
	// ...
	// When the main code doesn't access the file mapping anymore,
	// Close it.
	CloseHandle(hFileMapRW);
```

