assume cs:code
code segment
	dw 0123h,0456h,0789h,0abch,0fedh,0cbah,0987h
	mov bx,0
	mov ax,0
	mov cx,8	;ȷ��ѭ������
	
	s: add ax,cs:[bx]
	add bx,2	;bx��ż�2������ƫ�Ƶ�ַ
	loop s
	
	mov ax,4c00h
	int 21
	
code ends
end