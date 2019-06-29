1.根据下面给出的声明和数据，对每个表达式进行求值并写出它的值。在对每个表达式进行求值时使用原先给出的值（也就是说，某个表达式的结果不影响后面的表达式）。假定ints数组在内存中的起始位置是100,整型值和指针的长度都是四个字节。

```c
int ints[20] = {10, 20, 30, 40, 50,
                60, 70, 80, 90, 100,
                110,120,130,140,150,
                160,170,180,190,200};
(other declarations)
int *ip = ints + 3;
```



2.表达式array[i+j]和i+j[array]是不是相等？

不相等，因为他们的优先级不同



3.下面的声明试图按照从1开始的下标访问数组data，它能行吗？

赋值非法，这个指针尝试访问数组的第一个前一位。



4.

```c
char buffer[SIZE];
    char *front,*rear;
    front = buffer;
    rear = buffer;
    while(*rear != '\0')
        rear++;
    rear--;
    while(front < rear){
        if(*front != *rear)
            break;
        front++;
        rear--;
    }
    if(front >= rear){
        printf("It is a palindrome\n");
    }

```



5.指针在效率上可能强于下标，这是使用它们的动机之一，那么什么时候使用下标是合理的，尽管它可能在效率上有所损失？

数组的时候用下标



6.因为我对汇编代码看懂的也不多...

```c
#define SIZE 50
int x[SIZE];
int y[SIZE];
int i;

void
try1()
{
    for(i = 0; i < SIZE; i++){
        x[i] = y[i];
    }
}


```

这个是c语言的代码

这个其实困扰了挺久的，因为没有mian函数，xp里的debug无法使用

然后用linux下的gcc实现的

```assembly
	.file	"1.c"
	.text
	.comm	x,200,32
	.comm	y,200,32
	.comm	i,4,4
	.globl	try1
	.type	try1, @function
try1:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, i(%rip)
	jmp	.L2
.L3:
	movl	i(%rip), %eax
	movl	i(%rip), %ecx
	cltq
	leaq	0(,%rax,4), %rdx
	leaq	y(%rip), %rax
	movl	(%rdx,%rax), %edx
	movslq	%ecx, %rax
	leaq	0(,%rax,4), %rcx
	leaq	x(%rip), %rax
	movl	%edx, (%rcx,%rax)
	movl	i(%rip), %eax
	addl	$1, %eax
	movl	%eax, i(%rip)
.L2:
	movl	i(%rip), %eax
	cmpl	$49, %eax
	jle	.L3
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	try1, .-try1
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"
	.section	.note.GNU-stack,"",@progbits


```





7.





8.





9.int coin_values[] = {1,2,5,10,20,25,50,100};



10.

```c
int array[4][2];

```



array                        1000

array+2                    1008

array[3]                    1012

array[2]-1                 1006

&array[1][2]              1008

&array[2][0]              1008



11.

array　　　　　　　　　　 　1000                        int (*x)[2][3][6]

array+2                     1288                       int (*x)[2][3][6]

array[3]                    1432                       int (*x)[3][6]

array[2]-1                  1216                      int (*x)[3][6]

array[2][1]                  1360                      int (*x)[6]

array[1][0]+1                1168                      int (*x)[6] 

array[1][0][2]               1192                    int *x;

array[0][1][0]+2              1080                    int *x;

array[3][1][2][5]            can't tell               int x;

&array[3][1][2][5]           1572                     int *x;



12.

这个和堆栈的进栈和压栈一样



13.

*array                                                          array[0]

*(array+2)                                                    array[2]

*(array+1)+4                                                array[1]+4

*(*(array+1)+4)                                            array[1][4]

*(*(*(array+3)+1)+3)                                    array[3][1][3]

*(*(*array+1)+2)                                          array[0][1][2]

*(**array+2)                                                 array[0][0][2]

**(*array+1)                                                 array[0][1][0]

***array                                                       array[0][0][0]

 

14.

```c
int array[10][20];
int (*i)[20];
i = array[3,4];

```

15.

```c
unsigned int which;
int array[SIZE];

```

//unsigned是重点，是无符号数字

```c
if(array[whilch] == 5 && which < SIZE)
if(which < SIZE && array[which] == 5)

```



16.

第一个是array作为函数传递的值

第二个是定义的并且没有赋值



17.

void function(int const a,int const b[])

第一个const是给一个变量

第二个const是给一个数组



第一个是一个变量，只是简单的拷贝

第二个是一个数组，传递的值应该为指针，就算写了const，也是可以修改的



大家应该学过一句，形参的修改并不影响实参，在c语言中，既然写了const，也是可以通过指针进行修改的

```c
int swap_p(const int *a, const int *b)
{
	int *c;
	c = a;
	a = b;
	b = c;
	printf("%d\r\n", a);
	printf("%d\r\n", b);
	return a, b;
}
int main()
{
	const int a = 10;
	const int b = 20;
	swap_p(a, b);
}

```

这个例子不完整，因为main函数里的实参并没有得到改变...



18

```c
void function(a[][2][5]);

```





19.

```c
#include <stdio.h>

int
lookup_keyword(char const * const desired_word,
               char const *keyword_table[],int const size)
{
    char const **kwp;
    for(kwp = keyword_table; kwp < keyword_table + size; kwp++)
        if(strcmp(desired_word,*kwp) == 0)
            return kwp - keyword_table;

    return -1;
}



char const *keyword[] = {
        "do"
        "for"
        "if"
        "register"
        "return"
        "switch"
        "while"
        NULL
};

```



