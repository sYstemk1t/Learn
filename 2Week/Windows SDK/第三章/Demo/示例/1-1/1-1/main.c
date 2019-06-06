#include <stdio.h>
#include <stdlib.h>

struct list
{
	int data;
	struct list *next;
};

struct list *create_list()
{
	struct list *p = (struct list *)malloc(sizeof(struct list));
	p->data = 0;
	p->next = NULL;
	return p;
}

void tracerse(struct list *ls)
{
	struct list *p = ls;	//�׽ڵ�
	while (p)
	{
		printf("%d\r\n", p->data);	//��ӡ���������
		p = p->next;	//ָ���������һ���ڵ�
	}
}


struct list *insert_list(struct list *ls, int n, int data)  //ls�ǽṹ�壬n�ǵڼ�����data������
{
	struct list *p = ls;
	while (p && n--)
	{
		p = p->next;
	}
	if (!p)
	{
		return NULL;	//����nָ����һ����Ч��λ��;
	}
	else
	{
		struct list *node = create_list();
		node->data = data;
		node->next = p->next;
		p->next = node;
		return node;
	}
}

int delete_list(struct list *ls, int n)
{
	
	struct list *p = ls;
	while (p && --n)
	{
		p = p->next;
	}
	if (!p)	//�ж�n��ָ��
	{
		return 0;
	}
	else
	{
		struct list *node = p->next;
		if (!node)
		{
			return 0;
		}
		p->next = node->next;
		free(node);
		return 1;
	}

}

int main()
{
	struct list *first = create_list();		//����������׽ڵ�
	/*
	struct list *second = create_list();
	second->data = 10;
	struct list *third = create_list();
	third->data = 20;
	first->next = second;	//�������������
	second->next = third;
	
	free(third);
	second->next = NULL;		//���һ���ڵ�
	*/
	int i;
	for (i = 0; i < 10; i++)
	{
		insert_list(first, i, i);
	}
	//insert_list(first, 5, 700);	
	
	delete_list(first, 5);
	tracerse(first);
	//free(second);
	//first->next = third;
	system("pause");
}