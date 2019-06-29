#include <stdio.h>
#include <ctype.h>
#include <string.h>
/*第一个不懂的实例*/
int main1()
{
	int i = 10;
	int *p = NULL;
	p = i;	//如果加取地址符号，那么打印的结果就是i的地址
	printf("%d\r\n", p);
	system("pause");
	return 0;
}
//5.2第一个例子
void swap(int *a, int *b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
	
}

int main2()
{
	int i = 10;
	int j = 20;
	swap(&i, &j);	//指针传递的时候，变量名前面需要加取地址符号
	printf("%d\r\n", i);
	printf("%d\r\n", j);
	system("pause");
	return 0;
}



int main3()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int *p;
	p = a[0];
	
	for (int i = 0; i < 10; i++)
	{
		printf("%d\r\n", p[i]);
	}
	system("pause");
	return 0;
}

int strlen_alen(char *s)
{
	int n;
	for (n = 0; *s != '\0'; s++)	//s++代表指向字符串的下一个
	{
		n++;	//n是计数器，满足条件，n就+一次
	}
	return n;
}
int main4()
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



#define AllocSize 1000

static char allocbuf[AllocSize];

static char *allop = allocbuf;

char *alloc(int n)
{
	if (allocbuf + AllocSize - allop >= 0)	//检查是否有足够的空间
	{
		allop += n;
		return allop - n;
	}

	else
	{
		return 0;
	}

}


void afree(char *p)
{
	if (p >= allocbuf && p < allocbuf + AllocSize)
	{
		allop = p;
	}
}




int strlen_len(char *s)
{
	char *p = s;
	int i = 0;	//检查计数器
	while (*p != '\0')
	{
		i++;
		p++;
	}
	return i;

}

int main5()
{
	int i;
	i = strlen_len("hello");
	printf("%d\r\n", i);
	system("pause");
	return 0;
}

int main6()
{
	printf("Hello wolrd");
	system("pause");
}



void strcpy_cpy(char *s, char *t)
{
	int i = 0;
	while ((*s = *t) != '\0')
	{
		s++;
		t++;
	}
}

int main7()
{
	char a[20];
	char c[] = "i am teacher!";
	strcpy_cpy(a, c);
	printf("%s\r\n", c);
	printf("%s\r\n", a);
	system("pause");
}



int strcmp_cmp1(char *t, char *s)
{
	int i = 0;
	while (s[i] == t[i] != '\0')
	{
		i++;
		if (t[i] == '\0')	//检查到最后一位
		{
			return 0;
		}
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


int main8()
{
	
	char a[] = "iamstudent";
	char c[] = "iamstudent";
	//char c[] = "iamteacher!";
	int i;
	i = strcmp_cmp(a, c);
	printf("%d\r\n", i);

	system("pause");
	return 0;


}


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


int main10()
{

	char a[] = "iamstudent";
	char c[] = "iama";
	int i;
	i = strcmp_cmp(a, c);
	printf("%d\r\n", i);
	system("pause");
}


int main11()
{
	unsigned int g = -256;
	int a = 123, b = -1;
	float c = 3.14;
	int *d = &a;
	float *e = &c;

	printf("%d\r\n", a);
	printf("%d\r\n", b);
	printf("%f\r\n", c);
	printf("%d\r\n", *d);
	printf("%f\r\n", *e);
	printf("%d\r\n", g);
	system("pause");
	return 0;
}


int main12()
{
	char ch =  'a';

	char *cp = &ch;
	
	char *cd = NULL;
	

	printf("%p\r\n", &ch);
	printf("%c\r\n", ch);
	printf("%p\r\n", cp);
	printf("%p\r\n", &cp);
	printf("%c\r\n", *cp);
	printf("%p\r\n", cp);
	
	cd = *cp + 1;
	printf("%p\r\n", &ch);
	printf("%c\r\n", cd);
	cd = *++cp;
	printf("%p\r\n", &cd);
	

	cd = *(cp + 1);
	printf("%c\r\n", cd);
	return 0;
	
	

}


int strlen_len_len(char *s)
{
	int i = 0;
	char *p = s;
	while (*p++ || *p != '\0')
	{
		i++;
	}
	return i;
}

int main13()
{
	char *s = "hello";
	int i;
	i = strlen_len_len(s);
	printf("%d\r\n", i);
}

#define TRUE 1
#define FALSE 0
char find(char *s,char name)
{
	char *p = s;
	while (*p++ != '\0')
	{
		if (*p == name)
		{
			return *p;
		}

	}
	return 0;
}

int main14()
{
	char c = 0;
	char *s = "iamstudent";
	char a = 'u';
	c = find(s, a);
	printf("%c\r\n", c);
}



int main15()
{
	float values[5];
	float *p;
	for (p = &values[0]; p < &values[5];)
	{
		*p++ = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		printf("%f\r\n", values[i]);
	}
}


int main16()
{
	float values[5];
	float *p;
	for (p = &values[5]; p > &values[0];)
	{
		*--p = 0;
	}

	for (int i = 0; i < 5; i++)
	{
		printf("%f\r\n", values[i]);
	}
}

int main17()
{
	float values[5];
	float *p;
	for (p = &values[5 - 1]; p >= &values[0];p--)
	{
		p = 0;
	}


	for (int i = 0; i < 5; i++)
	{
		printf("%f\r\n", values[i]);
	}

}

int main18()
{
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int *c;
	c = &a[0];
	printf("%d\r\n", *c);
	*c = *(b + 3);	//这句的意思是：取b这个数据，下标3的内容
	printf("%d\r\n", *c);


}

int strcpy_acpy(char *buf, char *str)
{
	while ((*buf++ = *str++) != '\0' )
	{
		if (*buf == '\0')
		{
			return 0;
		}
	}
}
int main19()
{
	char a[10] = "hello";
	char b[5] = "world";
	strcpy_acpy(a, b);
	printf("%s", a);
}

int main20()
{
	int array[3][4] = { { 1,2,3 }, { 4,5,6 }, {7,8,9} };
	
	system("pause");
}


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