# bx和loop

## bx和内存单元的描述

比如 mov ax,[0]	//[0]的寻址空间就是ds:0,它自身写0，证明偏移地址也是0

![](D:\Learn\3Week\Assembly\第五章\img\1.png)

仔细看0c74：0000的里面的内容，然后对它进行修改

![](D:\Learn\3Week\Assembly\第五章\img\2.png)

既然里面可以写段地址：偏移地址，也可以写入寄存器

![](D:\Learn\3Week\Assembly\第五章\img\3.png)

它的段地址永远在ds中，mov ax,[bx]	//这里的bx仅仅是偏移地址

## loop

loop循环



## （）

“（）”代表一个寄存器或者一个内存单元中的内容。

加括号就是表示内容，不加括号代表寄存器

“（）”中的元素有三种类型：1.寄存器名、2.段寄存器名、内存单元的物理地址



## 约定符号

mov ax,[2]	//括号里只可以写常量



## [bx]

mov ax,[bx]

![](D:\Learn\3Week\Assembly\第五章\img\4.png)



mov [bx],ax

![](D:\Learn\3Week\Assembly\第五章\img\5.png)



问题5.1

mov ax,2000	ax = 2000

mov ds,ax	ds = 2000:0

mov bx,1000	bx = 1000

mov ax,[bx]	ax = 00be

inc bx

inc bx		bx = 1002

mov [bx],ax	bx = 00be

inc bx

inc bx	bx = 1004

mov bx,[ax]	bx = 00be



inc bx	bx = 1005



mov [bx],al	bx = be



inc bx 	bx = 1006

mov [bx]	al = be





![](D:\Learn\3Week\Assembly\第五章\img\6.PNG)



## loop指令

loop指令的格式是：loop编号，cpu执行loop指令的时候，要进行两步操作，

1.（cx） = （cx - 1）；

2.判断cx的值，不为零则跳转至标号执行程序，如果为0则向下继续执行

这个和c语言的while很像，不为0的时候一直执行

1.求2的2次方的结果

```assembly
assume cs:code
code segment
    mov ax,2
    add ax,ax
    mov ax,4c00h
    int 21h

code ends
end

```

2.求2的3次方的结果

```assembly
assume cs:code
code segment
    mov ax,2
    add ax,ax
    add ax,ax
    mov ax,4c00h
    int 21h

code ends
end

```

3.假如我们希望写2的1024次方呢？

```assembly
assume cs:code
code segment
    mov ax,2
    add ax,ax
    add ax,ax	;重复1024次，那样太low了
    mov ax,4c00h
    int 21h

code ends
end

```



```assembly
assume cs:code
code segment
    mov ax,2
    mov cx,11	;相当于定义一个值，每次自减，直到0
    s : add ax,ax	;s代表一个编号，每个编号代表一个地址，它实际标识了一个地址，这个地址处有一条指令，add ax,ax
    loop s		;每次执行loop指令的时候，都需要cx=cx-1,然后判断cx是不是为0，不为0则继续转向s编号执行
    mov ax,4c00h
    int 21h
code ends
end

```

![](D:\Learn\3Week\Assembly\第五章\img\7.png)



问题5.2

```assembly
assume cs:code
code segment
    mov ax,123	;ax寄存器的值是123
    mov bx,236	;bx寄存器的值是456
    mov cx,236	;计数器，一共循环236次
    s : add ax,bx	;s标号
    loop s		;检查cx是否为0
    mov ax,4c00h
    int 21h


code ends
end

```



问题5.3



```assembly
assume cs:code
code segment
    mov ax,0	;ax寄存器的值是0
    
    mov cx,123	;计数器，一共循环123次
    s : add ax,236	;s标号
    loop s		;检查cx是否为0
    mov ax,4c00h
    int 21h


code ends
end

```





## debug跟踪loop指令实现的循环

计算ffff：0006单元中的数乘以3，结果存储在dx中

ffff:0006 是一个字节类型的数据，范围在0-255之间，然后做三次加法

ffff：0006单元是一个字节单元，ax是16位寄存器，数据长度不一样

8位数据01H和16位数据0001H的数据长度不一样，但是值是相同的



如果ffff：0006单元中的数据是xxh，若要ax中的值和ffff：0006单元中的相等，ax中的数据应该为00xxh。

如果要ffff：0006单元向ax赋值，应该令ah=0；al=ffff：0006h



```assembly
assume cs:code
code segment
    mov ax,0ffffh	;大于9FFF的十六进制数据，在书写的时候都是以字母开头的，但是汇编不可以以字母开口，所以全部加0
    mov ds,ax	;设置ds：bx指向ffff：6
    mov bx,6	
    mov al,[bx]
    mov ah,0	
    mov dx,0	;累加寄存器清除为0
    mov cx,3	;循环三次

    s : add dx,ax	;s标号
    loop s	

    mov ax,4c00h
    int 21h		;程序返回

code ends
end

```



cs：ip指向程序的第一条指令

ds是段寄存器



使用g 偏移地址，可以快速定位到某一个指令上

或者使用p指令快速跳出循环







## debug和masm对指令处理的不同

debug中 mov ax,[0]	;表示将ds：0000处的数据送入通用寄存器ax中

但是在汇编源程序中， 指令 mov ax,[0] ;被当作指令mov ax,0处理



![](D:\Learn\3Week\Assembly\第五章\img\8.png)



![](D:\Learn\3Week\Assembly\第五章\img\9.png)



下面是汇编的：

![](D:\Learn\3Week\Assembly\第五章\img\10.png)



对于mov al,[0]这类指令在解释上有很多的不同,debug和源代码中写入同样的指令，但是解释却不相同



debug认为mov al,[] ；[]括号内的内容是一个内存单元，里面写的内存单元的偏移地址

编译器则认为[]内的内容是常量



如果我们需要在源程序中将内存单元的数据送入寄存器中，那么久可以通过偏移地址先送入寄存器，然后用寄存器当偏移地址来访问内存单元。



```assembly
mov ax,2000
mov ds,ax
mov bx,0	;将偏移地址段送入bx寄存器中
mov ak,[bx]	;将偏移地址所指向的内存空间的数据送入ax中

```



也可以直接在[]中写入内存单元的偏移地址



```assembly
mov ax,2000
mov ds,ax
mov ak,ds:[0]	;将偏移地址所指向的内存空间的数据送入ax中

```



```assembly
mov al,[0]	;将常量0送入al中，al是ax寄存器，因为ax是八位寄存器，所以它又分为高八位和低八位
mov al,ds:[0]	;将ds地址段偏移地址为0的数据送入al
mov al,[bx]	;汇编程序用，使用的时候得先将偏移地址送入bx寄存器中
mov al,ds:[bx]	;与汇编程序用同理

```



在汇编程序中，如果用指令访问一个内存单元，则必须在指令中用[]来表示内存单元，如果在[]里用一个常量直接给处内存单元的偏移地址，就必须在[]的前面给出段地址所在的段寄存器。

比如mov al,ds:[0];

如果不给出，编译会认为，[]里的是一个常量，直接翻译为常量处理

mov al,[0] ----> mov al,0



如果在[]里用寄存器，那么首先必须在前面给寄存器给值





## loop和[bx]的联合应用

计算ffff：0-ffff：b单元数据的和，结果存储在dx中

12个字节相加，结果不会大于65535，可以存



相加得到的数据是八位的，而ax是十六位寄存器，不可以直接存放



dl是八位寄存器，能容纳的数据在0-255之间，ffff：0-ffff：b中的数据也都是八位，如果仅仅只是累加12个八位数据，很可能造成进位丢失



**将内存单元的8位数据赋值到一个16位寄存器上，上面写了，8位数据01H和16位数据0001H的数据长度不一样，但是值是相同的**



**8位数据 -->  ax(16位寄存器)  -->  dx(16位寄存器)**



这样就不会造成运算对象的类型不匹配而且结果不会越界





问题5.3：

未使用循环



问题5.4：

```assembly
assume cs:code
code segment
mov ax,0ffffh
mov ds,ax
mov dx,0
mov cx,12
s : mpv ax,[bx]
mov ah,0
add dx,ax
inc bx
loop s
mov ax,4c00
int 21

code ends
end

```









## 段前缀



在**mov ax,[bx]中，内存单元的偏移地址由不bx给出，而短地址默认在ds中，我们可以默认给他在访问内存单元的指令中显式的给出内存单元的段地址所在的段寄存器**





mov ax,ds:[bx]	//将一个内存单元的内容送入ax，这个内存单元的长度为2字（字单元），存放一个字，偏移地址在bx中，段地址在ds中



**出现在访问内存单元的指令中，用于显式的指出内存单元的短地址的：ds、cs、ss、es，这些称为段前缀**





**如果要是稍微仔细一下，应该可以发现，其实段前缀就是为了解决debug和masm下的[]这个指令的不同，所以为了避免二义性，引入了段前缀**







## 一段安全空间

在任意的一段内存空间中写入数据，这是很危险，如果这段内存空间中存放的数据是系统数据或者代码，那么很有可能就会造成奔溃，（一般来说，如果系统检测到你在操作他， 一般就送你蓝屏警告）

```assembly
assume cs:code
code segment
    mov ax,0
    mov ds,ax
    mov ds:[26h],ax
    mov ax,4c00h
    int 21h

code ends
end

```

![](D:\Learn\3Week\Assembly\第五章\img\11.png)

执行到这一步的时候，这个dos窗口就卡死了，无法继续输入，造成这样的后果的根本原因就是，0000：0026处存放的是系统数据，但是我们的汇编指令将他修改了，然后他就死了。

因为我是xp_sp2，所以只会当前的dos窗口卡死，但是王爽的《汇编语言第三版》使用的是win2000，会这样提示：

![](D:\Learn\3Week\Assembly\第五章\img\12.png)



如果我们在纯dos（无任何窗口程序），可以不理会dos，直接用汇编语言去操作真实的硬件，因为运行在cpu实模式下的dos，没有能力对硬件系统进行管理。

但是到了windows2000，unix这些运行于cpu保护摸下的操作系统中，不理会操作系统去操作硬件，是不可能的。比如我们使用的debug就是command下的，command就是操作系统给用户提供的一层壳，我们只是在这个壳上进行操作



如果我们需要向内存中直接写入一段数据，可以写到0：200-0：2ff这段空间。



因为在dos中，这段空间一般是没有被其他程序的数据或者代码占用的





可以看一下啊

![](D:\Learn\3Week\Assembly\第五章\img\13.png)

如果忘了这条指令，可以去实验3下背一背debug下的指令。





## 段前缀使用

将内存ffff:0-ffff:b单元中的数据赋值到0:200-0:20b中

它两是同一段内存空间，复制可以选择循环



```assembly
assume cs:code
code segment
	mov bx,0
	mov cx,12	;控制循环次数
	
	s : mov ax,0ffffh	;
	mov ds,ax	;ds=ffffh
	mov dl,[bx]	;将ffff:bx中的数据送入dl
	
	mov ax,0020h	
	mov ds,ax	;ds=0020
	mov [bx],dl	;dl中的数据送入0020:bx中
	
	inc bx		;bx循环自增
	loop s		;循环s
	
	mov ax,4c00
	int 21
	
code ends
end
	

```





因为ffff：x和目标单元0020：x相当于大于64kb，在不同的64kb段里，上面的程序每次循环都是需要设置两次dx的值的。

我们为了提高效率，我们使用两个段寄存器存放原始单元ffff：x和0020：x的段地址





```assembly
assume cs:code
code segment
	mov ax,0ffffh
	mov ds,ax
	mov ax,0020
	mov es,ax
	mov bx,0	;bx = 0,此时的ds：bx指向ffff：0，es指向0020：0
	mov cx,12	;循环12次
	
	s : mov dl,[bx]	;将ffff:0中的数据送入dl
	mov ed:[bx],dl	;dl中的输入送入0020:0
	inc bx	;bx自增
	loop s	
	
	mov ax,4c00h
	int 21h
	
	
code ends
end

```



es存放目标空间0020：0-0020：b的段地址，用ds存放原始空间ffff:0-ffff:b的段地址，在访问内存单元的指令mov es:[bx],al,显式的用段前缀“es”给出单元的段地址，这样就避免了重复设置ds







## 实验4

1.编程，向内存0：200-0：23f以此传送数据0-63

```assembly
assume cs:code
code segment
	mov ax,0000h
	mov ds,ax
	mov bx,200h
	mov dx,0
	mov cx,64
	
	s : mov [bx],dx
	inc bx
	inc dx
	loop s
	
mov ax,4c00
int 21
code ends
end


```



2.向内存0:200~0:23F依次传送数据0~63(3FH),程序中只能使用9条指令，9条指令中包括“mov  ax,4c00h”和“int 21h”



```assembly
assume cs:code
code segment
	mov ax,0000h
	mov ds,ax
	mov bx,200h
	mov cx,64
	s : mov [bx],bl
	inc bx
	loop s
	mov ax,4c00
	int 21
code ends
end

```



正是因为每次循环，偏移量和传送的数据是相等的，所以可以省去一个变量表示传送的数据。





3.



```assembly
assume cs:code
code segment
	mov ax,cs	;cs:ip表示cpu执行指令的地址
	mov ds,ax
	mov ax,0020h
	mov es,ax
	mov bx,0
	mov cx,0fh
	s : mov al,[bx]
	mov es:[bx],al
	inc bx
	loop s
	
	mov 4c00h
	int 21h
	
code ends
end


```

