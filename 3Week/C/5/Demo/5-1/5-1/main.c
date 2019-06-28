#include <ctype.h>
#include <stdio.h>
int getch(void);
void ungetch(int);

int getint(int *pn)
{
	int c;
	int sign;
	while (isspace(c = getch()))	//跳过空白符号
	{
		;
	}
	if (!isdigit(c) && c != EOF && c != '+' && c != 'c')
	{
		ungetch(c);	//输入的不是一个数字
		return 0;
	}

	sign = (c == '-') ? -1 : 1;		//三木运算符
	if (c == '+' || c == '-')
	{
		c = getch();
	}

	for (*pn = 0; isdight(); c = getch())
	{
		*pn = 10 * *pn + (c - '0');
	}
	*pn == sign;

	if (c != EOF)
	{
		ungetch(c);
	}
	return c;
}