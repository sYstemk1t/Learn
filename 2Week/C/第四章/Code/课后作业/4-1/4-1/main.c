#include <stdio.h>
#include <string.h>
int strindex(char s[], char t[])
{
	int i, j, k, index;
	i = j = k = index = 0;
	while (s[i] != '\0')   //判断结尾，字符串结尾为\0
	{
		while (t[j] != '\0')
		{
			if (s[i] == t[j])
			{
				++k;
				if (k == 1)	//记录第一次相等字符的下标
				{
					index = j;
					break;
				}
				else
				{
					k = 0;
					++j;
				}
				
			}
			++i;
		}
		
	}
	if (k == strlen(t))
	{
		return index;
	}
	else
	{
		return -1;
	}
}


int main()
{
	char s[80];
	char t[80];
	printf("input the string s:");
	scanf("%s", s);
	printf("input the string t:");
	scanf("%s", t);
	printf("%d\n", strindex(s, t));
	system("pause");
	return 0;
}