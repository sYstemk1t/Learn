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


struct list
{
	struct student st;
	struct list *next;
};

struct list *create_list()//����һ���ڵ�
{
	return calloc(sizeof(struct list), 1);
}

void traverse(struct list *ls)//ѭ����������
{
	struct list *p = ls;
	while (p)
	{
		printf("ID = %d, name = %s\n", p->st.ID, p->st.name);//��ӡ���������������
		p = p->next;//ָ���������һ���ڵ�node
	}
}

struct list *insert_list(struct list *ls, int n, struct student st)//��ָ��λ�ò���Ԫ��
{
	struct list *p = ls;
	while (p && n--)
	{
		p = p->next;
	}
	if (!p)
		return NULL;//nָ����һ����Ч��λ��
	else
	{
		struct list *node = create_list();
		node->st = st;
		node->next = p->next;
		p->next = node;
		return node;
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

int main00()//��ȡstudent.dat��������ȡ�������ID��С��������
{
	FILE *p = fopen("student.dat", "rb");//��stduent��dat�ļ�
	if (p == NULL)
	{
		return 0;
	}

	struct student st[100] = { 0 };
	int index = 0;
	while (fread(&st[index++], sizeof(struct student), 1, p) > 0);//ѭ�����֮��ͨ��index��ֵ��֪���ļ������ж��ٸ���¼

	for (int i = 0; i < index - 1; i++)//ͨ��ð�����򽫶�ȡ���ļ�¼ID��С��������
	{
		for (int j = 1; j < index - i - 1; j++)
		{

			if (st[j].ID < st[j - 1].ID)
			{
				struct student tmp = st[j];
				st[j] = st[j - 1];
				st[j - 1] = tmp;
			}
		}
	}


	for (int i = 0; i < index - 1; i++)//��student�������ݴ�ӡ����Ļ
	{
		printf("id = %d, name= %s\n", st[i].ID, st[i].name);
	}

	return 0;
}

void sort_list(struct list *ls, int n)
{
	
	for (int i = 0; i < n; i++)
	{
		struct list *p = ls;
		for (int j = 0; j < n - i - 1; j++)
		{
			if ((p->st.ID) >(p->next->st.ID))
			{
				struct student tmp = p->st;
				p->st = p->next->st;
				p->next->st = tmp;
			}
			p = p->next;
		}
	}
}


int main()//��ȡstudent.dat��������ȡ�������ID��С��������
{
	FILE *p = fopen("student.dat", "rb");//��stduent��dat�ļ�
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
			break;
		insert_list(first, 0, st);
		index++;
	}//ѭ�����֮��ͨ��index��ֵ��֪���ļ������ж��ٸ���¼

	sort_list(first, index + 1);

	traverse(first);


	return 0;
}