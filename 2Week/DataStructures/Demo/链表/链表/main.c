#include <stdio.h>
#include <stdlib.h>

struct list
{
	int data;	//数据域
	struct list *next;	//指针域
};

struct single_list{
	struct list* head;
	int count;
};

struct list *create_list()	//建立一个节点
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
		p = p->next;	//指向链表的下一个节点的指针域
	}
}

void traver(struct list *ls)
{
	struct list *p = ls;
	if (p)
	{
		printf("%d\r\n", p->data);	//先序递归
		traver(ls->next);
	}
}

struct list *insert_list(struct list *ls, int n, int data)	//在指定位置插入元素
{
	
	struct list *p = ls;
	while (p && n--)	//判断p指针是否为空,n--假如链表有100个元素，每次判断的时候对index自减
	{
		p = p->next;
	}

	if (!p)
	{
		return NULL;	//n指向了一个无效的位置
	}
	else
	{
		struct list *sub = create_list();
		sub->data = data;
		sub->next = p->next;	//新节点的next指向要插入节点的next
		p->next = sub;	//	把要插入节点的next指向新节点
		return sub;
	}


}


int delete_list(struct list *ls, int n)	//删除指定位置元素
{
	struct list *p = ls;
	while (p && n--)
	{
		p = p->next;
	}
	if (!p)
	{
		return 0;	//	n指向的位置无效
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
			p->next = node->next;	//指向下一个
			free(node);		//释放掉当前的
			return 1;
		}
	}
}



int count_list(struct list *ls)	//返回链表个数
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



void clear_list(struct list *ls)	//清空链表
{
	struct list *p = ls->next;
	while (p)
	{
		struct list *tmp = p->next;	//定义临时变量，把p赋值给临时变量
		free(p);
		p = tmp;
	}
	ls->next = NULL;
}
int empty_list(struct list *ls)//返回链表是否为空
{
	if (ls->next)
		return 1;
	else
		return 0;
}

struct list *locale_list(struct list *ls, int n)//返回链表指定位置的节点
{
	struct list *p = ls->next;
	while (p && n--)
	{
		p = p->next;
	}
	return p;
}

struct list *elem_locale(struct list *ls, int data)//返回数据域等于data的节点
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

int elem_pos(struct list *ls, int data)//返回数据域等于data的节点位置
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

struct list *last_list(struct list *ls)//得到链表最后一个节点
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
	struct list *first = create_list();	//首节点创建
	/*
	struct list *second = create_list();	//首节点创建
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
	
	//traverse(first);	//while方法
	clear_list(first);
	traver(first);		//递归方法
	int c = count_list(first);
	printf("%d\r\n", c);
	system("pause");
}