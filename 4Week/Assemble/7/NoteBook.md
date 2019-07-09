# 定位内存地址方法

## and和or指令



and指令：逻辑与指令，按位进行与运算。

```assembly
mov al,01100011B
and al,00111011B
```

执行后，结果等于al = 00100011B

**逻辑与运算：参与运算的两个表达式都为真时，结果才为真，否则为假**

**1为真，0为假**





or指令：逻辑或指令，按位进行或运算

```assembly
mov al,01100011B
or al,00111011B
```

执行后：al = 01111011B

**逻辑或运算：参与运算的两个表达式，只有有一个为真，即为真**



## Ascii码

![](F:\Learn\4Week\Assemble\7\img\1.png)





## 字符形式给出的数据

在汇编语言中，用'...'的方法指明数据是以字符的形式给出的。

```assembly
assume cs:code,ds:data
data segment
	db 'unIX'
	db 'foRK'
data ends

code segment
start : mov al,'a'
		mov bl,'b'
		mov ax,4c00h
		int 21h

code ends
end start
```

![](F:\Learn\4Week\Assemble\7\img\2.png)



data段的地址是0b8a，所以程序从0b9a开始执行，data段是程序中的第一个段，它就在程序的起始处，所以它的段地址为0b9a;



d命令查看，可以看到我们刚才保存的数据以16进制数码和ASCII码方式保存了。



![](F:\Learn\4Week\Assemble\7\img\3.png)









## 大小写转换



```assembly
assume cs:code,ds:data
data segment
	db 'BaSiC'
	db 'iNfOrMaTiOn'
data ends

code segment
start :mov ax,data	;设置ds指向data段
	mov ds,ax	
	mov bx,0	;设置bx=0,ds:bx指向'BaSiC'的第一个字母
	mov cx,5	;循环次数
	s : mov al,[bx]		;将ascii码从ds:bx所指向的单元中取出
	and al,11011111B	;将al中的ascii码的第5位置为0，变为大写字母
	mov [bx],al;		;将转换后的ascii码写回原来的单元
	inc bx				;bx+1,ds:bx指向下一个字母
	loop s
	mov bx,5			;设置bx=5，ds:bx指向'iNfOrMaTiOn'中的第一个字母
		
	mov cx,11			;循环11次，因为iNfOrMaTiOn有11个字母
	
	s0 : mov al,[bx]	
	or al,00100000B
	mov [bx],al
	inc bx
	loop s0
	

	mov ax,4c00h
	int 21h

code ends
end start
		
code ends
end start
```



![](F:\Learn\4Week\Assemble\7\img\4.png)

ascii码中，从第5位开始，区分大小写的。



## [bx+idata]

```assembly
mov ax,2000
mov ds,ax
mov bx,1000
mov ax,[bx]
mov cx,[bx+1]
mov cx,[bx+2]

```

![](F:\Learn\4Week\Assemble\7\img\5.png)





## 用[bx+idata]的方式进行数组处理

```assembly
assume cs:code,ds:data
data segment
	db 'BaSiC'
	db 'MinIX'
data ends

code segment
start :mov ax,data	;设置ds指向data段
	mov ds,ax	
	mov bx,0	;设置bx=0,ds:bx指向'BaSiC'的第一个字母
	mov cx,5	;循环次数
	s : mov al,[bx]		;将ascii码从ds:bx所指向的单元中取出
	and al,11011111B	;将al中的ascii码的第5位置为0，变为大写字母
	mov [bx],al;		;将转换后的ascii码写回原来的单元
	inc bx				;bx+1,ds:bx指向下一个字母
	loop s
	mov bx,5			;设置bx=5，ds:bx指向'iNfOrMaTiOn'中的第一个字母
		
	mov cx,11			;循环11次，因为iNfOrMaTiOn有11个字母
	
	s0 : mov al,[bx]	
	or al,00100000B
	mov [bx],al
	inc bx
	loop s0
	

	mov ax,4c00h
	int 21h

code ends
end start
		
code ends
end start
```

这个程序实现了将data中定义的第一个字符串转换为大写，第二个字符串转换为小写



```assembly
assume cs:code,ds:data
data segment
	db 'BaSiC'
	db 'MinIX'
data ends
code segment
start : mov ax,data
		mov ds,ax
		mov bx,5
		mov cx,5
		s : mov al,[bx]		;定位第一个字符串中的字符
		and al,11011111B
		mov [bx],al
		mov al,5[bx]		;定位第二个字符串中的字符
		or al,00100000B
		mov 5[bx],al
		
		inc bx
		loop s
		
		mov ax,4c00h
		int 21h

code ends
end start
```



这点和c语言有相似

c语言:a[i],b[i]

汇编语言:0[bx],5[bx]





## SI和DI

si和di和8086cpu中和bx功能相近的寄存器，si和di不能分成两个八位寄存器来使用。

```assembly
mov bx,0
mov ax,[bx]

mov si,0
mov ax,[si]

mov di,0
mov ax,[di]

mov bx,0
mov ax,[bx+123]

mov si,
mov ax,[si+123]

mov di,0
mov ax,[di+123]
```



问题：7.2



```assembly

assume cs:code,ds:data
data segment
	db 'welcome to masm'
	db '................'
data ends

code segment
start : mov ax,data
		mov ds,ax
		mov sl,0
		mov cx,8
		s : mov ax,[si]
		mov [di],ax
		add si,2
		add di,2
		loop s
		
		mov ax,4c00h
		int 21h
		
code ends
end start
```



问题7.3

```assembly

assume cs:code,ds:data
data segment
	db 'welcome to masm'
	db '................'
data ends

code segment
start : mov ax,data
		mov ds,ax
		mov sl,0
		mov cx,8
		s : ax,0[si]
		mov 16[si],ax
		add si,2
		loop s
		
		mov ax,4c00h
		int 21h
		
code ends
end start
```



![](F:\Learn\4Week\Assemble\7\img\6.png)



## [bs+si]和[bs+di]



```assembly
assume cs:code
code segment
    mov ax,2000h
    mov ds,ax
    mov bx,1000h
    mov si,0
    mov ax,[bx+si]
    inc si
    mov cx,[bx+si]
    inc si
    mov di,si
    add cx,[bx+di]
    mov ax,4c00h
    int 21h
code ends
end
```



![](F:\Learn\4Week\Assemble\7\img\7.png)





## [bx+si+idata]和[bx+di+idata]



1.[idata]用一个常量来表示地址，可用于直接定位一个内存单元

2.[bx]用一个变量来表示内存地址，可用于间接定位一个内存单元

3.[bx+idata]用一个变量和常量表示，可在一个起始地址的基础上用变量间接定位一个内存单元

4.[bx+si]用两个变量表示地址

5.bx[bx+si+idata]用两个变量和一个常量表示地址





问题7.6

```assembly
assume cs:code,ds:data
data segmnet
	db '1. file'
	db '2. eile'
	db '3. search'
	db '4. view'
	db '5. options'
	db '6. help'
data ends


code segment
start :mov ax,data
		mov ds,ax
		mov bx,0
		mov cx,6	;循环6次
		
		s : mov al,[bx+3]	;改变6行，第3列的字符串
		and al,11011111B
		mov [bx+3],al	
		add bx,16	;跨越整个字符串，这个字符串中字符串最大16
		loop s
		
		mov ax,4c00h
		int 21h
		
code ends
end start
```





问题7.7

```assembly
assume cs:code,ds:data
data segment
	db 'ibm            '
	db 'dec            '
	db 'dos            '
	db 'vax            '
data ends
code segment
start : mov ax,data
		mov ds,ax
		mov bx,0
		mov cx,4
		s : mov si,0
		mov cx,3
		s0 : mov al,[bx+si]
		and al,11011111B
		inc si
		loop s0
		add bx,16
		loop s
		mov ax,4c00h
		int 21h

code ends
end start
```

7.8

```assembly
assume cs:code ,ds:data ,ss:stack
data segment
	db '1. file'
	db '2. eile'
	db '3. search'
	db '4. view'
	db '5. options'
	db '6. help'
data ends
stack segment
dw 0,0,0,0,0,0,0,0	;定义一个段，用来坐栈段，容量为16个字节
stack ends

code segmnet
start : mov ax,stack
		mov ss,ax
		mov sp,16
		mov ax,data
		mov ds,ax
		mov bx,0
		mov cx,4
		s0 : push cx	;将外层循环的cx值压栈
		mov si,0
		mov cx,3	;cx设置外层循环
		
		s: mov al,[bx+si]	;
		and al,11011111B
		mov [bx+si],al
		loop s
		add bx,16
		pop cx
		mov ax,4c00h
		int 21h
		
code ends
end start 

```





7.9

```assembly
assume cs:code ,ss:stack ,ds:data
stack segment
	dw 0,0,0,0,0,0,0,0
stack ends

data segment
	db '1. display      '
	db '2. brows        '
	db '3. replace      '
	db '4. modify       '
data ends


code segment
	start :
		mov ax,stack
		mov ss,ax
		mov sp,16
		
		mov ax,data
		mov ds,ax
		mov bx,0
		
		mov cx,4
		
		s0 : push cx
		mov si.3
		
		mov cx,4
		s : mov al,[bx+si]
		and al,11011111B
		mov [bx+si],al
		inc si
		loop s
		
		add bx,16
		pop cx
		loop s0
		
		mov ax,4c00h
		int 21h

code ends
end start
```

