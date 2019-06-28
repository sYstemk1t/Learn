#include <stdio.h>
#include <string.h>
int strncpy_cpy(char *s, char *t, int n)
{
	while (*t && n-- > 0)
	{
		*s++ = *t++;
	}
	while (n-- > 0)
	{
		*s++ = '\0';
	}
}


int strnacr_cat(char *s, char *t, int n)

{
	while (*s)
		s++;
	while ((*s++ = *t++) && n-- > 0)
		;
	
}


int strncmp_nmp(char *s, char *t, int n)
{
	for (; *s == *t; s++, t++)
		if (*s == '\0' || --n <= 0)
			return 0;
	return *s - *t;
}

int main()
{
	char c[] = "ares";
	char b[] = "sees";
	char d[] = "cccs";
	strncpy_cpy(c, b, 1);
	strnacr_cat(c, d, 1);
	strncmp_nmp(c, b, 2);
}