#include <stdio.h>
#include <string.h>

int strcat_cat(char *s, char *t)
{
	int i = 0;
	int j = 0;
	while (s[i] != '\0')
	{
		i++;
		while (s[i] == '\0')
		{
			for (int k = 0; k < sizeof(t); k++)
			{
				s[i] = t[k];	//������˵�����ݽ����Ĳ�����һ�����飬����ָ��5��Ӧ�ÿ�ʼ��world������������飬����ûЧ��...

				i++;
			}
		}
	}
}

int main()
{
	char c[]= "hello";
	char d[] = "world";
	strcat_cat(c, d);
}