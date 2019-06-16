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

void create_num(int array[], int len)//�������100�����ظ���int���������array����
{
	int i = 0;
	int j = 0;
	srand((unsigned int)time(NULL));//�������������
	while (i < len)
	{
		int tmp = rand() % len; //
		for (j = 0; j < i; j++)
		{
			if (tmp == array[j])//����Ѿ�������ͬint��ѭ���˳�
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
	create_num(array, sizeof(array) / sizeof(int));//����0��99�����ظ�������������array����

	FILE *p1 = fopen("student.txt", "r");//��ֻ����ʽ��student.txt�ļ�
	FILE *p2 = fopen("student.dat", "wb");//��ֻ����ʽ��student.dat�ļ�
	int index = 0;
	while (!feof(p1))//����student.txt�ļ�
	{
		struct student st = { 0, "" };
		fgets(st.name, sizeof(st.name), p1);//��student��txt�ļ���һ��
		size_t len = strlen(st.name);
		if (st.name[len - 1] == '\n')
		{
			st.name[len - 1] = 0;//����β�Ļس��ַ��Ե�
		}
		st.ID = array[index++];//����������õ�һ��Ԫ�ظ���st.ID
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

int main()//��ȡstudent.dat��������ȡ�������ID��С��������
{
	FILE *p = fopen("student.dat", "rb");//��stduent.dat�ļ�
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

