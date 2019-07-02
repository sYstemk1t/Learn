# 结构体

## 基础知识

结构体类型可以同时存储超过一个的单独数据，c语言提供了两种类型的聚合数据类型，数组和结构

数组：只可以保存同类型的数据，它的每个元素是通过下标引用或引用间接访问

结构体：可以是多种数据类型，并且每个数据元素长度可以不同



### 结构体声明

```c
struct student
{
    int a;
    float b;
    double c;
    char d;
    char *f;
}
int main()
{
    struct student st1;
    printf("%d\r\n",sizeof(st1));
    system("pause");
}

```

首先我们应该知道这个结构体有多大，看编译器的对齐方式，在vc6中的对齐方式是4字节对齐。

上述结构体的大小是：

int	4

float	4

double 	8

char 	4

char	4

结果是24，如果不详细，可以自己写一些，然后用sizeof来量



```c
#include <stdio.h>
struct student
{
	int a;
	float b;
	double c;
	char d;
	char *f;
} st1[20], *z;


int main()
{
	st1[0].a = 10;
	st1[0].b = 3.14;
	st1[0].c = 3.11111111;
	st1[0].d = 'a';
	st1[0].f = 'f';
	printf("%d\r\n", st1[0].a);
	printf("%f\r\n", st1[0].b);
	printf("%lf\r\n", st1[0].c);
	printf("%c\r\n", st1[0].d);
	printf("%c\r\n", st1[0].f);
	system("pause");
}

```

上面的写法的意思是：它包含了20个结构，z是指针，指向这个结构





## 结构成员

```c
#include <stdio.h>
struct sleep
{
	int a;
	double b;
};
struct student
{
	int a;
	float b;
	double c;
	char d;
	char *f;
	struct sleep *s;
	struct simple *sp;
};


int main()
{
	struct student st1;
	st1.s.a = 8;
	printf("%d\r\n", st1.s.a);
	system("pause");
}

```



通过这个例子，我们可以知道，结构体中是可以嵌套结构体的，使用.的方式，来对它进行赋值或者使用





## 间接访问

```c
#include <stdio.h>
struct sleep
{
	int a;
	double b;
	char *p;
};
struct student
{
	int a;
	float b;
	double c;
	char d;
	char *f;
	struct sleep *s;
	struct simple *sp;
};

void func(struct student *cp)
{
	cp->f = 'a';
	printf("%c\r\n", cp->f);
}

int main()
{
	struct student *st1;
	st1 = malloc(sizeof(st1));
	func(st1);
	st1->a = 10;
	printf("%d\r\n", st1->a);
	system("pause");
}

```



这里有一个算是比较坑的地方，如果是要使用结构体指针的话，那么必须使用malloc去开辟内存空间，不然使用就报错。



**如果要使用箭头操作符，左操作数必须是一个指针结构的指针**





## 结构体自引用

```c
#include <stdio.h>
struct self_erf1
{
    int a;
    struct self_erf1 b;
    int c;
}

```

**注意这样的写法是错误的，因为成员b是另一个完整的结构，自身包含自身，有点像递归了**

```c
#include <stdio.h>
struct self_erf1
{
    int a;
    struct self_erf1 *b;
    int c;
}

```

**这样就合法了**

合法的愿意是在于b是一个指针而不是结构





## 不完整的声明

```c
#include <stdio.h>
struct B
{
	int qa;
	struct A	*b_b;
};
struct A
{
	int qb;
	struct B	*a_a;
};

int main()
{
	struct A *a;
	struct B *b;
	
	b = malloc(sizeof(b));
	b->b_b->qb = 10;
	printf("%d\r\n", b->b_b->qb);
	system("pause");
}

```



//这里有问题





## 结构体初始化

```c
#include <stdio.h>
struct student
{
	int age;
	char *name;
} st1[2] = {
	{11,"张三"},
	{12,"李四"}
};


int main()
{
	printf("%s : %d %s : %d\r\n", st1[0].name, st1[0].age, st1[1].name, st1[1].age);
	system("pause");
}


```



如果中间对结构体进行多次赋值的话，赋值的时候，需要加花括号，以逗号分隔





## 结构、指针和成员

```c
#include <stdio.h>

typedef struct
{
	int a;
	short b[2];
}ex2;
typedef struct ex
{
	int a;
	char b[3];
	ex2 c;
	struct ex *d;
}ex;

int main()
{
	ex x = { 10, "Hi", { 5, { -1, 25 } }, 0 };
	ex *px = &x;
	px->a = 10;
}

```

px是一个指针变量，此处访问无需任何间接访问操作符。





## 访问结构

**指针变量指向结构体，那么通过指针可以访问一个指定成员**



## 访问结构成员

定义指针变量 struct 结构体名 *指针名



指针名 = &结构体







## 访问嵌套的结构

```c
#include <stdio.h>

typedef struct
{
	int a;
	short b[2];
}ex2;
typedef struct ex
{
	int a;
	char b[3];
	ex2 c;
	struct ex *d;
}ex;

int main()
{
	ex x = { 10, "Hi", { 5, { -1, 25 } }, 0 };
	ex *px = &x;
	*px->c.b;
}


```



*px -> c.b

这个访问结果就是访问的是ex2这个结构体中的b

![](D:\Learn\4Week\C\C与指针\img\1.png)



## 访问指针成员

```c
#include <stdio.h>

typedef struct
{
	int a;
	short b[2];
}ex2;
typedef struct ex
{
	int a;
	char b[3];
	ex2 c;
	struct ex *d;
}ex;

int main()
{
	ex x = { 10, "Hi", { 5, { -1, 25 } }, 0 };
	ex *px = &x;
	ex y;
	x.d = &y;
}

```

这个时候的x.d就包含了整个ex这个结构体

![](D:\Learn\4Week\C\C与指针\img\2.png)

## 结构体在内存中的分配



```c
#include <stdio.h>
struct student
{
	int a;
	char *c;
	double d;
};


int main()
{
	struct student st1;
	st1.a = 10;
	st1.c = 'a';
	st1.d = 3.14;

	getchar();
}

```









![](D:\Learn\4Week\C\C与指针\img\3.png)



这样就印证了我们开始说的，因为我用的编译器是vs，它默认是4字节对齐方式





## 作为函数传递结构

```c
#include <stdio.h>
struct student
{
	int a;
	char *name;
};


void func(struct student *cp)
{
	cp->a = 20;
	cp->name = "zhang";
}


int main()
{
	struct student *p;
	p = malloc(sizeof(p));
	func(p);
	printf("name is %s,age is %d ", p->name, p->a);
	system("pause");
}

```





## 位段

不同长度的字段实际上存储于一个或多个整形变量中

**用signed或unsigned证书显式地声明位段**

signed是有符号数，ubsigned是无符号数





## 联合体

**简单理解为，一荣俱荣一损俱损**

```c
#include <stdio.h>

union student{
	int a;
	float c;
};
int main()
{
	union student st1;
	st1.a = 10;
	printf("%d\r\n",st1.a);
	printf("%d\r\n",st1.c );
	system("pause");
}

```

联合体的大小计算中，取最大的那个类型

