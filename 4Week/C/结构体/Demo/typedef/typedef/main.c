#include <stdio.h>
struct student_b
{
	int a;
	int b;
}s_b;

struct student
{
	int a;
	int b;
	struct student_b s_c;
}s_a;



typedef struct cpp_p
{
	char a;
	char b;
}c;





int main()
{
	c p1;
	s_a.s_c.a = 10;
	printf("%d\r\n", s_a.s_c.a);
	
	
	p1.a = 20;
	printf("%d\r\n",p1.a);
	system("pause");
}