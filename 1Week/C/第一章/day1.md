title: day1
date: 2019-05-13 18:39:03
categories: categories
tags:
	c

---



<!--more-->

# linux中打印hello

安装ubuntu操作系统，并且安装tools

```c
#include <stdio.h>    //标准的输入输出头文件
int main()			//不接受任何值传递的main函数
{					//c语言的代码都需要写在大的花括号内
	printf("Hello\n");    //调用printf将hello打印到屏幕上
}
```

一个c语言的程序，无论大小，都是由函数和变量名组成的

main函数是一个特殊的函数名，每一个程序都是从main函数的起点开始工作，这也就是每一个c与语言的程序的入门，都是main函数。（如果对c语言了解的很清楚的人，这句话其实是错误的，真证明的启动入口为mainCRTStartup），老版本的vc6可见。

![](/img/0.png)



练习1-1 

```c
#include <stdio.h>
/*正常代码
int main()
{
    printf("hello,world\n");
    getchar();
}
*/

/*输出结果为，语法错误，缺少}*/
int main()
{
    printf("hello world\n);
        getchar();
}
```

练习1-2

```c
#include <stdio.h>
/*当printf输出包含\c,\c的内容为任何的时候*/
int main()
{
    printf("hello wolrd\q");
    getchar();
    /*输出结果就是把q正常输出了*/
}
```

printf函数的一些功能，printf是一个通用的格式化函数

# 变量与算术表达式

使用公式c=(5/9)(F-32)打印花式温度和摄氏度对照表

```c
#include <stdio.h>
int main()
{
	int fahr,celsius;
    int lower,upper,step;
    lower = 0;  //温度的下线
    upper = 300;	//温度的上限
    step = 20;		//步长
    fahr = lower;    //
    while (fahr <= upper)
    {
        celsius = 5 * (fahr-32) / 9;
        printf("%d\t%d\n",fahr,celsius);
        fahr = fahr + step;  //
    }
}
```

这个程序用到了c语言的基础类型，int类型，除了int，c语言还有其他的数据类型

char	字符型1个字节

short	短整型

long	长整形

double	双精度浮点数

float	单精度浮点数

int	整形

c语言的代码执行过程是自上而下的，比如说你把一个变量定义在了下方，但是你在上面使用，是无法使用这个变量，c语言的编译器也会很开心的告诉你，这个变量未定义。

上面的这段代码执行后会有一个比较大的问题，与0摄氏度对应的温度应该为-17.8度，但是输出的结果为17，因为我们使用了%d输出，%d输出的方式会将所有的浮点数全部按照整形来输出，所以我们需要对代码进行改善

```c
#include <stdio.h>
int main()
{
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;  //温度的下线
    upper = 300;	//温度的上限
    step = 20;		//步长
    fahr = lower;    //
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%3.0f\t%f\n", fahr, celsius);
        fahr = fahr + step;  //
    }
    system("pause");
}
```

因为输出的结果无法对齐，所以需要%3.0f这种打印方式，这种打印方式简单的来说，就是打印的时候让3.0去占屏幕的3个字符宽，然后使打印结果统一打印。

练习1-3

```c
/*修改温度转换程序，使之能够在转换表顶部打印一个标题*/
#include <stdio.h>
int main()
{
    printf("\t温度标题\n");
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;  //温度的下线
    upper = 300;	//温度的上限
    step = 20;		//步长
    fahr = lower;    //
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%3.0f\t%f\n", fahr, celsius);
        fahr = fahr + step;  //
    }
    system("pause");
}
```



练习1-4

```c
/*摄氏度温度转换华氏温度*/
#include <stdio.h>
int main()
{
    printf("\t温度标题\n");
    float fahr, celsius;
    float lower, upper, step;
    lower = 0;  //温度的下线
    upper = 300;	//温度的上限
    step = 20;		//步长
    fahr = lower;    //
    while (fahr <= upper)
    {
        celsius = (5.0 / 9.0)*(fahr - 32.0);
        printf("%3.0f\t%f\n", celsius, fahr);
        fahr = fahr + step;  //
    }
    system("pause");
}
```





# 循环语句

c语言中的循环有三种，一种while，一种do...while,一种for

介绍一下三种循环方式，

while的循环，条件写在while后的括号中，条件成立，一直循环

do...while,不管条件成立不成立，都会执行代码

for循环，条件写多少，它就执行多少次

```c
#include <stdio.h>
int main()
{
	int fahr;
    for(fahr = 0;fahr <= 300; fahr = fahr + 20)
    {	
        printf("%3d %6.1f\n",(5.0/9.0)*(fahr-32));
        
    }
    system("pause");
}
```

练习1-5

```c
/*修改温度转换程序，要求逆序排列*/
#include <stdio.h>
int main()
{
    int fahr;
    for (fahr = 300; fahr >=0; fahr = fahr - 20)   //
    {
        printf("%3d %6.1f\n",fahr, (5.0 / 9.0)*(fahr - 32));

    }
    system("pause");
}
```



# 符号常量

在程序中使用一些固定的数指，会给以后的代码带来一些不必要的麻烦，比如说日后需要修改某一处数指，需要修改的地址太多，所以我们使用define

练习1-6(自己给自己加的)

```c
/*修改程序，使其支持可随意修改*/
#include <stdio.h>
#define LOWER 0
#define UPPER 300
#define STEP 20
int main()
{
    int fahr;
    for (fahr = LOWER; fahr <= UPPER; fahr = fahr + STEP)   //
    {
        printf("%3d %6.1f\n", fahr, (5.0 / 9.0)*(fahr - 32));

    }
    system("pause");
}
```



# 字符输入输出

前面既然有了输出，那必然会有输出，比如说一个程序，我们需要他向用户提供结构，让用户来定义当前的温度，然后输出转换的过后的温度

```c
#include <stdio.h>
/*简单例子
int main()
{
    int c;   //定义一个变量
    c = getchar();   //接受一个字符的输入
    putchar(c);     //把这个字符输出到屏幕上
    system("pause");
}
*/

/*读一个字符，然后判断是不是文件结尾，输出字符,读取下一个*/
/*
int main()
{
    int c = NULL;
    while (c != EOF)  //此处EOF为c语言文件操作中的文件结尾
    {
        putchar(c);
        c = getchar();
    }
    system("pause");
}
*/

/*对上面的程序进行优化 */
int main()
{
    int c = NULL;
    while (getchar(c) != EOF)
    {
        putchar(c);
    }
    system("pause");
}
```



练习1-6

```c
/*验证表达式结果getchar*/
/*这个时候不管输入任何值，都是1*/
#include <stdio.h>
int main()
{
    int c = NULL;
    printf("%d", getchar() != EOF);
    system("pause");
}
```

练习1-7

```c
/*编写一个打印EOF值得程序*/
/*参考答案写出来得，因为我理解得EOF就是文件得结尾*/
#include <stdio.h>
int main()
{
    printf("%d\r\n", EOF);
    system("pause");
}
```



在c语言中，一个字符串得结尾是“\0”来结尾得

练习1-8

```c
#include <stdio.h>
/*思路想错了，以为需要ascll码表中得字符来做转换计数*/
/*
int main()
{
    char c = NULL;
    int c1 = NULL;
    while (getchar(c) != EOF)
    {
        if (c == '13')   //13代表ascll码表中得空格
        {
            ++c1;
        }
        printf("一共有%d个空格", c1);
        break;
    }
    system("pause");
}

*/


int main()
{
    int c = NULL;
    int c1 = NULL;
    int c2 = NULL;
    int c3 = NULL;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ')
        {
            ++c1;
        }
        if (c == '\t')
        {
            ++c2;
        }
        if (c == '\n')
        {
            ++c3;
        }
        
    }
    printf("空格个数%d", c1);
    printf("制表符个数%d", c2);
    printf("换行符%d", c3);
}
```





练习1-9

```c
#include <stdio.h>
/*题目没有说明输入得内容是字符串还是整形，按照整形做*/
int main()
{
    int c = NULL;
    int lastc = NULL;
    while (getchar(c) != EOF)
    {
        if (c != ' ')
        {
            putchar(c);
        }
        if (c == ' ')
        {
            if (lastc != ' ')
            {
                putchar(c);
            }
        }
    }
}
```





练习1-10

```c
#include <stdio.h>
int main()
{
    int c = NULL;
    int i = NULL;;
    int g = NULL;
    while (getchar(c) != EOF)
    {
        if (c == '\t')
        {
            printf("\\t");
        }
        if (c == "\b")
        {
            printf("\\");
        }
        if (c == '\b')
        {
            if (c != '\t')
            {
                putchar(c);
            }
        }
    }
    system("pause");
}
```

单词计数，比如要统计，有多少个单词

```c
#include <stdio.h>
#define IN 1
#define OUT 0
int main()
{
    int c;
    int n1;
    int nw;
    int nc;
    int state;
    state = OUT;
    n1 = nw = nc = 0;   //这条语句得意思是把这三个变量全部赋值为0
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
        {
            ++n1;
        }
        if (c == ' ' || c == '\n' || c == '\t')   //条件判断语句
        {
            state = OUT;
        }
        else if (state = OUT)    //符合条件判断语句
        {
            state = IN;
            ++nw;
        }
    }
    printf("%d\t%d\t%d\t\n", n1, nw, nc);
    system("pause");
}
```



# 或且非

&&与

参与运算的两个表达式都为真时，结果才为真，否则为假。

|| 或

参与运算的两个表达式只要有一个为真，结果就为真；两个表达式都为假时结果才为假

！ 非

参与运算的表达式为真时，结果为假；参与运算的表达式为假时，结果为真



练习1-11

```c
#include <stdio.h>
#define IN 1
#define OUT 0
int main()
{
    int c;
    int n1;
    int nw;
    int nc;
    int state;
    state = OUT;
    n1 = nw = nc = 0;   //这条语句得意思就是把这三个变量全部赋值为0 
    while ((c = getchar()) != EOF)
    {
        ++nc;
        if (c == '\n')
        {
            ++n1;
        }
        if (c == ' ' || c == '\n' || c == '\t')   //条件判断语句
        {
            state = OUT;
        }
        else if (state = OUT)    //符合条件判断语句
        {
            state = IN;
            ++nw;
        }
    }
    printf("%d\t%d\t%d\t\n", n1, nw, nc);
    system("pause");
}
```



练习1-12

```c
#include <stdio.h>
/*编写一个程序，以每行一个单词打印输出*/
int main()
{
    char c = NULL;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            putchar(c);
            printf("\n");
        }
    }
    system("pause");
}

```



# 数组

数组就是同一种数据类型得集合，连续排列，数组下标可以是任何整形表达式。

## 多路判定

在程序中经常使用这样得判定

if(条件1)

{

​	语句1

}

else if(条件2)

{

​	语句2

}

.....

练习1-13

```c
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int nc, ns, nw, i, m, n;                                    /*定义字符个数，单词结束判断条件，单词个数，循环变量*/
    int max;                                                    /*定义最长单词的字符数*/
    int p[50];                                                  /*定义单词长度数组*/
    char a[50][50];                                             /*定义单词字符数组*/
    char c;                                                     /*定义输入字符*/
    max = 0;                                                    /*最长单词字符数初始为0*/
    i = 1;                                                      /*单词长度数组下标初始值为1*/
    ns = nc = nw = 0;                                           /*单词判断初始条件，字符个数初始值，单词个数初始值都为0*/
    m = n = 1;                                                  /*单词数组下标初始值为1*/
    while ((c = getchar()) != EOF){                             /*当输入字符不是文件结束符*/
        if ((c >= 'A'&&c <= 'Z') || (c >= 'a'&&c <= 'z')){  /*当输入字符是字母时*/
            ++nc;                                               /*字符个数增加1个*/
            a[m][n] = '*';                                      /*单词数组赋值为星号*/
            ++n;                                                /*本单词数组的二元下标增加1位*/
            ns = 1;                                             /*单词判断为单词内*/
        }
        else if (ns == 1){                                      /*如果输入字符不是字母并且单词判断条件是在单词内*/
            ++nw;                                               /*单词个数增加1位*/
            ++m;                                                /*单词数组一元下标增加1位*/
            p[i] = nc;                                          /*字符个数赋值给单词长度数组*/
            if (nc >= max)                                      /*如果字符个数大于目前单词长度最大值*/
                max = nc;                                       /*当前字符个数赋值给单词长度最大值*/
            ++i;                                                /*单词长度数组下标增加1位*/
            n = 1;                                              /*单词数组二元下标回到初始值*/
            ns = nc = 0;                                        /*单词判断条件和字符个数回到初始值*/
        }
    }
    for (n = max; n >= 1; --n){                                   /*以下循环体是打印单词的垂直直方图，如果单词数组没有赋值星号，则打印空格*/
        for (m = 1; m <= nw; ++m){
            if (a[m][n] == '*'){
                printf("%c  ", a[m][n]);
            }
            else
                printf("   ");
        }
        printf("\n");
    }
    for (i = 1; i <= nw; ++i)                                     /*以下循环体是打印单词个数*/
        printf("%d  ", p[i]);
    printf("\n");
    system("pause");
    return 0;
}

```



练习1-14

```c
#include <stdio.h>
#define MAXHIST 15
#define MAXWORD 11
#define IN 1
#define OUT 0
int main()
{
    int c, i, j, nc, state;
    int len;
    int maxvalue;
    int ovflow;
    int wl[MAXWORD];
    state = OUT;
    nc = 0;
    ovflow = 0;
    for (i = 0; i < MAXWORD; ++i)
        wl[i] = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == ' ' || c == '\n' || c == '\t')
        {
            state = OUT;
            if (nc > 0)
                if (nc < MAXWORD)
                    ++wl[nc];
                else
                    ++ovflow;
            nc = 0;
        }
        else if (state == OUT)
        {
            state = IN;
            nc = 1;
        }
        else
            ++nc;
    }
    maxvalue = 0;
    for (i = 1; i < MAXWORD; ++i)
        if (wl[i] > maxvalue)
            maxvalue = wl[i];
#if 0
    for (i = 1; i < MAXWORD; ++i)
    {
        printf("%5d - %5d :", i, wl[i]);
        if (wl[i] > 0)
        {
            if ((len = wl[i] * MAXHIST / maxvalue) <= 0)
                len = 1;
        }
        else
            len = 0;
        while (len > 0)
        {
            putchar("*");
            --len;
        }
        putchar('\n');
    }
#else
    for (i = MAXWORD; i > 0; --i)
    {
        for (j = 1; j < MAXWORD; ++j)
            if (wl[j] * MAXWORD / maxvalue >= i)
                printf("  *  ");
            else
                printf("     ");
        putchar('\n');
    }
    for (i = 1; i < MAXWORD; ++i)
        printf("%4d ", i);
    putchar('\n');
    for (i = 1; i < MAXWORD; ++i)
        printf("%4d ", wl[i]);
    putchar('\n');
#endif
    if (ovflow > 0)
        printf("%d words >= %d\n", ovflow, MAXWORD);
    return 0;

}
```





