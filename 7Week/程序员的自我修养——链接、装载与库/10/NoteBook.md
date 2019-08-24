# 内存

## 程序的内存布局

**现代的应用程序都运行在一个内存空间里，在32位操作系统中，这个内存又4GB寻址能力。**





**在平坦的内存模型中，整个内存是一个统一的地址空间，用户可以使用一个32位的指针访问任意的内存位置**



**大多数操作系统会将一部分内存空间地址分配给内核，应用程序无法直接使用这一段内存空间，这段空间也成为内核空间。**



Windows在默认情况下会将高地址的2GB空间分配给内核，Linux默认将高地址的1GB空间分配给内核





- 栈：栈用于维护函数调用的上下文，离开了栈函数调用就无法实现，栈通常在用户空间的最高地址处分配，通常有数兆字节的大小

- 堆：堆是用来容纳应用程序动态内存分配的内存区域，当应用程序malloc或者new分配内存时，得到的内存来自堆。

- 可执行文件映像：这里存储着可执行文件在内存里的映像，由装载器在装载时将可执行文件的内存读取或映射到这里。

- 保留区：保留区并不是一个单一的内存区域，而是对内存中收到保护而进制访问内存区域的总称。

  ​						*Linux进程地址空间分布*

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\1.png)

**栈空间向低地址增长，堆空间向高地址增长，当堆或者栈空间不够用的时候，它按照图中的增长方向扩大自己的尺寸，直到预留空间被用完为止**





## 栈与调用惯例

### 栈

**栈遵守：先入栈的数据后出栈，后入站的数据先出栈**

**栈被定义为一个特殊容器：用户可以将数据压入栈(push)，也可以将数据弹出(pop)**

**栈的生长空间是向下的，压栈使得栈顶的地址减小，弹出使得栈顶地址变大**

​								         *程序栈实例*

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\2.png)



**栈保存了一个函数调用所需要的维护信息，这通常称为堆栈帧(Stack Frame)或活动记录(Activate Record)。**堆栈帧一般包括一下内容：

- 函数的返回地址和参数
- 临时变量：包括函数的非静态局部变量以及编译器自动生成的其他临时变量
- 保存的上下文：包括在函数调用前后需要保持不变的寄存器



**在i386的处理中，一个函数的活动记录用ebp和esp这两个寄存器划定范围：esp始终指向栈的顶部，同时也指向了当前函数的活动记录的顶部。而相对的，ebp寄存器指向了函数活动记录的一个固定位置，ebp寄存器又被称为桢指针**

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\3.png)

**ebp固定在指定位置不会改变，esp始终指向栈顶，随着函数的执行，esp会不停的变化**



在i386下函数调用：

- 把所有或一部分参数压入栈中，如果有其他参数没有入栈，那么使用某些特定的寄存器传递
- 把当前指令的下一条指令的地址压入栈中
- 跳转到函数体执行







## 未初始化的局部变量



```c
#include <stdio.h>
int main()
{
	char p[12];			//在这里下断点
   	return 0;
}
```



此时的数组p并没有进行初始化，在debug模式下，监视到的值就是"烫"，因为在debug模式下，将所有的分配出来的栈空间的每一个字节都初始化为0xcc，0xcccc的汉字编码就是烫，所以0xcccc被当作文本监视就是"烫"

未初始化设置0xcc的理由是判断一个变量是否被初始化，如果一个指针变量的值是0xcccccccc，那么我们就可以确定这个指针没有初始化，有时候我们也会看到"屯"，这是编译器使用了0xcdcdcdcd作为未初始化标记



### 调用惯例

## 

- 函数参数的传递顺序和方式

函数参数传递有很多方式，最常见的一种是栈传递，函数的调用方将参数压入栈中，函数自己再从栈中将参数取出。

- 栈的维护方式

在函数将参数压栈以后，函数体会被调用，此后需要将被压入栈中的参数全部弹出，以使得栈在函数调用前后保持一直

- 名字修饰

为了链接的时候堆调用惯例进行区分，调用管理要堆函数本身的名字进行修饰





![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\5.png)





### 函数返回值传递

除了参数的传递之外，函数与调用方的交互还有一个渠道就是返回值。

函数返回：

```c
#include <stdio.h>

typedef struct big_thing
{
	char buf[128];
}big_thing;

big_thing return_test()
{
	big_thing b;
	b.buf[0] = 0;
	return b;
}

int main()
{
	big_thing n = return_test();
	return 0;
}
```



```assembly
#include <stdio.h>

typedef struct big_thing
{
	char buf[128];
}big_thing;

big_thing return_test()
{
00FA1460  push        ebp  
00FA1461  mov         ebp,esp  
00FA1463  sub         esp,148h  
00FA1469  push        ebx  
00FA146A  push        esi  
00FA146B  push        edi  
00FA146C  lea         edi,[ebp-148h]  
00FA1472  mov         ecx,52h  
00FA1477  mov         eax,0CCCCCCCCh  
00FA147C  rep stos    dword ptr es:[edi]  
	big_thing b;
	b.buf[0] = 0;
00FA147E  mov         eax,1  
00FA1483  imul        ecx,eax,0  
00FA1486  mov         byte ptr b[ecx],0  
	return b;
00FA148E  mov         ecx,20h  
00FA1493  lea         esi,[b]  
00FA1499  mov         edi,dword ptr [ebp+8]  
00FA149C  rep movs    dword ptr es:[edi],dword ptr [esi]  
00FA149E  mov         eax,dword ptr [ebp+8]  
}
00FA14A1  push        edx  
00FA14A2  mov         ecx,ebp  
00FA14A4  push        eax  
00FA14A5  lea         edx,ds:[0FA14BCh]  
00FA14AB  call        @_RTC_CheckStackVars@8 (0FA1087h)  
00FA14B0  pop         eax  
00FA14B1  pop         edx  
00FA14B2  pop         edi  
00FA14B3  pop         esi  
00FA14B4  pop         ebx  
00FA14B5  mov         esp,ebp  
00FA14B7  pop         ebp  
00FA14B8  ret  
00FA14B9  lea         ecx,[ecx]  
00FA14BC  add         dword ptr [eax],eax  
00FA14BE  add         byte ptr [eax],al  
00FA14C0  les         edx,fword ptr [edx+edi*8]  
00FA14C3  add         byte ptr [edi+edi*8-1],bh  
00FA14C7  inc         dword ptr [eax-30000000h]  
00FA14CD  adc         al,0FAh  
00FA14CF  add         byte ptr [edx],ah  




int main()
{
00FA13C0  push        ebp  
00FA13C1  mov         ebp,esp  
00FA13C3  sub         esp,1D0h  
00FA13C9  push        ebx  
00FA13CA  push        esi  
00FA13CB  push        edi  
00FA13CC  lea         edi,[ebp-1D0h]  
00FA13D2  mov         ecx,74h  
00FA13D7  mov         eax,0CCCCCCCCh  
00FA13DC  rep stos    dword ptr es:[edi]  
	big_thing n = return_test();
00FA13DE  lea         eax,[ebp-1CCh]  			//将栈上的一个地址(ebp-1CCH)存储在eax中
00FA13E4  push        eax  						//将这个地址压入栈中
00FA13E5  call        _return_test (0FA1186h)  
00FA13EA  add         esp,4  
00FA13ED  mov         ecx,20h  
00FA13F2  mov         esi,eax  
00FA13F4  lea         edi,[n]  
00FA13FA  rep movs    dword ptr es:[edi],dword ptr [esi]  
	return 0;
00FA13FC  xor         eax,eax  
}
00FA13FE  push        edx  
00FA13FF  mov         ecx,ebp  
00FA1401  push        eax  
00FA1402  lea         edx,ds:[0FA1424h]  
00FA1408  call        @_RTC_CheckStackVars@8 (0FA1087h)  
00FA140D  pop         eax  
00FA140E  pop         edx  
00FA140F  pop         edi  
00FA1410  pop         esi  
00FA1411  pop         ebx  
00FA1412  add         esp,1D0h  
00FA1418  cmp         ebp,esp  
00FA141A  call        __RTC_CheckEsp (0FA1136h)  
00FA141F  mov         esp,ebp  
00FA1421  pop         ebp  
00FA1422  ret  
00FA1423  nop  
00FA1424  add         dword ptr [eax],eax  
00FA1426  add         byte ptr [eax],al  
00FA1428  sub         al,14h  
00FA142A  cli  
00FA142B  add         byte ptr [edi+edi*8-1],bh  
00FA142F  inc         dword ptr [eax+38000000h]  
00FA1435  adc         al,0FAh  
00FA1437  add         byte ptr [esi],ch  
```







- 首先main函数在栈上开辟了一块内存空间，并将这块空间的一部分作为传递给返回值的临时对象，这里称为temp
- 将temp对象的地址作为隐藏参数传递给return_test函数
- retrun_test函数将数据拷贝给temp对象，并将temp对象的地址用eax传出
- return_test返回之后，main函数将eax指向的temp对象的内容拷贝给n

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\6.png)









## 堆与内存管理

堆相对于栈来说，堆在任意时刻，任何程序发出请求，要么申请一段内存，要么释放一段已经申请过后的内存，而且申请的内存大小从几个字节到几个GB都是可以的。



### 什么是堆

栈上的数据在函数返回的时候就会被释放掉，所以无法将数据传递到函数的外部。而全局变量没有办法动态的产生，只能在编译的时候定义。

**堆是一个巨大的内存空间，常常占据整个虚拟空间的绝大部分，**程序可以申请一块连续的内存空间，并自由使用，这块内存空间在程序主动放弃之前都保持有效



```c
#include <stdio.h>

int main()
{
	char *p = (char *)malloc(1000);			//申请内存空间
	free(p);								//释放
}
```





### linux进程堆管理

**进程地址空间中，除了可执行文件、共享库、栈之外，剩余的未分配空间都可以被用来当作堆空间**



linux中的两种堆空间分配：**brk()系统调用、mmap()**



**mmap的作用和Windows下的VirtualAlloc很相似，它的作用是向操作系统申请一段虚拟地址空间，当然这块虚拟地址空间可能映射到某个文件，当它不将地址空间映射到某个文件的时候，我们称这块空间为匿名空间，匿名空间可以拿来分配作为堆空间**



```c
#include <stdio.h>
void *malloc(size_t nbytes)
{
	void *ret = mmap(0,nbytes,PROT_READ | PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS,0,0);
	if(ret == MAP_FAILED)
	{
		return 0;
	}
	return ret;
}



```







### Windows进程堆管理

​									Windows进程地址分布：

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\7.png)

**Windows的进程将地址空间分配给了各种EXE、DLL文件、堆、栈。EXE文件一般位于0x00004000起始的地址；而一部分DLL位于0X10000000起始的地址，如DLL运行库；还有一部分DLL接近0x80000000的位置，如系统DLL**



**Windows中每个线程的栈都是独立的，所以一个进程中有多少个线程，就有多少个对应栈，对于Windows来说，每个线程默认的栈大小是1MB，在线程启动时，系统会给它在进程地址空间中分配相对应的空间作为栈，线程栈的大小可以由创建线程时的CreatThread的参数指定**



**实际上VirtualAlloc申请的空间不一定只用于堆，它仅仅是向系统预留了一块虚拟地址，应用程序可以按照需要随时使用**



**在使用VirtualAlloc函数申请空间时，系统空间大小必须是页的整数倍，即对于X86系统来说，必须是4096字节的整数倍**





Windows中的堆管理器(Heap Manger)，堆管理器提供了一套与堆相关的API可以用来创建、分配、释放和销毁堆空间：

- HeapCreate：创建一个堆
- HeapAlloc:在一个堆里分配内存
- HeapFree：释放已经分配的内存
- HeapDestroy：摧毁一个堆



**堆管理器位于Windows的两个位置，一份位于NTDLL.DLL中，这个DLL是Windows操作系统用户层的最底层DLL，它负责Windows子系统DLL和Windows内核之间的接口**

**另一份在Windows内核Ntoskrnl.exe中，还存在一份类似的堆管理器，它负责Windows内核中的堆空间分配，Windows内核、内核组件、驱动程序使用堆时用到的都是这份堆分配代码**





**所有堆的实现里，都会存在重复释放同一片对立的内存产生错误**







### 堆分配算法

- 空闲链表：

  空闲链表(Free List)的方法实际上就是把堆中各个空闲的块按照链表的方式连接起来，当用户请求一块空间时，遍历整个列表，直到找到合适大小的块并且将它拆分；当用户释放空间时将它合并到空闲链表中

  空闲链表是这样的结构，在堆里的每一个空闲空间的开头（或结尾）有一个有（Header），头结构里记录了上一个（prev）和下一个（next）空闲块的地址，也就是说，所有的空闲块形成了一个链表

  ![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\8.png)



首先在空闲链表里查找组后容纳请求大小的一个空闲块，然后将这个块分成两部分，一部分为程序请求的空间，另一部分为剩余下来的空闲空间。

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\9.png)



**问题：一旦链表被破坏，或者记录长度的4字节空间被破坏，整个堆就无法进行正常工作，而这些数据恰恰容易被越界读写所接触到**





- 位图

位图的核心思想是将整个堆划分为大量的块(block)，每个块大小相同，当用户请求内存的时候，总是分配整数个块的空间给用户，第一个块我们称为已分配区域的头（head），其余的称为已分配区域的主体（body）。我们只需要一个整数数组来记录块的使用情况，由于每个块只有**有头、主体、空闲**三种情况，因此仅仅只需要两位即可表示一个块

![](F:\Learn\7Week\程序员的自我修养——链接、装载与库\10\Img\10.png)



- 对象池

**如果每一次分配的空间大小都一样，那么就可以按照这个每次请求分配的大小作为一个单位，把整个堆划分为大量的小块，每次请求的时候只需要找到一个小块就可以了**