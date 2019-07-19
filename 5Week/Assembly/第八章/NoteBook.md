# 数据处理问题

reg（寄存器）：ax、bx、cx、dx、al、ah、bh、bl、ch、cl、dh、dl、sp、bp、si、di

sreg（段寄存器）：ds、ss、cs、es

## bx、si、di和bp

8086CPU中，只有这4个寄存器可以用在“[...]”中进行内存单元寻址

**段寄存器可以独立使用用来寻址**

**不允许出现寄存器+寄存器的形式出现**

**在[]中使用寄存器bp，指令中没有显性给出段地址，段地址默认为ss中**





## 机器指令处理的数据在哪里

**CPU、内存、端口中存放的数据**



## 汇编语言中数据位置的表达

1.立即数(idata)

```assembly
mov ax,1
mov bx,2000h
```

2.寄存器

```assembly
mov ax,bx
mov ds,ax
push bx
mov ds:[0],ax
push ds
mov ss,ax
mov sp,ax
```

3.段地址和偏移地址

**不明确的指出是哪个段地址，默认为ds中**

```assembly
mov ax,[0]
mov ax,[bs+8]
mob ax,[bx+si+9]
;以上指令的默认段是ds
mov ax,[bp]
mov ax,[bp+si+9]
mob ax,[bp+si]
;以上指令的默认段是ss

mov ax,ds:[0]
mov ax,ds:[si+0]
mob ax,es:[bx]
mov ax,ss:[bx+si]
;以上指令的跟随显性给出的段寻址
```





## 寻址方式

8086寻址方式，段地址*10+偏移地址

![](F:\Learn\5Week\Assembly\第八章\img\0.png)





## 指令处理数据多长



8086中可以处理两种尺寸的数据，Byte和Word

```assembly
mov ax,1
mov ax,bx
mov ds,ax
mov ds:[0],ax
inc ax
;以上是字操作
mov al,10
mov al,bl
mob ds:[0],l
mov al,ds:[0]
inc al
;以上是字节操作
```



**在没有寄存器名存在的情况下，用操作符X ptr指明内存单元的长度，X在汇编中可以是Word或者Byte**

word:

```assembly
mov word ptr ds:[0],1
inc word ptr [bx]
inc word ptr ds:[0]
add word ptr [bx],2
```

byte:

```assembly
mov byte ptr ds:[0],1
inc byte ptr [bx]
inc byte ptr ds:[0]
add byte ptr [bx],2
```





## 寻址方式综合应用

```assembly
assume cs:code,ds:data,ss:stack
data segment
	db 'KFC'
	db 'KEN DE JI'
	dw 137			;38		;12
	dw 40			;70		;14	
	db 'PDP'		;'VAX'	;16
data ends
stack segment
	db 128 dup(0)
stack ends
code segment
start : 
		mov ax,stack
		mov ss,ax
		mov sp,128
		mov bx,data
		mov bs,bx
		mov bx,0
		
		mov word ptr ds:[bx+12],38
		mov word ptr ds:[bx+14],70
		
		mov si,0
		mov byte ptr ds:[bx+16+si],'V'
		inc si
		mov byte ptr ds:[bx+16+si],'A'
		inc si
		mov byte ptr ds:[bx+16+si],'X'
		
		mov ax,4c00h
		int 21h
		
code ends
end start 
```

**8086cpu提供[bx+si+idata]的寻址方式为结构化数据的处理提供了方便**

**用bx定位整个结构体，idata定位结构体中某一项，用si定位数组项中的元素**

汇编新的写法：[bx].idata	、	[bx].idata[si]





## div指令

**div是一个除法指令**

**1.除数：有8位和16位两种，在一个reg寄存器单元中**

**2.被除数：默认放在AX或者DX和AX中，如果除数位8位，被除数为16位，默认在AX中存放；如果除数为16位，被除数则为32位，在DX和AX中存放，DX中存放高16位，AX存放低16位**

**3.如果除数为8位，则AL存储除法操作的商，AH存储除法操作的余数；如果除法为16位，则AX存储除法操作的商，DX存储除法操作的余数**

![](F:\Learn\5Week\Assembly\第八章\img\2.png)







## 伪指令dd

```assembly
assume cs:code,ds:data
data segment
db 1	;字节型数据
dw 1	;字型数据
dd 1	;双字行数据
```







## dup

```assembly
assume cs:code,ds:data
data segment
	db 3 dup (0)
	db 3 dup ('abc',"abc")
```

**格式为db 次数 dup (重复的字节型数据)**



