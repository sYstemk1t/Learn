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
				s[i] = t[k];	//正常来说，传递进来的参数是一个数组，这里指向5，应该开始把world填充进入这个数组，但是没效果...

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