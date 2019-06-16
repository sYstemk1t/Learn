#include <stdio.h>
#include <stdlib.h>

struct list
{
	int data;	//������
	struct list *next;	//ָ����
};

struct single_list{
	struct list* head;
	int count;
};

struct list *create_list()	//����һ���ڵ�
{
	struct list *p = (struct list *)malloc(sizeof(struct list));
	p->data = 0;
	p->next = NULL;
	return p;
}

void traverse(struct list *ls)
{
	struct list *p = ls->next;
	while (p)
	{
		printf("%d\r\n", p->data);
		p = p->next;	//ָ���������һ���ڵ��ָ����
	}
}

void traver(struct list *ls)
{
	struct list *p = ls;
	if (p)
	{
		printf("%d\r\n", p->data);	//����ݹ�
		traver(ls->next);
	}
}

struct list *insert_list(struct list *ls, int n, int data)	//��ָ��λ�ò���Ԫ��
{
	
	struct list *p = ls;
	while (p && n--)	//�ж�pָ���Ƿ�Ϊ��,n--����������100��Ԫ�أ�ÿ���жϵ�ʱ���index�Լ�
	{
		p = p->next;
	}

	if (!p)
	{
		return NULL;	//nָ����һ����Ч��λ��
	}
	else
	{
		struct list *sub = create_list();
		sub->data = data;
		sub->next = p->next;	//�½ڵ��nextָ��Ҫ����ڵ��next
		p->next = sub;	//	��Ҫ����ڵ��nextָ���½ڵ�
		return sub;
	}


}


int delete_list(struct list *ls, int n)	//ɾ��ָ��λ��Ԫ��
{
	struct list *p = ls;
	while (p && n--)
	{
		p = p->next;
	}
	if (!p)
	{
		return 0;	//	nָ���λ����Ч
	}
	else
	{
		struct list *node = p->next;
		if (!node)	
		{
			return 0;
		}
		else
		{
			p->next = node->next;	//ָ����һ��
			free(node);		//�ͷŵ���ǰ��
			return 1;
		}
	}
}



int count_list(struct list *ls)	//�����������
{
	struct list *p = ls->next;
	int count = 0;
	while (p)
	{
		p = p->next;
		count++;
	}
	return count;
}



void clear_list(struct list *ls)	//�������
{
	struct list *p = ls->next;
	while (p)
	{
		struct list *tmp = p->next;	//������ʱ��������p��ֵ����ʱ����
		free(p);
		p = tmp;
	}
	ls->next = NULL;
}
int empty_list(struct list *ls)//���������Ƿ�Ϊ��
{
	if (ls->next)
		return 1;
	else
		return 0;
}

struct list *locale_list(struct list *ls, int n)//��������ָ��λ�õĽڵ�
{
	struct list *p = ls->next;
	while (p && n--)
	{
		p = p->next;
	}
	return p;
}

struct list *elem_locale(struct list *ls, int data)//�������������data�Ľڵ�
{
	struct list *p = ls->next;
	while (p)
	{
		if (p->data == data)
			break;
		p = p->next;
	}
	return p;
}

int elem_pos(struct list *ls, int data)//�������������data�Ľڵ�λ��
{
	struct list *p = ls->next;
	int index = 0;
	while (p)
	{
		if (p->data == data)
			break;
		p = p->next;
		index++;
	}
	return index;
}

struct list *last_list(struct list *ls)//�õ��������һ���ڵ�
{
	struct list *p = ls->next;
	struct list *pre = p;
	while (p)
	{
		pre = p;
		p = p->next;
	}
	return pre;
}
int main()
{
	struct list *first = create_list();	//�׽ڵ㴴��
	/*
	struct list *second = create_list();	//�׽ڵ㴴��
	second->data = 2;
	first->next = second;
	struct list *three = create_list();
	three->data = 10;
	second->next = three;
	three->next = NULL;
	free(three);
	second->next = NULL;
	traverse(first);
	*/
	int i = 0;
	for (i = 0; i < 10; i++)
	{
		insert_list(first,i,i);
	}
	//insert_list(first, 5, 9);
	
	//traverse(first);	//while����
	clear_list(first);
	traver(first);		//�ݹ鷽��
	int c = count_list(first);
	printf("%d\r\n", c);
	system("pause");
}