/*Ä£·Âstrendº¯Êý*/
#include <stdio.h>
#include <string.h>
int strend_end(char *s, char *t)
{
	int i = 0;
	while (s[i] != '\0')
	{
		i++;
		while (t[i] == '\0')
		{
			for (int j = 0; j < sizeof(s); j++)
			{
				if (s[i] == t[i])
				{
					i--;
					if (i == 0)
					{
						return 1;
					}
					else
					{
						continue;
					}
					
				}
				else
				{
					return 0;
				}
			}
		}
	}
	
}
int main()
{
	int i;
	char c[] = "iama";
	char a[] = "aaa";
	i = strend_end1(c, a);
	printf("%d\r\n", i);
	system("pause");
}