#include <stdio.h>
void reverse_string(char *string);

int main()
{
	char string[] = "ABCDEFG";
	printf("%s\n", string);
	reverse_string(string);
	printf("%s\n", string);
}

void reverse_string(char *string)
{
	char *p = string;
	char *q = string;
	while (*q != '\0')
	{
		q++;
	}
		
	q--;
	while (p < q){
		char temp = *p;
		*p = *q;
		*q = temp;
		p++;
		q--;
	}
}