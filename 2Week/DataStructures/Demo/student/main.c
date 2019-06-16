#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct student 
{
	unsigned int ID;
	char name[20];
};

struct list
{
	struct student st;
	struct list *next;
};

struct list *create_list()
{
	return calloc(sizeof(struct list), 1);
}

struct list *insert_list(struct list *ls, int n, struct student st)
{
	struct list *p = ls;
	struct list *node = NULL;
	while (p && n--)
	{
		p = p->next;
	}
	if (!p)
		return NULL;
	else
	{
		node = create_list();
		node->st = st;
		node->next = p->next;
		p->next = node;
	}
	return node;
}

void traverse(struct list *ls)
{
	struct list *p = ls;
	while (p)
	{
		printf("id = %d, name = %s\n", p->st.ID, p->st.name);
		p = p->next;
	}
}

void create_num(int array[], int len)//随机生成100个不重复的int，结果放入array数组
{
	int i = 0;
	int j = 0;
	srand((unsigned int)time(NULL));//生成随机数种子
	while (i < len)
	{
		int tmp = rand() % len; //
		for (j = 0; j < i; j++)
		{
			if (tmp == array[j])//如果已经存在相同int，循环退出
				break;
		}
		if (j == i)
		{
			array[i] = tmp;
			i++;
		}
	}
}



int main03()
{
	int array[100];
	create_num(array, sizeof(array) / sizeof(int));//生成0到99，不重复，乱序结果放入array数组

	FILE *p1 = fopen("student.txt", "r");//以只读方式打开student.txt文件
	FILE *p2 = fopen("student.dat", "wb");//以只读方式打开student.dat文件
	int index = 0;
	while (!feof(p1))//遍历student.txt文件
	{
		struct student st = { 0, "" };
		fgets(st.name, sizeof(st.name), p1);//从student。txt文件读一行
		size_t len = strlen(st.name);
		if (st.name[len - 1] == '\n')
		{
			st.name[len - 1] = 0;//把行尾的回车字符吃掉
		}
		st.ID = array[index++];//从数组里面得到一个元素赋给st.ID
		fwrite(&st, sizeof(struct student), 1, p2);
	}
	fclose(p1);
	fclose(p2);
	return 0;
}

int main02()
{
	FILE *p = fopen("student.dat", "rb");
	if (p == NULL)
	{
		return 0;
	}
	struct student st;
	while (fread(&st, sizeof(st), 1, p) > 0)
	{
		printf("ID = %u, name = %s\n", st.ID, st.name);
	}
	fclose(p);
	return 0;
}

void bubble_list(struct list *ls, int n)
{
	for (int i = 0; i < n; i++)
	{
		struct list *p = ls->next;
		for (int j = 0; j < n - i - 1; j++)
		{
			if ((p->st.ID) >(p->next->st.ID))
			{
				struct student st = p->st;
				p->st = p->next->st;
				p->next->st = st;
			}
			p = p->next;
		}
	}
}

int main()//读取student.dat，并将读取结果按照ID从小到大排序
{
	FILE *p = fopen("student.dat", "rb");//打开stduent.dat文件
	if (p == NULL)
	{
		return 0;
	}

	struct list *first = create_list();
	int index = 0;
	while (1)
	{
		struct student st;
		if (fread(&st, sizeof(struct student), 1, p) <= 0)
		{
			break;
		} else
		{
			insert_list(first, 0, st);
		}
		index++;
	}

	bubble_list(first, index);
	traverse(first);
	

	return 0;
}

