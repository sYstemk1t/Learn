#include <stdio.h>
#define NKEYS 10000
struct student
{
	int age;
	char *name;
}keytab[] = {
	18, "张三",
	19, "李四",
	20, "王麻子",
	21, "张瑞"
};

struct student1
{
	int age;
	char *name;

}stu1;

int main1()
{
	stu1.age = 18;
	printf("%d\r\n", stu1.age);
	printf("%s\r\n", keytab[1].name);

	system("pause");
}


int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

int main()
{

}