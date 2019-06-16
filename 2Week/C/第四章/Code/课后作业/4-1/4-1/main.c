#include <stdio.h>
#include <string.h>
int strindex(char s[], char t[])
{
	int i = 0, j = 0, pos;
	int slen = strlen(s);
	int tlen = strlen(t);

	while (i < slen && j < tlen)
	{
		if (s[i] == t[j])
		{
			pos = i;
			while (i+1 < slen && j+1 < tlen)
			{
				if (s[++i] != t[++j])
				{
					j = 0;
					i = pos + 1;
					break;
				}
			}
			if (j == tlen - 1)
				return pos;
		}
		else
		{
			++i;
		}
	}
	/*
	while (s[i] != 0)
	{
		if (s[i] == t[j])
		{
			pos = i;
			++i;
			++j;
			while (t[j] != 0 && s[i] == t[j])
			{
				++i;
				++j;
			}
			if (j == strlen(t))
				return pos;
			else
			{
				i = pos + 1;
				j = 0;
			}
		}
		else
		{
			++i;
		}
	}
	*/
	
	return -1;
}


int main()
{
	char s[80];
	char t[80];
	//adminiaminiser
	//minis
	//KMP, Boyer Morre
	printf("input the string s:");
	scanf("%s", s);
	printf("input the string t:");
	scanf("%s", t);
	printf("%d\n", strindex(s, t));
	system("pause");
	return 0;
}