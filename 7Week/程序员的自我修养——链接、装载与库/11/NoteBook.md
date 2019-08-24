# 运行库

## 入口函数和程序初始化

### 程序从main开始嘛

c代码：

```c
#include <stdio.h>
#include <stdlib.h>
int a = 3;
int main(int argc,char *argv[])
{
	int *p = (int *)malloc(sizeof(int));
	scanf("%d", p);
	printf("%d\r\n", a + *p);
	free(p);
	return 0;
}
```

c++代码：

```c
#include <stdio.h>
using namespace std;
#include <iostream>
#include <string.h>
string v;
double foo()
{
	return 1.0;
}

double g = foo();
int main()
{
	
}
```



操作系统装载程序后，首先运行的并不是main的第一行，而是某些别的代码，这些代码负责准备好main函数执行所需要的环境，并且调用main函数，这时候你才可以在main函数编码；**在main返回之后，它会记录main函数的返回值，调用atexit注册的函数，然后结束进程。**



- 操作系统在创建进程后，把控制权交到了程序的入口，这个入口往往是运行库中的某个入口函数
- 入口函数对运行库和程序运行环境进行初始化，包括堆、I/O、线程、全程变量构成等等
- 入口函数在完成初始化以后，调用main函数，正式开始执行程序主体部分
- main函数执行完成后，返回到入口函数，入口函数进行清理工作，包括全局变量析构、堆销毁、关闭I/O等，然后进行系统调用结束进程。



### 入口函数如何实现

### glibc

glibc的启动情况在不同的情况下差距很大，比如静态的glibc和动态的glibc，glibc用于可执行文件和共享库的差别。



在glibc的源代码中**/libc/sysdeps/i86/elf/Start.s**中查看

```assembly
_start:
	/* Clear the frame pointer.  The ABI suggests this be done, to mark
	   the outermost frame obviously.  */
	xorl %ebp, %ebp

	/* Extract the arguments as encoded on the stack and set up
	   the arguments for `main': argc, argv.  envp will be determined
	   
_start:
	/* Clear the frame pointer.  The ABI suggests this be done, to mark
	   the outermost frame obviously.  */
	xorl %ebp, %ebp

	/* Extract the arguments as encoded on the stack and set up
	   the arguments for `main': argc, argv.  envp will be determined
	   later in __libc_start_main.  */
```

可以看到start函数最终调用了名为“__libc_start_main”的函数。







### MSVC CRT入口函数

```c
*mainCRTStartup(void)
*wmainCRTStartup(void)
*WinMainCRTStartup(void)
*wWinMainCRTStartup(void)
*
*Purpose:
*       These routines do the C runtime initialization, call the appropriate
*       user entry function, and handle termination cleanup.  For a managed
*       app, they then return the exit code back to the calling routine, which
*       is the managed startup code.  For an unmanaged app, they call exit and
*       never return.
*
*       Function:               User entry called:
*       mainCRTStartup          main
*       wmainCRTStartup         wmain
*       WinMainCRTStartup       WinMain
*       wWinMainCRTStartup      wWinMain
*
*Entry:
```





![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\11\Img\1.png)



**MSVC的CRT默认的入口函数为mainCRTStart**

**alloc是唯一可以不适用堆的动态分配机制。alloc可以在栈上分配任意大小的空间，并且在函数返回的时候自动释放，像局部变量一样**



mainCRTStart函数的总体过程：

- 初始化和OS版本有关的全局变量
- 初始化堆
- 初始化I/O
- 获取命令行参数和环境变量
- 初始化C库的一些数据
- 调用main并记录返回值
- 检查错误并将main的返回值返回





### 运行库与I/O

I/O程序指代了程序与外界的交换，包括文件、管道、网络、命令行、信号等。

**对于一个任意类型的文件，操作系统会提供一组操作函数，这包括打开文件、读写文件、移动文件指针等**



```c
#include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *f = fopen("test.dat", "wb");			//创建文件指针
	if (f == NULL)
	{
		return -1;
	}
	fwrite("123", 3, 1, f);			//对当前文件流的文件进行写入，写入内容为123
	fclose(f);						//关闭文件指针
	return 0;
}
```



在操作系统层面，文件操作也有类似于FILE的概念，在Linux中，**这叫做文件描述符(File Descriptor),在Windows中，叫做句柄(Handle)。**





**在内核中，每一个进程都有一个私有的“打开文件表”，这个表是一个指针数组，每一个元素都指向一个内核的打开文件对象**

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\11\Img\2.png)







### MSVC CRT的入口函数初始化

系统堆初始化：

MSVC入口函数初始化包含两个部分，**堆初始化和I/O初始化，**MSVC的堆初始化由函数_heap_init完成，这个函数的定义位于**heapinit.c**

**mainCRTStart  -> _heap_init();**

```c
int __cdecl _heap_init (
        int mtflag
        )
{
        //  Initialize the "big-block" heap first.
        if ( (_crtheap = HeapCreate( mtflag ? 0 : HEAP_NO_SERIALIZE,
                                     BYTES_PER_PAGE, 0 )) == NULL )
            return 0;
           
           
         return 1;
}
```

在32为环境编译下，MSVC的堆初始化过程出气的简单，它仅仅 调用了HeapCreate这个API创建一个系统堆



**MSVC的malloc函数必然是调用了HeapAlloc这个API**





I/O初始化

FILE结构的定义(FILE结构实际定义在在C语言标准中并未指出，因此不同的版本有不同的实现)





```c
struct _iobuf{
    char *_ptr;
    int _cnt;
    char *_base;
    int _flag;
    int _file;
    int _charbuf;
    int _bufsize;
    char *_tmpfname;
};typedef struct _iobuf FILE;
```



这个FILE结构中最重要的一个字段是_file，file是一个整数，通过file可以访问到文件举兵表中的某一项。

**在Windows中，用户态使用句柄(Handle)来访问内核文件对象，句柄本身是一个32位的数据类型，在有些场合使用int来存储，有些场合使用指针来表示**



MSVC的CRT中，已经打开的文件句柄的信息使用数据结构ioinfo来表示：



```c
typedef struct {
    intptr_t osfhnd;
    char osfile;
    char popech;
} ioinfo;
```

osfile的值可由一系列值用按位或的方法得出：

- FOPEN(0x01)句柄被打开
- FEOFLAG(0x02)已到达文件末尾
- FCRLF(0x04)在文本模式中，行缓冲已遇到回车符号
- FPIPE(0x08)管道文件
- FNOINHERIT(0x10)句柄打开时具有属性O_NOINHERIT（不遗传给子进程）
- FAPPEND(0x20)句柄打开时具有属性O_APPEND(在文件末尾追加数据)
- FDEV(0x40)设备文件
- FTEXT(0x80)文件以文本模式打开



在/crt/src/ioinit.c中有一个数组

```c
int _nhandle;

/*
 * Array of pointers to arrays of ioinfo structs.
 */
_CRTIMP ioinfo * __pioinfo[IOINFO_ARRAYS];
```



这就是用户态的打开文件表。这个表其实是一个二维数组，第二维的大小为32个ioinfo结构，因此该表总共可以容纳的元素总量为**64*32+2048个句柄，**此外**_nhandle**记录该表的实际元素个数。



**FILE结构的_file字段的意义可以从pioinfo的定义里看出，通过file得到打开文件表的下表变换为：**

**_file的第5位到第10位是第一维坐标(共6位)，file的第0位到第4位是第二维坐标**

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\11\Img\3.png)



MSVC的I/O初始化主要进行了如下几个工作：

- 建立打开文件表
- 如果能够继承自父进程，那么从父进程获取继承的句柄
- 初始化标准输入输出







## C/C++运行库

### C语言运行库

**各种标准库函数代码集合称之为运行时库，c语言的运行库，即被称为C运行库(CRT)**



一个C语言运行库大致包含了如下功能：

- 启动与退出：包括入口函数及入口函数所以来的其他函数等
- 标准函数：由C语言标准规定的C语言标准库所拥有的函数实现
- I/O：I/O功能的封装和实现
- 堆：堆的封装和实现
- 语言实现：语言中一些特殊功能的实现
- 调试：实现调试功能的代码





### C语言标准库

**ANSI C标准库由24个c头文件组成**

- 标准输入输出(stdio.h)
- 文件操作（stdio.h）
- 字符操作（ctype.h）
- 字符串操作（string.h）
- 数学函数（math.h）
- 资源管理（stdlib.h）
- 格式转换（stdlib.h）
- 时间/日期（time.h）
- 断言（assert.h）

特殊库

- 变长参数（stdarg.h）
- 非局部跳转（setjump.h）







### glibc和MSVC CRT

**C语言运行库从某种程度来说是C语言程序和不同操作系统平台之间的抽象层，它将不同操作系统API抽象成相同的库函数**









## 运行库与多线程

### CRT的多线程困扰

线程的访问能力非常自由，它可以访问进程内存里的所有数据，甚至包括其他线程的堆栈，但实际应用中线程也拥有自己的私有存储空间，包括：

- 栈（尽管并非完全无法被其他线程访问，但一般情况仍可认为是私有的数据）
- 线程的局部存储。线程局部存储是某些操作系统为线程单独提供的私有空间，但通常只有很局限的尺寸
- 寄存器（包括pc寄存器），寄存器是执行流的基本数据，因此为线程私有

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\11\Img\4.png)

第一方面：主流的CRT都会有相应功能，MSVC CRT提供了很多函数用于线程的创建和推出；在Linux下，glibc也提供了函数用于线程的创建和推出



第二方面：c语言运行库必须支持多线程环境

- errno：在c标准库里，大多数错误代码是在函数返回前赋值在名为errrno的全局变量里的。多线程并发的时候，有可能A线程的errno值在获取之前就被B线程给覆盖，从而得到错误的信息
- strtok等函数会使用函数内部的局部静态变量来存储字符串的位置，不同的线程调用这个函数将会把它内部的静态局部变量弄混乱
- malloc/new：堆分配和堆释放函数在不加锁的情况下线程是不安全的。
- 异常处理：在早期的C++运行库里，不同的线程抛出的异常会彼此冲突，从而造成信息丢失的情况
- printf/fprintf及其他的I/O函数：流输出函数同样是线程不安全的，因为它们共享了同一个控制台或文件输出
- 其他线程不安全函数：包括与信号相关的一些函数



C标准不哭中在不进行线程安全保护情况下自然的具有线程安全的函数有：

- 字符处理（ctype.h），包括isdigit、toupper等，这些函数同时还是可重入的
- 字符串处理函数（string.h），包括stelen、strcmp等
- 数学函数（math.h）
- 字符串转整数、浮点数（stdlib.h）
- 获取环境变量（stdlib.h）
- 变长数组辅助函数（stdarg.h）
- 非局部跳转函数（setjump.h）



### CRT改进

使用TLS：

errno必须成为各个线程的私有成员。在glibc中，errno被定义为一个宏：

```c
#define error (*__errno_location());
```

函数__errno_location在不同的库版本情况下有不同的定义，在单线程中，它仅仅返回了函数errno的地址，在多线程中，不同的线程调用这个函数返回的地址则各不相同。



加锁：

在多线程版本的运行库中，线程不安全的函数内部会自动的枷锁，包括malloc、printf等，而异常处理的错误也早早就解决了，因此在使用多线程版本运行库时，在malloc/new前后不进行加锁，也不会出现并发错误。









### 线程局部存储实现

**每个线程私有的数据包含线程的栈和当前的寄存器，但是这两种存储是非常不可靠的，栈会在每个函数退出和进入的时候改变；而寄存器更是少的可怜，我们不可能拿寄存器去存储所需要的数据**



**假设我们需要在线程中使用一个全局变量，但希望这个全局变量是线程私有的，而不是所有线程共享的，这个时候就用到线程局部错处（TSL）机制。TSL的用法很简单，如果要定义一个全局变量为TSL的类型，只需要在它的前面加上相对的关键字即可。**





**对于GCC来说，这个关键字就是__thread，比如我们需要定义一个TLS的全局整形变量：**

```c
__thread int number;
```

**对于MSVC来说，相应的关键字为__declspec(thread);**

```c
__declspec(thread) int number;
```

**一旦一个全局变量被定义TSL类型的，那么每个线程都会拥有这个变量的一个副本，任何线程堆该变量的修改都不会影响其他线程中该变量的副本。**





Windows TLS实现：

Windows系统中，一个全局变量或者静态变量会被放到“.data”或“.bss”段中，但是我们使用__declspec(thread)定义一个线程私有变量的时候，编译器会把这些变量放到PE文件中的".tls"段中。当系统启动一个新的进程时，它会从进程的堆中分配一个足够大小的空间，然后把".tls"段中的内容复制到这块内存空间，于是每个线程都有自己独立的一个".tls"副本。



对于一个TLS变量来说，它可能是一个c++的全局对象，那么每个线程在启动的时候不仅仅需要复制".tls"的内容那么简单，还需要把这些TLS对象初始化，必须逐个地调用它们的全局构造函数，而且当线程退出的时候，还需要逐个地将它们西沟，正如普通的全局对象在进程启动和退出时都需要构造、析构一样



**TLS表中保存了所有TLS变量的构造函数和析构函数的地址，Windows系统就是根据TLS表中的内容，在每次线程启动或退出时堆TLS变量进行构造和析构。TLS表本身往往位于PE文件的".rdata"段中**



**对于WIndows线程来说，系统都会建立一个关于线程信息的结构，叫做“线程环境块”。这个结构里保存的是线程的堆栈地址、线程ID等相关信息，其中有一个域是一个TLS数组，它在TEB中的偏移0x2c，对于每个线程来说，x86的FS段寄存器所指的段就是该线程的TEB，于是要得到一个线程的TLS数组的地址可以通过FS：[0x2c]访问到**







## C++全局构造与析构

留坑











## fread

fread函数声明：

```c
size_t fread
{
	void *buffer,
	size_t elementSize,
	size_t count,
	FILE *stream
}
```



### 缓冲

缓冲：将对控制多次的写入放到一个数组里，等到数组被填满之后再一次性完成系统调用写入

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\11\Img\5.png)

**全缓冲：除了用户手动调用fflush外，当缓冲满的时候，缓冲才会被flush掉**

**行缓冲：这种缓冲仅仅使用于文本，在输入输出遇到一个换行符的时候，缓冲就被flush掉**

