# 标志寄存器

CPU内部的寄存器中，有一种特殊的寄存器（对于不同的处理机，个数和结构都可能不同）

**1.用来存储相关指令的某些指令结果**

**2.用来为cpu执行相关指令提供行为依据**

**3.用来控制cpu的相关工作方式**



flag寄存器和其他寄存器不一样，其他寄存器是用来存放数据的，都是整个寄存器具有一个含义，**而flag寄存器是按位起作用，每一位都有专门的含义**



**CF、PF、ZF、SF、OF、DF标志位**



**flag的1、3、5、12、13、14、15位在8086CPU中没有使用，不具有含义**



![](F:\Learn\5Week\Assembly\第十一章\img\3.png)



![](F:\Learn\5Week\Assembly\第十一章\img\1.png)



## ZF标志



flag的第6位是ZF，零标志位。它记录相关指令执行后，其结果是否为0.

**如果结果为0，zf为1，如果结果不为0，zf为0**



**运算指令是会影响标志寄存器的**





## PF标志

flag第2位为PF，奇偶标志位。它记录相关指令执行后，其结果的所有bit位中1的个数是否为偶数。如果1的个数为偶数，pf=1，如果为奇数，pf=0





## SF标志

flag的第七位是SF，符号标志位。它记录相关指令执行后，其结果是否为负，如果结果为负，sf=1，如果非负，sf=0



 

## CF标志

flag第零位是CF，进位标志位。一般情况下，在进行无符号数运算的时候，它记录了运算结果的最高位有效位向更高位的进位值，或从更高位的借位值

在前面的运算中，我们说的两个8位寄存器寄存器进行相加，如果有进位，将进位丢弃，其实并没有丢弃，它将这个进位送进了CF标志位进行保存









## OF标志

有符号数：-128~127		;字节类型

有符号数:  -32768~32767	;字型数据

**如果运算超过了机器所能表达的范围，就会产生溢出**



**CF是对无符号数运算有意义的标志位，OF是对有符号数运算有意义的标志位**









## ADC指令与SBB指令

**ADC指令**

```assembly
![2](F:\Learn\5Week\Assembly\第十一章\img\2.png)
assume cs:code,ds:data
data segment
	dw 128 dup (0)
	
data ends

code segment
	call add_128
	mov ax,4c00h
    int 21h
    
 
 
add_128:
	push ax
	push bx
    push si
    push di
    
    sub ax,ax	;将cf设置为0
    
    mov cx,8
    
s: 	mov ax,ds:[si]
	abc ax,ds:[di]		;ds:[si]中的数据与ax中的数据相加，然后将进位存入CF标志位中
	mov ds:[si],ax
	inc si
	inc si
	inc di
	inc di
	loop s
	
	pop di
	pop si
	
	pop bx
	pop ax
	
	
	ret 
	



```





**SBB指令**



```assembly
debug 模式下：
mob dx,1000
mov ax,0005
sub ax,6
sbb dx,6	;会将进位减掉
```



![](F:\Learn\5Week\Assembly\第十一章\img\2.png)





## cmp指令

**cmp是比较指令，cmp的功能相当于减法指令，只是不保存结果，但是会对标志位产生影响**





```assembly
cmp ax,bx
ax = bx 	;zf = 1	
ax != bx 	;zf = 0
ax < bx		;cf = 1
ax >= bx 	;cf = 0

ax > bx		;cf = 0 && zf = 0
ax <= bx	;cf = 1 || zf = 1

```



## ## 跳转指令

```assembly
指令			含义						检测的相关标志位
je	 标号 	等于则转移					zf = 1
jne  标号		不等于则转移					zf = 0
jb	 标号		低于则转移					cf = 1
jnb	 标号		不低于则转移					cf = 0
ja	 标号		高于则转移					cf = 0 || zf = 0
jna	 标号		不高于则等于					cf = 1 && zf = 1
```

**跳转范围-128~127**









## DF标志和串传送指令



flag的第10位是DF，方向标志位。在串处理指令中，控制每次操作后si和di的增减

**df = 0	每次操作后si、di递增**

**df = 1	每次操作后si、和di递减**



```assembly

assume cs:code,ds:data,ss:stack
data segment
	db 16 dup (0)
data ends
code segment
	mov ax,0f000h
	mov ds,ax
	mov si,0ffffh
	mov ax,data
	mov es,ax
	mov di,15
	mov cx,16
	std
	rep movsb			




```





**movsb：movsb的功能是将ds:si指向的内存单元中的字节送入es:di中，然后根据标志寄存器df的值，将si和di递减或者递增**	；字节

**movsw：movsw的功能是将ds:si指向的内存单元中的字型数据送入es:di中，然后根据标志寄存器df的值，将si和di递减或者递增**	；字



**rep指令的作用是根据cx的值，重复执行后面的串传送指令。由于每执行一次movsb或movsw指令si和di都会递减或递增到前一个或后一个单元，则rep movsb就可以循环实现(cx)个字符的传送**



**cld指令：将标志寄存器的df位置为0**

**std指令：将标志寄存器的位置为1**









## pushf和popf



**pushf是将标志位寄存器中的内容送入栈中**

**popf是将标志位寄存器中的内容从栈中取出**







