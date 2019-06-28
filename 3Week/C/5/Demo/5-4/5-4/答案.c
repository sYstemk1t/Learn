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
	}	//这两行的意思是让两个指针不停的加，一直到结尾

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