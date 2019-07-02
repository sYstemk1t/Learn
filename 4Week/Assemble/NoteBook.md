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



