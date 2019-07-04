# 包含多个段的程序

安全的空间：0:200-02FF,但是这个段内只有256个字节



在操作系统中，合法的通过操作系统取的空间都是安全的，因为操作系统不会让一个程序所用的空间和其他程序以及系统自己的空间相冲突



程序取得所需空间的方法：

​	1.在加载程序的时候分配

​	2.程序在执行的过程中向系统申请





## 在代码段中使用数据

```assembly
assume cs:code
code segment
	dw 0123h,0456h,0789h,0abch,0fedh,0cbah,0987h
	mov bx,0
	mov ax,0
	mov cx,8	;确定循环几次
	
	s: add ax,cs:[bx]
	add bx,2	;bx存放加2递增的偏移地址
	loop s
	
	mov ax,4c00h
	int 21
	
code ends
end

```



**dw的意思是定义字型数据**

八个字型数据，所以上面定义的字形数据占用16个字节

**定义的字型数据存放在代码段中，程序在运行的时候CS中存放代码段的段地址**



字形数据，占用为2，字节为1



所以这八个字形数据的偏移地址就是0、2、4、6、8、A、C、E处



这个程序将告诉我们如何直接指明程序的入口：



```c
assume cs:code
code segment
	dw 0123h,0456h,0789h,0abch,0fedh,0cbah,0987h
	start: mov bx,0
	mov ax,0
	mov cx,8	;确定循环几次
	
	s: add ax,cs:[bx]
	add bx,2	;bx存放加2递增的偏移地址
	loop s
	
	mov ax,4c00h
	int 21
	
code ends
end start

```



**在程序的第一条指令前面加上了一个start，而这个标号在伪指令end的后面出现**



**end的作用除了通知编译器程序结束外，还可以通知编译器的入口在什么地方**





## 在代码段中使用栈



将程序中定义的数据逆序存放

```assembly
assume cs:code
code segment
	dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
	dw,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
	;用dw定义16个字型数据，在程序加载后，将取得16个字型的内存空间，存放这16个数据，在后面的程序中将这段空间当作栈来用
	start mov ax,cs
	mov ss,ax
	mov sp,30h		;设置栈顶ss:sp指向cs:30
	
	mov bx,0
	mov cx,8
	s : push cs:[bx]
	add bx,2
	loop s			;将代码段中0-15单元中的8个字型数据依此入栈
	
	mov bx,0
	mov cx,8
	
	s0 : pop cs:[bx]
	add bx,2
	loop s0			;依此出栈8个自行数据到代码段0-15单元中
	
	mov ax,4c00h
	int 21h
	
code ends
end start			;说明程序入口在start中

```

**字型数据使用字节来存储，比如说定义了16个字型数据，使用32字节空间来存储**





## 将数据、代码、栈放入不同的段

如果数据、栈和代码需要的空间超过64KB，就不能放在一个段中（8086cpu模式的限制，一个段容量不能大于64KB）。



```assembly
assume cs:code,ds:data,ss:stack
	dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
data ends
stack segment
	dw,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
stack ends
code segment
start : mov ax,stack
		mov ss,ax
		mov sp,20h
		mov ax,data
		mov ds,ax
		mov cx,8
		s : push [bx]
		add bx,2
		loop s
		mov ax,4c00h
		int 21h
	
	code ends
	end start
		


```

**定义不同的段，需要给不同的段起段名**



程序中有多个段的时候，通过地址访问，地址包含段地址和偏移地址。

**段名相当于一个标号，它代表了段地址**



在8086cpu中，不允许将一个数值送入段寄存器中，必须使用通用寄存器做中继



**我们所自定义出来的标号，只是为了我们阅读方便，在源程序中，cpu并不知道他们**



```assembly
assume cs:b,ds:a,ss:c
a segment 
	dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
a ends

c segment
	dw,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
c ends

b segment
	d : mov ax,c
	mov ss,ax
	mov sp,20h
	mov ax,a
	mov ds,ax
	mov bx,0
	mov cx,8
	s : push [bx]
	add bx,2
	loop s
	
	mov bx,0
	mov cx,8
	
	s0 : pop [bx]
	add bx,2
	loop s0
	
	mov ax,4c00h
	int 21h

b ends
end d
```



**虽然我们在data段和stack段中只定义初始化了4个字节的内存，但在汇编中，直接给你分配了16个字节的空间，不足的按00补全。**

