# 转移指令原理

**可以修改IP，或同时修改CS和IP的指令统称为转移指令**

8086cpu的转移行为有以下几类：

​	只修改IP时，称为段内转移，比如：jmp ax

​	同时修改CS和IP时，称为时间转移，比如：jmp 1000:0



由于转移指令对IP的修改范围不同，段内转移又分为：短转移和近转移

​	短转移IP的范围范围是-128~127

​	近转移IP的修改范围是-32768~32767



8086CPU的转移指令分为以下几类：

​	无条件转移指令（如：jmp）

​	条件转移指令

​	循环指令

​	过程

​	中断



## 操作符offset

**offset的功能是取得标号的偏移地址**



```assembly
assume cs:code
code segmnet
	start : mov ax,offset start
			s : mov ax,offset s

code ends
end start
```





问题9.1：

```assembly
assume cs:code
code segment
	s: 	mov ax,bx		;占用两个字节，一个字
		mov si,offset s
		mov di,offset s0
		mob dx,cs:[si]
		mov cs:[di],dx
	s0:	nop				;nop机器码占一个字节
		nop
		
		mov ac,4c00h
		int 21h

code ends
end start

```





## jmp指令

jmp为无条件跳转指令，可以修改ip，也可以同时修改cs和ip

jmp需要给出两种信息：

​	1.转移的目的地址

​	2.转移的距离(段间转移、段内短转移、段内近转移)







jmp原理

**1.cpu从cs：ip读取指令，将指令放入指令缓存器中**

**2.ip = ip + 所读指令的字节数**

**3.执行指令缓存器中的内容，回到第一步**



**标号处地址 - jmp指令后的第一个字节的地址**







## 依据位移进行转移指令的jmp指令



```assembly
jmp far ptr 	;段间转移	-32768~32767
jmp short ptr	;短转移	-128~127
```



jmp short 标号的功能是：(ip)=(ip)+8位位移

​	1.8位位移=标号处的地址-jmp指令后的第一个字节的地址

​	2.short指明此处的位移为8位位移

​	3.8位位移的范围为-128~127，用补码标识

​	4.8位位移由编译程序在编译时算出







## jmp 段间转移

**“jmp far ptr 标号”实现的是段间转移，又称为远转移：**

**cs=标号所在段的段地址；ip=标号在段中的偏移地址**

**far ptr 指明了指令用标号的段地址和偏移地址修改cs和ip**

```assembly
assume cs:code 
code segment
	start : mov ax,0
			mov bx,0
			jmp far ptr s
			db 256 dup (0)
			s : add ax,1
			inc ax
			mov ax,4c00h
			int 21h
code ends
end start 
```

![](F:\Learn\5Week\Assembly\第九章\img\0.png)

jmp处的机器码：高地址是转移的段地址；低地址是偏移地址 







## 寄存器转移指令



```assembly
assume cs:code 
code segment
	mov ax,2222
	jmp ax
	mov ax,4c00h
	int 21h
code ends
end
```











## 转移指令在内存中的jmp



**jmp word ptr 内存单元地址（段内转移）**

**功能：从内存单元地址处存放着一个字，是转移的目的偏移地址**

```assembly
mov ax,0123h
mov ds:[0],ax
jmp word ptr ds:[0]
;执行后，ip = 0123h

mov ax,0123h
mov [bx],ax
jmp word ptr [bx]
;仔细阅读了上面的书应该知道，除了bp以前，所有的默认段寄存器都是ds
```



**jmp dword ptr 内存单元地址(段间转移)**

**从内存单元地址处开始存放着两个字，高地址处的字是转移的目的段地址，低地址处是转移的目的偏移地址**

**cs = (内存单元地址 + 2)；ip = （内存单元地址）**



```assembly
mov ax,0123h
mov ds:[0],ax
mov word ptr ds:[2],0
jmp dword ptr ds:[0]
;执行后，cs=0，ip=0123h，cs:ip = 0000:0123
```







## 条件转移指令jcxz

**jmp为无条件跳转指令**

**jcxz为条件跳转指令**

```assembly
if cx == 0 
jcxz 标号
```



**jcxz为短转移指令，范围只可以是-128~127**











## 根据位移进行转移

**jmp short 标号**

**jmp near ptr 标号**

**jcxz 标号**

**loop 标号**

**jmp 2000:0100	;debug中的指令，汇编语言不认识**

## loop指令

类似循环

```assembly
s : mov cx,10	;先检测cx的值是不是0
	add ax,1
	loop s
;上面的程序执行的结果就是ax累加1
	

```





