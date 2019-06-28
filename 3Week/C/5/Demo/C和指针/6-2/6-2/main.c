#include <stdio.h>
int del_substr(char *str, char const *substr)
{
	char *p = str;
	char *ps = NULL;
	char *s = NULL;
	if (str != NULL)
	{
		if (substr == NULL)
		{
			return 1;
		}
		while (*p != '\0')
		{
			s = substr;
			ps = p;
			while (*s != '\0')
			{
				if (*s++ != *ps++)
				{
					break;
				}
			}
			if (*s == '\0')
			{
				while (*p++ = *ps++)
				{
					;
				}
				return 1;
				
			}
			p++;
		}
	}
	return 0;
}
int main()
{
	char *p = "iamaenudent";
	char *q = 'en';
	del_substr(p, q);
}