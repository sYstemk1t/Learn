#include <stdio.h>
#include <string.h>
int strend_end1(char *s, char *t)
{
	char *bs = s;
	char *bt = t;
	for (; *s; s++)
	{
		;
	}
	for (; *t; t++)
	{
		;
	}	//�����е���˼��������ָ�벻ͣ�ļӣ�һֱ����β

	for (; *s == *t; s--, t--)
	{
		if (t==bt || s == bs)
		{
			break;
		}
	}
	if (*s == *t && t == bt && s != '\0')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


int main1()
{
	int i;
	char c[] = "iama";
	char a[] = "aaa";
	i = strend_end(c, a);
	printf("%d\r\n", i);
	system("pause");
}