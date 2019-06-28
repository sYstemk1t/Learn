# 指针与数组

**指针是一种保存变量地址的变量。**



## 指针与地址

同样的机器都有一系列连续标号或者编址的存储单元和谐存储单元可以单个进行操纵，也可以以连续程序的方式操作。

通常情况下，机器的一个字节可以存放一个char类型的数据，两个相邻的字节存储单元可以存储一个short（短整形，放在内存中是字）类型的数据。而4个相邻的字节存储单元可以存储一个long（长整形）类型的数据。指针是可以存放一个地址的一组存储单元（通常是两个字，四个字节）,

```c

int c = 10;
int *p = NULL;	//定义的指针的最好初始化一下
p = &c;

```

这个时候的p等于多少呢？

p = 10;

**取地址运算符&只能用于内存中的对象，即变量与数组元素，不能用于表达式、常量或者register类型的变量**

**register是将变量放入cpu内部寄存器**



一元运算符*是间接寻址引用运算符，当它作用于指针时，将访问指针锁指向的对象。



```c
int x = 1;
int y = 2;
int z[10];	//数组也可以不初始化，但是必须写明数组有多少元素
int *ip;	//定义了一个指针
ip = &x;
y = *ip;
*ip = 0;
ip = &z[0];

```



**指针只可以指向某种特定的数据类型**

**void指针也称为无类型指针，可以存放指向任意类型的指针，但是它不能简介引用其自身**

***和++这样的一元运算符遵循从左往右的结合顺序**



由于指针也是变量，所以再程序中可以直接引用，而不需要通过简介引用的方法。





## 指针与函数参数

由于c语言是以船只的方式将参数值传递给被调用函数，因此被调函数不可以直接修改主调函数的值，

```c
void swap(int a, int b)
{
	int c;
	c = a;
	a = b;
	b = c;
	printf("%d\r\n", a);
	printf("%d\r\n", b);
}

int main()
{
	int i = 10;
	int j = 20;
	swap(i, j);
	system("pause");
}

```



上面的代码就实现了将传递的参数进行调换，但是书上给我们说的是需要修改主调函数中的值，我们再去main函数中打印两个变量的值，这个时候发现，他们两个并没有什么变化。

这个时候我们就可以用指针来实现

```c
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
}

int main()
{
	int i = 10;
	int j = 20;
	swap(&i, &j);	//指针传递的时候，变量名前面需要加取地址符号
	printf("%d\r\n", i);
	printf("%d\r\n", j);
	system("pause");
}

```



**循环调用getint函数给一个整形数组赋值**

解释一下getint函数的作用，getint将输入的字符流分解成证书，且每次调用得到一个整数，getint需要返回将转换后得到的数，并且，再到达输入结尾时要返回文件结束标记。

isspace函数的作用，isspace判断输入字符是否为空格、回车、制表符等



getch()是从缓冲区中无回显地读字符

ungetch()是把一个字符退回到键盘缓冲区中





习题5-1、5-2非独立完成







## 指针与数组

声明一个数组

int a[10];	//声明一个数字，里面存放的10个整形数据

声明一个指针

int *p;	//声明一个整形的指针

赋值

p = &a[0];	//数组名就是数组的第一个元素

赋值

int x;

x = *p;	//指针中，加‘*’代表取内容



**数组名代表的就是该数组最开始的第一个元素**



**指针是一个变量**

```c
int strlen(char *s)
{
	int n;
	for (n = 0; *s != '\0'; s++)	//s++代表指向字符串的下一个
	{
		n++;	//n是计数器，满足条件，n就+一次
	}
	return n;
}
int main()
{
	int i;
	int j;
	int o;
	char s[100] = "hello,wolrd";
	char *c = "学c真难";
	i = strlen("你好，世界");
	j = strlen(s);
	o = strlen(c);
	printf("%d\r\n", i);
	printf("%d\r\n", j);
	printf("%d\r\n", o);
	system("pause");
	return 0;
}

```



在函数的定义中：

```c
char c[100] = "xxxx";
char *c = "xxxx";

```

他们的定义出来的功能是不一样的。





## 地址算术运算

实现一个strlen

```c
int strlen_len(char *s)
{
	char *p = s;
	int i = 0;	//检查计数器
	while (*p != '\0')
	{
		i++;
		p++;	//代表下一个位置
	}
	return i;

}

int main()
{
	int i;
	i = strlen_len("hello");
	printf("%d\r\n", i);
	system("pause");
	return 0;
}


```

书上写的意思是，首先先用一个*p指向这个字符数组，然后使用while循环进行检查（“\0是字符串的结尾”）,最后返回的时候，因为本来指针变量p指向s这个字符数组的时候，它的自身已经是5了，所以返回的时候需要减去这个5



上面程序使用了一个c语言里经常使用的malloc和free，通过检查内存的方式来帮助增强记忆



如果要做任何指针的之间的运算，必须是同类型之间的，如果不同类型，可以进行类型的强制转换



## 字符指针和函数

**字符串常量是一个字符数组**

```c
printf("Hello Wolrd");

```

查看一下他的函数实现

![](D:\Learn\3Week\C\5\img\1.png)

可以看到，他最后也是通过一个char指针访问字符串的。



```c
char amessage[] = "nw is the time";
char *pmessage = "now is teh time";

```

上面的这两个定义有很大的区别的，amessage是仅仅声明了一个初始化字符串以及空字符'\0'的一维数组，数组中的每个字符可以单独修改，但是amessage始终指向同一个存储位置。



但是pmessage是一个指针，指向一个字符串常量，之后它可以指向任意位置。



### strcpy

strcpy(x,t)，把指针t指向的字符串复制到指针s指向的位置。实际上实现的是指针的拷贝，而并没有复制字符串。

数组的方法实现strcpy

```c
void strcpy(char *s,char *t)
{
	int i = 0;	
    while((s[i] = t[i]) != '\0')
    {
        i++;	//下标加1
    }  
}

```

指针的方法实现strcpy

```c
void strcpy(char *s,char *t)
{
    int i = 0;
    while((*s[i] = *t[i]) != '\0')
    {
        i++;
    }  
}

```

因为参数都是值传递的，所以在strcpy函数中可以以任何方式使用参数s和t；

然后我们实现strcmp

strcmp的函数实现就是对比两个字符串中的数据是否一直

```c

int strcmp_cmp(char *t, char *s)
{
	int i = 0;
	while (s[i] == t[i] != '\0')
	{
		i++;
		if (t[i] == '\0')	//检查到最后一位
		{
			return 0;
		}	//如果跳出了这层循环，证明已经不当等了，就拿当前i对应的值做比较
	}
	if (s[i] > t[i])
	{
		return 1;
	}
	else
	{
		return -1;
	}	
}


int main()
{
	
	char a[] = "iamstudent";
	char c[] = "iamteacher!";
	int i;
	i = strcmp_cmp(a, c);
	printf("%d\r\n", i);
	system("pause");
}

```

我对题目理解错了，修改后的程序

```c

int strcmp_cmp(char *t, char *s)
{
	int i = 0;
	while (s[i] == t[i] != '\0')
	{
		i++;
		if (t[i] == '\0')	//检查到最后一位
		{
			return 0;
		}	//如果跳出了这层循环，证明已经不当等了，就拿当前i对应的值做比较
	}
	return s[i] - t[i];
}


int main()
{
	
	char a[] = "iamstudent";
	char c[] = "iamteacher!";
	int i;
	i = strcmp_cmp(a, c);
	printf("%d\r\n", i);
	system("pause");
}

```







### 进出栈标准用法

*p++ = val	//将val压入栈

val = *--p	//将栈顶元素弹出到val中





## 指针数据以及指向指针的指针

**函数的运行速度vs2013中看不出来**

**这道题也不是很会**



## 多维数组

前面我们说过了一维数组，但是也可以有二维数组，甚至多维数组，比如打游戏的时候的地图，就是三维数组。

判断年份的问题：

```c
#include <stdio.h>
static char daytab[2][13] = {
	{ 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 },	//非闰年
	{ 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }	//闰年
};

int day_of_year(int year, int month, int day)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;	//判断是否闰年
	for (i = 1; i < month; i++)
		day += daytab[leap][i];		//循环加，加到传递的月份，然后计算
	return day;
}

void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int i, leap;
	leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	for (i = 1; yearday > daytab[leap][i]; i++)
		yearday -= daytab[leap][i];
	*pmonth = i;
	*pday = yearday;
}

int main()
{
	int m, d;
	int i = day_of_year(2019, 6, 26);
	month_day(2019, 177, &m, &d);
	printf("%d\r\n", i);
	printf("月：%d日：%d\r\n", m, d);
	system("pause");
}

```



## 指针数组的初始化



```c
char *month_name(int n)
{
    static char *name[] = {
        "zhangsan",
        "lisi",
        "wangmazi",
     
    }
}

```

这个时候的name和上序的例子一样，是一个一维数组，数组的元素为字符指针。



## 指针与多维数组

```c
int a[10][20];	//代表有200的int
int *b[10];	//仅仅分配了10个指针，并且未初始化

```

指针数组的好处就是：数组的每一行长度可以不同，b的每个元素不必指向具有常量的具体个数。

```c
char *name = {"zhang","wang","li","zhao"};

```

![](D:\Learn\3Week\C\5\img\2.png)

如果使用二维数组就是这样的

![](D:\Learn\3Week\C\5\img\3.png)

有没有发现，如果二维数组每一个元素都是同等大小的话，中间就不会有任何填充





## 命令行参数

main函数一般有两个参数，第一个参数argc，一个argv

**argc用于参数计数，表示运行程序时命令行中参数数目；**

**argv用于参数向量，是一个指向字符串数组的指针，其中每个字符串对应一个参数**

**通常使用多级指针处理这些字符串**



按照c的约定，argv[0]的值是启动该程序的程序名，因此argc的值至少为1，如果argc的值为1，则说明程序名后面没有命令行参数。

```c
echo hello,world;

```



这一行中，argc的值为3，argv[0]、argv[1]、argv[1]的值分别为

argv[0] = echo

argv[1] = hello,

argv[2] = world



第一个可选参数为argv[1],最后一个可选参数为argv[argc-1].



程序echo的第一个版本将argv看成一个字符指针数组



```c
#include <stdio.h>

int main(int argc,char *argv[])	
{
    //默认的默认的argc为1
    int i;	
    for(i=1;i<argc;i++)	//i=1；1不小于1，所以不执行，直接跳出循环	
        				//这个程序中的argv为D
    {
		printf("%s%s",argv[i],(i<argc-1)? " ": " ");        
    }
    printf("\n");
    return 0;
}

```

![](D:\Learn\3Week\C\5\img\4.png)

这样就实现了一个echo，其实这个echo我也没懂，正常的逻辑应该进入程序，不满足条件，只打印一个换行



因为argv是一个指向指针的数组，所以可以通过指针而非数组下标的方式处理命令行参数。



```c
#include <stdio.h>
/* echo command-line arguments; 2nd version */
main(int argc, char *argv[])
{
while (--argc > 0)
printf("%s%s", *++argv, (argc > 1) ? " " : "");
printf("\n");
return 0;
}

```



argv是一个指向参数字符串数组起始的指针，所以自增运算（++argv）将使得它在最开始指向argv[1]而非argv[0]。每一次执行自增运算，就使得argv指向下一个参数，*argv就是指向那个参数的指针。



**printf的格式化参数也可以是表达式**





## 指向函数的指针

在c语言中，函数本身不是变量，但是可以定义指向函数的指针，这种函数的指针可以被赋值、存放在数组中、传递给函数以及作为函数的返回值等等

