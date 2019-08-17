# Windows下的动态链接



## DLL简介

DLL即动态链接库的缩写，Windows系统中大量采用了这种DLL机制，甚至包括Windows的内核结构都很大程序依赖于DLL机制

**DLL与EXE文件其实是一个概念，它们都是由PE格式的二进制文件，稍微有些不同的是PE文件头部中由个符号位标识该文件是EXE或者DLL，而DLL的扩展名不一定是dll，页可以是.ocx(ocx控件)或是.CPL（控制面板程序）**



ELF的动态链接可以实现运行时加载，使得各种功能模块以插件的方式存在





### 进程地址空间和内存管理

32位系统中，Windows开始支持进程拥有独立的地址空间，一个DLL在不同的进程中拥有不同的私有数据副本



DLL的代码与地址是有关系的，所以它知识在某些情况下可以被多个进程间共享









### 基地址和RVA

PE里有两个很常用的概念的概念就是：基地址(Base Address)和相对地址(RVA)，当一个PE文件被装载的时候，其进程地址空间中的起始地址就是基地址。

**对于PE文件来说，它都有一个优先装载的基地址，这个值就是PE文件头中的Image Base**







## DLL共享数据段



Windows提供的API可以实现进程间的通信。其中有一种方法使用DLL来实现进程间的通信，这个原理与16位Windows中的DLL实现进程间的通信十分类似



**正常情况下，每个DLL的数据段在各个进程中都是独立的，每个进程拥有自己的副本。但是Windows允许将DLL的数据段设置为共享的，即任何进程都可以共享该DLL的同一份数据段**





**进程间共享方式也产生了一定的安全漏洞，因为任意一个进程都可以访问这个共享的数据段，那么只要破坏了该数据段的数据就会导致所有所有该数据段的进程出现问题。甚至恶意攻击者可以在GUEST的权限下运行某个进程破坏共享的数据，从而映像那么系统管理员权限使用同一个DLL的进程。**







### DLL的简单例子

在DLL中，我们需要显式的“告诉”编译器我们需要导出哪个符号，否则编译器默认符号不到处，我们在程序使用DLL导出符号的时候，这个过程被称为导入(Import)



"__declspec(dllexport)"表示该符号是从本DLL导出的符号

"__declspec(dllimport)表示该符号是从别的DLL导入的符号"

".def"文件声明导入导出符号。".def"扩展名的文件是类似于ld链接器的链接脚本文件







### 创建DLL

```c
__declspec(dllexport) double Add (double a,double b)
{
    return a + b;
}

__declspec(dllexport) double Sub (double a,double b)
{
    return a + b;
}

__declspec(dllexport) double Mul (double a,double b)
{
    return a * b;
}


```



![](F:\Learn\5Week\程序员的自我修养\9\IMG\0.png)



DLL中三个导出函数以及它们的相对地址





### 使用DLL

程序使用DLL的过程起始是引用DLL中的导出函数和符号的过程，即导入过程，对于从其他DLL导入的符号，我们需要使用"__declspec(dllimport)"显式的声明某个符号为导入符号。



**把.lib和.o文件链接起来，形成最终的可执行文件**



**.lib文件是一组目标文件的集合，这是在动态链接中没有错误的**





![](F:\Learn\5Week\程序员的自我修养\9\IMG\1.png)





### 使用模块定义文件

两种方式分别为：

"__deslspec(dllexport)"

".def声明"



使用.def文件可以控制一些链接的过程







### DLL显式运行时链接



**LoadLibary(或者LoadLibaryEx)，这个函数用来装载一个DLL到进程地址空间，它的功能跟dlopen相似**



**GetProcAddress，用来查找某个符号的地址，与dlsym相似**



**FreeLibary，用来卸载某个已加载的模块，与dlclose相似**











## 符号导出导入表

### 导出表

当一个PE需要将一些函数或变量提供给其他PE文件使用的时候，我们把这种行为叫做**符号导出(Symbol Exporting)**,最典型的就是把一个DLL将符号导出给EXE使用。



在Windows PE中，符号导出的概念是所有符号被集中放在了**导出表(Export Table)**的结构中。

**导出表提供了一个符号名与符号地址的映射关系，即可以通过某个符号查找相对的地址**

**符号修饰机制：每个符号都是一个ASCII字符串，符号名可能跟相对应的函数或者变量名相同，也可能不同**



PE头中有一个叫做DataDirectory的结构数组，这个数组中有16个元素，每个元素中保存的是一个地址和一个长度。**其中第一个元素就是导出表的结构的地址和长度。**



**导出表是一个IMAGE_EXPORT_DIRECTORY**



```c
typedef struct _IMAGE_EXPORT_DIRECTORY {
    DWORD   Characteristics;
    DWORD   TimeDateStamp;
    WORD    MajorVersion;
    WORD    MinorVersion;
    DWORD   Name;
    DWORD   Base;
    DWORD   NumberOfFunctions;
    DWORD   NumberOfNames;
    DWORD   AddressOfFunctions;     // RVA from base of image
    DWORD   AddressOfNames;         // RVA from base of image
    DWORD   AddressOfNameOrdinals;  // RVA from base of image
} IMAGE_EXPORT_DIRECTORY, *PIMAGE_EXPORT_DIRECTORY;

```



导出表结构中，最后的三个成员指向的是三个数组，这三个数组是导出表中的最重要的结构，它们是**导出地址表、符号名表、名字序号对应表**



![](F:\Learn\5Week\程序员的自我修养\9\IMG\3.png)





这三个数组中，前两个比较好理解，**第一个叫做导出地址表**，它存放的是各个函数的RVA；、

**第二个是函数名表**，它保存的是导出函数的名字，所有的函数名都是按照ASCII顺序排序的

**第三个是名字序号对应表**







### 序号

早期的Windows并没有虚拟内存机制，对于内存空间以KB计算的年代，如果把一个函数的dll全部放入内存中，是一种浪费



当时的DLL的导出函数主要是序号，一个导出函数的序号就是函数在EAT中的地址下标加上一个BASE值（默认值是1）。



现代使用最多的方式是函数名



**默认情况下，全局函数和变量是不导出的**







### exp文件

在创建DLL的同时会得到一个EXP文件，这个文件实际上是链接在创建DLL时产生的临时文件



链接器在创建DLL时与静态链接时一样采用两遍扫描过程，DLL一般都有导出符号，链接器在第一遍时会遍历所有的目标文件并且收集所有导出符号信息并创建DLL的导出表，



第一遍：**为了方便，链接器把这个导出表放在一个临时目标文件叫做".edata"**的段中，这个目标文件就是EXP文件



第二遍：链接器把这个EXP文件当作普通目标文件一样，与其他输入的目标文件链接在一起并输出DLL，这个时候EXP中的“.edata”段也会被输出到DLL文件中并成为导出表。



**现代编译器很少会在DLL中单独保留".edata段，而是把它合并到只读数据段".rdata"段中**







### 导出重定向

DLL有一个很有意思的机制叫做**导出重定向(Export Forwarding)**,顾名思义就是将某个导出符号重定向到另外一个DLL。

**Windows xp中，KERNEL32.DLL中的HeapAlloc函数就被重定向到NTDLL.DLL中的RelAllocHeap函数，调用HeapAlloc函数相当于调用RtlAllocHeap函数**









### 导入表

如果我们使用的某个程序用到了来自DLL的函数或者变量，那么我们就把这种行为称为符号导入



导入表：**在某个PE文件被加载时，Windows加载器的其中一个任务就是将所有需要导入的函数地址确定并且将导入表中的元素调整到正确的地址，以实现动态链接的过程**



![](F:\Learn\5Week\程序员的自我修养\9\IMG\4.png)



在构建Windows DLL时，还链接了支持DLL运行的基本运行库，这个基本运行库需要用到Kernel32.dll





**在PE中，导入表是一个IMAGE_IMPORT_DESCRIPTOR的结构数组，每一个结构对应一个被导入的DLL。**

```c
typedef struct _IMAGE_IMPORT_DESCRIPTOR {
    union {
        DWORD   Characteristics;            // 0 for terminating null import descriptor
        DWORD   OriginalFirstThunk;         // RVA to original unbound IAT (PIMAGE_THUNK_DATA)
    } DUMMYUNIONNAME;
    DWORD   TimeDateStamp;                  // 0 if not bound,
                                            // -1 if bound, and real date\time stamp
                                            //     in IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT (new BIND)
                                            // O.W. date/time stamp of DLL bound to (Old BIND)

    DWORD   ForwarderChain;                 // -1 if no forwarders
    DWORD   Name;
    DWORD   FirstThunk;                     // RVA to IAT (if bound this IAT has actual addresses)
} IMAGE_IMPORT_DESCRIPTOR;
typedef IMAGE_IMPORT_DESCRIPTOR UNALIGNED *PIMAGE_IMPORT_DESCRIPTOR;
```





结构体中的FirstThunk指向一个导入地址数组，IAT是导入表中最重要的结构，IAT中每个元素对应一个被导入的符号，元素的值在不同的情况下有不同的含义。





![](F:\Learn\5Week\程序员的自我修养\9\IMG\5.png)







### 



## DLL优化

DLL的代码段和数据段本身并不是地址无关的，它默认需要被装载到由ImageBase指定的目标地址中。如果目标地址被占用，那么就需要装载到其他地址，便会引起整个DLL的Rebase。
符号和字符串的比较和查找过程也会影响DLL性能。



###  重定基地址（Rebasing）

PE的DLL中的代码段并不是地址无光的，它在被装载时有一个固定的目标地址，这个地址也就是PE里面所谓的**基地址**。
对于DLL来说，一个进程中，多个DLL不可以被装载到同一个虚拟地址，每个DLL所占用的虚拟地址区域之间都不可以重叠。
Windows PE采用**装载时重定位**：在DLL模块装载时，如果目标地址被占用，那么操作系统就会为它分配一块新的空间，并且将DLL装载到该地址。对于DLL每个绝对地址引用都进程重定位。
由于DLL内部地址都是基于基地址的，或者是相对于基地址的RVA。那么所有需要重定位的地址都只需要加上一个固定差值。PE里面把这种特殊的重定位过程叫做**重定基地址**。
EXE是不可以重定位的，不过这也没问题，因为EXE文件是进程运行时第一个装入虚拟空间的，所以它的地址不会被人抢占。

##### 改变默认基地址

对于一个程序来说，它所用到的DLL基本是固定的程序每次运行时，这些DLL的装载顺序和地址也是一样的。

##### 系统DLL

Windows系统在进程空间中专门划出一块0x70000000~0x80000000区域，用于映射这些常用的系统DLL。



### 序号

一个DLL中每一个导出的函数都有一个对应的**序号**。一个导出**函数**甚至没有函数名，但它必须有唯一的序号。序号标示被导出函数地址在DLL导出表中位置。



### 导入函数绑定当一个程序运行时，所有被依赖的DLL都会被装载，并且一系列导入导出符号依赖关系都会被重新解析。这些DLL都会以同样的顺序被装载到同样的内存地址，所以它们的导出符号的地址都是不变的。
DLL绑定：使用editbin可以对EXE和DLL绑定。
editbin对绑定的程序的导入符号进行遍历查找，找到以后就把符号的运行时的目标地址写入到被绑定程序的导入表内。
INT这个数组就是用来保存绑定符号的地址的。
DLL绑定地址失效：

- 一种情况，被依赖的DLL更新导致DLL的导入函数地址发生变化。
- 另一种情况，被依赖的DLL在装载时发生重定基址，导致DLL的装载地址与被绑定时不一致。

第一种情况的失效，PE做法时当对程序绑定时，对于每个导入的DLL，链接器把DLL的时间戳和校验和保存到被绑定的PE文件的导入表中。在运行时，Windows会核对将要被装载的DLL与绑定时的DLL版本是否相同，并且确认该DLL没有发生重定基址。







## C++与动态链接

C++编写动态链接库在Windows平台下最好遵循以下指导：

- 所有的接口都应该抽象
- 所有的全局函数都应该使用”extern C”来防止名字修饰的不兼容
- 不要使用C++标准库STL
- 不要使用异常
- 不要使用虚析构函数
- 不要在DLL里面申请内存
- 不要在接口中使用重载方法



## DLL HELL

由于早期Windows缺乏一种很有效的DLL版本控制机制，DLL不兼容文件在Windows非常严重，被人们称为DLL噩梦(DLL hell)。
DLL HELL发生的三种可能原因：

- 由使用旧版本的DLL替代原来一个新版本的DLL引起
- 由新版DLL中的函数无意发生改变而引起
- 由新版DLL按照引入一个新BUG

##### 解决DLL Hell的方法

- - 静态链接
  - 防止DLL覆盖：使用windows保护技术
  - 避免DLL冲突：每个应用程序拥有一份自己依赖的DLL
  - .NET 下DLL Hell的解决方案：在.NET框架中，一个程序集有两种类型：应用程序集以及库程序。一个程序集包块一个或多个文件，所以需要一个清单文件来描述程序集。这个清单文件叫做**Manifest文件**。Manifest文件描述了程序集的名字，版本号以及程序集的各种资源，同时也描述了该程序集的运行所依赖的资源，包括DLL以及其他资源文件等。操作系统会根据DLL的manifest文件去寻找对应的DLL并调用。

 

