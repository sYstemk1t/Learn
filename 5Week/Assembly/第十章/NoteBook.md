# CALL和RET指令

call和ret指令都是转移指令，它们都修改ip，或同时修改cs和ip。

 





## ret和retf

**pop : sp + 2**

**push : sp - 2**

 

ret称为近转移，它只修改ip

retf称为段间转移，它修改了cs和ip

```assembly
assume cs:code,ss:stack
stack segment
	db 128 dup (0)
stack ends


code segment
	mov ax,4c00h
	int 21h
start :
	mov ax,stack
	mov ss,ax
	mov sp,128
	mov ax,0
	push ax
	mov bx,0
	ret		;这条指令执行后，ip = 0000

code ends
end start
```



![](F:\Learn\5Week\Assembly\第十章\img\0.png)





```assembly
assume cs:code,ss:stack
stack segment
	db 128 dup (0)
stack ends


code segment
	mov ax,4c00h
	int 21h
start :
	mov ax,stack
	mov ss,ax
	mov sp,128
	mov ax,0
	push cs		;这条指令执行后，ip = cs的值，
	push ax
	mov bx,0
	retf		;cs=0000

code ends
end start
```



![](F:\Learn\5Week\Assembly\第十章\img\1.png)



## call指令



**CPU执行call指令时，进行两部操作：**

**1.将当前的IP或者CS和IP压入栈中**

**2.转移**

**call不能实现短转移，除此之外，call指令实现转移的方法和jmp指令原理相同**





## call指令转移

**1.cs：ip读取指令放入指令缓存器**

**2.ip = ip + 所读指令的字节数**

**3.执行指令，回到第一步**

 

```assembly
assume cs:code,ss:stack
stack segment
	db 16 dup (0)
stack ends

code segment
	start : 
		mov ax,ss
		mov ax,0
		call s1
	s1:
		mov bx,1234h
		inc bx
		call s2
	s2:
		mov ax,offset s1
		inc ax
		mov ax,4c00h
		int 21h
code ends
end start 
```







![](F:\Learn\5Week\Assembly\第十章\img\4.png)





## jmp与call不同点

**jmp直接位移，并不需要考虑其他的**

**call也是位移，但是中间多了一层push ip**



**cs：ip读取指令放入指令缓存器**

**ip = ip + 所读指令字节数**

**指令缓存器中的内容，回到第一步**



```assembly
内存地址	机器码		汇编指令
1000:0		B8 00 00	mov ax,0
1000:3		E8 01 00 	call s			;这里做了一个push ip,这里的ip是6
1000:6		40			inc ax			;call指令绕过了这条指令，不执行
1000:7		58			s : pop ax		;ax = 6

```



**jmp不会操作push**







## call far ptr标号

这条指令展开的写法：

```assembly
call far ptr 标号 	;展开如下
push cs
push ip
jmp far ptr 标号
```







## jmp reg





```assembly
mov ax,6
call 6	;相当于把ip进行改变

```





![](F:\Learn\5Week\Assembly\第十章\img\6.png)







## 转移指令在内存中

jmp word ptr ds:[0]			;ip = ds:[0]

call word ptr ds:[0]			; ip = ds:[0]

指向上面的命令之前，首先需要**push ip**

**然后jmp word ptr 内存单元地址**

**配合ret使用**



call dword ptr ds:[0]		;ip = ds:[0]		ds = ds:[2]

执行上面的命令之前，首先

**push cs**

**push ip**

**jmp dword ptr 内存单元地址**

**配合retf使用**









## call指令和ret指令



call指令并不是单纯的位移，它还会执行一条指令:**push ip**







## mul乘法指令

8bit

```assembly
mul al
mul byte ptr ds:[0]

```



16bit

```assembly
mul ax
mul word ptr ds:[0]
```





