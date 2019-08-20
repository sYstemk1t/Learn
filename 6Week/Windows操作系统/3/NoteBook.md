# Windows进程和线程

## 进程和线程概念

程序是一个广泛使用的术语，在不同的上下文中可能有不同的定义；相对而言，进程是一个层次上的概念，有较为清晰和严格的定义。



### 多进程模型

可以简单的把进程(process)理解成一个独立的任务，它不是一个正在被执行的程序，它有自己的指令流和内存空间，同时，还拥有一颗仅供自己使用的虚拟CPU。从整个系统的角度来看，多个进程是分时执行的，但是对于每个进程来说，它的指令流按顺序执行，好像独占了一颗CPU一样。

![](F:\Learn\6Week\Windows操作系统\3\IMG\0.png)

**每个进程都有自己的运行时间轴，就像一个单独的处理器运行一样，系统负责切换进程，让他们得以轮流执行**

操作系统需要做的事情是：

**维护一个全局进程表，**记录下当前哪些进程在被执行；

**把时间分成适当的片段，**在现代处理器结构中，这可以通过时钟中断来完成，因此每次时钟终端到来前系统就会获得控制权

**进程间实施切换，**保留上一个进程的环境信息，回复下一个进程的执行环境

### 进程与程序

**程序内存结构与进程有一定的联系**

![](F:\Learn\6Week\Windows操作系统\3\IMG\1.png)

内存区域三种类型：**静态数据区、动态数据区、维护控制流信息和局部状态的调用栈区**

**对c/c++程序来说，静态数据区存放的是全局变量以及静态变量等信息，这就是数据区域**

**动态数据区：程序执行过程中根据需要而分配或回收内存的区域**

**调用栈区：调用函数中的状态信息，包含了所有的局部变量和当前指令流经过此次函数调用的位置**



程序代表的两种情况：

- 程序代表了一个进程，通常用启动该进程的二进制可执行模块的文件名来表示程序的名称。在Windows平台上往往是一个.exe文件

- 程序代表了一个二进制可执行模块，通常用该模块的文件名来表示程序的名称。在Windows平台上，既可以是.exe文件，也可以是DLL文件或者其他后缀的文件

  

**一个进程包含有代码和数据，以及在执行过程中有关控制流状态的信息，当它在运行过程中需要更多的内存，它可以从动态内存区域获取内存，不用的时候再释放这些内存**

**当一个进程完成所有的功能，进程会通知操作系统，终止进程，将内存进行回收，当进程出错或者状态不正确的时候，进程也会杀死进程(kill a process)**



现代操作系统中，默认情况下进程只有一个控制流，尽管这个控制流可以跨越多个模块，但是它的调用栈只有一个，进程可以拥有很多个控制流，每个控制流对应一个调用栈。



## 线程的基本概念



线程不仅仅是一个控制流，线程的调用栈(call stack)记录它作为控制流的状态信息，包括每一层函数调用和返回的指令地址。

**线程一定隶属于某个进程，其控制流可以访问这个进程中的资源，包括所有的内存数据以及系统分配给此进程的其他资源**

**一个进程可以有多个线程，由于这些线程隶属于同一个进程，所以它们之间相互通信效率很高，并且所有的资源对他们来说都是共享的**





### 线程模型

现代计算中的两种线程模型：

- 用户及线程(user-level threads)

   应用程序在操作兄提供的单个控制流的基础上，通过某个控制点上分离一些模拟的控制流，从而模拟多个控制流的行为。

- 内核级线程(kernel-level threads)

   由于操作系统对控制流有完全的控制能力，甚至可以通过硬件中断来强迫一个进程或线程暂停执行，以便于把处理器时间移交给其他的进程或线程，所以内核级线程可能应用各种算法来分配处理器时间

  



**在支持内存级线程的环境中，进程可以容纳多个线程，这导致了多线程程序设计模型。由于多个线程在同一个进程环境中，它们共享了几乎所有的资源，所以线程之间的通信要方标和高效，但是这种表理性也容易使得线程之间因同步不正确而导致数据被破坏，而且这种错误存在不确定性**





### 线程调度算法

线程调度算法：

- 先到先服务算法：在非抢占式系统中，这一算法比较自然，用一个EIFO队列就可以满足。所有的线程构成一个队列，最先进入队列的线程获得处理器执行权，等到放弃处理器执行权时，又回到队列尾部，下一个下称继续执行。如果有新的线程进入，则添加到队列尾部
- 时间片轮转调度算法：处理器的时间被分成了最大值不超过某个值的时间片段，称为时间片，然后，用轮转的方式分配给每一个线程。当一个线程获得处理器执行权后，按照自身逻辑继续执行，直到时间片用完，或者主动放弃执行权。系统获得处理器控制权后，用轮转的方式找到下一个等待中的线程。**时钟中断每次都要打断一个线程的运行**
- 优先级调度法：在时间轮转算法中，一个基本的假设是所有的线程都同等重要。每一个线程都有一个优先级值，高优先级的线程总是优先被考虑。





### 线程与进程的关系

进程提供了一个完全的执行环境，同时也有一个控制流完成其预定的功能。操作系统按进程来分配处理器资源，在这种系统中，对线程的支持可以在用户模式下完成，即用户级线程模型

![](F:\Learn\6Week\Windows操作系统\3\IMG\2.png)



在支持内核级线程系统中，进程仅仅只是一个执行环境，它包含了一个或者多个线程，每个线程代表一个单独的指令流，操作系统按线程分配处理器资源

![](F:\Learn\6Week\Windows操作系统\3\IMG\3.png)

**Windows中的线程是内核级的线程**







## Windows中进程和线程的数据结构

```c
typedef struct _KPROCESS {

    //
    // The dispatch header and profile listhead are fairly infrequently
    // referenced.
    //

    DISPATCHER_HEADER Header;
    LIST_ENTRY ProfileListHead;

    //
    // The following fields are referenced during context switches.
    //

    ULONG_PTR DirectoryTableBase[2];

#if defined(_X86_)

    KGDTENTRY LdtDescriptor;
    KIDTENTRY Int21Descriptor;
    USHORT IopmOffset;
    UCHAR Iopl;
    BOOLEAN Unused;

#endif

#if defined(_AMD64_)

    USHORT IopmOffset;

#endif

    volatile KAFFINITY ActiveProcessors;

    //
    // The following fields are referenced during clock interrupts.
    //

    ULONG KernelTime;
    ULONG UserTime;

    //
    // The following fields are referenced infrequently.
    //

    LIST_ENTRY ReadyListHead;
    SINGLE_LIST_ENTRY SwapListEntry;

#if defined(_X86_)

    PVOID VdmTrapcHandler;

#else

    PVOID Reserved1;

#endif

    LIST_ENTRY ThreadListHead;
    KSPIN_LOCK ProcessLock;
    KAFFINITY Affinity;

    //
    // N.B. The following bit number definitions must match the following
    //      bit field.
    //
    // N.B. These bits can only be written with interlocked operations.
    //

#define KPROCESS_AUTO_ALIGNMENT_BIT 0
#define KPROCESS_DISABLE_BOOST_BIT 1
#define KPROCESS_DISABLE_QUANTUM_BIT 2

    union {
        struct {
            LONG AutoAlignment : 1;
            LONG DisableBoost : 1;
            LONG DisableQuantum : 1;
            LONG ReservedFlags : 29;
        };
   
        LONG ProcessFlags;
    };

    SCHAR BasePriority;
    SCHAR QuantumReset;
    UCHAR State;
    UCHAR ThreadSeed;
    UCHAR PowerState;
    UCHAR IdealNode;
    BOOLEAN Visited;
    union {
        KEXECUTE_OPTIONS Flags;
        UCHAR ExecuteOptions;
    };

#if !defined(_X86_) && !defined(_AMD64_)

    PALIGNMENT_EXCEPTION_TABLE AlignmentExceptionTable;

#endif

    ULONG_PTR StackCount;
    LIST_ENTRY ProcessListEntry;
} KPROCESS, *PKPROCESS, *PRKPROCESS;
```

**每个KPROCESS对象都代表一个进程，即每个进程都有KPROCESS对象**



**进程对象本身是可以被等待的，也就是说，如果一个线程调用Windows的等待函数，在一个进程对象上等待，那么，当此进程对象编程有信号状态时，此等待就会成，所以说，进程对象是可等待的对象**





## 进程和线程运行状态监视工具

### ProcMon工具

