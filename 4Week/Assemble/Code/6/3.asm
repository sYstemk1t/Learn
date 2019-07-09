assume cs:code,ds:data,ss:stack
data segment
    dw 0123h,0456h,0789h,0abch,0defh,0fedh,0cbah,0987h
data ends

stack segment
    dw 0,0,0,0,0,0,0,0
stack ends

code segment
start:
    mov ax,stack       
    mov ss,ax
    mov sp,16          ;将逻辑上设置的栈段真正设为栈段区域

    mov ax,data          ;设置数据区域段地址
    mov ds,ax

    push ds:[0]
    push ds:[2]
    pop ds:[2]
    pop ds:[0]

    mov ax,4c00h
    int 21h

code ends
end start