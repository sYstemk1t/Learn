/*
* ģ��getint�����ı�д������
* ��дһ����ȡ��������getfloat����
*/
#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

/* getfloat��������ȡ��������*pf */
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
/* �ú���������"+-������"������»�ͣ���ڶ����ַ��������������ȡ������������EOF�� */

#define SIZE    10
/* �򵥲���getfloat���� */
int main()
{
	int i;
	float array[SIZE];

	for (i = 0; i < SIZE && getfloat(&array[i]) != EOF; ++i)
		printf("%.2f\n", array[i]);
	return 0;
}