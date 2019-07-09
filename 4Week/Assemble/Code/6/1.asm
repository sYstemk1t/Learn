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