#include <stdio.h>
char *find_char(char const *source, char const *chars)
{
	
	char *p = source;
	
	if(source == NULL  || chars == NULL)
	{

		return NULL;
	}
	while (*p != '\0')
	{
		*p++;
		if (*p == chars)
		{
			return *p;
		}
	}
	return NULL;
}



int main()
{
	char *p = "abcdbf";
	char *a = 'b';
	char b = 0;
	b = find_char(p, a);
	printf("%c", a);
	system("pause");
}