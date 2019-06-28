/*
* 模仿getint函数的编写方法，
* 编写一个读取浮点数的getfloat函数
*/
#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getfloat函数：读取浮点数给*pf */
int getfloat(float *pf)
{
	int c, sign;
	float   power;

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if ((c == '+' || c == '-') && !isdigit(c = getch())) {
		ungetch((sign == -1) ? '-' : '+');
		ungetch(c);
		return 0;
	}

	for (*pf = 0; isdigit(c); c = getch())
		*pf = *pf * 10 + (c - '0');

	if (c == '.') {
		for (power = 1.0; isdigit(c = getch());) {
			*pf = *pf * 10 + (c - '0');
			power *= 10;
		}
	}
	*pf = *pf / power * sign;
	if (c != EOF)
		ungetch(c);
	return c;
}
/* 该函数在遇到"+-非数字"的情况下会停留在读该字符串而不会继续读取输入流而到达EOF处 */

#define SIZE    10
/* 简单测试getfloat函数 */
int main()
{
	int i;
	float array[SIZE];

	for (i = 0; i < SIZE && getfloat(&array[i]) != EOF; ++i)
		printf("%.2f\n", array[i]);
	return 0;
}