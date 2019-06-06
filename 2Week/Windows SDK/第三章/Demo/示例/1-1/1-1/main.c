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
	struct list *p = ls;	//首节点
	while (p)
	{
		printf("%d\r\n", p->data);	//打印链表的数据
		p = p->next;	//指向链表的下一个节点
	}
}


struct list *insert_list(struct list *ls, int n, int data)  //ls是结构体，n是第几个，data是数据
{
	struct list *p = ls;
	while (p && n--)
	{
		p = p->next;
	}
	if (!p)
	{
		return NULL;	//代表n指向了一个无效的位置;
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
	if (!p)	//判断n的指向
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
	struct list *first = create_list();		//创建链表的首节点
	/*
	struct list *second = create_list();
	second->data = 10;
	struct list *third = create_list();
	third->data = 20;
	first->next = second;	//对链表进行连接
	second->next = third;
	
	free(third);
	second->next = NULL;		//最后一个节点
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