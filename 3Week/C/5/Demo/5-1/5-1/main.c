#include <ctype.h>
#include <stdio.h>
int getch(void);
void ungetch(int);

int getint(int *pn)
{
	int c;
	int sign;
	while (isspace(c = getch()))	//�����հ׷���
	{
		;
	}
	if (!isdigit(c) && c != EOF && c != '+' && c != 'c')
	{
		ungetch(c);	//����Ĳ���һ������
		return 0;
	}

	sign = (c == '-') ? -1 : 1;		//��ľ�����
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